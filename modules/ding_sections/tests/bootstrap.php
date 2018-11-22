<?php

/**
 * @file
 * Bootstraping PHPUnit.
 */

// @codingStandardsIgnoreStart
/**
 * Reseting states between tests run.
 */
function resetState($lms_url) {
  @file_get_contents($lms_url . '/reset.php');
}
// @codingStandardsIgnoreEnd