<?php

function get_search_context($facets, $numTotalObjects) {
  $bib_zoom_count = $number_of_library_materials = get_term_count($facets, 'facet.acSource', array('bibzoom (album)')); 
  $numTotalObjects = $numTotalObjects - $bib_zoom_count;
  //file_put_contents("/home/quickstart/work/debug/debugsearchcontext1.txt", print_r($facets , TRUE), FILE_APPEND);
  $material_type = get_material_type($facets, $numTotalObjects);
  if ($material_type != 'book') {
    return $material_type; 
  }
  $age_group = get_age_group($facets);
  if ($age_group == 'children') {
    return get_children_genres($facets);;
  } else {
    $genre_category = get_genre_category($facets);
    if ($genre_category == 'fiction') {
      //file_put_contents("/home/quickstart/work/debug/debugsearchcontext9.txt", print_r(get_fiction_genres($facets) . ' ', TRUE), FILE_APPEND);
      return get_fiction_genres($facets);
    } else if ($genre_category == 'nonfiction') {
      return get_non_fiction_genres($facets);
    } 
  }

}

function get_material_type($facets, $total_number) {
  if (is_films($facets, $total_number))
    return 'film';
  else if (is_music($facets, $total_number))
    return 'music';
  else
    return 'book';
}

function is_films($facets, $total_number) {
   $film_types = array('film (net)', 'dvd', 'blue-ray');
   $number_of_films = get_term_count($facets, 'facet.type', $film_types);
   return evalute_condition($number_of_films, $total_number, 0.5);
}


function is_music($facets, $total_number) {
   $music_types = array('cd (musik)', 'grammofonplade', 'node');
   $number_of_music = get_term_count($facets, 'facet.type', $music_types );
   $number_of_library_materials = get_term_count($facets, 'facet.acSource', array('bibliotekets materialer'));
   return evalute_condition($number_of_music, $number_of_library_materials, 0.5);
}

function get_age_group($facets) {
   $number_of_adult = get_term_count($facets, 'facet.category',  array('voksenmaterialer'));
   $number_of_children = get_term_count($facets, 'facet.category', array('børnematerialer'));
   //file_put_contents("/home/quickstart/work/debug/debugsearchcontext6.txt", print_r($number_of_adult . ' ' . $number_of_children . ' : ', TRUE), FILE_APPEND);
   return ($number_of_adult > $number_of_children ) ? 'adult' : 'children';
}

function get_genre_category($facets) {
  $top_number_of_fiction = 0;
  $top_number_of_non_fiction = 0;
  if (isset($facets['facet.fiction']) && is_array($facets['facet.fiction']->terms)) {
    $top_number_of_fiction = reset($facets['facet.fiction']->terms);
  }
  if (isset($facets['facet.nonFiction']) && is_array($facets['facet.nonFiction']->terms)) {
    $top_number_of_non_fiction = reset($facets['facet.nonFiction']->terms);
  }
  //file_put_contents("/home/quickstart/work/debug/debugsearchcontext8.txt", print_r($top_number_of_fiction . ' ' . $top_number_of_non_fiction . ' : ', TRUE), FILE_APPEND);
  return ($top_number_of_fiction > $top_number_of_non_fiction ) ? 'fiction' : 'nonfiction';
}

function get_fiction_genres($facets) {
  $fiction_genres = array(
    'krimi' => array('krimi'),
    'kærlighed' => array('kærlighed', 'erotik', 'sex'),
    'fantasy' => array('science fiction', 'fantasy'),
  );
  return get_detail_genre($facets, $fiction_genres, 'facet.fiction', 'fiction');
}

function get_non_fiction_genres($facets) {
  $fiction_genres = array(
    'haver' => array('haver'),
    'kogebøger' => array('slankeretter', 'ernæring', 'diætretter', 'vegetarretter', 'kost'),
  );
  return get_detail_genre($facets, $fiction_genres, 'facet.nonFiction', 'nonfiction');
}

function get_children_genres($facets) {
  $fiction_genres = array(
    'piger' => array('piger'),
    'drenge' => array('drenge'),
  );
  return get_detail_genre($facets, $fiction_genres, 'facet.fiction', 'children');
}

function get_detail_genre($facets, $genres, $facet_name, $default_value) {
  $top_genre_count = 0;
  $top_genre_name = '';
  foreach ($genres as $genre_name => $genre) {
    $genre_count = get_top_term_count($facets, $facet_name, $genre);
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

function get_top_term_count($facets, $facet_name, $term_names = array()) {
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

function get_term_count($facets, $facet_name, $term_names = array()) {
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

function evalute_condition($number_of_terms, $total_number, $pass_ratio) {
  if ($total_number != 0) {
  $term_ratio = $number_of_terms/$total_number;
  //file_put_contents("/home/quickstart/work/debug/debugsearchcontext4.txt", print_r($number_of_terms  . ' ' . $total_number . ' ' . $pass_ratio . ' ' . $term_ratio . ' | ', TRUE), FILE_APPEND);
  return ($term_ratio >  $pass_ratio);
  } else {
    return false;
  }
}


?>
