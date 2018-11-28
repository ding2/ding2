<?php
/**
 * @file
 * Panels pane to display search result count.
 */

$plugin = array(
  'title' => t('Ting search - result count'),
  'description' => t("Display Result count."),
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

  $search_result = ting_search_current_results();
  if (isset($search_result)) {
    // OpenSearch only delivers the number of manifestions but the search
    // result can also include materials. Because of this, we need to display
    // different types of result counts based on the "more results" value,
    // which basically checks if theres more than one page available for the
    // search result pagination.
    $results = $search_result->hasMoreResults() ?
      $search_result->getNumTotalObjects() :
      $search_result->getNumCollections();

    $block->content = array(
      'count' => array(
        '#theme' => 'html_tag',
        '#tag' => 'span',
        '#attributes' => array('class' => array('count')),
        '#value' => format_plural($results, '1 Result', '@count Results'),
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
