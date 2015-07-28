<?php

function ting_ting_object_page_manager_tasks() {
  return array(
    'title' => t('Ting object'),
    'task type' => 'page',
    'admin title' => t('Ting object'),
    'admin description' => t('Lorem ipsum dolor sit amet, consectetur adipiscing elit. Quae cum essent dicta, discessimus. Nos commodius agimus. Ille incendat? Ut optime, secundum naturam affectum esse possit.'),
    'admin path' => 'ting/object/%ting_object',
    'handler type' => 'context',
    'hook menu' => 'ting_ting_object_menu',
    'hook menu alter' => 'ting_ting_object_menu_alter',
    'get arguments' => 'ting_ting_object_get_arguments',
    'get context placeholders' => 'ting_ting_object_get_contexts',
    'disabled' => variable_get('ting_ting_object_disabled', TRUE),
    'enable callback' => 'ting_ting_object_enable',
  );
}

function ting_ting_object_menu_alter(&$items, $task) {
  if (variable_get('ting_ting_object_disabled', TRUE)) {
    return;
  }

  // Override the node view handler for our purpose.
  $callback = $items['ting/object/%ting_object']['page callback'];
  if ($callback == 'ting_object_page_view' || variable_get('page_manager_override_anyway', FALSE)) {
    $items['ting/object/%ting_object']['page callback'] = 'ting_ting_object_page';
    $items['ting/object/%ting_object']['file path'] = $task['path'];
    $items['ting/object/%ting_object']['file'] = $task['file'];
  }
  else {
    // automatically disable this task if it cannot be enabled.
    variable_set('ting_ting_object_page', TRUE);
    if (!empty($GLOBALS['ting_enabling_ting_object'])) {
      drupal_set_message(t('Page manager module is unable to enable ting/object/%ting_object because some other module already has overridden with %callback.', array('%callback' => $callback)), 'error');
    }
  }
}

function ting_ting_object_page($ting_object) {
  $task = page_manager_get_task('ting_object');
  ctools_include('context');
  ctools_include('context-task-handler');
  $contexts = ctools_context_handler_get_task_contexts($task, '', array($ting_object));
  $output = ctools_context_handler_render($task, '', $contexts, array($ting_object->ding_entity_id));
  return $output;
}

function ting_ting_object_get_arguments($task, $subtask_id) {
  return array(
    array(
      'keyword' => 'ting_object',
      'identifier' => t('Ting object id'),
      'id' => 17,
      'name' => 'ting_object_id',
      'settings' => array(),
    ),
  );
}

function ting_ting_object_get_contexts($task, $subtask_id) {
  return ctools_context_get_placeholders_from_argument(ting_ting_object_get_arguments($task, $subtask_id));
}

/**
 * Callback to enable/disable the page from the UI.
 */
function ting_ting_object_enable($cache, $status) {
  variable_set('ting_ting_object_disabled', $status);

  // Set a global flag so that the menu routine knows it needs
  // to set a message if enabling cannot be done.
  if (!$status) {
    $GLOBALS['ting_enabling_ting_object'] = TRUE;
  }
}
