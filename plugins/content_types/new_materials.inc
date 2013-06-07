<?php

$plugin = array(
  'title' => t('Ting new materials list'),
  'description' => t('Show a list of new materials'),
  'single' => TRUE,
  //'content_types' => array('ting_new_materials'),
  'edit form' => 'ting_new_materials_content_type_edit_form',
  'render callback' => 'ting_new_materials_content_type_render',
  'category' => t('Ting'),
  'required context' => array(new ctools_context_optional(t('New Materials'), 'node')),
  'render last' => TRUE,
);

/**
 * Render the ting search results amount block.
 */
function ting_new_materials_content_type_render($subtype, $conf, $panel_args, $context) {
  //file_put_contents("/home/quickstart/work/debug/debugnewslist.txt", print_r("Ramt" , TRUE), FILE_APPEND);
  //file_put_contents("/home/quickstart/work/debug/debugnewslist.txt", print_r($context , TRUE), FILE_APPEND);
  global $pager_page_array, $pager_total;
  $block = new stdClass();
//
//  if ($pager_total[0] == TRUE) {
//    $results = drupal_static('ting_search_results');
//    $from = ($pager_page_array[0] < 1 ? 1 : ($pager_page_array[0])*$results->numTotalCollections+1);
//    $to = $from + ($results->numTotalCollections-1);
//    $total = $results->numTotalObjects;
//    $block->title = t('Search results text');
//    $block->content = '<div class="ting-search-amount-block">' . format_plural($total,
//      'Show %from-%to of 1 result',
//      'Show %from-%to of <em class="placeholder">@count</em> results', array(
//        '%from' => $from,
//        '%to' => $to,
//    )) . '</div>';
//  }
  $new_materials_node = $context[0]->data;
  $results = ting_new_materials_get_new_materials_posts($new_materials_node);
  $block->content = theme('ting_search_results', array('results' => $results));
  return $block;
}

/**
 * Enable admin settings page
 */
function ting_new_materials_content_type_edit_form($form, &$form_state) {
  return $form;
}

