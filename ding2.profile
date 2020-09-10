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
    if ($form_id == 'opensearch_admin_settings') {
      $form['opensearch']['opensearch_url']['#default_value'] = 'https://opensearch.addi.dk/b3.5_5.2/';
      $form['opensearch']['opensearch_recommendation_url']['#default_value'] = 'http://openadhl.addi.dk/1.1/';
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
  // Add customerror pages.
  ding2_set_customerror_pages();

  // Set cookie page.
  ding2_set_cookie_page();

  // Set EU cookie compliance settings.
  ding2_set_eu_cookie_compliance_settings();

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
    'ding_user_form' => st('Enable normal user login (you should only select this if you are not using adgangsplatformen)'),
    'ding_adgangsplatformen' => st('Single sign-on with Adgangsplatformen'),
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
      'ding_user_form',
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
  // Modules we don't have an explicit dependency on but still want enabled by
  // default. If the user later on does not need the module it can be disabled
  // manually.
  $modules = array_merge(array(
    'opensearch',
    'l10n_update',
    'ting_fulltext',
    'ting_infomedia',
    'ting_field_search',
    'ting_smart_search',
    'ting_subsearch_secondary',
    'ting_subsearch_suggestions',
    'ting_subsearch_translate',
    'ding_eresource',
    'ding_app_content_rss',
    'ding_app_variables',
    'ding_campaign_plus',
    'ding_campaign_plus_auto',
    'ding_campaign_plus_basic',
    'ding_campaign_plus_facet',
    'ding_campaign_plus_object',
    'ding_campaign_plus_search',
    'ding_webtrekk',
  ), $modules);

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
 * Add page with std. cookie information.
 */
function ding2_set_cookie_page() {
  $body = '<p><strong>Hvad er cookies?</strong></p>
    <p>En cookie er en lille tekstfil, som lægges på din computer, smartphone, ipad eller lignende med det formål at indhente data. Den gør det muligt for os at måle trafikken på vores site og opsamle viden om f.eks. antal besøg på vores hjemmeside, hvilken browser der bliver brugt, hvilke sider der bliver klikket på, og hvor lang tid der bruges på siden. Alt sammen for at vi kan forbedre brugeroplevelsen og udvikle nye services.</p>
    <p><strong>Hvorfor informerer Biblioteket om cookies?</strong></p><p>Ifølge "Bekendtgørelse om krav til information og samtykke ved lagring af eller adgang til oplysninger i slutbrugerens terminaludstyr" BEK nr 1148 af 09/12/2011 (<a class="external" href="https://www.retsinformation.dk/Forms/R0710.aspx?id=139279">https://www.retsinformation.dk/Forms/R0710.aspx?id=139279</a>) er alle danske hjemmesider forpligtet til at informere om, hvorvidt de anvender cookies. Det sker, så brugeren kan beslutte, om de fortsat ønsker at besøge hjemmesiden, eller om de evt. ønsker at blokere for cookies.</p>
    <p><strong>Afvis cookies</strong></p>
    <p>Du kan vælge at afvise cookies ved at trykke "Afvis" i den popup, der vises første gang du besøger vores hjemmeside. Har du tidligere besøgt hjemmesiden og accepteret cookies, kan du tilbagekalde ved at trykke "Privatlivsindstillinger" i bunden og herefter trykke på knappen "Tilbagekald samtykke".</p>
    <p>Når du afviser blokerer vi alle cookies. Der er dog undtagelser. Strengt nødvendige cookies, som hjemmesiden ikke fungerer korrekt uden, accepterer du automatisk ved brug af hjemmesiden og vil ikke blive påvirket af, at du afviser cookies. Hvis du logger ind som låner eller opretter dig accepterer du samtidig også brug af vores session-cookie (mere om denne i nedenstående) og denne vil ligeledes heller ikke blive påvirket af dit valg om at afvise cookies.</p>
    <h3>Hvilke cookies bruger vi?</h3>
    <p><strong>Session-cookie</strong></p>
    <p>Når du logger ind for at se lånerstatus, reservere m.m. sættes en såkaldt sessions-cookie. Denne cookie forsvinder, når du logger ud igen. Denne cookie er en forudsætning for, at vi kan tilbyde denne funktionalitet, så du når logger ind, accepterer du samtidig også at vi indstiller denne cookie. Den er dermed ikke påvirket af dit valg om at afvise cookies som forklaret i ovenstående. Når du opretter dig som bruger på biblioteket, skal du samtidig også accepterer vores privatlivspolitik, der indeholder yderligere information om, hvordan vi behandler dine data, når du logger ind.</p>
    <p><strong>Nødvendige cookies</strong></p>
    <p>Nødvendige cookies hjælper med at gøre en hjemmeside brugbar og den kan ikke fungerer korrekt uden. Du accepterer dermed disse cookies, når du bruger vores hjemmeside, og de vil blive indstillet selvom du afviser. Disse cookies indeholder ingen personfølsomme oplsyninger.</p>
    <p><strong>Funktionelle cookies</strong></p>
    <p>Visse stedet bruger vi cookies til at forbedre funktionalitet som f.eks. at huske dine valg, så du ikke skal trykke på samme knap om og om igen. Når du afviser cookies vil disse ikke blive indstillet, og det kan dermed betyde foringelse af brugeroplevelsen.</p>
    <p><strong>Statistik cookies</strong></p>
    <p>Vi bruger cookies til at føre statistik over trafikken på hjemmesiden. Al indsamlet statistik gemmes anonymiseret. Vi bruger dette statistik til at undersøge brugsadfærd med det formål at forbedre kvaliteten af indhold og brugeroplevelsen på hjemmesiden. Afviser du cookies vil denne tracking blive blokeret.</p>';

  $page_lead = 'Vi vil gerne tilbyde vores brugere en overskuelig og brugervenlig hjemmeside. For at sikre os, at indholdet på siden er relevant og til at finde rundt i, benytter vi os af cookies. Cookies giver os vigtige informationer om, hvordan vores side bliver brugt, hvilke sider der bliver set mest, hvor længe vores brugere bliver på siderne osv.';

  $node = new stdClass();
  $node->uid = 1;
  $node->title = 'Cookies på hjemmesiden';
  $node->type = 'ding_page';
  $node->language = 'und';
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

  $paragraph = new ParagraphsItemEntity(array('field_name' => 'field_ding_page_paragraphs', 'bundle' => 'ding_paragraphs_text'));
  $paragraph->is_new = TRUE;
  $paragraph->field_ding_paragraphs_text[LANGUAGE_NONE][0]['value'] = $body;
  $paragraph->field_ding_paragraphs_text[LANGUAGE_NONE][0]['format'] = 'ding_wysiwyg';
  $paragraph->setHostEntity('node', $node);

  // This will also save the node.
  $paragraph->save();

  // Permissions, see: ding_permissions module
  // display EU Cookie Compliance popup: anonymous user, authenticated user
  // administer EU Cookie Compliance popup: administrators, local administrator
}

/**
 * Get the nid of the current node used as cookie page.
 *
 * @return mixed
 *   The node ID of the cookie page node.
 *   FALSE if no cookie page node was found.
 */
function ding2_get_cookie_node_nid() {
  $path = drupal_lookup_path('source', 'cookies');
  if ($path && strpos($path, 'node/') === 0) {
    $path = explode('/', $path);
    return $path[1];
  }
  return FALSE;
}

/**
 * Sets the standard ding2 settings for EU cookie compliance module.
 */
function ding2_set_eu_cookie_compliance_settings() {
  // Ensure that translation variables are enabled for EU Cookie Compliance.
  $controller = variable_realm_controller('language');
  $old_variables = $controller->getEnabledVariables();
  $old_list = variable_children($old_variables);
  $variables = array_merge($old_list, array('eu_cookie_compliance'));
  $controller->setRealmVariable('list', $variables);

  // Set cookie compliance variables.
  $eu_cookie_compliance = i18n_variable_get('eu_cookie_compliance', 'da', []);

  // Ding2 whitelisted cookies. If more are needed: add to array and call this
  // function again in an update.
  $whitelisted_cookies = [
    'has_js',
  ];

  // Ensure we don't override any whitelisted cookies added by administrators or
  // other modules.
  if (empty($eu_cookie_compliance['whitelisted_cookies'])) {
    $eu_cookie_compliance['whitelisted_cookies'] = implode("\r\n", $whitelisted_cookies);
  }
  else {
    foreach ($whitelisted_cookies as $cookie) {
      if (strpos($eu_cookie_compliance['whitelisted_cookies'], $cookie) === FALSE) {
        $eu_cookie_compliance['whitelisted_cookies'] .= "\r\n" . $cookie;
      }
    }
  }

  $eu_cookie_compliance = array_merge($eu_cookie_compliance, [
    'method' => 'opt_in',
    'show_disagree_button' => 1,
    'popup_enabled' => TRUE,
    'popup_info' => [
      'value' => '<h2>Hjælp os med at forbedre oplevelsen på hjemmesiden ved at acceptere cookies.</h2>',
      'format' => 'ding_wysiwyg',
    ],
    'popup_agreed' => array(
      // We do not use the module in a mode where text is displayed after the
      // user agrees but the module expects a value so set an empty string.
      'value' => '',
      'format' => 'ding_wysiwyg',
    ),
    'popup_agree_button_message' => 'Jeg accepterer brugen af cookies',
    'popup_agreed_enabled' => FALSE,
    'popup_disagree_button_message' => 'Mere info',
    'disagree_button_label' => 'Afvis',
    'withdraw_enabled' => 1,
    'withdraw_message' => [
      'value' => '<h2>Vi bruger cookies på hjemmesiden for at forbedre din oplevelse</h2><p>Du har givet os samtykke. Tryk her for at tilbagekalde.</p>',
      'format' => 'ding_wysiwyg',
    ],
    'withdraw_tab_button_label' => 'Privatlivsindstillinger',
    'withdraw_action_button_label' => 'Tilbagekald samtykke',
    // This will make the popup use the bottom position.
    'popup_position' => FALSE,
    'popup_link' => 'cookies',
    'popup_bg_hex' => '0D0D26',
    'popup_text_hex' => 'FFFFFF',
    'popup_height' => '',
    'popup_width' => '100%',
    'popup_delay' => 1000,
    'exclude_admin_pages' => TRUE,
    'consent_storage_method' => 'provider',
    // Use the name of the latest ding2 update hook to change the provider
    // settings to ensure that users have to agree again.
    'cookie_name' => 'cookie-agreed-7083',
  ]);
  i18n_variable_set('eu_cookie_compliance', $eu_cookie_compliance, 'da');
}

/**
 * Setup customerror pages for 403 and 404 status codes.
 */
function ding2_set_customerror_pages() {
  // Set the 403 page.
  $content_403 = array(
    'value' => '<h3>Adgang nægtet</h3><p>Du har ikke adgang til at tilgå siden.</p>',
    'format' => 'ding_wysiwyg',
  );
  variable_set('customerror_403_title', 'Adgang nægtet');
  variable_set('customerror_403', $content_403);
  variable_set('site_403', 'customerror/403');

  // Set the 403 for authenticated users.
  $content_403_authenticated = array(
    'value' => '<h3>' . t('access denied: insufficient permissions') . '</h3><p>' . t('access denied: insufficient permissions') . '</p>',
    'format' => 'plain_text',
  );
  variable_set('customerror_403_authenticated_title',
    t('access denied: insufficient permissions'));
  variable_set('customerror_403_authenticated', $content_403_authenticated);

  // Set the 404 page.
  $content_404 = array(
    'value' => '<h3 class="field-teaser">UPS! Vi kan ikke finde den side du søger.</h3><p><strong>Hvad gik galt?</strong><br />Der kan være flere årsager til, at vi ikke kan finde det du leder efter:</p><p>- Stavefejl: Måske har du stavet forkert, da du skrev søgeordet. Eller der er en stavefejl i det link, du har fulgt.</p><p>- Siden er flyttet/slettet: Måske findes siden ikke længere eller den er blevet flyttet.</p><p><br /><strong>Bibliotek.dk</strong><br />Prøv den landsdækkende base <a href="http://bibliotek.dk/" target="_blank" title="Bibliotek.dk">bibliotek.dk</a>. Bibliotek.dk er en gratis service, hvor du kan se, hvad der er blevet udgivet i Danmark, og hvad der findes på danske biblioteker. Databasen opdateres dagligt.<br />Du kan bestille materialer til afhentning på dit lokale bibliotek. Du skal være registreret bruger på biblioteket.</p><p><br /><strong>Kom videre - kontakt dit bibliotek</strong><br />Find kontakt oplysninger på <a href="/biblioteker">\'den ønskede afdeling\'</a>.</p>',
    'format' => 'ding_wysiwyg',
  );
  variable_set('customerror_404_title', 'Siden blev ikke fundet');
  variable_set('customerror_404', $content_404);
  variable_set('site_404', 'customerror/404');
}
