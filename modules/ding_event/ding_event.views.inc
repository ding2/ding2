<?php

/**
 * @file
 * Provide views data and handler information for ding_event.module.
 */

/**
 * Implements hook_views_data().
 */
function ding_event_views_data() {
  $data['node']['ding_event_date'] = array(
    'title' => t('Ding event date'),
    'help' => t('Date range when the event is active.'),
    'sort' => array(
      'handler' => 'ding_event_handler_sort_ding_event_date',
    ),
  );
  return $data;
}
