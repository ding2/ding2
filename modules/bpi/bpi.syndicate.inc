<?php
/**
 * @file
 * Syndication logic here.
 */

/**
 * Cache ID for agency_id => agency_name mapping.
 */
define('BPI_AGENCY_CACHE', 'bpi_agency_cache');

/**
 * Define syndication page markup.
 *
 * This includes search form, filtering and found content.
 *
 * @return array
 *   Form structure.
 *
 * @ingroup forms
 */
function bpi_syndicate_page_form($form, &$form_state) {
  // Check configuration have been,
  if (bpi_service_is_configured()) {
    drupal_add_library('system', 'drupal.ajax');

    $search_phrase = _bpi_current_search_phrase();

    $form['bpi_search_query'] = array(
      '#type' => 'textfield',
      '#default_value' => $search_phrase,
    );

    $form['bpi_search_submit'] = array(
      '#type' => 'submit',
      '#value' => t('Search'),
    );

    $form['bpi_search_filters'] = array(
      '#type' => 'item',
      '#markup' => bpi_build_filters(),
    );

    $items = bpi_search_get_items();
    if (!empty($items)) {
      $sort_direction = bpi_get_next_sorting();
      $sort_text = ($sort_direction == BPI_SORT_DESCENDING) ? t('Show latest on top') : t('Show oldest on top');
      $sort_url_components = _bpi_build_query('sort', $sort_direction);
      $form['bpi_search_sort'] = array(
        '#type' => 'item',
        '#markup' => l($sort_text, 'admin/bpi', array('query' => $sort_url_components)),
      );
    }

    $form['bpi_search_results'] = array(
      '#type' => 'item',
      '#markup' => theme('bpi_search_results', array(
        'items' => $items,
        'empty' => t('No results'),
      )),
    );

    pager_default_initialize(
      isset($items[0]['total_count']) ? $items[0]['total_count'] : 0,
      variable_get('bpi_content_per_page', BPI_CONTENT_PER_PAGE)
    );

    $pager = theme('pager');

    $form['bpi_search_pager'] = array(
      '#type' => 'item',
      '#markup' => $pager,
    );

    $form['#attached']['css'][] = drupal_get_path('module', 'bpi') . '/css/bpi-admin.styles.css';
    $form['#submit'][] = 'bpi_syndicate_page_form_submit';
  }

  return $form;
}

/**
 * Syndication page form validator.
 */
function bpi_syndicate_page_form_validate($form, &$form_state) {
  if (empty($form_state['values']['bpi_search_query'])) {
    form_set_error('bpi_search_query', t('Enter some keywords.'));
  }
}

/**
 * Custom submit handler for syndication page form.
 *
 * @see bpi_syndicate_page_form()
 *
 * @param array $form
 *   Form structure.
 * @param array $form_state
 *   Form state values.
 *
 * @ingroup forms
 */
function bpi_syndicate_page_form_submit($form, &$form_state) {
  $query_parameters = array(
    'query' => array(
      BPI_SEARCH_PHRASE_KEY => $form_state['values']['bpi_search_query'],
    ),
  );

  // Redirect to search results.
  drupal_goto('admin/bpi', $query_parameters);
}

/**
 * Perform a search within the BPI well.
 *
 * @param string $query
 *   Query string.
 * @param int $page
 *   Page offset.
 * @param array $filters
 *   Array of filters/sorting.
 * @param string $sort
 *   Sorting order.
 *
 * @return \Bpi\Sdk\NodeList|array
 *   Search result items.
 */
function bpi_search_content($query = '', $page = 1, $filters = array(), $sort = 'desc') {
  try {
    $bpi = bpi_client_instance();
    $amount = variable_get('bpi_content_per_page', BPI_CONTENT_PER_PAGE);
    $offset = $page * $amount;

    $bpi_data = $bpi->searchNodes(
      array(
        'amount' => $amount,
        'offset' => $offset,
        'filter' => $filters,
        'sort' => array(
          'pushed' => $sort,
        ),
        'search' => $query,
      )
    );

    if ($bpi_data->count() > 0) {
      return $bpi_data;
    }
  }
  catch (Exception $e) {
    watchdog_exception('bpi', $e);
    drupal_set_message(t('Failed to fetch data. Check reports for more information.'), 'error');
  }

  return array();
}

