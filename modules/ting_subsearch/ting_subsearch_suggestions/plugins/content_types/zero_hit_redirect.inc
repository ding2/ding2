<?php
/**
 * @file
 * Panels pane for ting subsearch zero hit redirect panels pane.
 */

$plugin = array(
  'title' => t('Ting subsearch suggestions - zero hit redirect'),
  'description' => t('Performs a subsearch redirect if user search returned zero results and display message on redirected page.'),
  'content_types' => array('ting_subsearch_suggestions_zero_hit_redirect'),
  'render callback' => 'ting_subsearch_suggestions_zero_hit_redirect_render',
  'edit form' => 'ting_subsearch_suggestions_zero_hit_redirect_edit_form',
  'category' => t('Ting'),
  'required context' => new ctools_context_required(t('Keywords'), 'string'),
);

/**
 * Render ting subsearch zero hit redirect pane.
 */
function ting_subsearch_suggestions_zero_hit_redirect_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  $keys = isset($context->data) ? $context->data : '';

  // If we're already redirecting from a zero-hit search avoid trying to find
  // suggestions for our own suggestion. Display a zero hit suggestions message.
  if (!empty($_GET['original-search'])) {
    $block->content = theme('ting_subsearch_message', [
      'message' => t('Showing results for <strong>"@suggestion"</strong>. The search for <strong>"@original_search"</strong> returned 0 hits.', [
        '@suggestion' => $keys,
        '@original_search' => $_GET['original-search'],
      ]),
      'type' => 'suggestions',
      'suggestion' => $keys,
      'suggestion_num_results' => '',
      'original_search' => $_GET['original-search'],
      'original_search_num_results' => 0,
    ]);

    return $block;
  }

  // Get the search result and bail out if it's not a zero hit.
  $search_result = ting_search_current_results();
  if (!isset($search_result) || $search_result->getNumTotalObjects() > 0) {
    return $block;
  }

  $suggestion = ting_subsearch_suggestions_suggest_keys($keys);
  if ($suggestion) {
    $subsearch_request = $search_result
      ->getSearchRequest()
      ->withFullTextQuery($suggestion);

    // Perform subsearch with suggestion.
    $subsearch_result = ting_subseach_do_subsearch($subsearch_request);

    // If the subsearch returned any result perform a zero hit redirect.
    if ($subsearch_result->getNumTotalObjects() > 0) {
      $query = [
        'original-search' => $keys,
      ] + ting_subsearch_get_query_parameters();

      drupal_goto('search/ting/' . $suggestion, ['query' => $query]);
    }
  }

  return $block;
}

/**
 * Enable admin settings page.
 */
function ting_subsearch_suggestions_zero_hit_redirect_edit_form($form, &$form_state) {
  return $form;
}
