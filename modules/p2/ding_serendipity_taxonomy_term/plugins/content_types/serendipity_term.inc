<?php

/**
 * @file
 * Serendipity taxonomy term ctools content_type.
 */

$plugin = array(
  'title' => t('Ding serendipity taxonomy term'),
  'description' => t('Displays serendipity content based on a taxonomy term.'),
  'admin info' => 'ding_serendipity_term_admin_info',
  'single' => TRUE,
  'edit form' => 'ding_serendipity_term_content_type_edit_form',
  'render callback' => 'ding_serendipity_term_content_type_render',
  'category' => t('Ding!'),
  'required context' => array(
    new ctools_context_optional(t('Term'), 'taxonomy_term'),
  ),
);

/**
 * Implements hook_content_type_admin_info().
 */
function ding_serendipity_term_admin_info($subtype, $conf, $context) {
  return ding_serendipity_get_default_admin_info($subtype, $conf, $context);
}

/**
 * Implements hook_content_type_edit_form().
 */
function ding_serendipity_term_content_type_edit_form($form, &$form_state) {
  module_load_include('inc', 'ding_serendipity', 'plugins/content_types/serendipity');
  $base = ding_serendipity_form_base($form_state);
  $form += $base;
  $form['entity_type'] = array(
    '#type' => 'select',
    '#title' => t('Entity type'),
    '#options' => array(
      'node' => t('Node'),
      'ting_object' => t('Ting object'),
    ),
    '#default_value' => (isset($form_state['conf']['entity_type'])) ? $form_state['conf']['entity_type'] : 'node',
    '#description' => t('Select the entity type to display in this list.'),
  );
  $node_options = array();
  $node_types = node_type_get_types();
  foreach ($node_types as $type) {
    $node_options[$type->type] = $type->name;
  }
  // We assume the most common thing to display would be events.
  $form['bundle'] = array(
    '#type' => 'select',
    '#title' => t('Node type'),
    '#options' => $node_options,
    '#default_value' => (isset($form_state['conf']['bundle'])) ? $form_state['conf']['bundle'] : 'ding_event',
    '#description' => t('Select a node type if node is selected above.'),
    '#states' => array(
      'visible' => array(
        ':input[name="entity_type"]' => array('value' => 'node'),
      ),
    ),
  );
  return $form;
}

/**
 * Implements hook_content_type_edit_form_submit().
 */
function ding_stt_serendipity_term_content_type_edit_form_submit($form, &$form_state) {
  ding_serendipity_form_base_submit($form_state);
  $form_state['conf']['entity_type'] = $form_state['values']['entity_type'];
  $form_state['conf']['bundle'] = $form_state['values']['bundle'];
}

/**
 * Implements hook_content_type_render().
 */
function ding_stt_serendipity_term_content_type_render($subtype, $conf, $args, $context) {
  if (isset($context[0]->data)) {
    $selected_term = $context[0]->data;
  }
  if ($conf['entity_type'] == 'node') {
    $node = node_load($args[0]);
    $conf['bundle'] = $node->type;
  }
  $context = array(
    'entity_type' => $conf['entity_type'],
    'bundle' => $conf['bundle'],
    'taxonomy_term' => $args[0],
    'related' => TRUE,
    'view_mode' => !empty($conf['view_mode']) ? $conf['view_mode'] : 'big_teaser',
    'sort_weight' => !empty($conf['sort_weight']) ? $conf['sort_weight'] : FALSE,
    'max' => !empty($conf['max']) ? $conf['max'] : 4,
    'min' => !empty($conf['min']) ? $conf['min'] : 4,
    'random' => !empty($conf['random']) ? TRUE : FALSE,
  );

  $content = ding_serendipity_render($context);
  $block = new stdClass();
  $block->title = t('Inspiration');
  $block->content = $content;
  return $block;
}
