<?php
/**
 * @file
 * Contains all pages callback and related functions.
 */

/**
 * Page callback for processing and generating ICS file based on GET params.
 */
function ding_event_subscriptions_callback() {
  $output = '';
  $params = drupal_get_query_parameters();
  $events = ding_event_subscriptions_get_events($params);
  $output .= theme('ding_event_subscriptions_ics', array('events' => $events));

  header('Content-type: text/calendar; charset=utf-8');
  header('Content-Disposition: inline; filename=calendar.ics');

  echo $output;
  exit;
}
