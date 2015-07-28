<?php
/**
 * @file
 * This file implements support for drush into the module.
 *
 * Adds support to generate the colors css file after a theme update.
 */

/**
 * Implements hook_drush_command().
 */
function ding_base_drush_command() {
  return array(
    'css-generate' => array(
      'description' => dt('Generates the current themes color css file.'),
      'arguments' => array(),
      'options' => array(),
      'aliases' => array('cgen'),
      'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    ),
  );
}

/**
 * Regenerate color stylesheet base on current theme.
 */
function drush_ding_base_css_generate() {
  ding_base_rewrite_color_stylesheet();
}
