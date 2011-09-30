<?php

/**
 * @file result.inc
 * Provides search results as a Panels content type.
 */


$plugin = array(
  'title' => t('Ting search carousel'),
  'description' => t('A carousel displaying search results against the Ting system'),
  'single' => TRUE,
  'content_types' => array('carousel'),
  'render callback' => 'ting_search_carousel_carousel_content_type_render',
  'defaults' => array(),
  'edit form' => 'ting_search_carousel_carousel_content_type_edit_form',
  'category' => array(t('Ting'), -9),
  'required context' => new ctools_context_required(t('Ting object'), 'ting_object'),
  'admin title' => 'ting_search_carousel_carousel_content_type_admin_title',
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
  
  $searches = variable_get('ting_search_carousel_searches', array());
  
  $block->content = theme('ting_search_carousel', $searches);
  return $block;
}

/**
 * Return the pane titles.
 */
function ting_search_carousel_carousel_content_type_admin_title($subtype, $conf, $context) {
  return t('Søgninger');
}

/**
 * Returns an edit form for the content type.
 */
function ting_search_carousel_carousel_content_type_edit_form(&$form, &$form_state) {
  return $form;
}
