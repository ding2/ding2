<?php

/**
 * @file
 * This module provides serendipity functions based on user lists and loans.
 */

use Ting\Search\BooleanStatementGroup;
use Ting\Search\BooleanStatementInterface;
use Ting\Search\TingSearchCommonFields;
use Ting\Search\TingSearchFieldFilter;

/**
 * Implements hook_serendipity_info().
 */
function ding_entity_rating_serendipity_info() {
  return array(
    'materials_by_rating' => array(
      'title' => t('Materials by ratings'),
      'description' => t('Get materials based on author or subject from users top rated materials'),
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
  // TODO why do we return an empty array is we are not on the frontpage? @MSD.
  if (!$context['frontpage'] || !ding_user_is_provider_user($user)) {
    return array();
  }

  $results = array();
  if (!isset($context['interest'])) {
    // Fetch random high rated element.
    $rnd_id = ding_entity_rating_get_highly_rated_material_id();
    $ting_object = ding_entity_load($rnd_id);
  }
  else {
    // Get entity from context.
    // TODO what if rated_entity is not defined within the context? @MSD.
    $ting_object = ding_entity_load($context['rated_entity'], 'ting_object');
  }

  if (!empty($ting_object) && is_object($ting_object)) {
    $facets = array();

    $field_filters = [];
    // Extract subjects, add them as filters.
    $subject = $ting_object->getSubjects();
    foreach ($subject as & $facet) {
      $field_filters[] = new TingSearchFieldFilter(TingSearchCommonFields::SUBJECT, $facet);
    }

    // Build author array, add them as filters.
    if (count($facets) == 0) {
      $authors = $ting_object->getCreators();
      foreach ($authors as $author) {
        $field_filters[] = new TingSearchFieldFilter(TingSearchCommonFields::AUTHOR, $author);
      }
    }

    // Perform a search for materials with any of the subjects or authors.
    $query = ting_start_query()->withFilters($field_filters, BooleanStatementInterface::OP_OR);

    if (empty($query)) {
      return array();
    }

    $results = ding_serendipity_do_search($query);

    foreach ($results as & $item) {
      $item['info'] = array(
        // TODO is it intentional that Query is uppercase? @MSD.
        'Query' => $query,
        'description' => t(
          'Because you liked !item',
          array(
            '!item' => l(
              $ting_object->getTitle(),
              entity_uri('ting_object', $ting_object)['path']
            ),
          )
        ),
      );
    }
  }

  return $results;
}

/**
 * Get a random high rated material from the users ratings.
 *
 * The objects are sorted by the rating.
 * The entity is selected randomly from materials rated 4 or 5 stars.
 *
 * @return string|null
 *   Ting object id or NULL if this does not exist.
 */
function ding_entity_rating_get_highly_rated_material_id() {

  // Load rating list.
  $list = ding_list_get_list(DING_ENTITY_RATING_LIST);

  // Lower limit for high rating definition.
  $min_rating = 4;

  // Filter non high rated materials away.
  $ratings = array();
  foreach ($list->getElements() as $element) {

    if ($element->getData('weight', 0) < $min_rating) {
      continue;
    }

    $ratings[] = $element;
  }

  // No high ratings available.
  if (count($ratings) == 0) {
    return NULL;
  }

  // Fetch random element.
  $random_key = array_rand($ratings);
  $rated_element = $ratings[$random_key];

  if (!empty($rated_element->getValue())) {
    return $rated_element->getValue();
  }
  return NULL;
}
