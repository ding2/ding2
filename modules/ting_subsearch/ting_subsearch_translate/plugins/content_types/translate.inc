<?php

/**
 * @file
 * Ting subsearch translate content_type plugin definition.
 */

$plugin = array(
  'title' => t('Ting subsearch translate'),
  'description' => t('Display a suggestion based on translation of user search.'),
  'content_types' => array('ting_subsearch_translate'),
  'render callback' => 'ting_subsearch_translate_content_type_render',
  'edit form' => 'ting_subsearch_translate_content_type_edit_form',
  'category' => t('Ting'),
  'required context' => new ctools_context_required(t('Keywords'), 'string'),
);

/**
 * Render ting subsearch translate pane.
 */
function ting_subsearch_translate_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  // Return early if module is not configured.
  if (empty(variable_get('ting_subsearch_translate_google_key', ''))) {
    return $block;
  }

  $search_result = ting_search_current_results();
  if (!isset($search_result)) {
    return $block;
  }

  $num_results = $search_result->getNumTotalObjects();
  $factor = variable_get('ting_subsearch_translate_factor', 50);
  $ratio = ting_subsearch_get_genre_ratio($search_result);

  // Trigger ajax subsearch if conditions is satisfied.
  if ($num_results == 0 || $ratio >= $factor) {
    $block->content = ting_subsearch_get_ajax_placeholder_render_array('ting_subsearch_translate');
  }

  return $block;
}

/**
 * Enable admin settings page.
 */
function ting_subsearch_translate_content_type_edit_form($form, &$form_state) {
  return $form;
}
