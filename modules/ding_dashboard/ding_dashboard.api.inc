<?php
/**
 * @file
 * Editorial custom hooks definition.
 */

/**
 * Allows additional node object alterations.
 *
 * Perform actions after the node received an editorial action, but before it
 * is saved to database.
 *
 * @param string $action
 *   Action that takes place.
 * @param object $node
 *   Node object that is being altered.
 *
 * @see ding_dashboard_valid_actions()
 */
function hook_editorial_status_changed($action, $node) {
  if ($action == 'approve') {
    $node->status = 1;
  }
}
