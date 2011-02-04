<?php
// $Id$

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

  return $tasks;
}

/**
 * Clean up after our-self.
 */
function ding2_install_cleanup() {
  variable_del('ding_install_tasks');
}