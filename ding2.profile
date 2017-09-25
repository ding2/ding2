<?php
/**
 * @file
 * The installation profile which is called after the profile have been enabled
 * so .install is called first.
 */

// Initialise profiler.
!function_exists('profiler_v2') ? require_once 'libraries/profiler/profiler.inc' : FALSE;
profiler_v2('ding2');

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Allows the profile to alter the site configuration form.
 */
function ding2_form_install_configure_form_alter(&$form, $form_state) {
  $form['site_information']['site_name']['#default_value'] = $_SERVER['SERVER_NAME'];

  $form['server_settings']['site_default_country']['#default_value'] = 'DK';
  $form['server_settings']['date_default_timezone']['#default_value'] = 'Europe/Copenhagen';
  // Remove the timezone-detect class to stop auto detection (which guesses
  // Berlin, not Copenhagen).
  unset($form['server_settings']['date_default_timezone']['#attributes']);
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

    // Set default values in ting search form to help aegir/bulk installations.
    if ($form_id == 'ting_admin_ting_settings') {
      $form['ting']['ting_search_url']['#default_value'] = 'http://opensearch.addi.dk/3.0/';
      $form['ting']['ting_recommendation_url']['#default_value'] = 'http://openadhl.addi.dk/1.1/';
    }

    if ($form_id == 'ting_covers_admin_addi_settings_form') {
      $form['addi']['addi_wsdl_url']['#default_value'] = 'http://moreinfo.addi.dk/2.1/';
    }
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
      'display_name' => st('Module selection'),
      'display' => TRUE,
      'type' => 'form',
      'run' => INSTALL_TASK_RUN_IF_NOT_COMPLETED,
    ),

    // Enable modules.
    'ding2_module_enable' => array(
      'display_name' => st('Enable modules'),
      'display' => TRUE,
      'run' => INSTALL_TASK_RUN_IF_NOT_COMPLETED,
      'type' => 'batch',
    ),

    // Import ding2 translations.
    'ding2_import_ding2_translations' => array(
      'display_name' => st('Import translations'),
      'display' => TRUE,
      'run' => INSTALL_TASK_RUN_IF_NOT_COMPLETED,
      'type' => 'batch',
    ),

    // Configure and revert features.
    'ding2_add_settings' => array(
      'display_name' => st('Add default page and settings'),
      'display' => TRUE,
      'run' => INSTALL_TASK_RUN_IF_NOT_COMPLETED,
      'type' => 'batch',
    ),

    // Set up menu.
    'ding2_render_og_menus' => array(
      'display_name' => st('OG Menus'),
      'display' => module_exists('ding_example_content'),
      'run' => module_exists('ding_example_content') ? INSTALL_TASK_RUN_IF_NOT_COMPLETED : INSTALL_TASK_SKIP,
      'type' => 'batch',
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
 * Translation callback.
 *
 * @param string $install_state
 *   An array of information about the current installation state.
 *
 * @return array
 *   List of batches.
 */
function ding2_import_ding2_translations(&$install_state) {
  // Enable danish language.
  include_once DRUPAL_ROOT . '/includes/locale.inc';
  locale_add_language('da', NULL, NULL, NULL, '', NULL, TRUE, FALSE);

  // Add import of ding2 translations.
  $operations = array();
  $operations[] = array(
    '_ding2_insert_translation',
    array(
      'default',
      '/profiles/ding2/translations/da.po',
    ),
  );

  $operations[] = array(
    '_ding2_insert_translation',
    array(
      'field',
      '/profiles/ding2/translations/fields_da.po',
    ),
  );

  $batch = array(
    'title' => st('Installing ding translations'),
    'operations' => $operations,
    'file' => drupal_get_path('profile', 'ding2') . '/ding2.install_callbacks.inc',
  );

  return $batch;
}

/**
 * Helper function to configure the last parts.
 *
 * Reverts features and adds some basic pages.
 */
function ding2_add_settings(&$install_state) {
  // Set page not found.
  ding2_set_page_not_found();

  // Set cookie page.
  ding2_set_cookie_page();

  // Add menu item to secondary menu.
  $link = array(
    'menu_name' => 'menu-secondary-menu',
    'weight' => 50,
    'link_title' => 'Kontakt',
    'link_path' => 'contact',
    'language' => LANGUAGE_NONE,
  );
  menu_link_save($link);

  // Give admin user the administrators role to fix varnish cache of logged in
  // users.
  ding2_add_administrators_role(1);

  // Add features to a batch job to get them reverted.
  $operations = array();
  $features = array(
    'ting_reference',
    'ting_material_details',
    'ding_base',
    'ding_user_frontend',
    'ding_content',
    'ding_page',
    'ding_frontend',
    'ding_ting_frontend',
    'ding_event',
    'ding_library',
    'ding_news',
    'ding_groups',
    'ding_frontpage',
  );

  // Revert features.
  foreach ($features as $feature) {
    $operations[] = array(
      '_ding2_features_revert',
      array($feature),
    );
  }

  $batch = array(
    'title' => st('Reverting features'),
    'operations' => $operations,
    'file' => drupal_get_path('profile', 'ding2') . '/ding2.install_callbacks.inc',
  );

  return $batch;
}

/**
 * Install task to build default og menu values for example content.
 */
function ding2_render_og_menus(&$install_state) {
  $menus = array();
  $results = db_query("select menu_name as menu_name from {og_menu}");
  foreach ($results as $row) {
    $menus[] = $row->menu_name;
  }

  $batch = array(
    'title' => st('Updating Default link'),
    'operations' => array(
      array('og_menu_default_links_batch_default_links_process', array($menus)),
    ),
    'file' => drupal_get_path('module', 'og_menu_default_links') . '/og_menu_default_links.batch.inc',
  );

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
 * Fetch ding install tasks from modules implementing hook_ding_install_tasks().
 *
 * This install task is invoked when Drupal is fully functional.
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
 * Installation task that handle selection of provider and modules.
 */
function ding2_module_selection_form($form, &$form_state) {
  // Available providers.
  $providers = array(
    'fbs' => 'FBS',
    'alma' => 'Alma',
    'connie' => 'Connie (for testing without a library system)',
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
    '#default_value' => 'fbs',
  );

  //
  // SSL proxy settings.
  //
  $form['proxy'] = array(
    '#title' => st('SSL proxy'),
    '#type' => 'fieldset',
    '#description' => st('If the sysytem is running behind an SSL reverse proxy such as nginx.'),
  );

  $form['proxy']['sslproxy_enable'] = array(
    '#type' => 'checkbox',
    '#title' => 'Enable SSL proxy',
    '#description' => st('Enable the SSL proxy module.'),
    '#default_value' => TRUE,
  );

  $form['proxy']['sslproxy_var'] = array(
    '#type' => 'textfield',
    '#title' => st('SSL Proxy Variable'),
    '#description' => st('The variable being set by the SSL proxy server.'),
    '#default_value' => 'X-FORWARDED-PROTO',
  );

  $form['proxy']['sslproxy_var_value'] = array(
    '#type' => 'textfield',
    '#title' => st('SSL Proxy Variable Value'),
    '#description' => st('The value of the variable being set by the SSL proxy server.'),
    '#default_value' => 'https',
  );

  //
  // Optional modules.
  //
  $modules = array(
    'ding_contact' => st('Contact module'),
    'ding_example_content' => st('Add example content'),
    'bpi' => st('BPI'),
    'ding_debt' => st('Ding payment'),
    'ding_dibs' => st('Dibs payment gateway'),
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
    '#default_value' => array(
      'ding_contact',
      'ding_debt',
      'ding_dibs',
    ),
  );

  //
  // Favicon, logo & iOS icon upload.
  //
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
  $form['#submit'][] = 'ding2_module_selection_form_submit';

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
      form_set_error('iosicon_upload', st('The iOS icon could not be uploaded.'));
    }
  }

  // If the user provided a path for iOS icon file, make sure a file exists at
  // that path.
  if ($form_state['values']['iosicon_path']) {
    $path = _system_theme_settings_validate_path($form_state['values']['iosicon_path']);
    if (!$path) {
      form_set_error('iosicon_path', st('The custom iOS icon path is invalid.'));
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

  // Load existing theme settings and update theme with extra information.
  $settings = variable_get('theme_ddbasic_settings', array());

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
  variable_set('theme_ddbasic_settings', array_merge($settings, $values));

  // Get selected provider.
  if (!empty($values['providers_selection'])) {
    $module_list[] = $values['providers_selection'];
  }

  // Get list of selected modules.
  if (!empty($values['modules_selection'])) {
    $module_list += array_filter($values['modules_selection']);
  }

  // Enable ssl proxy.
  if (isset($values['sslproxy_enable']) && $values['sslproxy_enable']) {
    // Set configuration.
    variable_set('sslproxy_var', $values['sslproxy_var']);
    variable_set('sslproxy_var_value', $values['sslproxy_var_value']);

    // Enable module.
    $module_list['sslproxy'] = 'sslproxy';
  }

  // Store selection to batch them in the next task.
  variable_set('ding_module_selected', $module_list);
}

/**
 * Builds an batch module enable operations list based on module list.
 *
 * @param array $module_list
 *   List of module names to change to operations.
 *
 * @return array
 *   Batch operation list.
 */
function ding2_module_list_as_operations($module_list) {
  // Resolve the dependencies now, so that module_enable() doesn't need
  // to do it later for each individual module (which kills performance).
  // @See http://drupalcontrib.org/api/drupal/contributions!commerce_kickstart!commerce_kickstart.install/function/commerce_kickstart_install_additional_modules/7
  $files = system_rebuild_module_data();
  $modules_sorted = array();
  foreach ($module_list as $module) {
    if ($files[$module]->requires) {
      // Create a list of dependencies that haven't been installed yet.
      $dependencies = array_keys($files[$module]->requires);
      $dependencies = array_filter($dependencies, 'ding2_filter_dependencies');
      // Add them to the module list.
      $module_list = array_merge($module_list, $dependencies);
    }
  }
  $module_list = array_unique($module_list);
  foreach ($module_list as $module) {
    $modules_sorted[$module] = $files[$module]->sort;
  }
  arsort($modules_sorted);

  $operations = array();
  foreach ($modules_sorted as $module => $weight) {
    $operations[] = array(
      '_ding2_enable_module',
      array(
        $module,
        $files[$module]->info['name'],
      ),
    );
  }

  return $operations;
}

/**
 * Enable selected ding2 modules as a batch process.
 */
function ding2_module_enable(&$install_state) {
  $modules = variable_get('ding_module_selected', array());
  $modules[] = 'l10n_update';
  $modules[] = 'ting_infomedia';
  $modules[] = 'ding_eresource';

  $operations = ding2_module_list_as_operations($modules);

  $batch = array(
    'title' => st('Installing additional functionality'),
    'operations' => $operations,
    'file' => drupal_get_path('profile', 'ding2') . '/ding2.install_callbacks.inc',
  );

  variable_del('ding_module_selected');

  return $batch;
}

/**
 * Helper function to filter out already enabled modules.
 *
 * @param string $dependency
 *   Name of the module that we want to check.
 *
 * @return bool
 *   If module exists and is enabled FALSE else TRUE.
 */
function ding2_filter_dependencies($dependency) {
  return !module_exists($dependency);
}

/**
 * Add administrators role to a user.
 *
 * @param int $uid
 *   Users Drupal id.
 */
function ding2_add_administrators_role($uid) {
  $roles = user_roles(TRUE);
  $rid = array_search('administrators', $roles);

  $account = user_load($uid);
  $edit['roles'] = array(
    DRUPAL_AUTHENTICATED_RID => 'authenticated user',
    $rid => 'administrators',
  );
  user_save($account, $edit);
}

/**
 * Adds a new static page to the site and set it as the default 404 page.
 */
function ding2_set_page_not_found() {
  $node = new stdClass();
  $node->uid = 1;

  $node->title = 'Siden blev ikke fundet';
  $node->type = 'ding_page';
  $node->language = 'und';
  $node->field_ding_page_body = array(
    'und' => array(
      array(
        'value' => '<div class="field-teaser">UPS! Vi kan ikke finde den side du søger.</div><p><strong>Hvad gik galt?</strong><br />Der kan være flere årsager til, at vi ikke kan finde det du leder efter:</p><p>- Stavefejl: Måske har du stavet forkert, da du skrev søgeordet. Eller der er en stavefejl i det link, du har fulgt.</p><p>- Siden er flyttet/slettet: Måske findes siden ikke længere eller den er blevet&nbsp;flyttet.</p><p><br /><strong>Bibliotek.dk</strong><br />Prøv den landsdækkende base <a href="http://bibliotek.dk/" target="_blank" title="Bibliotek.dk">bibliotek.dk</a>. Bibliotek.dk er en gratis service, hvor du kan se, hvad der er blevet udgivet i Danmark, og hvad der findes på danske biblioteker. Databasen opdateres dagligt.<br />Du kan bestille materialer til afhentning på dit lokale bibliotek. Du skal være registreret bruger på Odense Centralbibliotek.</p><p><br /><strong>Kom videre -&nbsp;kontakt&nbsp;dit bibliotek</strong><br />Vælg <a href="http://oc.fynbib.dk/biblioteker">&#39;Biblioteker&#39;</a> i menuen ovenfor og find kontakt oplysninger på den ønskede afdeling.</p>',
        'format' => 'ding_wysiwyg',
        'safe_value' => '<div class="field-teaser">UPS! Vi kan ikke finde den side du søger.</div><p><strong>Hvad gik galt?</strong><br />Der kan være flere årsager til, at vi ikke kan finde det du leder efter:</p><p>- Stavefejl: Måske har du stavet forkert, da du skrev søgeordet. Eller der er en stavefejl i det link, du har fulgt.</p><p>- Siden er flyttet/slettet: Måske findes siden ikke længere eller den er blevet flyttet.</p><p><br /><strong>Bibliotek.dk</strong><br />Prøv den landsdækkende base <a href="http://bibliotek.dk/" target="_blank" title="Bibliotek.dk">bibliotek.dk</a>. Bibliotek.dk er en gratis service, hvor du kan se, hvad der er blevet udgivet i Danmark, og hvad der findes på danske biblioteker. Databasen opdateres dagligt.<br />Du kan bestille materialer til afhentning på dit lokale bibliotek. Du skal være registreret bruger på Odense Centralbibliotek.</p><p><br /><strong>Kom videre - kontakt dit bibliotek</strong><br />Vælg <a href="http://oc.fynbib.dk/biblioteker">\'Biblioteker\'</a> i menuen ovenfor og find kontakt oplysninger på den ønskede afdeling.</p>',
      ),
    ),
  );
  $node->field_ding_page_lead = array(
    'und' => array(
      array(
        'value' => '- men denne side kan måske hjælpe dig videre',
        'format' => NULL,
        'safe_value' => '- men denne side kan måske hjælpe dig videre',
      ),
    ),
  );
  $node->path = array(
    'alias' => 'siden-ikke-fundet',
    'language' => 'und',
  );

  node_save($node);

  // Set the 404 page.
  variable_set('site_404', 'siden-ikke-fundet');
}

/**
 * Add page with std. cookie information.
 */
function ding2_set_cookie_page() {

  $eu_cookie_compliance_da['popup_enabled'] = TRUE;
  $eu_cookie_compliance_da['popup_clicking_confirmation'] = FALSE;
  $eu_cookie_compliance_da['popup_info']['value'] = '<p>Vi bruger cookies på hjemmesiden for at forbedre din oplevelse.</p><p>Læs mere her: <a href="' . url('cookies') . '">Hvad er cookies?</a></p>';
  $eu_cookie_compliance_da['popup_info']['format'] = 'ding_wysiwyg';
  $eu_cookie_compliance_da['popup_agree_button_message'] = 'Jeg accepterer brugen af cookies';
  $eu_cookie_compliance_da['popup_disagree_button_message'] = 'Læs mere';
  $eu_cookie_compliance_da['popup_find_more_button_message'] = 'Mere info';
  $eu_cookie_compliance_da['popup_hide_button_message'] = 'Luk';
  $eu_cookie_compliance_da['popup_agreed'][value] = '<p>Tak fordi du accepterer cookies</p><p>Du kan nu lukke denne besked, eller læse mere om cookies.</p>';
  $eu_cookie_compliance_da['popup_agreed']['format'] = 'ding_wysiwyg';
  $eu_cookie_compliance_da['popup_link'] = 'cookies';
  $eu_cookie_compliance_da['popup_link_new_window'] = FALSE;
  $eu_cookie_compliance_da['popup_bg_hex'] = '0D0D26';
  $eu_cookie_compliance_da['popup_text_hex'] = 'FFFFFF';
  $eu_cookie_compliance_da['popup_position'] = FALSE;
  $eu_cookie_compliance_da['popup_agreed_enabled'] = FALSE;
  $eu_cookie_compliance_da['popup_height'] = '';
  $eu_cookie_compliance_da['popup_width'] = '100%';
  $eu_cookie_compliance_da['popup_delay'] = 1;

  // Set cookie compliance variables
  variable_set('eu_cookie_compliance_da', $eu_cookie_compliance_da);
  variable_set('eu_cookie_compliance_cookie_lifetime', 365);

  $body = '<p><strong>Hvad er cookies?</strong></p>
          <p>En cookie er en lille tekstfil, som lægges på din computer, smartphone, ipad eller lignende med det formål at indhente data. Den gør det muligt for os at måle trafikken på vores site og opsamle viden om f.eks. antal besøg på vores hjemmeside, hvilken browser der bliver brugt, hvilke sider der bliver klikket på, og hvor lang tid der bruges på siden. Alt sammen for at vi kan forbedre brugeroplevelsen og udvikle nye services.</p>
          <p>Når du logger ind for at se lånerstatus, reservere m.m. sættes en såkaldt sessions-cookie. Denne cookie forsvinder, når du logger ud.</p>
          <p><strong>Afvis eller slet cookies</strong></p>
          <p>Du kan altid afvise cookies på din computer ved at ændre indstillingerne i din browser. Du skal dog være opmærksom på, at hvis du slår cookies fra, kan du ikke bruge de funktioner, som forudsætter, at hjemmesiden kan huske dine valg.<br>Alle browsere tillader, at du sletter cookies enkeltvis eller alle på en gang. Hvordan du gør det, afhænger af, hvilken browser du anvender.<br>På Erhvervsstyrelsens hjemmeside kan du finde vejledninger i at afvise og slette cookies i forskellige browsertyper. (<a class="external" href="http://erhvervsstyrelsen.dk/cookies">http://erhvervsstyrelsen.dk/cookies</a>)</p>
          <p><strong>Webtrends</strong></p>
          <p>Vi bruger Webtrends til at føre statistik over trafikken på hjemmesiden. Al indsamlet statistik er anonym.<br>- Webtrends - om brug af cookies på websider (<a class="external" href="http://webtrends.com/terms-policies/privacy/cookie-policy">http://webtrends.com/terms-policies/privacy/cookie-policy</a>)<br>- Hvis du vil fravælge cookies fra Webtrends kan du læse mere på <a class="external" href="http://kb.webtrends.com/articles/Information/Opting-out-of-Tracking-Cookies-1365447872915">http://kb.webtrends.com/articles/Information/Opting-out-of-Tracking-Cookies-1365447872915</a> (engelsk) eller trykke på linket <a class="external" href="https://ondemand.webtrends.com/support/optout.asp?action=out">https://ondemand.webtrends.com/support/optout.asp?action=out</a>. For at aktivere cookies igen kan du trykke på linket <a class="external" href="https://ondemand.webtrends.com/support/optout.asp?action=in">https://ondemand.webtrends.com/support/optout.asp?action=in</a></p>
          <p><strong>Hvorfor informerer Biblioteket om cookies?</strong></p><p>Ifølge "Bekendtgørelse om krav til information og samtykke ved lagring af eller adgang til oplysninger i slutbrugerens terminaludstyr" BEK nr 1148 af 09/12/2011 (<a class="external" href="https://www.retsinformation.dk/Forms/R0710.aspx?id=139279">https://www.retsinformation.dk/Forms/R0710.aspx?id=139279</a>) er alle danske hjemmesider forpligtet til at informere om, hvorvidt de anvender cookies. Det sker, så brugeren kan beslutte, om de fortsat ønsker at besøge hjemmesiden, eller om de evt. ønsker at blokere for cookies.</p>';

  $page_lead = 'Vi vil gerne tilbyde vores brugere en overskuelig og brugervenlig hjemmeside. For at sikre os, at indholdet på siden er relevant og til at finde rundt i, benytter vi os af cookies. Cookies giver os vigtige informationer om, hvordan vores side bliver brugt, hvilke sider der bliver set mest, hvor længe vores brugere bliver på siderne osv.';

  $node = new stdClass();
  $node->uid = 1;
  $node->title = 'Cookies på hjemmesiden';
  $node->type = 'ding_page';
  $node->language = 'und';
  $node->field_ding_page_body = array(
    'und' => array(
      array(
        'value' => $body,
        'format' => 'ding_wysiwyg',
        'safe_value' => $body,
      ),
    ),
  );
  $node->field_ding_page_lead = array(
    'und' => array(
      array(
        'value' => $page_lead,
        'format' => NULL,
        'safe_value' => $page_lead,
      ),
    ),
  );
  $node->path = array(
    'alias' => 'cookies',
    'language' => 'und',
  );

  // Create the node.
  node_save($node);

  // Permissions, see: ding_permissions module
  // display EU Cookie Compliance popup: anonymous user, authenticated user
  // administer EU Cookie Compliance popup: administrators, local administrator
}

/**
 * Enabling Shortcuts plugin for Administration Menu module.
 */
function ding2_admin_menu_shortcuts() {
  if (module_exists('admin_menu')) {
    $content = variable_get('admin_menu_components', array());

    if (empty($content)) {
      module_load_include('inc', 'admin_menu', 'admin_menu');
    }

    $content['icon'] = '1';
    $content['menu'] = '1';
    $content['account'] = '1';
    $content['shortcut.links'] = '1';

    variable_set('admin_menu_components', $content);
  }
}
