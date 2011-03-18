<?php

/**
 * JSON callback to Ting search autocomplete
 */
function ting_search_autocomplete_js() {
	$items = array();
	$query = (isset($_REQUEST['query'])) ? $_REQUEST['query'] : '';

	if (strlen($query) > 0)
	{
		$cache = cache_get(md5($query), 'cache_ting_search_autocomplete');
		if ($cache)
		{
			$items = $cache->data;
		}
		else
		{
      $path = drupal_get_path('module', 'ting');
      require $path . '/ting.client.inc';

			$terms = array();

			$scanResults = ting_do_scan($query, 10);
			foreach ($scanResults->terms as $term)
			{
				$term->score = $term->count;
				$terms[strtolower($term->name)] = $term;
			}

			$suggestions = ting_get_spell_suggestions($query);
			if (is_array($suggestions))
			{
				foreach ($suggestions as $suggestion)
				{
					if (!isset($terms[strtolower($suggestion->word)]))
					{
						$suggestScan = ting_do_scan($suggestion->word, 1);
						if (($term = array_shift($suggestScan->terms)) &&
								(strtolower($suggestion->word) == strtolower($term->name)))
						{
							$term->score = $term->count * $suggestion->weight;
							$terms[$term->name] = $term;
						}
					}
				}
			}

			uasort($terms, 'ting_search_autocomplete_term_sort');
			$terms = array_reverse($terms);

			$items = array();
			foreach ($terms as $term)
			{
				$items[$term->name] = t('!ord !resultater',
          array('!ord' => '<span class="term">'.$term->name.'</span>',
          '!resultater' => '<span class="count">'.format_plural($term->count, t('(1 resultat)'), t('(@count resultater)')))).'</span>';
			}

			$items = array_slice($items, 0, 10);
			cache_set(md5($query), $items, 'cache_ting_search_autocomplete', CACHE_TEMPORARY);
		}
	}
	$return = array();
	foreach ($items as $id => $value)
	{
		$return[] = $value.'|'.$id;
	}
	echo implode("\n", $return);
	exit;
}

function ting_search_autocomplete_term_sort($t1, $t2) {
	if ($t1->score > $t2->score){
		return 1;
	} elseif ($t2 > $t1->score) {
		return -1;
	} else {
		return 0;
	}
}
