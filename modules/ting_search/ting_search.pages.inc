<?php

/**
 * Process variables for ting-search-results.tpl.php.
 */
function template_preprocess_ting_search_results(&$variables) {
  $variables['search_results'] = '';
  if (!empty($variables['module'])) {
    $variables['module'] = check_plain($variables['module']);
  }

  foreach ($variables['results'] as $result) {
    $variables['search_results'] .= theme('search_result', array('result' => $result, 'module' => $variables['module']));
  }
  $variables['pager'] = theme('ting_search_pager', array('tags' => NULL));

  $search_result = ting_search_current_results();
  if (isset($search_result)) {
    $count = $search_result->hasMoreResults() ?
      $search_result->getNumTotalObjects() :
      $search_result->getNumCollections();

    $variables['search_results_count'] = theme('ting_search_results_count', array(
      'count' => $count,
    ));
  }
}
