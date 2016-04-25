<?php
/**
 * @file
 * Ctools plugin definition file.
 */

$plugin = array(
  'title' => t('Ding item viewer'),
  'category' => t('Ding!'),
  'description' => t('Display ting objects in a carousel view.'),
  'single' => TRUE,
  'content_types' => 'ding_item_viewer_content_type',
  'render callback' => 'ding_item_viewer_content_type_render',
  'edit form' => 'ding_item_viewer_content_type_edit_form',
);
