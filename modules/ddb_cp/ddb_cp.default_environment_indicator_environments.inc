<?php
/**
 * @file
 * ddb_cp.default_environment_indicator_environments.inc
 */

/**
 * Implements hook_default_environment_indicator_environment().
 */
function ddb_cp_default_environment_indicator_environment() {
  $export = array();

  $environment = new stdClass();
  $environment->disabled = FALSE; /* Edit this to true to make a default environment disabled initially */
  $environment->api_version = 1;
  $environment->machine = 'default';
  $environment->name = 'Default';
  $environment->regexurl = '.*';
  $environment->settings = array(
    'color' => '#ff2a2a',
    'text_color' => '#ffffff',
    'weight' => '3',
    'position' => 'top',
    'fixed' => 0,
  );
  $export['default'] = $environment;

  $environment = new stdClass();
  $environment->disabled = FALSE; /* Edit this to true to make a default environment disabled initially */
  $environment->api_version = 1;
  $environment->machine = 'development';
  $environment->name = 'Development';
  $environment->regexurl = '.*-dev.ddbcms.dk';
  $environment->settings = array(
    'color' => '#336699',
    'text_color' => '#ffffff',
    'weight' => '1',
    'position' => 'top',
    'fixed' => 0,
  );
  $export['development'] = $environment;

  $environment = new stdClass();
  $environment->disabled = FALSE; /* Edit this to true to make a default environment disabled initially */
  $environment->api_version = 1;
  $environment->machine = 'staging';
  $environment->name = 'Staging';
  $environment->regexurl = '.*-stg.ddbcms.dk';
  $environment->settings = array(
    'color' => '#c48000',
    'text_color' => '#ffffff',
    'weight' => '2',
    'position' => 'top',
    'fixed' => 0,
  );
  $export['staging'] = $environment;

  return $export;
}
