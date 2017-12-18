<?php
/**
 * @file
 * Syndication logic here.
 */

require_once __DIR__ . '/bpi.channel.inc';

/**
 * Cache ID for agency_id => agency_name mapping.
 */
define('BPI_AGENCY_CACHE', 'bpi_agency_cache');

/**
 * Query string parameter name for sorting.
 *
 * Must not be 'sort' as this conflicts with Drupal's built in sort query
 * parameter.
 */
define('BPI_QUERY_SORT_NAME', 'sorting');

/**
 * Default page size for paging.
 */
define('BPI_DEFAULT_PAGE_SIZE', 10);

/**
 * Key for storing data in session.
 */
define('BPI_ALL_FACETS_KEY', 'BPI_ALL_FACETS');

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
  // Check BPI configuration has been set.
  if (bpi_service_is_configured()) {
    bpi_check_bpi_user();

    drupal_add_library('system', 'drupal.ajax');

    $query_form = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array(
          'bpi-query',
        ),
      ),
    );

    $query_form['bpi_search'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('bpi-search'),
      ),
    );

    $query_form['bpi_search']['bpi_search_query'] = array(
      '#type' => 'textfield',
      '#default_value' => _bpi_get_current_search_phrase(),
      '#description' => t('Search in body, teaser, title and category'),
    );

    $query_form['bpi_search']['bpi_search_actions'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array(
          drupal_html_class('container-inline'),
        ),
      ),
    );

    $query_form['bpi_search']['bpi_search_actions']['bpi_search_submit'] = array(
      '#type' => 'submit',
      '#value' => t('Search'),
    );

    if (_bpi_get_current_search_phrase()) {
      $query_form['bpi_search']['bpi_search_actions']['bpi_search_reset'] = array(
        '#type' => 'item',
        '#markup' => l(t('Reset search'), current_path(), array(
          'query' => NULL,
          'attributes' => array(
            'class' => array('button'),
          ),
        )),
      );
    }

    // Must be called before building facets ui.
    $items = bpi_search_get_items();

    bpi_build_search_facets($query_form);

    bpi_build_subscriptions($query_form);

    $total_items = isset($items[0]['total_count']) ? $items[0]['total_count'] : 0;
    $page_size = _bpi_get_query_parameter('amount', BPI_DEFAULT_PAGE_SIZE);
    pager_default_initialize($total_items, $page_size);

    $result_form = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array(
          'bpi-result',
        ),
      ),
    );

    if (!empty($items)) {
      $result_form['bpi_search_info'] = array(
        '#type' => 'container',
        '#attributes' => array(
          'class' => array('bpi-search-info', 'container-inline'),
        ),
      );

      $current_page = pager_find_page();
      $items_from = $current_page * $page_size + 1;
      $items_to = min(($current_page + 1) * $page_size, $total_items);

      $result_form['bpi_search_info']['bpi_search_paging_info'] = array(
        '#type' => 'item',
        '#markup' => ($items_from < $items_to
                      ? t('Showing items @from–@to of @total', array(
                        '@from' => $items_from,
                        '@to' => $items_to,
                        '@total' => $total_items,
                      ))
                      : t('Showing item @from of @total', array(
                        '@from' => $items_from,
                        '@total' => $total_items,
                      ))),
      );

      $result_form['bpi_search_info']['bpi_search_amount'] = array(
        '#type' => 'select',
        '#title' => t('Page size'),
        '#options' => drupal_map_assoc(array(10, 20, 50, 100)),
        '#default_value' => _bpi_get_query_parameter('amount', BPI_DEFAULT_PAGE_SIZE),
        '#attributes' => array(
          'onchange' => 'form.submit()',
        ),
      );
    }
    else {
      $result_form['bpi_search_amount'] = array(
        '#type' => 'hidden',
      );
    }

    $result_form['bpi_search_results'] = array(
      '#type' => 'item',
      '#markup' => theme('bpi_search_results', array(
        'items' => $items,
        'empty' => t('No results'),
        'actions_callback' => bpi_get_user() ? 'bpi_syndicate_subscribe_to_channel_action_callback' : NULL,
      )),
    );

    $result_form['bpi_search_pager'] = array(
      '#type' => 'item',
      '#markup' => theme('pager'),
    );

    $query_form['loading'] = array(
      '#type' => 'item',
      '#markup' => '<div class="loading"><div class="message">' . t('Please wait') . '</div></div>',
    );

    $form['bpi_query'] = $query_form;
    $form['bpi_result'] = $result_form;

    $form['#attributes']['class'][] = 'bpi';
    $form['#attached']['css'][] = drupal_get_path('module', 'bpi') . '/css/bpi-admin.styles.css';
    $form['#attached']['js'][] = drupal_get_path('module', 'bpi') . '/js/bpi-admin.js';
    $form['#submit'][] = 'bpi_syndicate_page_form_submit';
  }

  return $form;
}

