<?php
/**
 * @file
 * ding_watchdog.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function ding_watchdog_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'watchdog_filtering_deduplicate';
  $strongarm->value = 1;
  $export['watchdog_filtering_deduplicate'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'watchdog_filtering_default_severity';
  $strongarm->value = array(
    0 => '0',
    1 => '1',
    2 => '2',
    3 => '3',
    4 => '4',
  );
  $export['watchdog_filtering_default_severity'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'watchdog_filtering_implementations';
  $strongarm->value = array(
    'dblog' => FALSE,
    'rules' => FALSE,
    'system' => FALSE,
  );
  $export['watchdog_filtering_implementations'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'watchdog_filtering_severity_access%20denied';
  $strongarm->value = FALSE;
  $export['watchdog_filtering_severity_access%20denied'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'watchdog_filtering_severity_actions';
  $strongarm->value = '';
  $export['watchdog_filtering_severity_actions'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'watchdog_filtering_severity_ajax';
  $strongarm->value = FALSE;
  $export['watchdog_filtering_severity_ajax'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'watchdog_filtering_severity_cron';
  $strongarm->value = FALSE;
  $export['watchdog_filtering_severity_cron'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'watchdog_filtering_severity_ding_event';
  $strongarm->value = '';
  $export['watchdog_filtering_severity_ding_event'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'watchdog_filtering_severity_ding_groups';
  $strongarm->value = '';
  $export['watchdog_filtering_severity_ding_groups'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'watchdog_filtering_severity_ding_news';
  $strongarm->value = '';
  $export['watchdog_filtering_severity_ding_news'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'watchdog_filtering_severity_fbs';
  $strongarm->value = '';
  $export['watchdog_filtering_severity_fbs'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'watchdog_filtering_severity_features';
  $strongarm->value = FALSE;
  $export['watchdog_filtering_severity_features'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'watchdog_filtering_severity_i18n_string';
  $strongarm->value = FALSE;
  $export['watchdog_filtering_severity_i18n_string'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'watchdog_filtering_severity_l10n_update';
  $strongarm->value = FALSE;
  $export['watchdog_filtering_severity_l10n_update'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'watchdog_filtering_severity_locale';
  $strongarm->value = FALSE;
  $export['watchdog_filtering_severity_locale'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'watchdog_filtering_severity_menu_block';
  $strongarm->value = FALSE;
  $export['watchdog_filtering_severity_menu_block'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'watchdog_filtering_severity_php';
  $strongarm->value = FALSE;
  $export['watchdog_filtering_severity_php'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'watchdog_filtering_severity_search_api';
  $strongarm->value = '';
  $export['watchdog_filtering_severity_search_api'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'watchdog_filtering_severity_system';
  $strongarm->value = FALSE;
  $export['watchdog_filtering_severity_system'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'watchdog_filtering_severity_ting';
  $strongarm->value = FALSE;
  $export['watchdog_filtering_severity_ting'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'watchdog_filtering_severity_ting%20client';
  $strongarm->value = FALSE;
  $export['watchdog_filtering_severity_ting%20client'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'watchdog_filtering_severity_ting_covers_ddb';
  $strongarm->value = '';
  $export['watchdog_filtering_severity_ting_covers_ddb'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'watchdog_filtering_severity_user';
  $strongarm->value = FALSE;
  $export['watchdog_filtering_severity_user'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'watchdog_filtering_severity_varnish';
  $strongarm->value = FALSE;
  $export['watchdog_filtering_severity_varnish'] = $strongarm;

  return $export;
}
