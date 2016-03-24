<?php
/**
 * @file
 * Editorial items operations.
 */

/**
 * Process the requested editorial action on a node.
 *
 * @param object $node
 *   Node object being altered.
 * @param string $action
 *   Action taking place on this node.
 */
function _ding_dashboard_action($node, $action) {
  $valid_actions = ding_dashboard_valid_actions();
  $dest = drupal_get_destination();

  if (!in_array($action, array_keys($valid_actions))) {
    $t = array(
      '@action' => $action
    );
    watchdog('editorial', t('Unknown action @action requested.'), $t, WATCHDOG_WARNING);
    drupal_goto($dest['destination']);
  }

  $callback = 'ding_dashboard' . $valid_actions[$action];
  if (function_exists($callback)) {
    $result = $callback($node);

    _ding_dashboard_node_persist($node, $action);
  }
  else {
    $t = array(
      '@callback' => $callback,
    );
    watchdog('editorial', t('No such @callback() method defined.'), $t, WATCHDOG_ERROR);
  }

  drupal_goto($dest['destination']);
}

/**
 * Update the node object.
 *
 * Notify other modules and call the node API to save the node.
 *
 * @param object $node
 *   Node object.
 * @param string $action
 *   Action being produced.
 */
function _ding_dashboard_node_persist($node, $action) {
  module_invoke_all('editorial_status_changed', $action, $node);
  node_save($node);
}

/**
 * Node push processing.
 *
 * @param object $node
 *   Node object being altered.
 *
 * @see _ding_dashboard_action()
 * @see ding_dashboard_valid_actions()
 */
function ding_dashboard_node_push($node) {
  $node->field_editorial_status[LANGUAGE_NONE] = array(
    array(
      'value' => EDITORIAL_NODE_PUSHED,
    ),
  );

  return EDITORIAL_NODE_PUSHED;
}

/**
 * Node approve processing.
 *
 * @param object $node
 *   Node object being altered.
 *
 * @see _ding_dashboard_action()
 * @see ding_dashboard_valid_actions()
 */
function ding_dashboard_node_approve($node) {
  $node->field_editorial_status[LANGUAGE_NONE] = array(
    array(
      'value' => EDITORIAL_NODE_APPROVED,
    ),
  );

  return EDITORIAL_NODE_APPROVED;
}

/**
 * Node reject processing.
 *
 * @param object $node
 *   Node object being altered.
 *
 * @see _ding_dashboard_action()
 * @see ding_dashboard_valid_actions()
 */
function ding_dashboard_node_reject($node) {
  $node->field_editorial_status[LANGUAGE_NONE] = array(
    array(
      'value' => EDITORIAL_NODE_REJECTED,
    ),
  );

  return EDITORIAL_NODE_REJECTED;
}
