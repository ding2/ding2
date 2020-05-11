<?php
/**
 * @file
 * Autocomplete functionality for ting reference related to cover upload.
 */

/**
 * Add autocomplete functionality to textfield.
 * @see ddb_cover_upload_material().
 *
 * @param string $string
 *   A string provided through input text field.
 *
 * @throws \DingProviderDoesntImplement
 *   The provider doesn't implement the given function.
 * @throws \DingProviderNoProvider
 *   No provider is configured for the given provider.
 */
function _cover_upload_search_autocomplete(string $string) {
  $matches = array();

  // Only use auto-complete if more that 3 chars have been written.
  if ($string && (strlen($string) > 3)) {
    // Let the provider build a query if it knows how to.
    if (ding_provider_implements('search', 'prepare_reference_query')) {
      $query = ding_provider_invoke('search', 'prepare_reference_query', $string);
    }
    else {
      // Else fall back to a standard free text search.
      $query = ting_start_query()->withFullTextQuery($string);
    }

    // Set limit and execute.
    $result = $query->withCount(10)->execute();

    // If there is no usable result, exit immediately, providing no reply.
    if ($result && $result->getNumTotalObjects()) {
      foreach ($result->getTingEntityCollections() as $entity_collection) {
        $object = $entity_collection->getTingObjectCollection()->getPrimaryObject();
        $matches[$entity_collection->id] = t('!title (!type, !year, !id)', array(
          '!title' => $object->getShortTitle() ?: '',
          '!type' => $object->getType() ?: '',
          '!year' => $object->getYear(),
          '!id' => $object->getSourceId(),
        ));
      }
    }
    else {
      $matches[$string] = t('No matches found');
    }
  }

  // Return the result as JSON.
  drupal_json_output($matches);
}
