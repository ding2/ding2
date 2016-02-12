<?php
/**
 * @file
 * Calculates the search context.
 */

/**
 * Calculate the most relevant context for a search.
 *
 * A search context har the highest priority.  A subject context the second
 * highest priority. Defaults to system context.
 *
 * @param array $facets
 *   The facets of the search results.
 * @param int $num_total_objects
 *   Number of objects.
 * @param string $search_string
 *   The search query string.
 *
 * @return int
 *   The context_id of the matching context.
 */
function ting_search_context_calculate_context(array $facets, $num_total_objects, $search_string) {
  // Todo this should accept a search object and get the relevant data
  // from there.
  $contexts = ting_search_context_get_all_contexts();
  $search_contexts = array();
  foreach ($contexts as $context) {
    if ($context->type == 'search') {
      $search_contexts[] = $context;
    }
  }
  $search_context = ting_search_context_check_search_context($search_contexts, $search_string);
  if ($search_context) {
    return $search_context->context_id;
  }

  $system_type = ting_search_context_get_material_type($facets, $num_total_objects);
  if ($system_type == 'book') {
    if ($num_total_objects == 0) {
      // Defaults to neutral on 0 hits searches.
      $system_type = 'neutral';
    }
    else {
      $system_type = ting_search_context_get_audience_fiction($facets);
    }
  }
  $subject_contexts = array();
  $system_context;
  foreach ($contexts as $context) {
    if ($system_type == $context->context && $context->type == 'subject') {
      $subject_contexts[] = $context;
    }
    if ($system_type == $context->context && $context->type == 'system') {
      $system_context = $context;
    }
  }
  $subject_context = ting_search_context_check_subject_contexts($facets, $subject_contexts, $system_context->context);
  if (isset($subject_context)) {
    return $subject_context->context_id;
  }
  else {
    return $system_context->context_id;
  }
}

/**
 * Check if a search context matches the search query string.
 *
 * If there are more than one match the
 * search context with the longest matching string is returned.
 *
 * @param array $search_contexts
 *   The search contexts.
 * @param string $search_string
 *   The search query string.
 *
 * @return mixed
 *   The context object i there is a matching context. Else false
 */
function ting_search_context_check_search_context(array $search_contexts, $search_string) {
  $result_string = '';
  $result_context = FALSE;
  foreach ($search_contexts as $search_context) {
    if (isset($search_context->search)) {
      if (strpos(mb_strtolower($search_string), mb_strtolower($search_context->search)) !== FALSE) {
        if (strlen($search_context->search) > strlen($result_string)) {
          $result_context = $search_context;
          $result_string = $search_context->search;
        }
      }
    }
  }
  return $result_context;
}

/**
 * Get the material type most prominent in the search result.
 *
 * @param array $facets
 *   The facets of the search results.
 * @param int $total_number
 *   Number of objects.
 *
 * @return string
 *   The system_contexts context name or book.
 */
function ting_search_context_get_material_type(array $facets, $total_number) {
  $audio_types = array('lydbog (net)', 'lydbog (cd-mp3)', 'lydbog (cd)');
  $film_types = array('film (net)', 'dvd', 'blue-ray');
  $music_types = array('cd (musik)', 'grammofonplade', 'node');
  if (ting_search_context_matches_material_type($facets, $total_number, $film_types)) {
    return 'film';
  }
  elseif (ting_search_context_matches_material_type($facets, $total_number, $music_types)) {
    return 'musik';
  }
  elseif (ting_search_context_matches_material_type($facets, $total_number, $audio_types)) {
    return 'lydbøger';
  }
  else {
    return 'book';
  }
}

/**
 * Check if a material type matches the material types in the facets.
 *
 * @param array $facets
 *   The facets of the search results.
 * @param int $total_number
 *   Number of objects.
 * @param array $type_array
 *   Array of material types to match against.
 *
 * @return bool
 *   True if the material type matches.
 */
function ting_search_context_matches_material_type(array $facets, $total_number, array $type_array) {
  $number_of_type = ting_search_context_get_term_count($facets, 'facet.type', $type_array);
  return ting_search_context_evalute_condition($number_of_type, $total_number, 0.5);
}


/**
 * Get audience and fiction/nonfiction.
 *
 * @param array $facets
 *   The facets of the search results.
 *
 * @return string
 *   The system_contexts context name.
 */
function ting_search_context_get_audience_fiction(array $facets) {
  $pass_ratio = variable_get('ting_search_context_pass_ratio', 0.60);
  $adult = ting_search_context_is_adult($facets, $pass_ratio);
  $fiction = ting_search_context_is_fiction($facets, $pass_ratio);
  $children = ting_search_context_is_children($facets, $pass_ratio);
  $nonfiction = ting_search_context_is_nonfiction($facets, $pass_ratio);
  if ($adult &&  $fiction) {
    return 'voksen_skøn';
  }
  elseif ($adult &&  $nonfiction) {
    return 'voksen_fag';
  }
  elseif ($children  &&  $fiction) {
    return 'børne_skøn';
  }
  elseif ($children  &&  $nonfiction) {
    return 'børne_fag';
  }
  else {
    return 'neutral';
  }
}

/**
 * Get audience.
 *
 * @param array $facets
 *   The facets of the search results.
 *
 * @param float $pass_ratio
 *   The ratio of relevant result needed to be considered a match.
 *
 * @return bolean
 *   True if adult.
 */
function ting_search_context_is_adult(array $facets, $pass_ratio) {
  $number_of_adult = ting_search_context_get_term_count($facets, 'facet.category', array('voksenmaterialer'));
  $number_of_children = ting_search_context_get_term_count($facets, 'facet.category', array('børnematerialer'));
  return ting_search_context_evalute_condition($number_of_adult, $number_of_adult + $number_of_children, $pass_ratio);
}

