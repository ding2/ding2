<?php

/**
 * @file
 * Stores a triggers for exporting content.
 */

/**
 * Implements hook_node_delete().
 */
function ding_mobilesearch_node_delete($node) {
  $types = _ding_mobilesearch_types();
  if (!in_array($node->type, array_keys($types), TRUE)) {
    return;
  }

  $plugin = $types[$node->type];
  if ($plugin['trigger'] != 'hook_node_insert') {
    return;
  }
  if (!empty($plugin['exec_callback']) && function_exists($plugin['exec_callback'])) {
    $plugin['exec_callback']('hook_node_delete', 'node', $node);
  }
}

/**
 * Implements hook_workflow().
 */
function ding_mobilesearch_workflow($op, $id, $new_sid, $entity, $force, $entity_type = '', $field_name = '', $transition = NULL, $user = NULL) {
  if ($op == 'transition post') {
    $state = workflow_state_load($new_sid);

    $names = node_type_get_names();
    foreach ($names as $machine_name => $name) {
      $key = 'mobilesearch_type__' . $machine_name;
      if (variable_get($key, FALSE)) {
        $trigger = variable_get($key . '__trigger', NULL);
        if ($trigger == 'hook_workflow__' . $state->name) {
          $plugin = $trigger = variable_get($key . '__plugin', NULL);
          $plugin_info = module_invoke_all('ding_mobilesearch_plugin_info');
          $plugin = $plugin_info[$plugin];

          if (!empty($plugin['exec_callback']) && function_exists($plugin['exec_callback'])) {
            $plugin['exec_callback']('hook_workflow', 'workflow', $entity);
          }
        }
      }
    }
  }
}

/**
 * Implementation of push to mongo action.
 */
function views_bulk_operations_push_mongo_rest($entity, $context) {
  $types = _ding_mobilesearch_types();
  if (!in_array($entity->type, array_keys($types), TRUE)) {
    return;
  }

  $plugin = $types[$entity->type];
  if ($plugin['trigger'] != 'hook_node_insert') {
    return;
  }
  if (!empty($plugin['exec_callback']) && function_exists($plugin['exec_callback'])) {
    $plugin['exec_callback']('hook_node_update', 'node', $entity);
  }
}