/**
 * Parses the BPI search result into more simpler structures.
 *
 * @return array
 *   Array of bpi fetched items, in structure:
 *   - bpi_id: bpi identifier
 *   - title: item title
 *   - date: item creation date in the BPI system
 *   - teaser: content teaser
 *   - body: content body
 *   - author: content author
 *   - category: content category
 *   - agency: content agency
 *   - audience: content audience
 *   - total_count: overall amount of items in the result
 *   - assets: array of links representing the images content
 */
function bpi_search_get_items() {
  $params = _bpi_build_query();
  $phrase = isset($params[BPI_SEARCH_PHRASE_KEY]) ? $params[BPI_SEARCH_PHRASE_KEY] : '';
  $page = pager_find_page();
  $sort = isset($_GET['sort']) ? $_GET['sort'] : BPI_SORT_DESCENDING;
  $filters = array(
    'category' => isset($params['category']) ? $params['category'] : '',
    'audience' => isset($params['audience']) ? $params['audience'] : '',
    'agency_id' => isset($params['agency']) ? $params['agency'] : '',
    'author' => isset($params['author']) ? $params['author'] : '',
  );

  $response = bpi_search_content($phrase, $page, $filters, $sort);
  $bpi_nodes = array();

  // Get agency_id=>agency cache.
  $agency_cache = array();
  $cache = cache_get(BPI_AGENCY_CACHE);
  if ($cache) {
    $agency_cache = $cache->data;
  }

  foreach ($response as $item) {
    /* @var $item \Bpi\Sdk\Item\Node */
    $current_item = $item->getProperties();
    $assets = $item->getAssets();

    $agency = isset($current_item['agency_name']) ? $current_item['agency_name'] : '';
    $agency_id = isset($current_item['agency_id']) ? $current_item['agency_id'] : '';

    // Set agency into cache.
    if (!empty($agency) && empty($agency_cache[$agency_id])) {
      $agency_cache[$agency_id] = $agency;
    }

    // Transform \Bpi\Sdk\Document properties items into array.
    $bpi_nodes[] = array(
      'bpi_id' => isset($current_item['id']) ? $current_item['id'] : '',
      'title' => isset($current_item['title']) ? $current_item['title'] : '',
      'date' => isset($current_item['pushed']) ? $current_item['pushed'] : '',
      'teaser' => isset($current_item['teaser']) ? $current_item['teaser'] : '',
      'body' => isset($current_item['body']) ? $current_item['body'] : '',
      'author' => isset($current_item['author']) ? $current_item['author'] : '',
      'category' => isset($current_item['category']) ? $current_item['category'] : '',
      'agency' => $agency,
      'agency_id' => $agency_id,
      'audience' => isset($current_item['audience']) ? $current_item['audience'] : '',
      'total_count' => isset($response->total) ? $response->total : 0,
      'assets' => (count($assets) > 0) ? $assets : array(),
      'editable' => !empty($current_item['editable']),
    );
  }

  // Save changes in agency cache.
  if (empty($cache) || (!empty($cache) && $agency_cache != $cache->data)) {
    cache_set(BPI_AGENCY_CACHE, $agency_cache);
  }

  return $bpi_nodes;
}

/**
 * Implements theme_HOOK().
 */
function theme_bpi_search_results($variables) {
  return theme('table', $variables);
}

/**
 * Implements hook_preprocess_HOOK().
 */
