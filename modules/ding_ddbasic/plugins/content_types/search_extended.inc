<?php
/**
 * @file
 * Content type plugin for all opening hours.
 */

/**
 * Array describing the plugin to CTools/Panels.
 */
$plugin = array(
  'title' => t('Search form: extended'),
  'description' => t('Show todays opening hours for all libraries.'),
  'single' => TRUE,
  'content_types' => array('list'),
  'category' => t('Ding!'),
);

/**
 * Render the block
 */
function ding_ddbasic_search_extended_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  $block->title = t('Search extended');
  $block->content = 'yada';

  return $block;
}

/**
 * Form for configuring the content type.
 */
function ding_ddbasic_search_extended_content_type_edit_form($form, &$form_state) {
  return $form;
}