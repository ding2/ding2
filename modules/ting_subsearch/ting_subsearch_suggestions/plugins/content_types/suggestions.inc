<?php
/**
 * @file
 * Panels pane for ting subsearch suggestions pane.
 */

$plugin = array(
  'title' => t('Ting subsearch suggestions'),
  'description' => t('Display a suggestion based on autocomplete and levenshtein distance.'),
  'content_types' => array('ting_subsearch_suggestions'),
  'render callback' => 'ting_subsearch_suggestions_content_type_render',
  'edit form' => 'ting_subsearch_suggestions_content_type_edit_form',
  'category' => t('Ting'),
  'required context' => new ctools_context_required(t('Keywords'), 'string'),
);

/**
 * Render ting subsearch suggestions pane.
 */
function ting_subsearch_suggestions_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  // Return early if search provider doesn't implement autocomplete suggestions.
  if (!ding_provider_implements('search', 'autocomplete_suggestions')) {
    return $block;
  }

  $search_result = ting_search_current_results();
  if (!isset($search_result)) {
    return $block;
  }

  $num_result = $search_result->getNumTotalObjects();
  $limit = variable_get('ting_subsearch_suggestions_trigger_limit', 5);

  // Trigger ajax subsearch if user search num result is below limit.
  if ($num_result <= $limit) {
    $block->content = ting_subsearch_get_ajax_placeholder_render_array('ting_subsearch_suggestions');
  }

  return $block;
}

/**
 * Enable admin settings page.
 */
function ting_subsearch_suggestions_content_type_edit_form($form, &$form_state) {
  return $form;
}
