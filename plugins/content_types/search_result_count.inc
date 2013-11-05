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
    $block->content = array(
      '#prefix' => '<h1 class="page-title">',
      '#surfix' => '</h1>',
      '#markup' => format_plural((int) $search_result->numTotalObjects,
        'Search result <span class="search-field-in-content--amount">(1 result)</span>',
        'Search result <span class="search-field-in-content--amount">(!count results)</span>', array(
          '!count' => $search_result->numTotalObjects,
        )
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
