<?php

function ting_search_autocomplete($query = NULL) {
  $query = $_GET['query'];
  $results   = array();
  $delimiter = 0;

  if ($query == TRUE) {
    $cache = cache_get(md5($query), 'cache_ting_search_autocomplete');
    if ($cache instanceof stdClass && is_array($cache->data)) {
      $return = $cache->data;
    }
    else {
      require_once drupal_get_path('module', 'ting') . '/ting.client.inc';

      $terms = array();

      // Scan for search results
      $scan_results = ting_do_scan($query, 'anyIndexes', 10);
      foreach ($scan_results->terms as $term) {
        $terms['any'][strtolower($term->name)] = $term;
      }
      uasort($terms['any'], 'ting_search_autocomplete_term_sort');
      $terms['any'] = array_reverse($terms['any']);

      // Scan for spell suggestions
      $spell_suggestions = ting_get_spell_suggestions($query, 3);
      foreach ($spell_suggestions as $spell_word) {
        if (strtolower($spell_word->word) == strtolower($query)) {
          continue;
        }
        $spell_word->count = $spell_word->weight;
        $spell_word->name  = $spell_word->word;
        $terms['spell'][$spell_word->word] = $spell_word;
      }

      foreach ($terms as $type => $row) {
        foreach ($row as $term) {
          if ($type == 'spell') {
            $return[] = array(
              'id'    => $term->name,
              'value' => drupal_substr($term->name, 0, 128),
              'label' => t('Did you mean \'@query\' ?', array('@query' => $term->name)),
            );
          }
          else {
            $return[] = array(
              'id'    => $term->name,
              'value' => drupal_substr($term->name, 0, 128),
              'label' => $term->name,
            );
          }
        }
      }

      cache_set(md5($query), $return, 'cache_ting_search_autocomplete', CACHE_TEMPORARY);
    }
  }
  drupal_json_output($return);
}

function ting_search_autocomplete_term_sort($t1, $t2) {
  if ($t1->count> $t2->count) {
    return 1;
  }
  elseif ($t2 > $t1->count) {
    return -1;
  }
  else {
    return 0;
  }
}
