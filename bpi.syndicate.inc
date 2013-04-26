<?php
/**
 * @file
 * Syndication logic here.
 */

/**
 * @todo
 *   Add some meaningful description durin' develpoment.
 * @return string
 *
 * @ingroup forms
 */
function bpi_syndicate_page_form($form, &$form_state) {
  $form['bpi_search_query'] = array(
    '#type' => 'textfield',
  );

  $form['bpi_search_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Search'),
  );

  // @todo
  // Lat3r.
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

function bpi_syndicate_page_form_submit($form, &$form_state) {
  $query = $form_state['values']['bpi_search_query'];

  if (!empty($query)) {
    drupal_goto('admin/bpi', array('query' => array('text' => $query)));
  }
}

function bpi_search_content($page = 1, $filters = array()) {

}

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

function bpi_search_get_markup() {
  $items = bpi_search_get_items();
  $data = array();

  foreach ($items as $item) {
    $data[] = theme('bpi_well_item', array('item' => $item));
  }

  return implode('', $data);
}
