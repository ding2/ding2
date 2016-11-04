<?php
/**
 * @file
 * Ding DDBasic opening hours pages.
 */

/**
 * Callback for fetching a week of opening hours.
 */
function ding_ddbasic_opening_hours_week_callback($node, $from, $to, $categories) {
  $commands = array();

  if (opening_hours_present_on_node($node->nid)) {
    if (!empty($categories)) {
      $categories = explode('|', $categories);
    }

    $tmp = theme('ding_ddbasic_opening_hours_week', array(
      'node' => $node,
      'timespan' => array($from, $to),
      'categories' => $categories,
    ));
  }

  // Note that we trim the output, so Drupal doesn't add the surrounding div
  // elements.
  $commands[] = ajax_command_replace('.opening-hours-week-' . $node->nid, trim($tmp));

  return array('#type' => 'ajax', '#commands' => $commands);
}
