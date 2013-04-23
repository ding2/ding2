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
  return array('param_name' => 'value');
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
 * Array containing key=>value pairs. Key is the name of the property.
 */
function hook_ting_post_execute($request, $response, $raw_response) {
  return array('property name' => 'property value');
}
