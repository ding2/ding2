<?php

/**
 * @file
 * Bootstraping tests.
 */

/**
 * Reset state.
 *
 * @param string $lms_url
 *   LMS url.
 */
function resetState($lms_url) {
  @file_get_contents($lms_url . '/reset.php');
}
