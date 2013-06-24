<?php

$plugin = array(
  'title' => t('Ting new materials list'),
  'description' => t('Show a list of new materials'),
  'single' => TRUE,
  'edit form' => 'ting_new_materials_content_type_edit_form',
  'render callback' => 'ting_new_materials_content_type_render',
  'category' => t('Ting'),
  'required context' => array(new ctools_context_optional(t('New Materials'), 'node')),
  'render last' => TRUE,
);

/**
 * Render the ting new materials results results amount block.
 */
function ting_new_materials_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
 
  $new_materials_node = $context[0]->data;
  $title = $new_materials_node->title;
  $search_results = ting_new_materials_get_new_materials_posts($new_materials_node);
  
  $number_of_results = '';
  global $pager_page_array, $pager_total;
  if ($pager_total[0] == TRUE) {
    $results = drupal_static('ting_search_results');
    $from = ($pager_page_array[0] < 1 ? 1 : ($pager_page_array[0])*$results->numTotalCollections+1);
    $to = $from + ($results->numTotalCollections-1);
    $total = $results->numTotalObjects;
    $number_of_results =  format_plural($total, 'Show %from-%to of 1 result',
      'Show %from-%to of <em class="placeholder">@count</em> results', array(
        '%from' => $from,
        '%to' => $to,
    )) ;
  }
  
  $results = theme('ting_search_results', array('results' => $search_results));  
  $block->content = theme('ting_new_materials', array('title' => $title, 'number_of_results' => $number_of_results, 'results' => $results));
  return $block;
}

/**
 * Enable admin settings page
 */
function ting_new_materials_content_type_edit_form($form, &$form_state) {
  return $form;
}

