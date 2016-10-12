<?php

/**
 * @file
 * This module provides serendipity functions based on user lists and loans
 */
 
/**
 * Implements hook_serendipity_info().
 */
function ding_entity_rating_serendipity_info() {
  return array(
    'materials_by_rating' => array(
      'title' => 'Materials by ratings',
      'description' => 'Get materials based on users ratings',
      'keys' => array('ting_object', 'frontpage'),
    ),
  );
}

/**
 * Ding ratings serendipity function.
 *
 * Select random objects depending on previously rated objects.
 *
 * @param array $context
 *   Serendipity context.
 *
 * @return array
 *   A serendipity results array.
 */
function ding_entity_rating_materials_by_rating_serendipity_add(array $context) {
  global $user;
  // TODO why do we return an empty array is we are not on the frontpage? @MSD
  if (!$context['frontpage'] || !ding_user_is_provider_user($user)) {
    return array();
  }

  $results = array();
  if (!isset($context['interest'])) {
    // Fetch random rated element.
    $ting_object = ding_entity_rating_get_material_by_rating();
  }
  else {
    // Get entity from context.
    // TODO what if rated_entity is not defined within the context? @MSD
    $ting_object = ding_entity_load($context['rated_entity'], 'ting_object');
  }
  
  if (!empty($ting_object) && is_object($ting_object)) {
    $facets = array();

    // Extract subjects.
    $subject = $ting_object->getSubjects();
    foreach ($subject as & $facet) {
      $facets[] = 'facet.subject="' . $facet . '"';
    }

    // Build author array.
    if (count($facets) == 0) {
      $authors = $ting_object->getCreators();
      foreach ($authors as $author) {
        $facets[] = 'facet.creator="' . $author . '"';
      }
    }

    // Search with only subjects.
    $query = implode(' OR ', $facets);

    if (empty($query)) {
      return array();
    }
    
    $results = ding_serendipity_do_search($query, array());

    foreach ($results as & $item) {
      $item['info'] = array(
        // TODO is it intentional that Query is uppercase? @MSD
        'Query' => $query,
        'description' => t(
          'Because you liked !item',
          array('!item' => $ting_object->getTitle())
        ),
      );
    }
  }
  
  return $results;
}

/**
 * Get a material from the users ratings.
 *
 * The objects are sorted by the rating.
 * The entity is selected randomly from the highest rating group.
 *
 * @return object
 *   Ting object entity.
 */
function ding_entity_rating_get_material_by_rating() {
  // Load rating list.
  $list = ding_list_get_list(DING_ENTITY_RATING_LIST);
  
  // Load elements.
  $elements = ding_list_load_elements($list);
  if (empty($elements)) {
    return NULL;
  }
  
  // Order elements by rating.
  $ratings = array();
  foreach ($elements as $key => $element) {
    $weight = ding_list_get_list_element_weight($element);
    $ratings[$weight][] = $element;
  }
  
  // Start at 5 (the max rating).
  // being the max rating in the codebase.
  $rating = DING_ENTITY_RATING_MAX_RATING;
  // And keep trying till this minimum rating.
  $min_rating = 3;

  // Fetch a rated element from the group of highest rated elements.
  $rated_element = NULL;
  while (is_null($rated_element) && $rating >= $min_rating) {
    if (!empty($ratings[$rating])) {
      $random_key = array_rand($ratings[$rating]);
      $rated_element = $ratings[$rating][$random_key];
      break;
    }
    
    $rating -= 1;
  }

  // Load and return the element if any.
  if (is_object($rated_element)) {
    $entity_id = ding_list_get_list_element_value($rated_element);
    return ding_entity_load($entity_id);
  }
  return NULL;
}
