<?php
/**
 * @file
 * ding_frontend.features.block_access.inc
 */

/**
 * Implements hook_block_access_defaults().
 */
function ding_frontend_block_access_defaults() {
  $block_access = array();

  // Exported Block Access settings for module block
  $block_access['block'] = array();

  return $block_access;
}
