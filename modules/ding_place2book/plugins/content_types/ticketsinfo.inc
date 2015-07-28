<?php
/*
 * @file
 * A panel pane for showing place2book tickets info.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Place2book tickets info'),
  'description' => t('Pane showing a booking link or info about ticket availability'),
  'category' => t('Ding!'),
  'single' => TRUE,
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'render callback' => 'ding_place2book_ticketsinfo_content_type_render',
);

/**
 * Implements hook_content_type_render().
 */
function ding_place2book_ticketsinfo_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  
  //$context->data contains the node object
  $block->content = '<input type="hidden" class="place2book-ticketinfo" value="' . $context->data->nid . '"/>';
  
  return $block;
} 