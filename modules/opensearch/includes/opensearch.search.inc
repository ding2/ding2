<?php
/**
 * @file
 * Implements handling of loans through OpenRuth.
 */

use OpenSearch\OpenSearchTingObject;

/**
 * Get a list of material types from the Well.
 */
function opensearch_search_material_types() {
  // Get a list of types by executing a null query and look at the facets
  // result.
  $options = [
    'facets' => ['facet.type'],
    'numFacets' => 99,
    'reply_only' => TRUE,
    'sort' => 'random',
  ];
  module_load_include('client.inc', 'ting');
  // TODO: search via the abstraction-layer (to be implemented).
  $result = ting_do_search("*", 0, 0, $options);

  $types = [];
  foreach ($result->facets['facet.type']->terms as $term => $count) {
    $types[drupal_strtolower($term)] = $count;
  }

  return $types;
}

/**
 * Load objects from Open Search.
 *
 * @param string[] $ids
 *   Array of ids to load from Open Search.
 *
 * @return Ting\TingObjectInterface[]
 *   An array of loaded objects.
 */
function opensearch_search_object_load(array $ids) {
  $objects = ting_get_objects($ids);
  foreach ($objects as $id => $object) {
    if (!empty($object)) {
      $objects[$id] = new OpenSearchTingObject($object);
    }
  }
  return $objects;
}
