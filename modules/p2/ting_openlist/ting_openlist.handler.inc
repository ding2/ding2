<?php

/**
 * @file
 * The provider functions.
 */

/**
 * Make a request to Openlist.
 *
 * This just wraps the ting_openlist_request() function, into the
 * ding_provider way of life.
 *
 * @param string $function
 *   Function name of the function to call on the service.
 * @param array $arguments
 *   Numerical array with the arguments, in their respectable order.
 * @param bool $detailed_log
 *   If set to true, the arguments send is logged by watchdog, if logging is
 *   active.
 *
 * @return mixed
 *   The Openlist request.
 */
function ting_openlist_handler_request($function, array $arguments, $detailed_log = FALSE) {
  return ting_openlist_request($function, $arguments, $detailed_log);
}
