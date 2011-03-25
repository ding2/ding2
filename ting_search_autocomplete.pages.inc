<?php

/**
 * JSON callback to Ting search autocomplete
 */
function ting_search_autocomplete_js() {
	$return = array();

	$query = isset($_REQUEST['query']) ? $_REQUEST['query'] : FALSE;

	if ($query !== FALSE)
	{
    $cache = cache_get(md5($query), 'cache_ting_search_autocomplete');

		if ($cache instanceof stdClass && is_array($cache->data)) {
			$return = $cache->data;
		}
		else {
      require_once drupal_get_path('module', 'ting') . '/ting.client.inc';

			$terms = array();

			$scanResults = ting_do_scan($query, 10);
			foreach ($scanResults->terms as $term) {
				$terms[strtolower($term->name)] = $term;
			}

      uasort($terms, 'ting_search_autocomplete_term_sort');
      $terms = array_reverse($terms);

			foreach ($terms as $term) {
				$return[] = t('!word !results',
          array('!word' => '<span class="term">' . $term->name . '</span>',
          '!results' => '<span class="count">' . format_plural($term->count, t('(1 result)'), t('(@count results)')))) . '</span>|' . $term->name;
			}

      cache_set(md5($query), $return, 'cache_ting_search_autocomplete', CACHE_TEMPORARY);
		}
	}

	echo implode("\n", $return);
	exit;
}

function ting_search_autocomplete_term_sort($t1, $t2) {
	if ($t1->count> $t2->count){
		return 1;
	} elseif ($t2 > $t1->count) {
		return -1;
	} else {
		return 0;
	}
}
