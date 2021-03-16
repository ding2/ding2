<?php

/**
 * @file
 * Ding DDBasic opening hours pages.
 */

/**
 * Callback for fetching a week of opening hours.
 *
 * @param object $node
 *   Current node object.
 * @param string $from
 *   Period start.
 * @param string $to
 *   Period end.
 * @param string|null $categories
 *   Categories, if more than 1 - items are imploded.
 *
 * @return array
 *   Ajax command.
 */
function ding_ddbasic_opening_hours_week_callback($node, $from, $to, $categories = NULL) {
  $commands = [];

  if (opening_hours_present_on_node($node->nid) && !empty($categories)) {
    $categories = explode('|', $categories);
  }

  $tmp = theme('ding_ddbasic_opening_hours_week', [
    'node' => $node,
    'timespan' => [$from, $to],
    'categories' => $categories,
  ]);

  // Note that we trim the output, so Drupal doesn't add the surrounding div
  // elements.
  $commands[] = ajax_command_replace('.opening-hours-week-' . $node->nid, trim($tmp));

  return ['#type' => 'ajax', '#commands' => $commands];
}
