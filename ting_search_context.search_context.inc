<?php

function ting_search_context_calculate_context($facets, $numTotalObjects) {
  $contexts = ting_search_context_get_all_contexts();
  file_put_contents("/home/quickstart/work/debug/debugcontexts.txt", print_r($contexts , TRUE), FILE_APPEND);
 
  $system_type = ting_search_context_get_material_type($facets, $numTotalObjects);
  //file_put_contents("/home/quickstart/work/debug/debugcontexts2.txt", print_r($material_type , TRUE), FILE_APPEND);
  if ($system_type == 'book') {
    $system_type = ting_search_context_get_audience_fiction($facets, $numTotalObjects); 
  }
  file_put_contents("/home/quickstart/work/debug/debugcontexts2.txt", print_r($system_type  , TRUE), FILE_APPEND);
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
  file_put_contents("/home/quickstart/work/debug/debugcontexts3.txt", print_r($subject_contexts , TRUE), FILE_APPEND);
  file_put_contents("/home/quickstart/work/debug/debugcontexts4.txt", print_r($system_context , TRUE), FILE_APPEND);
  $subject_context = ting_search_context_check_subject_contexts($facets, $subject_contexts, $system_context->context); 
  file_put_contents("/home/quickstart/work/debug/debugcontexts15.txt", print_r($subject_context , TRUE), FILE_APPEND);

}

function ting_search_context_get_material_type($facets, $total_number) {
  if (ting_search_context_is_films($facets, $total_number))
    return 'film';
  else if (ting_search_context_is_music($facets, $total_number))
    return 'musik';
  else if (ting_search_context_is_audio_book($facets, $total_number))
    return 'lydbøger';
  else
    return 'book';
}

function ting_search_context_is_audio_book($facets, $total_number) {
   $audio_types = array('lydbog (net)', 'lydbog (cd-mp3)', 'lydbog (cd)');
   $number_of_audio = ting_search_context_get_term_count($facets, 'facet.type', $audio_types);
   return ting_search_context_evalute_condition($number_of_audio , $total_number, 0.5);
}

function ting_search_context_is_films($facets, $total_number) {
   $film_types = array('film (net)', 'dvd', 'blue-ray');
   $number_of_films = ting_search_context_get_term_count($facets, 'facet.type', $film_types);
   return ting_search_context_evalute_condition($number_of_films, $total_number, 0.5);
}

function ting_search_context_is_music($facets, $total_number) {
   $music_types = array('cd (musik)', 'grammofonplade', 'node');
   $number_of_music = ting_search_context_get_term_count($facets, 'facet.type', $music_types );
   return ting_search_context_evalute_condition($number_of_music, $total_number, 0.5);
}

function ting_search_context_get_audience_fiction($facets, $total_number) {
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

function ting_search_context_is_adult($facets) {
   $number_of_adult = ting_search_context_get_term_count($facets, 'facet.category',  array('voksenmaterialer'));
   $number_of_children = ting_search_context_get_term_count($facets, 'facet.category', array('børnematerialer'));
   return ($number_of_adult > $number_of_children );
}

function ting_search_context_is_fiction($facets) {
   $number_of_fiction = ting_search_context_get_term_count($facets, 'facet.genreCategory',  array('fiktion'));
   $number_of_nonfiction = ting_search_context_get_term_count($facets, 'facet.genreCategory', array('nonfiktion'));
   return ($number_of_fiction > $number_of_nonfiction );
}

function ting_search_context_check_subject_contexts($facets, $subject_contexts, $type) {
  $index = ting_search_context_get_subject_index_by_type($type);
  $top_term_count = 0;
  $top_context = null;
  file_put_contents("/home/quickstart/work/debug/debugcontexts5.txt", print_r($index , TRUE), FILE_APPEND);
  foreach ($subject_contexts as $context) {
    if (isset($context->subject)) {
      $context->subject = preg_replace('/\s+/', '', $context->subject);
      $subjects= explode(',', $context->subject); 
    file_put_contents("/home/quickstart/work/debug/debugcontexts8.txt", print_r($subjects , TRUE), FILE_APPEND);
      $term_count = ting_search_context_get_top_term_count($facets, $index, $subjects);
      // Check if the current context is a better match than the previous.
      file_put_contents("/home/quickstart/work/debug/debugcontexts6.txt", print_r($term_count, TRUE), FILE_APPEND);
       file_put_contents("/home/quickstart/work/debug/debugcontexts7.txt", print_r($top_term_count, TRUE), FILE_APPEND);
      if ($term_count > $top_term_count) {
        $top_term_count = $term_count;
        $top_context = $context;
      }
    }
  }
  return $top_context;
}

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

function ting_search_context_get_fiction_genres($facets) {
  $fiction_genres = array(
    'krimi' => array('krimi'),
    'kærlighed' => array('kærlighed', 'erotik', 'sex'),
    'fantasy' => array('science fiction', 'fantasy'),
  );
  return ting_search_context_get_detail_genre($facets, $fiction_genres, 'facet.fictionSubject', 'fiction');
}

function ting_search_context_get_non_fiction_genres($facets) {
  $fiction_genres = array(
    'haver' => array('haver'),
    'kogebøger' => array('slankeretter', 'ernæring', 'diætretter', 'vegetarretter', 'kost'),
  );
  return ting_search_context_get_detail_genre($facets, $fiction_genres, 'facet.nonFictionSubject', 'nonfiction');
}

function ting_search_context_get_children_genres($facets) {
  $fiction_genres = array(
    'piger' => array('piger'),
    'drenge' => array('drenge'),
  );
  return ting_search_context_get_detail_genre($facets, $fiction_genres, 'facet.fictionSubject', 'children');
}

function ting_search_context_get_detail_genre($facets, $genres, $facet_name) {
  $top_genre_count = 0;
  $top_genre_name = '';
  foreach ($genres as $genre_name => $genre) {
    $genre_count = ting_search_context_get_top_term_count($facets, $facet_name, $genre);
    if ($genre_count > $top_genre_count) {
      $top_genre_count = $genre_count;
      $top_genre_name = $genre_name;
    }
  }
  if ($top_genre_count > 0) {
    return $top_genre_name;
  } 
}

function ting_search_context_get_top_term_count($facets, $facet_name, $term_names = array()) {
  $number_of_terms = 0;
  file_put_contents("/home/quickstart/work/debug/debugcontexts10.txt", print_r($facets, TRUE), FILE_APPEND);
  file_put_contents("/home/quickstart/work/debug/debugcontexts11.txt", print_r($term_names, TRUE), FILE_APPEND);
  file_put_contents("/home/quickstart/work/debug/debugcontexts14.txt", print_r($facet_name, TRUE), FILE_APPEND);
  if (isset($facets[$facet_name])) {
    $top_terms = array_slice($facets[$facet_name]->terms, 0, 3);
    file_put_contents("/home/quickstart/work/debug/debugcontexts12.txt", print_r($top_terms, TRUE), FILE_APPEND);
    foreach ($top_terms as $top_term => $term) {
      file_put_contents("/home/quickstart/work/debug/debugcontexts9.txt", print_r($top_term, TRUE), FILE_APPEND);
      if (in_array($top_term, $term_names)) {
        $number_of_terms += $term;
      }
    }
  }
  return $number_of_terms;
}

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

function ting_search_context_evalute_condition($number_of_terms, $total_number, $pass_ratio) {
  if ($total_number != 0) {
  $term_ratio = $number_of_terms/$total_number;
  return ($term_ratio >  $pass_ratio);
  } else {
    return false;
  }
}

