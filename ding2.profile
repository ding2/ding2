<?php

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Allows the profile to alter the site configuration form.
 */
function ding2_form_install_configure_form_alter(&$form, $form_state) {
  // Pre-populate the site name with the server name.
  $form['site_information']['site_name']['#default_value'] = $_SERVER['SERVER_NAME'];
}

/**
 * Implements hook_install_tasks().
 *
 * Collects install tasks from all modules implementing
 * hook_ding_install_tasks.
 *
 * As this function is called early and often, we have to maintain a cache or
 * else the task specifying a form may not be available on form submit.
 */
function ding2_install_tasks($install_state) {
  $tasks = module_invoke_all('ding_install_tasks') + variable_get('ding_install_tasks', array());
  if ($tasks && !$install_state['installation_finished']) {
    variable_set('ding_install_tasks', $tasks);
  }

  // Allow task callbacks to be located in an include file.
  foreach ($tasks as $name => $task) {
    if (isset($task['file'])) {
      require_once DRUPAL_ROOT . '/' . $task['file'];
    }
  }

  // Clean up if were finished.
  if ($install_state['installation_finished']) {
    variable_del('ding_install_tasks');
  }

  /**
   * We need at least one task to ensure that the rest of the tasks is
   * run. Without it, install_run_tasks() can manage to run through the tasks
   * up to 'install_bootstrap_full', and if there's no following tasks (when
   * 'install_configure_form' has been completed), it will think it's done
   * before we have a chance to read the variable and tell it otherwise.
   *
   * Luckily, we need to flush some caches anyway.
   */
  $ret = array(
    'ding2_flush_all_caches' => array(
      'display' => FALSE,
      'run' => INSTALL_TASK_RUN_IF_REACHED,
    ),
  ) + $tasks;
  return $ret;
}

/**
 * Install task that flushes caches. Ensures that the profile modules hook
 * implementations are available so we can invoke hook_ding_install_tasks and
 * get all the module provided tasks for the next round.
 */
function ding2_flush_all_caches() {
  // Only flush cache if we haven't picked up any install tasks yet.
  if (!variable_get('ding_install_tasks', NULL)){
    drupal_flush_all_caches();
  }
  return;
}
