<?php
/**
 * @file
 * ding_base.default_environment_indicator_environments.inc
 */

/**
 * Implements hook_default_environment_indicator_environment().
 */
function ding_base_default_environment_indicator_environment() {
  $export = array();

  $environment = new stdClass();
  $environment->disabled = FALSE; /* Edit this to true to make a default environment disabled initially */
  $environment->api_version = 1;
  $environment->machine = 'prod';
  $environment->name = 'Production';
  $environment->regexurl = '.*';
  $environment->settings = array(
    'color' => '#000000',
    'text_color' => '#ffffff',
    'weight' => '3',
    'position' => 'top',
    'fixed' => 0,
  );
  $export['prod'] = $environment;

  $environment = new stdClass();
  $environment->disabled = FALSE; /* Edit this to true to make a default environment disabled initially */
  $environment->api_version = 1;
  $environment->machine = 'stg';
  $environment->name = 'Staging';
  $environment->regexurl = '.*.stg.easysuite.dk';
  $environment->settings = array(
    'color' => '#c48000',
    'text_color' => '#ffffff',
    'weight' => '2',
    'position' => 'top',
    'fixed' => 0,
  );
  $export['stg'] = $environment;

  $environment = new stdClass();
  $environment->disabled = FALSE; /* Edit this to true to make a default environment disabled initially */
  $environment->api_version = 1;
  $environment->machine = 'dev';
  $environment->name = 'Development';
  $environment->regexurl = '.*.dev.easysuite.dk';
  $environment->settings = array(
    'color' => '#336699',
    'text_color' => '#ffffff',
    'weight' => '1',
    'position' => 'top',
    'fixed' => 0,
  );
  $export['dev'] = $environment;

  return $export;
}
