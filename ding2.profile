<?php

// Initialise profiler
!function_exists('profiler_v2') ? require_once('libraries/profiler/profiler.inc') : FALSE;
profiler_v2('ding2');

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Allows the profile to alter the site configuration form.
 */
if (!function_exists("system_form_install_configure_form_alter")) {
  function system_form_install_configure_form_alter(&$form, $form_state) {
    $form['site_information']['site_name']['#default_value'] = 'ding2';
  }
}

/**
 * Implements hook_form_alter().
 *
 * Select the current install profile by default.
 */
if (!function_exists("system_form_install_select_profile_form_alter")) {
  function system_form_install_select_profile_form_alter(&$form, $form_state) {
    foreach ($form['profile'] as $key => $element) {
      $form['profile'][$key]['#value'] = 'ding2';
    }
  }
}

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
function ding2_form_alter(&$form, &$form_state, $form_id) {
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
function ding2_form_install_configure_form_alter(&$form, &$form_state, $form_id) {
  // Pre-populate the site name with the server name.
  $form['site_information']['site_name']['#default_value'] = $_SERVER['SERVER_NAME'];
}

/**
 * Implements hook_install_tasks().
 *
 * As this function is called early and often, we have to maintain a cache or
 * else the task specifying a form may not be available on form submit.
 */
function ding2_install_tasks(&$install_state) {
  $tasks = variable_get('ding_install_tasks', array());

  if (!empty($tasks)) {
    // Allow task callbacks to be located in an include file.
    foreach ($tasks as $task) {#&$task) {

      if (isset($task['file'])) {
        require_once DRUPAL_ROOT . '/' . $task['file'];
      }
    }
  }

  // Clean up if were finished.
  if ($install_state['installation_finished']) {
    variable_del('ding_install_tasks');
  }

  include_once('libraries/profiler/profiler_api.inc');

  $ret = array(
    'ding2_fetch_ding_install_tasks' =>
      array(
        'display_name' => '...',
        /**
         * This task should be skipped and hidden when ding install tasks
         * have been fetched. Fetched tasks will appear instead.
         */
        'run' => empty($tasks) ? INSTALL_TASK_RUN_IF_REACHED : INSTALL_TASK_SKIP,
        'display' => empty($tasks),
      )
  ) + $tasks + array('profiler_install_profile_complete' => array());
  return $ret;
}

/**
 * Install task fetching ding install tasks from modules implementing
 * hook_ding_install_tasks. This install task is invoked when Drupal is
 * fully functional.
 */
function ding2_fetch_ding_install_tasks(&$install_state) {
  $ding_tasks = module_invoke_all('ding_install_tasks');
  variable_set('ding_install_tasks', $ding_tasks);
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

/**
 * Implements hook_ding_install_tasks().
 */
function ding2_ding_install_tasks() {

    $node = array();
    ob_start();
    require 'content/page-not-found.inc';
    ob_end_clean();

    $node = (object) $node;
    $node->uid = 1;

    node_save($node);

    //Provide default page for EU Cookie Compliance module
    $node = array();
    ob_start();
    require 'content/cookies.inc';
    ob_end_clean();

    $node = (object) $node;
    $node->uid = 1;

    node_save($node);
}