/**
 * Add additional actions to channel node list.
 *
 * @param array $actions
 *   The list of actions.
 * @param array $item
 *   The current item list.
 * @param array $variables
 *   The variables sent in the list function.
 */
function bpi_syndicate_subscribe_to_channel_action_callback(array &$actions, array $item, array &$variables) {
  $actions[] = l(t('Add node to channel'), 'admin/bpi/channel/node/add/' . $item['bpi_id']);
}

/**
 * Custom submit handler for syndication page form.
 *
 * @param array $form
 *   Form structure.
 * @param array $form_state
 *   Form state values.
 *
 * @see bpi_syndicate_page_form()
 *
 * @ingroup forms
 */
function bpi_syndicate_page_form_submit(array $form, array &$form_state) {
  $bpi_query = array();
  $sorting = _bpi_get_current_sorting();
  if (!empty($sorting)) {
    $bpi_query[BPI_QUERY_SORT_NAME] = $sorting;
  }
  $values = $form_state['values'];

  if (isset($values['bpi_search_amount']) && intval($values['bpi_search_amount']) > 0) {
    $bpi_query['amount'] = intval($values['bpi_search_amount']);
  }

  if (isset($values['bpi_search_query']) && trim($values['bpi_search_query'])) {
    $bpi_query[BPI_SEARCH_PHRASE_KEY] = trim($values['bpi_search_query']);
  }

  if (isset($values['bpi_facets'])) {
    foreach ($values['bpi_facets'] as $key => $value) {
      $selected_values = is_array($value) ? array_keys(array_filter($value)) : $value;
      if (!empty($selected_values)) {
        if (!isset($bpi_query['filter'])) {
          $bpi_query['filter'] = array();
        }
        $bpi_query['filter'][$key] = $selected_values;
      }
    }
  }

  // Redirect to search results.
  drupal_goto('admin/bpi', array('query' => _bpi_build_query($bpi_query, TRUE)));
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
 * @param array $sort
 *   Sorting order.
 *
 * @return \Bpi\Sdk\NodeList|array
 *   Search result items.
 */
function bpi_search_content($query = '', $page = 1, $filters = array(), $sort = array()) {
  try {
    $bpi = bpi_client_instance();
    $amount = max(intval(_bpi_get_query_parameter('amount')), BPI_DEFAULT_PAGE_SIZE);
    $offset = $page * $amount;

    $bpi_data = $bpi->searchNodes(
      array(
        'amount' => $amount,
        'offset' => $offset,
        'filter' => $filters,
        'sort' => $sort ? $sort : array(),
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
 * @return array|null
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
  if ($_SERVER['REQUEST_METHOD'] != 'GET') {
    return NULL;
  }

  $page = pager_find_page();
  $phrase = _bpi_get_current_search_phrase();
  $filters = _bpi_get_current_filter();
  $sort = _bpi_get_current_sorting();

  $response = bpi_search_content($phrase, $page, $filters, $sort);

  // Get agency_id=>agency cache.
  $agency_cache = array();
  $cache = cache_get(BPI_AGENCY_CACHE);
  if ($cache) {
    $agency_cache = $cache->data;
  }

  $bpi_nodes = bpi_nodelist_to_array($response, $agency_cache);

  // Save changes in agency cache.
  if (empty($cache) || (!empty($cache) && $agency_cache != $cache->data)) {
    cache_set(BPI_AGENCY_CACHE, $agency_cache);
  }

  return $bpi_nodes;
}

/**
 * Convert a BPI nodelist into more simple array structure.
 *
 * @param \Bpi\Sdk\NodeList $node_list
 *   The node list.
 *
 * @return array|null
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
function bpi_nodelist_to_array($node_list, array &$agency_cache = NULL) {
  $bpi_nodes = array();

  foreach ($node_list as $item) {
    $current_item = $item->getProperties();
    $assets = $item->getAssets();

    if ($agency_cache !== NULL) {
      $agency = isset($current_item['agency_name']) ? $current_item['agency_name'] : '';
      $agency_id = isset($current_item['agency_id']) ? $current_item['agency_id'] : '';

      // Set agency into cache.
      if (!empty($agency) && empty($agency_cache[$agency_id])) {
        $agency_cache[$agency_id] = $agency;
      }
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
      'total_count' => isset($node_list->total) ? $node_list->total : 0,
      'assets' => (count($assets) > 0) ? $assets : array(),
      'editable' => !empty($current_item['editable']),
      'syndications' => isset($current_item['syndications']) ? $current_item['syndications'] : NULL,
    );
  }

  return $bpi_nodes;
}

/**
 * Implements theme_HOOK().
 *
 * @param array $variables
 *   Theme variables.
 *
 * @return string
 *   An HTML string representing the themed output.
 */
function theme_bpi_search_results(array $variables) {
  return theme('table', $variables);
}

/**
 * Implements hook_preprocess_HOOK().
 */
function bpi_preprocess_bpi_search_results(array &$variables) {
  $items = $variables['items'];

  $table_head = array(
    array(
      'data' => bpi_get_sort_link(t('Title'), 'title'),
      'class' => array('bpi-title', _bpi_get_current_sorting('title') ? 'active' : ''),
    ),
    array(
      'data' => bpi_get_sort_link(t('Date'), 'pushed', 'desc'),
      'class' => array('bpi-pushed', _bpi_get_current_sorting('pushed') ? 'active' : ''),
    ),
    array(
      'data' => bpi_get_sort_link(t('Syndications'), 'syndications', 'desc'),
    ),
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

    $rows[$i]['date'] = format_date((new DateTime($item['date']))->getTimestamp(), 'short');
    $rows[$i]['syndications'] = $item['syndications'];

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
          array('query' => _bpi_get_filter_query($data, $item[$data]))
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
 * Get link for sorting by a field.
 *
 * @param string $text
 *   The text on the link.
 * @param string $field
 *   The field to sort by.
 * @param string $default_direction
 *   The sorting direction to use if not currently sorting of this field.
 *
 * @return string
 *   The link for sorting.
 */
function bpi_get_sort_link($text, $field, $default_direction = 'asc') {
  $current_sorting = _bpi_get_current_sorting($field);
  if (!empty($current_sorting)) {
    $sort_direction = $current_sorting == 'asc' ? 'desc' : 'asc';
  }
  else {
    $sort_direction = $default_direction;
  }
  $query = _bpi_build_query(array(
    BPI_QUERY_SORT_NAME => array(
      $field => $sort_direction,
    ),
  ), array(BPI_QUERY_SORT_NAME));
  $image = $current_sorting ? theme('tablesort_indicator', array('style' => $sort_direction)) : '';
  return l($text . $image, current_path(), array('query' => $query, 'html' => TRUE));
}

/**
 * Get current sorting or direction.
 *
 * @param string $field
 *   Field to get sorting direction for.
 *
 * @return string|array
 *   The current sorting (field => direction) or the direction for a specified
 *   field.
 */
function _bpi_get_current_sorting($field = NULL) {
  $sorting = _bpi_get_query_parameter(BPI_QUERY_SORT_NAME);
  if (!empty($field)) {
    return isset($sorting[$field]) ? $sorting[$field] : NULL;
  }
  return $sorting;
}

/**
 * Get current search.
 *
 * @return array
 *   The search.
 */
function _bpi_get_current_search_query() {
  $text = _bpi_get_query_parameter('text', NULL);
  $amount = _bpi_get_query_parameter('amount');
  $query = array();
  if (!empty($text)) {
    $query['text'] = $text;
  }
  if (!empty($amount)) {
    $query['amount'] = $amount;
  }
  return $query;
}

/**
 * Get current filter.
 *
 * @return array
 *   The filter.
 */
function _bpi_get_current_filter() {
  $value = _bpi_get_query_parameter('filter', array());
  // @TODO: Make sure that only valid filter parameters are present.
  // Rename key "agency_internal" to "agencyInternal" to match webservice
  // parameter.
  if (isset($value['agency_internal'])) {
    $value['agencyInternal'] = $value['agency_internal'];
    unset($value['agency_internal']);
  }
  return $value;
}

/**
 * Decide if a filter is currently applied.
 *
 * @return bool
 *   Whether a filter is applied or not.
 */
function _bpi_is_filter_applied() {
  $filter = _bpi_get_current_filter();
  // Filter is applied if something apart from logicalOperator is set.
  unset($filter['logicalOperator']);
  return !empty($filter);
}

/**
 * Get query for applying a filter.
 *
 * @param string $field
 *   The field to filter on.
 * @param string $value
 *   The value match.
 *
 * @return array
 *   The filter query.
 */
function _bpi_get_filter_query($field, $value, $clear = TRUE) {
  $query = array(
    'filter' => array(
      $field => array($value),
    ),
  );
  return _bpi_build_query($query, $clear ? array('filter') : FALSE);
}

/**
 * Merge a bpi query into the current query string.
 *
 * @param array $query
 *   The new query.
 * @param bool|array $clear
 *   Clear all or some parameters.
 *
 * @return array
 *   The merged query.
 */
function _bpi_build_query(array $query, $clear = FALSE) {
  $current_query = ($clear === TRUE) ? array() : _bpi_get_query_parameter();
  if (is_array($clear)) {
    foreach ($clear as $name) {
      unset($current_query[$name]);
    }
  }

  $bpi_query = array_replace_recursive($current_query, $query);
  return $bpi_query;
}

/**
 * Get bpi query parameter value from query string.
 *
 * @param string|array $path
 *   The parameter name or a list of names for multidimensional values.
 * @param mixed $default_value
 *   The default value.
 *
 * @return mixed
 *   The query parameter value or the default value if not found.
 */
function _bpi_get_query_parameter($path = NULL, $default_value = NULL) {
  $data = drupal_get_query_parameters();
  if (!empty($path) && !is_array($path)) {
    $path = array($path);
  }
  if (!empty($path)) {
    foreach ($path as $step) {
      if (!isset($data[$step])) {
        return $default_value;
      }
      $data = $data[$step];
    }
  }
  return $data;
}

/**
 * Used to retrieve the searched phrase after submit is clicked.
 *
 * @see bpi_syndicate_page_form()
 *
 * @return string|null
 *   Searched string.
 */
function _bpi_get_current_search_phrase() {
  return _bpi_get_query_parameter(BPI_SEARCH_PHRASE_KEY);
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
    'channels' => t('Channels'),
    'agency' => t('Agency'),
    'audience' => t('Audience'),
    'material' => t('Related materials'),
    'tags' => t('Tags'),
    'agency_id' => t('Agency'),
    'agency_internal' => t('Agency internal'),
    'logicalOperator' => t('Logical operator'),
  );
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

/**
 * Build facets form fields.
 *
 * @param array $form
 *   The form.
 */
function bpi_build_search_facets(array &$form) {
  $facets = bpi_get_facets();

  if (!empty($facets)) {
    $filter_form = array(
      '#type' => 'fieldset',
      '#title' => t('Filters'),
      '#collapsible' => TRUE,
      '#collapsed' => !_bpi_is_filter_applied(),
      '#attributes' => array(
        'class' => array(
          'bpi-filters',
        ),
      ),
    );

    $facets_form = array(
      '#type' => 'container',
      '#tree' => TRUE,
      '#attributes' => array(
        'class' => array(
          'bpi-facets',
        ),
      ),
    );

    // Use chosen to render select controls?
    $library = libraries_detect('chosen');
    $use_chosen = !empty($library['installed']);

    if ($use_chosen) {
      foreach ($library['files']['css'] as $file => $v) {
        $form['#attached']['css'][] = $library['library path'] . '/' . $file;
      }
      foreach ($library['files']['js'] as $file => $v) {
        $form['#attached']['js'][] = $library['library path'] . '/' . $file;
      }
    }

    foreach ($facets as $name => $terms) {
      $id = $name;
      $type = $use_chosen ? 'select' : 'checkboxes';
      $multiple = TRUE;
      $options = array();
      foreach ($terms as $term => $item) {
        $options[$term] = $item['title'];
      }
      $default_value = _bpi_get_query_parameter(array('filter', $name), array());

      if ($name == 'agency_internal') {
        $options = array(
          '' => t('All'),
        );
        if (isset($terms[0])) {
          $options['false'] = t('External sources');
        }
        if (isset($terms[1])) {
          $options['true'] = t('Libraries');
        }
        $default_value = _bpi_get_query_parameter(array('filter', $name));
        $multiple = FALSE;
        $type = 'select';
      }

      $facets_form[$id] = array(
        '#type' => $type,
        '#multiple' => $multiple,
        '#chosen' => $multiple && $use_chosen,
        '#size' => $multiple ? min(20, count($options)) : NULL,
        '#title' => bpi_label_mapper($name) ? bpi_label_mapper($name) : $name,
        '#options' => $options,
        '#default_value' => $default_value,
        '#attributes' => array(
          'data-placeholder' => $multiple ? t('Pick some values') : t('Pick a value'),
          'data-no-matches' => t('Nothing matches'),
        ),
        '#prefix' => '<div class="bpi-facet bpi-facet-' . drupal_html_class($name) . '">',
        '#suffix' => '</div>',
      );
    }

    // Add logical operator.
    $name = 'logicalOperator';
    $id = $name;
    $facets_form[$id] = array(
      '#type' => 'select',
      '#title' => bpi_label_mapper($name) ? bpi_label_mapper($name) : $name,
      '#options' => array(
        'and' => t('All must apply'),
        'or' => t('Any must apply'),
      ),
      '#default_value' => _bpi_get_query_parameter(array('filter', $name), 'and'),
      '#weight' => -10,
    );

    $filter_form['bpi_facets'] = $facets_form;

    $filter_form['bpi_actions'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array(
          drupal_html_class('container-inline'),
        ),
      ),
    );

    if (_bpi_get_current_filter()) {
      $filter_form['bpi_actions']['reset_filter'] = array(
        '#type' => 'item',
        '#markup' => l(t('Reset filters'), current_path(), array(
          'query' => _bpi_get_current_search_query(),
          'attributes' => array(
            'class' => array('button'),
          ),
        )),
      );
    }

    $form['bpi_filter'] = $filter_form;
  }
}

/**
 * Build list of and actions for user's subscriptions.
 *
 * @param array $form
 *   The form.
 */
function bpi_build_subscriptions(array &$form) {
  $user = bpi_get_user();

  if (empty($user)) {
    return;
  }

  $subscriptions = $user->getSubscriptions();
  // Subscriptions that's currently applied if any.
  $active_subscription = NULL;

  if (empty($subscriptions) && !_bpi_is_filter_applied()) {
    return;
  }

  $form['bpi_subscriptions'] = array(
    '#type' => 'fieldset',
    '#title' => t('Subscriptions'),
    '#attributes' => array(
      'class' => array(
        drupal_html_class('container-inline'),
        'bpi-subscriptions',
      ),
    ),
  );

  // Show users subscriptions if any.
  if (!empty($subscriptions)) {
    $active_filter = _bpi_get_current_filter();
    $user_subscriptions = array();
    foreach ($subscriptions as $subscription) {
      if (!bpi_channel_is_channel_subscription($subscription)) {
        $user_subscriptions[] = $subscription;
        if ($subscription->getFilter() == $active_filter) {
          $active_subscription = $subscription;
        }
      }
    }

    $user_subscription_titles = array_map(function ($subscription) {
      return $subscription->getTitle();
    }, $user_subscriptions);

    $options = array('' => t('(Select subscription)')) + array_combine($user_subscription_titles,
        $user_subscription_titles);

    $form['bpi_subscriptions']['subscription_id'] = array(
      '#type' => 'select',
      '#options' => $options,
      '#default_value' => $active_subscription ? $active_subscription->getTitle() : NULL,
    );

    $form['bpi_subscriptions']['subscription_apply'] = array(
      '#type' => 'submit',
      '#submit' => array('bpi_syndicate_subscription_form_submit'),
      '#value' => t('Apply subscription'),
      '#name' => 'subscription_apply',
      '#attributes' => array('formmethod' => 'post'),
    );
    $form['bpi_subscriptions']['subscription_update'] = array(
      '#type' => 'submit',
      '#submit' => array('bpi_syndicate_subscription_form_submit'),
      '#value' => t('Update subscription'),
      '#name' => 'subscription_update',
      '#attributes' => array('formmethod' => 'post'),
    );
    $form['bpi_subscriptions']['subscription_delete'] = array(
      '#type' => 'submit',
      '#submit' => array('bpi_syndicate_subscription_form_submit'),
      '#value' => t('Delete subscription'),
      '#name' => 'subscription_delete',
      '#attributes' => array('formmethod' => 'post'),
    );
  }

  if (_bpi_is_filter_applied() && !$active_subscription) {
    $form['bpi_subscriptions']['subscription_title'] = array(
      '#type' => 'textfield',
      '#attributes' => array(
        'placeholder' => t('Subscription title'),
      ),
    );
    $form['bpi_subscriptions']['subscription_create'] = array(
      '#type' => 'submit',
      '#submit' => array('bpi_syndicate_subscription_form_submit'),
      '#value' => t('Create subscription'),
      '#name' => 'subscription_create',
      '#attributes' => array('formmethod' => 'post'),
    );
  }
}

/**
 * Submit handler for subscriptions.
 *
 * @param array $form
 *   Form structure.
 * @param array $form_state
 *   Form state values.
 *
 * @see bpi_build_subscriptions()
 */
function bpi_syndicate_subscription_form_submit(array $form, array &$form_state) {
  $action = $form_state['triggering_element']['#name'];
  $user = bpi_get_user();

  $subscription_id = $form_state['values']['subscription_id'];
  $subscriptions = array_filter($user->getSubscriptions(), function($subscription) use ($subscription_id) {
    return $subscription->getTitle() == $subscription_id;
  });
  $selected_subscription = count($subscriptions) > 0 ? array_shift($subscriptions) : NULL;

  switch ($action) {
    case 'subscription_create':
      $title = trim($form_state['values']['subscription_title']);
      if (empty($title)) {
        drupal_set_message(t('Please specify a subscription title'), 'error');
        return;
      }

      // Subscriptions must have unique names (for each user).
      if (array_filter($user->getSubscriptions(), function($subscription) use ($title) {
        return $subscription->getTitle() == $title;
      })) {
        drupal_set_message(t('Subscription %title already exists', array('%title' => $title)), 'error');
        return;
      }

      $bpi = bpi_client_instance();
      try {
        $bpi->createSubscription($user->getId(), array(
          'title' => $title,
          'filter' => _bpi_get_current_filter(),
        ));
      }
      catch (\Exception $e) {
        watchdog_exception('bpi', $e);
        drupal_set_message(t('Error creating subscription'), 'error');
        return;
      }

      drupal_set_message(t('Subscription %title created', array('%title' => $title)));
      bpi_flush_user();

      break;

    case 'subscription_apply':
      if (!$selected_subscription) {
        drupal_set_message(t('Subscription %id does not exists', array('%id' => $subscription_id)), 'error');
        return;
      }

      drupal_set_message(t('Subscription %title applied', array('%title' => $selected_subscription->getTitle())));
      drupal_goto('admin/bpi', array('query' => array('filter' => $selected_subscription->getFilter())));

      break;

    case 'subscription_update':
      if (!$selected_subscription) {
        drupal_set_message(t('Subscription %id does not exists', array('%id' => $subscription_id)), 'error');
        return;
      }

      try {
        $bpi = bpi_client_instance();
        $bpi->deleteSubscription($user->getId(), $selected_subscription->getTitle());
        $bpi->createSubscription($user->getId(), array(
          'title' => $selected_subscription->getTitle(),
          'filter' => _bpi_get_current_filter(),
        ));
      }
      catch (\Exception $e) {
        drupal_set_message(t('Cannot update subscription %title', array('%id' => $selected_subscription->getTitle())), 'error');
        return;
      }

      drupal_set_message(t('Subscription %title updated', array('%title' => $selected_subscription->getTitle())));
      bpi_flush_user();
      break;

    case 'subscription_delete':
      if (!$selected_subscription) {
        drupal_set_message(t('Subscription %id does not exists', array('%id' => $subscription_id)), 'error');
        return;
      }

      try {
        $bpi = bpi_client_instance();
        $bpi->deleteSubscription($user->getId(), $selected_subscription->getTitle());
      }
      catch (\Exception $e) {
        drupal_set_message(t('Cannot delete subscription %title', array('%id' => $selected_subscription->getTitle())), 'error');
        return;
      }

      drupal_set_message(t('Subscription %title deleted', array('%title' => $selected_subscription->getTitle())));
      bpi_flush_user();
      break;
  }
}

/**
 * Get facets as an array.
 *
 * For performance reasons facets will only be loaded when no search or
 * filters are applied.
 *
 * @return array|null
 *   All facets.
 */
function bpi_get_facets() {
  // Reload facets if they're not cached locally.
  $reload = !isset($_SESSION[BPI_ALL_FACETS_KEY]) || !is_array($_SESSION[BPI_ALL_FACETS_KEY]);
  if (!$reload) {
    $query = _bpi_get_query_parameter();
    // Reload if neither text nor filter is applied.
    $reload = !_bpi_get_current_search_phrase() || !_bpi_get_current_filter();
  }

  if ($reload) {
    $bpi = bpi_client_instance();
    $result = $bpi->searchNodes();
    if (!empty($result)) {
      $facets = $result->getFacets();
      $_SESSION[BPI_ALL_FACETS_KEY] = bpi_facets_to_array($facets);
    }
    else {
      $_SESSION[BPI_ALL_FACETS_KEY] = NULL;
    }
  }

  return $_SESSION[BPI_ALL_FACETS_KEY];
}

/**
 * Convert facets into an array.
 *
 * @param \Bpi\Sdk\Facets $facets
 *   The facets.
 *
 * @return array
 *   The facets as an associative array.
 *   term => [
 *     title => term title,
 *     count => item count
 *   ]
 */
function bpi_facets_to_array(\Bpi\Sdk\Facets $facets) {
  $data = array();
  $facets = $facets->getFacets();
  if (isset($facets)) {
    foreach ($facets as $facet) {
      $data[$facet->getFacetName()] = array();
      foreach ($facet->getFacetTerms() as $name => $term) {
        $data[$facet->getFacetName()][$name] = array(
          'title' => $term->getTitle(),
          'count' => $term->getAmount(),
        );
      }
    }
  }

  // Sort by keys for consistency. The webservice may not always return facets
  // in the same order.
  ksort($data);

  return $data;
}
