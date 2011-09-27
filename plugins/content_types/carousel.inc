<?php

/**
 * @file result.inc
 * Provides search results as a Panels content type.
 */

/**
 * Callback function to supply a list of content types.
 *
 * This is only required to make CTools know that we're providing 
 * multiple types here (since we have no single => TRUE in the array).
 */
function ting_search_carousel_carousel_ctools_content_types() {
  return array(
    'title' => t('Ting search carousel'),
    'single' => TRUE,
    'description' => t('A carousel displaying search results against the Ting system'),
    'category' => t('Ting'),
  );
}

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
 *
 * We're not actually doing anything here, but we need to have this hook 
 * for this content type to work.
 */
function ting_search_carousel_carousel_content_type_edit_form(&$form, &$form_state) {
  return $form;
}

