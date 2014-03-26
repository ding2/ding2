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

    // Set default values in ting search form to help aegir/bulk installations.
    if ($form_id == 'ting_admin_ting_settings') {
      $form['ting']['ting_search_url']['#default_value'] = 'http://opensearch.addi.dk/3.0/';
      $form['ting']['ting_scan_url']['#default_value'] = 'http://openscan.addi.dk/2.0/';
      $form['ting']['ting_spell_url']['#default_value'] = 'http://openspell.addi.dk/1.2/';
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

    // Configure and revert features.
    'ding2_add_settings' => array(
      'display_name' => st('Add default page and settings'),
      'display' => TRUE,
      'run' => INSTALL_TASK_RUN_IF_NOT_COMPLETED,
      'type' => 'normal',
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
  $file = new stdClass();
  $file->uri = DRUPAL_ROOT . '/profiles/ding2/translations/da.po';
  $file->filename = basename($file->uri);
  _locale_import_po($file, 'da', LOCALE_IMPORT_OVERWRITE, 'default');

  // Import field translation group.
  $file = new stdClass();
  $file->uri = DRUPAL_ROOT . '/profiles/ding2/translations/fields_da.po';
  $file->filename = basename($file->uri);
  _locale_import_po($file, 'da', LOCALE_IMPORT_OVERWRITE, 'field');

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
 * Helper function to configure the last parts.
 *
 * Reverts features and adds some basic pages.
 */
function ding2_add_settings(&$install_state) {
  // Revert features to ensure they are all installed as default.
  $features = array(
    'ting_reference',
    'ting_material_details',
    'ding_base',
    'ding_user_frontend',
    'ding_path_alias',
    'ding_content',
    'ding_page',
    'ding_frontend',
    'ding_ting_frontend',
    'ding_event',
    'ding_library',
    'ding_news',
    'ding_groups',
    'ding_campaign_ctype',
    'ding_frontpage',
  );
  ding2_features_revert($features);

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
    '#default_value' => 'alma',
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
    '#description' => 'Enable the SSL proxy module.',
    '#default_value' => TRUE,
  );

  $form['proxy']['sslproxy_var'] = array(
    '#type' => 'textfield',
    '#title' => t('SSL Proxy Variable'),
    '#description' => t('The variable being set by the SSL proxy server.'),
    '#default_value' => 'X-FORWARDED-PROTO',
  );

  $form['proxy']['sslproxy_var_value'] = array(
    '#type' => 'textfield',
    '#title' => t('SSL Proxy Variable Value'),
    '#description' => t('The value of the variable being set by the SSL proxy server.'),
    '#default_value' => 'https',
  );

  //
  // Optional modules.
  //
  $modules = array(
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
    '#default_value' => array(
      'ding_contact',
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

  // Enable the provider (if selected) and modules.
  module_enable($module_list, TRUE);

  // Enable ssl proxy.
  if (isset($values['sslproxy_enable']) && $values['sslproxy_enable']) {
    module_enable(array('sslproxy'), TRUE);
    variable_set('sslproxy_var', $values['sslproxy_var']);
    variable_set('sslproxy_var_value', $values['sslproxy_var_value']);
  }
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
 * Reverts a given set of feature modules.
 *
 * @param array $modules
 *   Names of the modules to revert.
 */
function ding2_features_revert($modules = array()) {
  foreach ($modules as $module) {
    // Load the feature.
    if (($feature = features_load_feature($module, TRUE)) && module_exists($module)) {
      // Get all components of the feature.
      foreach (array_keys($feature->info['features']) as $component) {
        if (features_hook($component, 'features_revert')) {
          // Revert each component (force).
          features_revert(array($module => array($component)));
        }
      }
    }
  }
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
  $node = new stdClass();
  $node->uid = 1;

  $node->title = 'Cookie- og privatlivspolitik';
  $node->type = 'ding_page';
  $node->language = 'und';
  $node->field_ding_page_body = array(
    'und' => array(
      array(
        'value' => '<p><strong>Hvad er en cookie?</strong></p><p>En cookie er en lille tekstfil, der lagres i din browser for at kunne genkende din computer ved tilbagevendende besøg. Cookies er ikke aktive filer; de kan altså ikke udvikle virus eller spore indhold på din computer. Det eneste, de gør, er at sende anonyme oplysninger tilbage til os om fx besøgstidspunkt, -varighed osv.</p><p><strong>På denne hjemmeside bruger vi cookies til følgende formål:</strong></p><ul><li>Statistik: Vi bruger Google Analytics og Webtrends til at føre statistik over trafikken på siden, sådan at vi bedst muligt kan tilpasse den brugernes behov. Vi får blandt andet oplysninger om antal besøg, gennemsnitlig besøgsvarighed og færden rundt på siden.</li><li>Login: Når du logger ind for at se lånerstatus, reservere m.m. sættes en sessions-cookie. Denne cookie forsvinder når du lukker browseren.</li></ul><p><strong>Hvis du ikke vil tillade cookies</strong></p><p>Hvis du ikke vil tillade brugen af cookies på din computer, kan du ændre i indstillingerne i din browser, så den husker det fremover. Du kan også slette cookies, der allerede er lagret.<br />Se vejledning og læs mere om cookies på <a href="http://minecookies.org/cookiehandtering" target="_blank" title="Cookiehåndtering">http://minecookies.org/cookiehandtering</a>.<br />Vær opmærksom på, at du ved at spærre for cookies besværliggør brugen af hjemmesiden.</p><p><strong>Brug af personoplysninger</strong><br />Personoplysninger bliver på intet tidspunkt videregivet eller solgt til tredjepart, og vi indsamler ikke personoplysninger, uden du selv har givet os disse.</p>',
        'format' => 'ding_wysiwyg',
        'safe_value' => '<p><strong>Hvad er en cookie?</strong></p><p>En cookie er en lille tekstfil, der lagres i din browser for at kunne genkende din computer ved tilbagevendende besøg. Cookies er ikke aktive filer; de kan altså ikke udvikle virus eller spore indhold på din computer. Det eneste, de gør, er at sende anonyme oplysninger tilbage til os om fx besøgstidspunkt, -varighed osv.</p><p><strong>På denne hjemmeside bruger vi cookies til følgende formål:</strong></p><ul><li>Statistik: Vi bruger Google Analytics og Webtrends til at føre statistik over trafikken på siden, sådan at vi bedst muligt kan tilpasse den brugernes behov. Vi får blandt andet oplysninger om antal besøg, gennemsnitlig besøgsvarighed og færden rundt på siden.</li><li>Login: Når du logger ind for at se lånerstatus, reservere m.m. sættes en sessions-cookie. Denne cookie forsvinder når du lukker browseren.</li></ul><p><strong>Hvis du ikke vil tillade cookies</strong></p><p>Hvis du ikke vil tillade brugen af cookies på din computer, kan du ændre i indstillingerne i din browser, så den husker det fremover. Du kan også slette cookies, der allerede er lagret.<br />Se vejledning og læs mere om cookies på <a href="http://minecookies.org/cookiehandtering" target="_blank" title="Cookiehåndtering">http://minecookies.org/cookiehandtering</a>.<br />Vær opmærksom på, at du ved at spærre for cookies besværliggør brugen af hjemmesiden.</p><p><strong>Brug af personoplysninger</strong><br />Personoplysninger bliver på intet tidspunkt videregivet eller solgt til tredjepart, og vi indsamler ikke personoplysninger, uden du selv har givet os disse.</p>',
      ),
    ),
  );
  $node->field_ding_page_lead = array(
    'und' => array(
      array(
        'value' => 'Vi vil gerne tilbyde vores brugere en overskuelig og brugervenlig hjemmeside. For at sikre os, at indholdet på siden er relevant og til at finde rundt i, benytter vi os af cookies. Cookies giver os vigtige informationer om, hvordan vores side bliver brugt, hvilke sider der bliver set mest, hvor længe vores brugere bliver på siderne osv.',
        'format' => NULL,
        'safe_value' => 'Vi vil gerne tilbyde vores brugere en overskuelig og brugervenlig hjemmeside. For at sikre os, at indholdet på siden er relevant og til at finde rundt i, benytter vi os af cookies. Cookies giver os vigtige informationer om, hvordan vores side bliver brugt, hvilke sider der bliver set mest, hvor længe vores brugere bliver på siderne osv.',
      ),
    ),
  );
  $node->path = array(
    'alias' => 'cookies',
    'language' => 'und',
  );

  // Create the node.
  node_save($node);

  // Set the node as read more node.
  variable_set('cookiecontrol_privacynode', $node->nid);

  // Set short texts (cookie popup).
  variable_set('cookiecontrol_text', '<p>Dette site bruger cookies til at gemme oplysninger på din computer.</p>');
  variable_set('cookiecontrol_fulltext', '<p>Vi vil gerne tilbyde vores brugere en overskuelig og brugervenlig hjemmeside. For at sikre os, at indholdet på siden er relevant og til at finde rundt i, benytter vi os af cookies. Cookies giver os vigtige informationer om, hvordan vores side bliver brugt, hvilke sider der bliver set mest, hvor længe vores brugere bliver på siderne osv.</p>');
}