/**
 * Get Fiction/nonfiction.
 *
 * @param array $facets
 *   The facets of the search results.
 *
 * @param float $pass_ratio
 *   The ratio of relevant result needed to be considered a match.
 *
 * @return bolean
 *   True if fiction.
 */
function ting_search_context_is_fiction(array $facets, $pass_ratio) {
  $number_of_fiction = ting_search_context_get_term_count($facets, 'facet.genreCategory', array('fiktion'));
  $number_of_nonfiction = ting_search_context_get_term_count($facets, 'facet.genreCategory', array('nonfiktion'));
  return ting_search_context_evalute_condition($number_of_fiction, $number_of_fiction + $number_of_nonfiction, $pass_ratio);
}

/**
 * Get audience.
 *
 * @param array $facets
 *   The facets of the search results.
 *
 * @param float $pass_ratio
 *   The ratio of relevant result needed to be considered a match.
 *
 * @return bolean
 *   True if children.
 */
function ting_search_context_is_children(array $facets, $pass_ratio) {
  $number_of_adult = ting_search_context_get_term_count($facets, 'facet.category', array('voksenmaterialer'));
  $number_of_children = ting_search_context_get_term_count($facets, 'facet.category', array('børnematerialer'));
  return ting_search_context_evalute_condition($number_of_children, $number_of_adult + $number_of_children, $pass_ratio);
}

/**
 * Get Fiction/nonfiction.
 *
 * @param array $facets
 *   The facets of the search results.
 *
 * @return bolean
 *   True if nonfiction.
 */
function ting_search_context_is_nonfiction(array $facets, $pass_ratio) {
  $number_of_fiction = ting_search_context_get_term_count($facets, 'facet.genreCategory', array('fiktion'));
  $number_of_nonfiction = ting_search_context_get_term_count($facets, 'facet.genreCategory', array('nonfiktion'));
  return ting_search_context_evalute_condition($number_of_nonfiction, $number_of_fiction + $number_of_nonfiction, $pass_ratio);
}

/**
 * Check if a subject context matches the search result.
 *
 * @param array $facets
 *   The facets of the search results.
 * @param array $subject_contexts
 *   The search contexts.
 * @param string $type
 *   The system context type.
 *
 * @return mixed
 *   The context object i there is a matching context. Else null
 */
function ting_search_context_check_subject_contexts(array $facets, array $subject_contexts, $type) {
  $index = ting_search_context_get_subject_index_by_type($type);
  $top_term_count = 0;
  $top_context = NULL;
  foreach ($subject_contexts as $context) {
    if (isset($context->subjects)) {
      $subjects = array_map('trim', explode(',', $context->subjects));
      $term_count = ting_search_context_get_top_term_count($facets, $index, $subjects);
      // Check if the current context is a better match than the previous.
      if ($term_count > $top_term_count) {
        $top_term_count = $term_count;
        $top_context = $context;
      }
    }
  }
  return $top_context;
}

/**
 * Get the relevant index name for a given system context type.
 *
 * @param string $type
 *   The system context type.
 *
 * @return string
 *   The name of the index.
 */
function ting_search_context_get_subject_index_by_type($type) {
  $indexes = array(
    'film' => 'subject',
    'musik' => 'subject',
    'lydbøger' => 'subject',
    'voksen_skøn' => 'fictionSubject',
    'voksen_fag' => 'subject',
    'børne_skøn' => 'fictionSubject',
    'børne_fag' => 'subject',
    'neutral' => 'subject',
  );
  return 'facet.' . $indexes[$type];
}


/**
 * Gets the number of term names.
 *
 * Helper function to get the number of term_names which match the top 3 term
 * in the relevant facet.
 *
 * @param array $facets
 *   The facets of the search results.
 * @param string $facet_name
 *   The name of the facet to use.
 * @param array $term_names
 *   The term names to evaluate.
 *
 * @return int
 *   The sum of the matched terms.
 */
function ting_search_context_get_top_term_count(array $facets, $facet_name, $term_names = array()) {
  $number_of_terms = 0;
  if (isset($facets[$facet_name])) {
    $top_terms = array_slice($facets[$facet_name]->terms, 0, 3);
    foreach ($top_terms as $top_term => $term) {
      if (in_array($top_term, $term_names)) {
        $number_of_terms += $term;
      }
    }
  }
  return $number_of_terms;
}

/**
 * Helper function to get the number of term_names which match facet terms.
 *
 * @param array $facets
 *   The facets of the search results.
 * @param string $facet_name
 *   The name of the facet to use.
 * @param array $term_names
 *   The term names to evaluate.
 *
 * @return int
 *   The sum of the matched terms.
 */
function ting_search_context_get_term_count(array $facets, $facet_name, $term_names = array()) {
  $number_of_terms = 0;
  if (isset($facets[$facet_name])) {
    $terms = $facets[$facet_name]->terms;
    foreach ($term_names as $term_name) {
      if (isset($terms[$term_name])) {
        $number_of_terms += $terms[$term_name];
      }
    }
  }
  return $number_of_terms;
}

/**
 * Helper function to evalute if number of terms exceeds the treshhold ratio.
 *
 * @param int $number_of_terms
 *   The number of terms.
 * @param int $total_number
 *   Total number.
 * @param float $pass_ratio
 *   The ratio which is has to be exceeded.
 *
 * @return bolean
 *   True if ratio is exceeded.
 */
function ting_search_context_evalute_condition($number_of_terms, $total_number, $pass_ratio) {
  if ($total_number != 0) {
    $term_ratio = $number_of_terms / $total_number;
    return ($term_ratio > $pass_ratio);
  }
  else {
    return FALSE;
  }
}
