<?php

/**
 * @file ting_objects.inc
 * Provide an array of Ting objects as a Panels relation.
 */

/**
 * Implementation of hook_ctools_relationships().
 */
function ting_recommendation_panes_ting_objects_ctools_relationships() {
  $args = array();
  $args['ting_objects'] = array(
    'title' => t('Ting objects'),
    'keyword' => 'ting_objects',
    'description' => t('Finds the related library from a node context.'),
    'context' => 'ting_recommendation_panes_ting_objects_context',
    'settings form' => 'ding_panels_related_library_settings_form',
  );
  return $args;
}

/**
 * Return a new context based on an existing context
 */
function ting_recommendation_panes_ting_objects_context($context = NULL, $conf) {
  // If unset it wants a generic, unfilled context, which is just NULL
  if (empty($context->data)) {
    return ctools_context_create_empty('node');
  }

  if (isset($context->data->field_library_ref[0]) && $context->data->field_library_ref[0] > 0) {
    $node = node_load($context->data->field_library_ref[0]);
    if ($node) {
      return ctools_context_create('node', $node);
    }
  }
  return FALSE;
}

/**
 * Settings form for the relationship
 */
function ting_recommendation_panes_ting_objects_settings_form($conf) {
  return $form;
}
