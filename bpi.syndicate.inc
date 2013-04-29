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

  // @todo
  // Search filters here.
  $form['bpi_search_filters'] = array();

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
    $query_parameters = array('query' => array('text' => $query));
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
 * Create query string key/value pairs.
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
function _bpi_build_query($key, $value) {
  $current_path = parse_url(reset(drupal_get_destination()));
  $query = isset($current_path['query']) ? $current_path['query'] : '';
  $new_query_pairs = array();

  if (!empty($query)) {
    // Get the parameters array.
    $components = explode('&', $query);

    /// Iterate and rearrange them.
    foreach ($components as $component) {
      $temp = explode('=', $component);
      // It's required to decode some values here, since Drupal's url() encodes it
      // weird, munging the 'space' entity value (%20).
      $new_query_pairs[$temp[0]] = urldecode($temp[1]);
    }
  }

  // Append the new key/value pair to existing ones.
  if (!empty($key) && !empty($value)) {
      $new_query_pairs[$key] = $value;
  }

  return $new_query_pairs;
}

function _bpi_current_search_phrase() {
  return isset($_GET['text']) ? check_plain($_GET['text']) : '';
}
