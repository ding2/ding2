<?php
/**
 * @file
 * Editorial custom hooks definition.
 */

/**
 * Perform actions after the node received an editorial action, but before it
 * is saved to database.
 *
 * Allows additional node object alterations.
 *
 * @see ding_dashboard_valid_actions()
 *
 * @param string $action
 *   Action that takes place.
 * @param object $node
 *   Node object that is being altered.
 */
function hook_editorial_status_changed($action, $node) {
  if ($action == 'approve') {
    $node->status = 1;
  }
}
