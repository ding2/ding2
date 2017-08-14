<?php
/**
 * @file
 * Implements handling of loans through OpenRuth.
 */

/**
 * Get a list of material types from the Well.
 *
 * @return string[]
 *   List of material names.
 */
function connie_search_search_material_types() {
  return ['material_type_1', 'material_type_2'];
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
function connie_search_search_object_load(array $ids) {
  // TODO BBS-SAL: return something more usefull when we have a class that is
  // suitable.
  return [];
}
