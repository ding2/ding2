<?php

/**
 * Implements hook_ctools_plugin_pre_alter().
 */
function ddbasic_ctools_plugin_pre_alter(&$plugin, &$info) {
  switch ($plugin['module'] . ' ' . $plugin['name']) {
    case 'ting_search search_result_count':
      $plugin['render callback'] = 'ddbasic_ctools_plugin__ting_search_result_count_content_type_render';
      break;
  }
}

function ddbasic_ctools_plugin__ting_search_result_count_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  $search_result = drupal_static('ting_search_results');
  if (isset($search_result)) {
    $results = isset($search_result->numTotalObjects) ? (int) $search_result->numTotalObjects : 0;
    $string = format_plural($results > 1 ? $results : 1, 'Result', 'Results');
    $block->content = array(
      'title' => array(
        '#theme' => 'html_tag',
        '#tag' => 'h1',
        '#attributes' => array('class' => array('page-title')),
        // '#prefix' => '<h1 class="page-title">',
        // '#suffix' => '</h1>',
        '#value' => t('Search result')
      ),
      'string' => array(
        '#theme' => 'html_tag',
        '#tag' => 'span',
        '#attributes' => array('class' => array('search-string')),
        '#value' => '"' . $search_result->search_key . '"'
      ),
      'count' => array(
        '#theme' => 'html_tag',
        '#tag' => 'span',
        '#attributes' => array('class' => array('count')),
        '#value' => '(' . format_plural($results, '1 Result', '@count Results') . ')'
      )
    );
  }

  return $block;
}