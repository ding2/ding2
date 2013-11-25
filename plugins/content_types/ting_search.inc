<?php

$plugin = array(
  'title' => t('Ting search - search results text'),
  'description' => t("Show a string with 'Showing x - y of z results'"),
  'single' => TRUE,
  'content_types' => array('ting_search'),
  'render callback' => 'ting_search_content_type_render',
  'category' => t('Ting'),
  'render last' => TRUE,
);

/**
 * Render the ting search results amount block.
 */
function ting_search_content_type_render($subtype, $conf, $panel_args, $context) {
  global $pager_page_array, $pager_total;
  $block = new stdClass();

  if ($pager_total[0] == TRUE) {
    $results = drupal_static('ting_search_results');
    $from = ($pager_page_array[0] < 1 ? 1 : ($pager_page_array[0]) * $results->numTotalCollections + 1);
    $to = $from + ($results->numTotalCollections - 1);
    $total = $results->numTotalObjects;
    $block->title = t('Search results text');
    $block->content = '<div class="ting-search-amount-block">' . format_plural($total,
      'Show %from-%to of 1 result',
      'Show %from-%to of <span class="placeholder">@count</span> results', array(
        '%from' => $from,
        '%to' => $to,
      )
    ) . '</div>';
  }
  return $block;
}

/**
 * Enable admin settings page.
 */
function ting_search_ting_search_content_type_edit_form($form, &$form_state) {
  return $form;
}

