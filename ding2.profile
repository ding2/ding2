<?php

// Initialise profiler
!function_exists('profiler_v2') ? require_once('libraries/profiler/profiler.inc') : FALSE;
profiler_v2('ding2');

/**
 * Implements hook_form_alter().
 *
 * Remove #required attribute for form elements in the installer
 * as they prevent the install profile from being run using drush
 * site-install.
 *
 * These elements will usually be added by modules implementing
 * hook_ding_install_tasks and passing a default administration form. While
 * setting elements as required in the administration is reasonable, during
 * the instalation we may present the users with required form elements
 * they do not know how to handle and thus prevent them from completing the
 * installation.
 */
function ding2_form_alter(&$form, $form_state, $form_id) {
  // Proces all forms during installation except the Drupal default
  // configuration form
  if (defined('MAINTENANCE_MODE') && MAINTENANCE_MODE == 'install' &&
      $form_id != 'install_configure_form') {
    array_walk_recursive($form, '_ding2_remove_form_requirements');
  }
}


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

  include_once('libraries/profiler/profiler_api.inc');

  /**
   * We need at least one task to ensure that the rest of the tasks is
   * run. Without it, install_run_tasks() can manage to run through the tasks
   * up to 'install_bootstrap_full', and if there's no following tasks (when
   * 'install_configure_form' has been completed), it will think it's done
   * before we have a chance to read the variable and tell it otherwise.
   *
   * Luckily, we need to flush some caches anyway.
   *
   * Also append the completion task for profiler.
   */
  $ret = array(
    'ding2_flush_all_caches' => array(
      'display' => FALSE,
      'run' => INSTALL_TASK_RUN_IF_REACHED,
    ),
  ) + $tasks + array('profiler_install_profile_complete' => array());
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

/**
 * Function to remove all required attributes from a form element array.
 */
function _ding2_remove_form_requirements(&$value, $key) {
  // Set required attribute to false if set.
  if ($key === '#required') {
    $value = FALSE;
  }
}