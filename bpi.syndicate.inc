<?php

/**
 * @file
 * Syndication logic here.
 */

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
  drupal_add_library('system', 'drupal.ajax');

  $search_phrase = _bpi_current_search_phrase();

  $form['bpi_actions'] = array(
    '#type' => 'item',
    '#markup' => implode('', array(
      l(t('Settings'), 'admin/config/bpi'),
      l(t('Statistics'), 'admin/bpi/statistics/nojs', array('attributes' => array('class' => array('use-ajax')))),
    )),
    '#prefix' => '<div class="bpi-admin-actions">',
    '#suffix' => '</div>',
  );

  $form['bpi_search_query'] = array(
    '#type' => 'textfield',
    '#default_value' =>$search_phrase,
  );

  $form['bpi_search_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Search'),
  );

  $form['bpi_search_filters'] = array(
    '#type' => 'item',
    '#markup' => bpi_build_filters(),
  );

  $sort_direction = bpi_get_next_sorting();
  $sort_text = ($sort_direction == SORT_DESCENDING) ?  t('Show latest on top') : t('Show oldest on top');
  $sort_url_components = _bpi_build_query('sort', $sort_direction);
  $form['bpi_search_sort'] = array(
    '#type' => 'item',
    '#markup' => l($sort_text, 'admin/bpi', array('query' => $sort_url_components)),
  );

  $items = bpi_search_get_items();
  $markup = bpi_search_get_markup($items);
  $form['bpi_search_results'] = array(
    '#type' => 'item',
    '#markup' => $markup,
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

  $form['#attached']['css'][] = drupal_get_path('module', 'bpi') . '/css/bpi-pages.styles.css';
  $form['#submit'][] = 'bpi_syndicate_page_form_submit';

  return $form;
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
  $query = $form_state['values']['bpi_search_query'];
  $query_parameters = array();

  if (!empty($query)) {
    $query_parameters = array(
      'query' => array(
        SEARCH_PHRASE_KEY => $query
      )
    );
  }
  else {
    drupal_set_message(t('Enter some keywords.'), 'error');
  }

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
 */
function bpi_search_content($query = '', $page = 1, $filters = array(), $sort = 'desc') {
  $endpoint = variable_get('bpi_service_url', '');
  $agency_id = variable_get('bpi_agency_id', '');
  $api_key = variable_get('bpi_api_key', '');
  $secret_key = variable_get('bpi_secret_key', '');

  try {
    $bpi = new Bpi($endpoint, $agency_id, $api_key, $secret_key);
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
    watchdog(
      'bpi',
      t('Failed to fetch content from BPI well with message %message'),
      array('%message' => $e->getMessage()),
      WATCHDOG_ERROR
    );
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
 */
function bpi_search_get_items() {
  $params = _bpi_build_query();
  $phrase = isset($params[SEARCH_PHRASE_KEY]) ? $params[SEARCH_PHRASE_KEY] : '';
  $page = pager_find_page();
  $sort = isset($_GET['sort']) ? $_GET['sort'] : SORT_DESCENDING;
  $filters = array(
    'category' => isset($params['category']) ? $params['category'] : '',
    'audience' => isset($params['audience']) ? $params['audience'] : '',
    'agency_id' => isset($params['agency']) ? $params['agency'] : '',
    'author' => isset($params['author']) ? $params['author'] : '',
  );

  $response = bpi_search_content($phrase, $page, $filters, $sort);
  $bpi_nodes = array();

  foreach ($response as $item) {
    $current_item = $item->getProperties();
    $bpi_nodes[] = array(
      'bpi_id' => isset($current_item['id']) ? $current_item['id'] : '',
      'title' =>  isset($current_item['title']) ? $current_item['title'] : '',
      'date' =>  isset($current_item['pushed']) ? $current_item['pushed'] : '',
      'teaser' =>  isset($current_item['teaser']) ? $current_item['teaser'] : '',
      'body' =>  isset($current_item['body']) ? $current_item['body'] : '',
      'author' =>  isset($current_item['author']) ? $current_item['author'] : '',
      'category' =>  isset($current_item['category']) ? $current_item['category'] : '',
      'agency' =>  isset($current_item['agency_id']) ? $current_item['agency_id'] : '',
      'audience' =>  isset($current_item['audience']) ? $current_item['audience'] : '',
      'total_count' => isset($response->total) ? $response->total : 0,
    );
  }

  return $bpi_nodes;
}

/**
 * Creates markup from found content during search.
 *
 * @return string
 *   HTML markup.
 *
 * @ingroup themable
 */
function bpi_search_get_markup($items) {
  $data = array();

  // Iterate through items and theme them.
  if (is_array($items)) {
    foreach ($items as $item) {
      $dt = new DateTime();
      $item['date'] = format_date($dt->setTimestamp($item['date'])), 'Y-m-d H:i:s');
      $data[] = theme('bpi_well_item', array('item' => $item));
    }
  }

  return implode('', $data);
}

/**
 * Create key/value pairs from the query string.
 *
 * This is a helper function for drupal core l() function.
 * Munges the query string into key/value pairs array, so it is accepted by the l() function.
 * Ex. admin/bpi?key1=value1&key2=value2
 *
 * @param string $key
 *   Parameter key.
 * @param string $value
 *   Parameter value.
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

      // Certain keys we don't want to be in resulting array.
      if ($ignore == $temp[0]) {
        continue;
      }

      // It's required to decode some values here, since Drupal's url() encodes it
      // weird, munging the 'space' entity value (%20).
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
  return isset($_GET[SEARCH_PHRASE_KEY]) ? check_plain($_GET[SEARCH_PHRASE_KEY]) : '';
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
    SEARCH_PHRASE_KEY,
    'author',
    'category',
    'agency',
    'audience',
  );
}

/**
 * Createa filters markup, based on current query string.
 *
 * @return string
 *   HTMl markup.
 *
 * @ingroup themable
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

    $item['name'] = $key;
    $item['value'] = $value;
    $item['search_value'] = $value;
    $item['search_stripped_filter'] = _bpi_build_query('', '', $key);

    $filters_markup[] = theme('bpi_filter_item', array('filter' => $item));
  }

  return implode('', $filters_markup);
}

/**
 * Maps BPI keys to translatables.
 *
 * @param string $key
 *   Label identifier.
 * @return string
 *   Translatable human-readable label value.
 *
 */
function bpi_label_mapper($key) {
  $map = bpi_available_map();

  return isset($map[$key]) ? $map[$key] : '';
}

/**
 * BPI related translatables definition.
 *
 * @return array
 *   An array of transaltables in structure:
 *   - bpi_key: translatable
 */
function bpi_available_map() {
  return array(
    SEARCH_PHRASE_KEY => t('Query'),
    'author' => t('Author'),
    'category' => t('Category'),
    'agency' => t('Agency'),
    'audience' => t('Audience'),
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

  return ($sort_dir == SORT_ASCENDING) ? SORT_DESCENDING : SORT_ASCENDING;
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
    $_SESSION['bpi']['syndicate_id'] = $bpi_id;
    drupal_goto(str_replace('_', '-', 'node/add/' . $bpi_ctype), array('query' => array('from' => 'bpi')));
  }
  else {
    drupal_goto('admin/bpi');
  }
}
