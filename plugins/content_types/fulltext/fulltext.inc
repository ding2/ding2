<?php
/**
 * @file
 * Renders a parsed data-well fulltext XML document as content.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Ting fulltext'),
  'description' => t('Fulltext display of ting object docdook relation.'),
  'single' => TRUE,
  'content_types' => array('fulltext'),
  'render callback' => 'ting_fulltext_type_render',
  'category' => t('Ting'),
);

/**
 * Render callback function.
 */
function ting_fulltext_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  if (isset($panel_args[1][0])) {
    $path = drupal_get_path('module', 'ting_fulltext');
    // Include functions to parse the xml.
    include_once $path . '/includes/ting_fulltext.pages.inc';

    $block->content = array(
      '#theme' => 'ting_fulltext',
      '#fields' => ting_fulltext_parse($panel_args[1][0]),
    );
  }

  return $block;
}

/**
 * Plugin settings form.
 */
function ting_fulltext_content_type_edit_form($form, &$form_state) {
  return $form;
}