function bpi_preprocess_bpi_search_results(&$variables) {
  $items = $variables['items'];

  $table_head = array(
    array(
      'data' => t('Title'),
      'class' => 'bpi-title',
    ),
    t('Date'),
    array(
      'data' => t('Details'),
      'class' => 'bpi-details',
    ),
    t('Photo'),
    t('Editable'),
    t('Actions'),
  );

  // Set table defaults.
  $variables['header'] = $table_head;
  $variables['sticky'] = TRUE;
  $variables['rows'] = array();

  // If no data, do not process anything.
  if (empty($items)) {
    return;
  }

  $rows = array();
  foreach ($items as $i => $item) {
    $rows[$i]['title'] = sprintf(
      '<b>%s</b><br />%s',
      $item['title'],
      $item['teaser']
    );

    $rows[$i]['date'] = date_format(new DateTime($item['date']), 'Y-m-d H:i:s');

    // Add details.
    $rows[$i]['details'] = '';
    // Map link text => data.
    $details = array(
      'category' => 'category',
      'author' => 'author',
      'agency' => 'agency_id',
      'audience' => 'audience',
    );
    foreach ($details as $text => $data) {
      $rows[$i]['details'] .= sprintf(
        '%s %s<br/>',
        bpi_label_mapper($data),
        l(
          $item[$text],
          'admin/bpi',
          array('query' => _bpi_build_query($text, $item[$data], 'page'))
        )
      );
    }

    // Add photos icon as css class.
    $class = count($item['assets']) > 0 ? 'photos' : 'no-photos';
    $rows[$i]['photo'] = array('data' => '', 'class' => "bpi-photo $class");

    // Add editable icon as css class.
    $class = $item['editable'] ? 'editable' : 'not-editable';
    $rows[$i]['editable'] = array('data' => '', 'class' => "bpi-photo $class");

    // Add action links.
    $actions = array(
      l(t('Preview'),
        'admin/bpi/preview/nojs/' . $item['bpi_id'],
        array('attributes' => array('class' => 'use-ajax'))
      ),
      l(t('Syndicate'),
        'admin/bpi/syndicate/' . $item['bpi_id']
      ),
    );
    $rows[$i]['actions'] = implode(' ', $actions);
  }

  // Unset old data.
  unset($variables['items']);

  // Set table data.
  $variables['rows'] = $rows;
}

/**
 * Create key/value pairs from the query string.
 *
 * This is a helper function for drupal core l() function.
 * Munges the query string into key/value pairs array, so it is accepted
 * by the l() function.
 * Ex. admin/bpi?key1=value1&key2=value2
 *
 * @param string $key
 *   Parameter key.
 * @param string $value
 *   Parameter value.
 * @param string $ignore
 *   Key to be ignored. Used in removing filters.
 *
 * @return array
 *   An array, in structure:
 *   - key: value
 */
function _bpi_build_query($key = '', $value = '', $ignore = NULL) {
  $destination = drupal_get_destination();
  $current_path = parse_url(reset($destination));
  $query = isset($current_path['query']) ? $current_path['query'] : '';

  $new_query_pairs = array();

  if (!empty($query)) {
    // Get the parameters array.
    $components = explode('&', $query);

    // Iterate and rearrange them.
    foreach ($components as $component) {
      $temp = explode('=', $component);

      // Ignore a key from query string.
      if ($temp[0] == $ignore) {
        continue;
      }

      // It's required to decode some values here, since Drupal's url()
      // encodes it weird, munging the 'space' entity value (%20).
      $new_query_pairs[$temp[0]] = urldecode($temp[1]);
    }
  }

  // Append the new key/value pair to existing ones.
  if (!empty($key) && !empty($value) && $key != $ignore) {
    $new_query_pairs[$key] = $value;
  }

  return $new_query_pairs;
}

/**
 * Used to retrieve the searched phrase after submit is clicked.
 *
 * @see bpi_syndicate_page_form()
 *
 * @return string
 *   Searched string.
 */
