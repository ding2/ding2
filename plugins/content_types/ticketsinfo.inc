<?php
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
  $block->content = render_place2book_ticketsinfo($context->data);
  
  return $block;
}

/**
 * Implements hook_content_type_edit_form().
 */
function ding_place2book_ticketsinfo_content_type_edit_form($form, &$form_state) {
  //Reference 
  
  return $form;
} 

/**
 * Implements hook_content_type_edit_form_submit().
 */
function ding_place2book_ticketsinfo_content_type_edit_form_submit(&$form, &$form_state) {
  //Reference
}