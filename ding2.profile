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

    // Update translations.
    'ding2_import_translation' => array(
      'display_name' => st('Set up translations'),
      'display' => TRUE,
      'run' => INSTALL_TASK_RUN_IF_NOT_COMPLETED,
      'type' => 'batch',
    ),
  ) + $tasks + array('profiler_install_profile_complete' => array());
  return $ret;
}

/**
 * Translation callback.
 *
 * @param string $install_state
 *   An array of information about the current installation state.
 *
 * @return array
 *   List of batches.
 */
function ding2_import_translation(&$install_state) {
  // Enable l10n_update.
  module_enable(array('l10n_update'), TRUE);

  // Enable danish language.
  include_once DRUPAL_ROOT . '/includes/locale.inc';
  locale_add_language('da', NULL, NULL, NULL, '', NULL, TRUE, FALSE);

  // Import our own translations.
  $file = new stdClass;
  $file->uri = DRUPAL_ROOT . '/profiles/ding2/translations/ding2tal_da.po';
  $file->filename = basename($file->uri);
  _locale_import_po($file, 'da', LOCALE_IMPORT_OVERWRITE, 'default');

  // Build batch with l10n_update module.
  $history = l10n_update_get_history();
  module_load_include('check.inc', 'l10n_update');
  $available = l10n_update_available_releases();
  $updates = l10n_update_build_updates($history, $available);

  // Fire of the batch!
  module_load_include('batch.inc', 'l10n_update');
  $updates = _l10n_update_prepare_updates($updates, NULL, array());
  $batch = l10n_update_batch_multiple($updates, LOCALE_IMPORT_KEEP);
  return $batch;
}

/**
 * Implements hook_install_tasks_alter().
 *
 * Remove default locale imports.
 */
function ding2_install_tasks_alter(&$tasks, $install_state) {
  // Remove core steps for translation imports.
  unset($tasks['install_import_locales']);
  unset($tasks['install_import_locales_remaining']);

  // Callback for language selection.
  $tasks['install_select_locale']['function'] = 'ding2_locale_selection';
}

/**
 * Set default language to english.
 */
