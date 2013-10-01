<?php

// Initialise profiler.
!function_exists('profiler_v2') ? require_once 'libraries/profiler/profiler.inc' : FALSE;
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
 * the installation we may present the users with required form elements
 * they do not know how to handle and thus prevent them from completing the
 * installation.
 */
function ding2_form_alter(&$form, &$form_state, $form_id) {
  // Process all forms during installation except the Drupal default
  // configuration form.
  if (defined('MAINTENANCE_MODE') && MAINTENANCE_MODE == 'install' &&
      $form_id != 'install_configure_form') {
    array_walk_recursive($form, '_ding2_remove_form_requirements');
  }
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
    foreach ($tasks as $task) {
      if (isset($task['file'])) {
        require_once DRUPAL_ROOT . '/' . $task['file'];
      }
    }
  }

  // Clean up if were finished.
  if ($install_state['installation_finished']) {
    variable_del('ding_install_tasks');
  }

  include_once 'libraries/profiler/profiler_api.inc';

  $ret = array(
    // Add task to select provider and extra ding modules.
    'ding2_module_selection_form' => array(
      'display_name' => 'Module selection',
      'display' => TRUE,
      'type' => 'form',
      'run' => empty($tasks) ? INSTALL_TASK_RUN_IF_REACHED : INSTALL_TASK_SKIP,
    ),

    // Add extra tasks based on hook_ding_install_task, which may be provided by
    // the selection task above.
    'ding2_fetch_ding_install_tasks' => array(
      'display_name' => 'Configure ding...',
      // This task should be skipped and hidden when ding install tasks
      // have been fetched. Fetched tasks will appear instead.
      'run' => empty($tasks) ? INSTALL_TASK_RUN_IF_REACHED : INSTALL_TASK_SKIP,
      'display' => empty($tasks),
    ),
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
 * Installation task that handle selection of provider and modules to extend
 * default ding2 installation.
 *
 * @return array
 *  Form with selection of different modules.
 */
function ding2_module_selection_form($form_state) {
  $form = array(
    '#tree' => TRUE,
  );

  // Available providers.
  $providers = array(
    'alma' => 'Alma',
    'openruth' => 'Openruth',
  );

  $form['providers'] = array(
    '#title' => st('Select library provider'),
    '#type' => 'fieldset',
    '#description' => st('Select the provider that matches your library system.'),
  );

  $form['providers']['selection'] = array(
    // Title left empty to create more space in the ui.
    '#title' => '',
    '#type' => 'radios',
    '#options' => $providers,
  );

  //
  // Optional modules.
  //
  $modules = array(
    'ding_adhl_frontend' => st('ADHL (Other that have borrowed)'),
    'ding_campaign' => st('Add ding campaigns'),
    'ding_permissions' => st('Set default permissions'),

    // Modules that's not part of the make files yet.
    'ding_example_content' => st('Add example content to the site'),
  );

  $form['modules'] = array(
    '#title' => st('Select ding extras'),
    '#type' => 'fieldset',
    '#description' => st('Select optional ding extension. You can always enable/disable these in the administration interface.'),
  );

  $form['modules']['selection'] = array(
    // Title left empty to create more space in the ui.
    '#title' => '',
    '#type' => 'checkboxes',
    '#options' => $modules,
  );

  //
  // Submit the selections.
  //
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => st('Enable modules'),
  );

  return $form;
}

/**
 * Submit handler that enables the modules.
 *
 * It also enabled the provider selected in the form defined above.
 */
function ding2_module_selection_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  $module_list = array();

  // Get selected provider.
  if (!empty($values['providers']['selection'])) {
    $module_list[] = $values['providers']['selection'];
  }

  // Get list of selected modules.
  $module_list += array_filter($values['modules']['selection']);

  // Enable the provider (if selected) and modules.
  module_enable($module_list, TRUE);
}
