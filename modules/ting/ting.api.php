<?php
/**
 * @file
 * Hooks provided by the Ting module.
 */

/**
 * Set additional parameters to ting request.
 *
 * @param object $request
 *   ting_execute request.
 *
 * @return array
 *   Array containing key=>value pairs. Key is the name of the parameter.
 */
function hook_ting_pre_execute($request) {
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
function hook_ting_post_execute($request, $response, $raw_response) {
  // Add additional property to resulting object.
  return array('marcexchange' => array('marcxchange data'));
}

/**
 * Allow other modules to alter the cache_key before saving and fetching results
 * from the ting_cache.
 *
 * Since hook_ting_pre_execute and hook_ting_post_execute is not run for cached
 * requests, we need this hook to give other modules, that doesn't always alter
 * the request in the same way, a chance to modify the cache key. This enables
 * the ting_cache system to differentiate and use the correct results from the
 * ting_cache bin.
 *
 * @param string $cid.
 *   The cache key that can be altered.
 */
function hook_ting_cache_key(&$cid) {
  // Determine context.
  $context = 'search';

  // Modify cache key based on some context.
  if ($context == 'search') {
    $cid .= ':module';
  }
}