function _bpi_current_search_phrase() {
  return isset($_GET[BPI_SEARCH_PHRASE_KEY]) ? check_plain($_GET[BPI_SEARCH_PHRASE_KEY]) : '';
}

/**
 * List of filters that are available.
 *
 * Basically that's limited to what is to be showed in filtering section.
 *
 * @return array
 *   Array of filter identifiers.
 */
function bpi_available_filters() {
  return array(
    BPI_SEARCH_PHRASE_KEY,
    'author',
    'category',
    'agency',
    'audience',
  );
}

/**
 * Creates filters markup, based on current query string.
 *
 * @return string
 *   HTMl markup.
 *
 * @ingroup themeable
 */
function bpi_build_filters() {
  $components = _bpi_build_query();
  $filters_markup = array();
  $enabled_filters = bpi_available_filters();

  foreach ($components as $key => $value) {
    // Limit the filtering options.
    if (!in_array($key, $enabled_filters)) {
      continue;
    }

    // Used in link.
    $value_text = $value;

    // Get agency name from cache.
    if ($key == 'agency') {
      $cache = cache_get(BPI_AGENCY_CACHE);
      if ($cache && isset($cache->data[$value])) {
        $value_text = $cache->data[$value];
      }
    }

    $item['name'] = $key;
    $item['label'] = bpi_label_mapper($key);
    $item['value'] = $value;
    $item['search_value'] = $value;
    $item['search_stripped_filter'] = _bpi_build_query('', '', $key);

    $item['link'] = l($value_text, 'admin/bpi', array('query' => array($key => $value)));
    $item['remove'] = l(
      theme_image(
        array(
          'path' => drupal_get_path('module', 'bpi') . '/images/cross.png',
          'width' => 16,
          'height' => 16,
          'alt' => '',
          'attributes' => array(),
        )
      ),
      'admin/bpi',
      array(
        'query' => $item['search_stripped_filter'],
        'html' => TRUE,
        'attributes' => array(
          'class' => array('bpi-filter-remove-cross'),
        ),
      )
    );

    $filters_markup[] = theme('bpi_filter_item', array('filter' => $item));
  }

  return implode('', $filters_markup);
}

/**
 * Maps BPI keys to translatable.
 *
 * @param string $key
 *   Label identifier.
 *
 * @return string
 *   Translatable human-readable label value.
 */
function bpi_label_mapper($key) {
  $map = bpi_available_map();

  return isset($map[$key]) ? $map[$key] : '';
}

/**
 * BPI related translatable definition.
 *
 * @return array
 *   An array of translatable in structure:
 *   - bpi_key: translatable
 */
function bpi_available_map() {
  return array(
    BPI_SEARCH_PHRASE_KEY => t('Query'),
    'author' => t('Author'),
    'category' => t('Category'),
    'agency' => t('Agency'),
    'audience' => t('Audience'),
    'material' => t('Related materials'),
  );
}

/**
 * Get the next sorting order.
 *
 * Just reverse the direction. End.
 *
 * @return string
 *   Direction sorting identifier.
 */
function bpi_get_next_sorting() {
  $sort_dir = isset($_GET['sort']) ? $_GET['sort'] : '';

  return ($sort_dir == BPI_SORT_ASCENDING) ? BPI_SORT_DESCENDING : BPI_SORT_ASCENDING;
}

/**
 * Prepares data before the actual syndication occurs.
 *
 * Creates a session entry, storing the BPI content, which is lately
 * inserted into an empty corresponding node form.
 *
 * @param int $bpi_id
 *   Content ID, as as stored in BPI service.
 */
function bpi_syndicate_action($bpi_id) {
  $bpi_ctype = variable_get('bpi_content_type', '');

  if (!empty($bpi_ctype)) {
    drupal_goto(str_replace('_', '-', 'node/add/' . $bpi_ctype), array('query' => array('bpi_id' => $bpi_id)));
  }
  else {
    drupal_goto('admin/bpi');
  }
}
