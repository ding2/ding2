<?php
/**
 * @file
 * Hooks provided by the Opensearch module.
 */

/**
 * Allow other modules to alter the cache_key.
 *
 * Alter is done before saving and fetching results from the opensearch_cache.
 *
 * Please ensure that this is as fast as possible. So use the drupal_fast_static
 * method as this will be called for earch search request.
 *
 * @param string $cid
 *   The cache key that can be altered.
 * @param \TingClientSearchRequest $request
 *   The current request object.
 */
function hook_opensearch_cache_key_alter(&$cid, $request) {
  // Determine context.
  $context = 'search';

  // Modify cache key based on some context.
  if ($context === 'search') {
    $cid .= ':module';
  }
}

/**
 * Set additional parameters to ting request.
 *
 * @param object $request
 *   The Ting request.
 *
 * @return array
 *   Array containing key=>value pairs. Key is the name of the parameter.
 */
function hook_opensearch_pre_execute($request) {
  // In case you need to add additional parameters to request.
  return array('includeMarcXchange' => TRUE);
}

/**
 * Set extra properties to resulting object.
 *
 * @param object $request
 *   ting_execute request.
 * @param object $response
 *   ting_execute result.
 * @param object $raw_response
 *   Raw response from ting.
 *
 * @return array
 *   Array containing key=>value pairs. Key is the name of the property.
 */
function hook_opensearch_post_execute($request, $response, $raw_response) {
  // Add additional property to resulting object.
  return array('marcexchange' => array('marcxchange data'));
}
