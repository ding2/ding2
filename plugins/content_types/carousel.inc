<?php

/**
 * @file
 * Provides search results as a Panels content type.
 */

$plugin = array(
  'title' => t('Ting search carousel'),
  'single' => TRUE,
  'description' => t('A carousel displaying search results against the Ting system'),
  'category' => t('Ting'),
);

/**
 * Return the pane contents.
 */
function ting_search_carousel_carousel_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  $path = drupal_get_path('module', 'ting_search_carousel');
  drupal_add_js($path . '/js/ting_search_carousel.js');
  drupal_add_js(array('tingSearchCarousel' => array('resultsPerPage' => 6)), 'setting');
  drupal_add_css($path . '/css/ting_search_carousel.css');

  $searches = variable_get('ting_carousel_search_queries', array());

  $block->content = theme('ting_search_carousel', array('searches' => $searches));
  return $block;
}

/**
 * Return the pane titles.
 */
function ting_search_carousel_carousel_content_type_admin_title($subtype, $conf, $context) {
  return t('Search');
}

/**
 * Returns an edit form for the content type.
 */
function ting_search_carousel_carousel_content_type_edit_form($form, &$form_state) {
  return $form;
}
