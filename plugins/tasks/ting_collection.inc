<?php

function ting_ting_collection_page_manager_tasks() {
  return array(
    'title' => t('Ting collection'),
    'task type' => 'page',
    'admin title' => t('Ting collection'),
    'admin description' => t('Lorem ipsum dolor sit amet, consectetur adipiscing elit. Quae cum essent dicta, discessimus. Nos commodius agimus. Ille incendat? Ut optime, secundum naturam affectum esse possit.'),
    'admin path' => 'ting/collection/%ting_collection',
    'handler type' => 'context',
    'hook menu' => 'ting_ting_collection_menu',
    'hook menu alter' => 'ting_ting_collection_menu_alter',
    'get arguments' => 'ting_ting_collection_get_arguments',
    'get context placeholders' => 'ting_ting_collection_get_contexts',
    'disabled' => variable_get('ting_ting_collection_disabled', TRUE),
    'enable callback' => 'ting_ting_collection_enable',
  );
}

function ting_ting_collection_menu_alter(&$items, $task) {
  if (variable_get('ting_ting_collection_disabled', TRUE)) {
    return;
  }

  // Override the node view handler for our purpose.
  $callback = $items['ting/collection/%ting_collection']['page callback'];
  if ($callback == 'ting_collection_page_view' || variable_get('page_manager_override_anyway', FALSE)) {
    $items['ting/collection/%ting_collection']['page callback'] = 'ting_ting_collection_page';
    $items['ting/collection/%ting_collection']['file path'] = $task['path'];
    $items['ting/collection/%ting_collection']['file'] = $task['file'];
  }
  else {
    // automatically disable this task if it cannot be enabled.
    variable_set('ting_ting_collection_page', TRUE);
    if (!empty($GLOBALS['ting_enabling_ting_collection'])) {
      drupal_set_message(t('Page manager module is unable to enable ting/collection/%ting_collection because some other module already has overridden with %callback.', array('%callback' => $callback)), 'error');
    }
  }
}

function ting_ting_collection_page($ting_collection) {
  $task = page_manager_get_task('ting_collection');
  ctools_include('context');
  ctools_include('context-task-handler');
  $contexts = ctools_context_handler_get_task_contexts($task, '', array($ting_collection));
  $output = ctools_context_handler_render($task, '', $contexts, array($ting_collection->ding_entity_id));
  return $output;
}

function ting_ting_collection_get_arguments($task, $subtask_id) {
  return array(
    array(
      'keyword' => 'ting_collection',
      'identifier' => t('Ting collection id'),
      'id' => 17,
      'name' => 'ting_collection_id',
      'settings' => array(),
    ),
  );
}

function ting_ting_collection_get_contexts($task, $subtask_id) {
  return ctools_context_get_placeholders_from_argument(ting_ting_collection_get_arguments($task, $subtask_id));
}

/**
 * Callback to enable/disable the page from the UI.
 */
function ting_ting_collection_enable($cache, $status) {
  variable_set('ting_ting_collection_disabled', $status);

  // Set a global flag so that the menu routine knows it needs
  // to set a message if enabling cannot be done.
  if (!$status) {
    $GLOBALS['ting_enabling_ting_collection'] = TRUE;
  }
}

