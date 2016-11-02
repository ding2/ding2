<?php

/**
 * Callback for fetching a week of opening hours.
 */
function ding_ddbasic_opening_hours_week_callback($node, $from, $to) {
  $commands = array();

  $GLOBALS['ddbasic_opening_hours_week_timespan'] = array($from, $to);

  if (opening_hours_present_on_node($node->nid)) {
    $tmp = theme('opening_hours_week', array('node' => $node));
  }

  // Note that we trim the output, so Drupal doesn't add the surrounding div
  // elements.
  $commands[] = ajax_command_replace('.opening-hours-week-' . $node->nid, trim($tmp));

  return array('#type' => 'ajax', '#commands' => $commands);
}
