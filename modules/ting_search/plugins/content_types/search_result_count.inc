<?php
/**
 * @file
 * Panels pane to display page title with result count.
 */

$plugin = array(
  'title' => t('Ting search - page title'),
  'description' => t("Display title with result count."),
  'content_types' => array('ting_search'),
  'render callback' => 'ting_search_result_count_content_type_render',
  'category' => t('Ting'),
  'required context' => new ctools_context_required(t('Keywords'), 'string'),
  'render last' => TRUE,
);

/**
 * Render the ting search results amount block.
 */
function ting_search_result_count_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  $search_result = drupal_static('ting_search_results');
  if (isset($search_result)) {
    $results = isset($search_result->numTotalObjects) ? (int) $search_result->numTotalObjects : 0;
    $block->content = array(
      'title' => array(
        '#theme' => 'html_tag',
        '#tag' => 'h1',
        '#attributes' => array('class' => array('page-title')),
        '#value' => t('Search result'),
      ),
      'string' => array(
        '#theme' => 'html_tag',
        '#tag' => 'span',
        '#attributes' => array('class' => array('search-string')),
        '#value' => '"' . $search_result->search_key . '"',
      ),
      'count' => array(
        '#theme' => 'html_tag',
        '#tag' => 'span',
        '#attributes' => array('class' => array('count')),
        '#value' => '(' . format_plural($results, '1 Result', '@count Results') . ')',
      ),
    );
  }

  return $block;
}

/**
 * Enable admin settings page.
 */
function ting_search_search_result_count_content_type_edit_form($form, &$form_state) {
  return $form;
}
