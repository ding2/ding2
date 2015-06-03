<?php

/**
 * Calculate the most relevant context for a search. A search context har the highest priority.
 * A subject context the second highest priority. Defaults to system context.
 *
 * @param array $facets
 *   The facets of the search results.
 * @param int $numTotalObjects
 *   Number of objects
 * @param $search_string
 *   The search query string.
 *
 * @return int
 *   The context_id of the matching context.
 */
function ting_search_context_calculate_context($facets, $numTotalObjects, $search_string) {
  //Todo this should accept a search object and get the relevant data from there.
  $contexts = ting_search_context_get_all_contexts();
  $search_contexts = array();
  foreach ($contexts as $context) {
    if ($context->type == 'search') {
      $search_contexts [] = $context;
    }
  }
  $search_context = ting_search_context_check_search_context($search_contexts, $search_string);
  if ($search_context) {
    return $search_context->context_id;
  }
  file_put_contents("/home/quickstart/work/debug/debugcontexts.txt", print_r($contexts , TRUE), FILE_APPEND);

  $system_type = ting_search_context_get_material_type($facets, $numTotalObjects);
  if ($system_type == 'book') {
    $system_type = ting_search_context_get_audience_fiction($facets);
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
  } else {
    return $system_context->context_id;
  }
}

/**
 * Check if a search context matches the search query string
 *
 * @param array $search_contexts
 *   The search contexts.
 *
 * @param string $search_string
 *   The search query string.
 *
 * @return mixed
 *   The context object i there is a matching context. Else false
 *
 */
function ting_search_context_check_search_context($search_contexts, $search_string) {
  foreach ($search_contexts as $search_context) {
    if (isset($search_context->search))
      if (strpos(strtolower($search_string), strtolower($search_context->search)) !== false) {
        return $search_context;
      }
  }
  return false;
}

/**
 * Get the material type most prominent in the search result
 *
 * @param array $facets
 *   The facets of the search results.
 *
 * @param int $total_number
 *   Number of objects
 *
 * @return string
 *   The system_contexts context name or book.
 */
function ting_search_context_get_material_type($facets, $total_number) {
  $audio_types = array('lydbog (net)', 'lydbog (cd-mp3)', 'lydbog (cd)');
  $film_types = array('film (net)', 'dvd', 'blue-ray');
  $music_types = array('cd (musik)', 'grammofonplade', 'node');
  if (ting_search_context_matches_material_type($facets, $total_number, $film_types))
    return 'film';
  else if (ting_search_context_matches_material_type($facets, $total_number, $music_types))
    return 'musik';
  else if (ting_search_context_matches_material_type($facets, $total_number, $audio_types ))
    return 'lydbøger';
  else
    return 'book';
}

/**
 * Check if a material type matches the material types in the facets.
 *
 * @param array $facets
 *   The facets of the search results.
 *
 * @param int $total_number
 *   Number of objects
 *
 * @return boolean
 *   True if the material type matches.
 */
function ting_search_context_matches_material_type($facets, $total_number, $type_array) {
   $audio_types = array('lydbog (net)', 'lydbog (cd-mp3)', 'lydbog (cd)');
   $number_of_type = ting_search_context_get_term_count($facets, 'facet.type', $type_array);
   return ting_search_context_evalute_condition($number_of_type , $total_number, 0.5);
}


/**
 * Get audience and fiction/nonfiction.
 *
 * @param int $total_number
 *   Number of objects
 *
 * @return string
 *   The system_contexts context name.
 */
function ting_search_context_get_audience_fiction($facets) {
  $adult = ting_search_context_is_adult($facets);
  $fiction = ting_search_context_is_fiction($facets);
  if ($adult &&  $fiction)
    return 'voksen_skøn';
  else if ($adult &&  !$fiction)
    return 'voksen_fag';
  else if (!$adult &&  $fiction)
    return 'børne_skøn';
  else if (!$adult &&  !$fiction)
    return 'børne_fag';
}

/**
 * Get audience
 *
 * @param array $facets
 *   The facets of the search results.
 *
 * @return bolean
 *   True if adult.
 */
function ting_search_context_is_adult($facets) {
   $number_of_adult = ting_search_context_get_term_count($facets, 'facet.category',  array('voksenmaterialer'));
   $number_of_children = ting_search_context_get_term_count($facets, 'facet.category', array('børnematerialer'));
   return ($number_of_adult > $number_of_children );
}

/**
 * Get Fiction/nonfiction
 *
 * @param array $facets
 *   The facets of the search results.
 *
 * @return bolean
 *   True if fiction.
 */
function ting_search_context_is_fiction($facets) {
   $number_of_fiction = ting_search_context_get_term_count($facets, 'facet.genreCategory',  array('fiktion'));
   $number_of_nonfiction = ting_search_context_get_term_count($facets, 'facet.genreCategory', array('nonfiktion'));
   return ($number_of_fiction > $number_of_nonfiction );
}

/**
 * Check if a subject context matches the search result
 *
 * @param array $facets
 *   The facets of the search results.
 *
 * @param array $subject_contexts
 *   The search contexts.
 *
 * @param string $type
 *   The system context type.
 *
 * @return mixed
 *   The context object i there is a matching context. Else null
 *
 */
function ting_search_context_check_subject_contexts($facets, $subject_contexts, $type) {
  $index = ting_search_context_get_subject_index_by_type($type);
  $top_term_count = 0;
  $top_context = null;
  foreach ($subject_contexts as $context) {
    if (isset($context->subject)) {
      $context->subject = preg_replace('/\s+/', '', $context->subject);
      $subjects= explode(',', $context->subject);
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
 * Get the relevant index name for a given system context type
 *
 * @param string $type
 *   The system context type.
 *
 * @return string
 *   The name of the index.
 *
 */
function ting_search_context_get_subject_index_by_type($type) {
  $indexes = array (
    'film' => 'subject',
    'musik' => 'subject',
    'lydbøger' => 'subject',
    'voksen_skøn' => 'fictionSubject',
    'voksen_fag' => 'subject',
    'børne_skøn' => 'fictionSubject',
    'børne_fag' => 'subject',
  );
  return 'facet.' . $indexes[$type];
}


/**
 * Helper function to get the number of term_names which match the top 3 term in the relevant facet.
 *
 * @param array $facets
 *   The facets of the search results.
 *
 * @param string $facets_name
 *   The name of the facet to use.
 *
 * @param array $term_names
 *   The term names to evaluate.
 *
 * @return int
 *   The sum of the matched terms.
 *
 */
function ting_search_context_get_top_term_count($facets, $facet_name, $term_names = array()) {
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
 * Helper function to get the number of term_names which match the relevant facet terms.
 *
 * @param array $facets
 *   The facets of the search results.
 *
 * @param string $facets_name
 *   The name of the facet to use.
 *
 * @param array $term_names
 *   The term names to evaluate.
 *
 * @return int
 *   The sum of the matched terms.
 *
 */
function ting_search_context_get_term_count($facets, $facet_name, $term_names = array()) {
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
 *
 * @param int $total_number
 *   Total number.
 *
 * @param double $pass_ratio
 *   The ratio which is has to be exceeded.
 *
 * @return bolean
 *   True if ratio is exceeded.
 *
 */
function ting_search_context_evalute_condition($number_of_terms, $total_number, $pass_ratio) {
  if ($total_number != 0) {
  $term_ratio = $number_of_terms/$total_number;
  return ($term_ratio >  $pass_ratio);
  } else {
    return false;
  }
}