function ding2_locale_selection(&$install_state) {
  $install_state['parameters']['locale'] = 'en';
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
 *   Form with selection of different modules.
 */
function ding2_module_selection_form($form, &$form_state) {
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

  $form['providers']['providers_selection'] = array(
    // Title left empty to create more space in the ui.
    '#title' => '',
    '#type' => 'radios',
    '#options' => $providers,
  );

  //
  // Optional modules.
  //
  $modules = array(
//    'ding_adhl_frontend' => st('ADHL (Other that have borrowed)'),
//    'ding_campaign' => st('Add ding campaigns'),
    'ding_contact' => st('Contact module'),
    'ding_example_content' => st('Add example content'),
    'ting_new_materials' => st('Ting New Materials'),
  );

  $form['modules'] = array(
    '#title' => st('Select ding extras'),
    '#type' => 'fieldset',
    '#description' => st('Select optional ding extension. You can always enable/disable these in the administration interface.'),
  );

  $form['modules']['modules_selection'] = array(
    // Title left empty to create more space in the ui.
    '#title' => '',
    '#type' => 'checkboxes',
    '#options' => $modules,
  );

  //
  // Favicon, logo & iOS icon upload.
  //
  // Setup a hidden field, that system_setting_form knows.
  $form['var'] = array('#type' => 'hidden', '#value' => 'theme_ddbasic_settings');

  // Logo settings.
  $form['logo'] = array(
    '#type' => 'fieldset',
    '#title' => st('Logo image settings'),
    '#description' => st('If toggled on, the following logo will be displayed.'),
    '#attributes' => array('class' => array('theme-settings-bottom')),
  );
  $form['logo']['default_logo'] = array(
    '#type' => 'checkbox',
    '#title' => st('Use the default logo'),
    '#default_value' => TRUE,
    '#tree' => FALSE,
    '#description' => st('Check here if you want the theme to use the logo supplied with it.'),
  );
  $form['logo']['settings'] = array(
    '#type' => 'container',
    '#states' => array(
      // Hide the logo settings when using the default logo.
      'invisible' => array(
        'input[name="default_logo"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['logo']['settings']['logo_path'] = array(
    '#type' => 'textfield',
    '#title' => st('Path to custom logo'),
    '#description' => st('The path to the file you would like to use as your logo file instead of the default logo.'),
    '#default_value' => '',
  );
  $form['logo']['settings']['logo_upload'] = array(
    '#type' => 'file',
    '#title' => st('Upload logo image'),
    '#maxlength' => 40,
    '#description' => st("If you don't have direct file access to the server, use this field to upload your logo."),
  );

  // Favicon.
  $form['favicon'] = array(
    '#type' => 'fieldset',
    '#title' => st('Shortcut icon settings'),
    '#description' => st("Your shortcut icon, or 'favicon', is displayed in the address bar and bookmarks of most browsers."),
  );
  $form['favicon']['default_favicon'] = array(
    '#type' => 'checkbox',
    '#title' => st('Use the default shortcut icon.'),
    '#default_value' => TRUE,
    '#description' => st('Check here if you want the theme to use the default shortcut icon.'),
  );
  $form['favicon']['settings'] = array(
    '#type' => 'container',
    '#states' => array(
      // Hide the favicon settings when using the default favicon.
      'invisible' => array(
        'input[name="default_favicon"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['favicon']['settings']['favicon_path'] = array(
    '#type' => 'textfield',
    '#title' => st('Path to custom icon'),
    '#description' => st('The path to the image file you would like to use as your custom shortcut icon.'),
    '#default_value' => '',
  );
  $form['favicon']['settings']['favicon_upload'] = array(
    '#type' => 'file',
    '#title' => st('Upload icon image'),
    '#description' => st("If you don't have direct file access to the server, use this field to upload your shortcut icon."),
  );

  // iOS icon.
  $form['iosicon'] = array(
    '#type' => 'fieldset',
    '#title' => st('iOS icon settings'),
    '#description' => st("Your iOS icon, is displayed at the homescreen."),
  );
  $form['iosicon']['default_iosicon'] = array(
    '#type' => 'checkbox',
    '#title' => st('Use the default iOS icon.'),
    '#default_value' => TRUE,
    '#description' => st('Check here if you want the theme to use the default iOS icon.'),
  );
  $form['iosicon']['settings'] = array(
    '#type' => 'container',
    '#states' => array(
      // Hide the favicon settings when using the default favicon.
      'invisible' => array(
        'input[name="default_iosicon"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['iosicon']['settings']['iosicon_path'] = array(
    '#type' => 'textfield',
    '#title' => st('Path to custom iOS icon'),
    '#description' => st('The path to the image file you would like to use as your custom iOS icon.'),
  );
  $form['iosicon']['settings']['iosicon_upload'] = array(
    '#type' => 'file',
    '#title' => st('Upload iOS icon image'),
    '#description' => st("If you don't have direct file access to the server, use this field to upload your iOS icon."),
    '#default_value' => '',
  );

  //
  // Submit the selections.
  //
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => st('Enable modules'),
  );

  // Validate and submit logo, iOS logo and favicon.
  $form['#validate'][] = 'ding2_module_selection_form_validate';
  $form['#validate'][] = 'system_theme_settings_validate';
  $form['#submit'][] = 'ding2_module_selection_form_submit';
  $form['#submit'][] = 'system_theme_settings_submit';

  return $form;
}

/**
 * Validate handler for ding2_module_selection_form().
 */
function ding2_module_selection_form_validate($form, &$form_state) {
  // We depend on core system module.
  require_once DRUPAL_ROOT . '/modules/system/system.admin.inc';

  $validators = array('file_validate_extensions' => array('ico png gif jpg jpeg apng svg'));

  // Check for a new uploaded favicon.
  $file = file_save_upload('iosicon_upload', $validators);
  if (isset($file)) {
    // File upload was attempted.
    if ($file) {
      // Put the temporary file in form_values so we can save it on submit.
      $form_state['values']['iosicon_upload'] = $file;
    }
    else {
      // File upload failed.
      form_set_error('iosicon_upload', t('The iOS icon could not be uploaded.'));
    }
  }

  // If the user provided a path for iOS icon file, make sure a file exists at
  // that path.
  if ($form_state['values']['iosicon_path']) {
    $path = _system_theme_settings_validate_path($form_state['values']['iosicon_path']);
    if (!$path) {
      form_set_error('iosicon_path', t('The custom iOS icon path is invalid.'));
    }
  }
}
/**
 * Submit handler that enables the modules.
 *
 * It also enabled the provider selected in the form defined above.
 * And iOS upload handling.
 */
function ding2_module_selection_form_submit($form, &$form_state) {
  // We depend on core system module.
  require_once DRUPAL_ROOT . '/modules/system/system.admin.inc';

  $values = $form_state['values'];
  $module_list = array();

  // Extract the name of the theme from the submitted form values, then remove
  // it from the array so that it is not saved as part of the variable.
  $key = $values['var'];
  unset($values['var']);

  // If the user uploaded a iOS icon, save it to a permanent location
  // and use it in place of the default theme-provided file.
  if ($file = $values['iosicon_upload']) {
    unset($values['iosicon_upload']);
    $filename = file_unmanaged_copy($file->uri);
    $values['ios_icon'] = 0;
    $values['ios_path'] = $filename;
    $values['toggle_iosicon'] = 1;
  }

  // If the user entered a path relative to the system files directory for
  // a logo or favicon, store a public:// URI so the theme system can handle it.
  if (!empty($values['iosicon_path'])) {
    $values['iosicon_path'] = _system_theme_settings_validate_path($values['iosicon_path']);
  }

  // Save iOS logo to theme settings.
  variable_set($key, $values);

  // Get selected provider.
  if (!empty($values['providers_selection'])) {
    $module_list[] = $values['providers_selection'];
  }

  // Get list of selected modules.
  if (!empty($values['modules_selection'])) {
    $module_list += array_filter($values['modules_selection']);
  }

  // Enable the provider (if selected) and modules.
  module_enable($module_list, TRUE);
}
