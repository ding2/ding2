<?php

function ting_search_context_calculate_context($facets, $numTotalObjects) {
  $contexts = ting_search_context_get_all_contexts();
  //file_put_contents("/home/quickstart/work/debug/debugcontexts.txt", print_r($contexts , TRUE), FILE_APPEND);
 
  $system_type = ting_search_context_get_material_type($facets, $numTotalObjects);
  //file_put_contents("/home/quickstart/work/debug/debugcontexts2.txt", print_r($material_type , TRUE), FILE_APPEND);
  if ($system_type == 'book') {
    $system_type = ting_search_context_get_audience_fiction($facets, $total_number); 
  }
  $age_group = ting_search_context_get_age_group($facets);
  if ($age_group == 'children') {
    return ting_search_context_get_children_genres($facets);;
  } else {
    $genre_category = ting_search_context_get_genre_category($facets);
    if ($genre_category == 'fiction') {
      return ting_search_context_get_fiction_genres($facets);
    } else if ($genre_category == 'nonfiction') {
      return ting_search_context_get_non_fiction_genres($facets);
    } 
  }
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

function ting_search_context_get_detail_genre($facets, $genres, $facet_name, $default_value) {
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
  } else {
    return $default_value;
  }
}

function ting_search_context_get_top_term_count($facets, $facet_name, $term_names = array()) {
  $number_of_terms = 0;
  if (isset($facets[$facet_name])) {
    $top_terms = array_slice($facets[$facet_name]->terms, 0, 3);
    foreach ($top_terms as $top_term => $term) {
      if (in_array($top_term, $term_names)) {
        $number_of_terms = $term;
        break;
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

