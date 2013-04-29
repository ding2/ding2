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
  $form['bpi_search_query'] = array(
    '#type' => 'textfield',
    '#default_value' => _bpi_current_search_phrase(),
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

  $markup = bpi_search_get_markup();
  $form['bpi_search_results'] = array(
    '#type' => 'item',
    '#markup' => $markup,
  );

  $form['#attached']['css'][] = drupal_get_path('module', 'bpi') . '/css/pages.styles.css';
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
 * @todo dummy
 * @param type $page
 * @param type $filters
 */
function bpi_search_content($page = 1, $filters = array()) {

}

/**
 * @todo dummy
 * @return type
 */
function bpi_search_get_items() {
  return array(
    array(
      'bpi_id' => mt_rand(1, 99),
      'title' => 'Article title',
      'date' => '03/25/2013-11:03',
      'teaser' => 'Lorem ipsum dolor sit amet, consectetur adipiscing elit.',
      'author' => 'Martin Cording',
      'category' => 'Latest stories',
      'agency' => 'Aarhus library',
      'audience' => 'Students',
    )
  );
}

/**
 * Creates markup from found content during search.
 *
 * @return string
 *   HTML markup.
 *
 * @ingroup themable
 */
function bpi_search_get_markup() {
  $items = bpi_search_get_items();
  $data = array();

  // Iterate through items and theme them.
  foreach ($items as $item) {
    $data[] = theme('bpi_well_item', array('item' => $item));
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
  $current_path = parse_url(reset(drupal_get_destination()));
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

    // Clear the search results, if query filter is removed.
    if ($key == SEARCH_PHRASE_KEY) {
      $item['search_stripped_filter'] = array();
    }

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

  return ($sort_dir == SORT_DESCENDING) ? SORT_ASCENDING : SORT_DESCENDING;
}
