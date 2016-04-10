<?php

/**
 * @file
 *
 * Admin page callbacks for the Ting field search module.
 */

/**
 * Profile form builder.
 */
function ting_field_search_profile_form($form, &$form_state, $profile = FALSE) {
  // Show a message to the administrator if the module isn't installed
  // correctly. We provide a callback to correct this.
  if (!ting_field_search_get_status()) {
    drupal_set_message(t('Ting field search is NOT installed correctly and will not work properly. Please go to <a href="@install">Installation</a> to correct this.', array(
        '@install' => url('admin/config/ting-field-search/install', array(
          'query' => drupal_get_destination()
        )),
      )
    ), 'error');
  }

  if ($profile) {
    $profile = array_shift($profile);
    $profile->facets = ting_field_search_facets_load($profile->pid);
  }
  else {
    // If we're creating get a new profile object with defaults.
    $profile = ting_field_search_profile_create();
  }

  // Save the original profile object in form_state for later use.
  $form_state['original_profile'] = $profile;

  $form['profile'] = array(
    '#type' => 'fieldset',
    '#title' => t('Create profile'),
  );

  $form['profile']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Profile title'),
    '#description' => t('Enter the title of the profile'),
    '#required' => TRUE,
    '#maxlength' => 255,
    '#default_value' => $profile->title,
  );
  $form['profile']['name'] = array(
    '#type' => 'machine_name',
    '#title' => t('Name (identificator used in URI)'),
    '#description' => t('Enter a unique machine-name for this profile.'),
    '#maxlength' => 64,
    '#default_value' => $profile->name,
    '#machine_name' => array(
      'exists' => 'ting_field_search_profile_exists',
      'source' => array('profile', 'title'),
      'label' => t('Name'),
    ),
    '#disabled' => $profile->pid,
  );
  $form['profile']['weight'] = array(
    '#type' => 'select',
    '#title' => t('Weight'),
    '#description' => t('Determines the profile\'s position when shown in the admin UI and to the user in the select box.'),
    '#options' => drupal_map_assoc(range(-15, 15)),
    '#default_value' => $profile->weight,
  );

  // The main config element. Note that we don't use #tree = TRUE; this should
  // not be needed and saves a level in the hierarchy.
  $form['config'] = array(
    '#type' => 'vertical_tabs',
    '#tree' => TRUE,
  );

  // User interaction
  $form['config']['user_interaction'] = array(
    '#type' => 'fieldset',
    '#title' => t('User interaction'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#weight' => -15,
  );
  $form['config']['user_interaction']['exposed'] = array(
    '#type' => 'checkbox',
    '#title' => t('Exposed'),
    '#description' => t('Show this profile in the select box, so the user can select it before searching.'),
    '#default_value' => $profile->config['user_interaction']['exposed'],
  );
  $form['config']['user_interaction']['sticky'] = array(
    '#type' => 'checkbox',
    '#title' => t('Sticky'),
    '#description' => t('Sticky profiles stay selected when the user navigates the search result.'),
    '#default_value' => $profile->config['user_interaction']['sticky'],
  );
  $form['config']['user_interaction']['alter_links'] = array(
    '#type' => 'checkbox',
    '#title' => t('Alter links'),
    '#description' => t('Append the profile on search links generated on all the search related pages shown with this profile (search result, collection and object pages).'),
    '#default_value' => $profile->config['user_interaction']['alter_links'],
  );

  // Search request settings.
  $form['config']['search_request'] = array(
    '#type' => 'fieldset',
    '#title' => t('Search request'),
    '#description' => t('These settings all effect how the search request is altered when the profile is used on the search result and material pages.'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#weight' => -14,
  );
  $form['config']['search_request']['search_well_profile'] = array(
    '#type' => 'textfield',
    '#title' => t('Search well profile'),
    '#description' => t('Enter the name of the well profile to use when searching. Leave empty to use the <strong>%standard</strong> profile configured in the standard search settings.', array(
      '%standard' => variable_get('ting_search_profile', ''),
    )),
    '#default_value' => $profile->config['search_request']['search_well_profile'],
  );
  $form['config']['search_request']['result_well_profile'] = array(
    '#type' => 'textfield',
    '#title' => t('Result well profile'),
    '#description' => t('Enter name of an alternative well profile to use when displaying search results with this profile. Leave empty to use the same for all requests.'),
    '#default_value' => $profile->config['search_request']['result_well_profile'],
  );
  $form['config']['search_request']['query'] = array(
    '#type' => 'textfield',
    '#title' => t('Query'),
    '#description' => t('Enter a base search query that is appended to every search request, when using this profile.'),
    '#maxlength' => 256,
    '#default_value' => $profile->config['search_request']['query'],
  );
  $form['config']['search_request']['new_materials'] = array(
    '#type' => 'textfield',
    '#title' => t('New materials'),
    '#description' => t('Restrict the search result to only contain new materials acquired whitin the specified number of days.'),
    '#default_value' => $profile->config['search_request']['new_materials'],
    '#element_validate' => array('element_validate_number'),
  );

  // Search result fieldset.
 $form['config']['search_result'] = array(
    '#type' => 'fieldset',
    '#title' => t('Search result'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#weight' => -13,
  );
  $form['config']['search_result']['results_per_page'] = array(
    '#type' => 'textfield',
    '#title' => t('Results per page'),
    '#description' => t('Enter the number of results to display on the search page by default.'),
    '#default_value' => $profile->config['search_result']['results_per_page'],
    '#element_validate' => array('element_validate_integer_positive'),
  );
  $form['config']['search_result']['default_sort'] = array(
    '#type' => 'select',
    '#title' => t('Default sorting'),
    '#description' => t('Select the default sorting'),
    // Use a helper function from ting_search to get available sort options.
    '#options' => ting_search_sort_options(),
    '#default_value' => $profile->config['search_result']['default_sort'],
  );
  $form['config']['search_result']['ranking'] = array(
    '#type' => 'select',
    '#title' => t('Ranking type'),
    '#description' => t('Set the ranking to use when using the best match sort option above.'),
    // These options are copied from ting.admin.inc from Ting module.
    '#options' => array(
      'rank_frequency' => t('Best match'),
      'rank_general' => t('General Rank'),
      'rank_none' => t('No rank'),
    ),
    '#default_value' => $profile ? $profile->config['search_result']['ranking'] : 'rank_frequency',
  );

  // Webtrends fieldset.
  $form['config']['webtrends'] = array(
    '#type' => 'fieldset',
    '#title' => t('Webtrends Analytics'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#weight' => -11,
  );
  $form['config']['webtrends']['onsite_ad'] = array(
    '#type' => 'checkbox',
    '#title' => t('Onsite ads reports'),
    '#description' => t('Track the use of this profile as an onsite ad in Webtrends.'),
    '#default_value' => $profile->config['webtrends']['onsite_ad'],
  );
  $form['config']['webtrends']['onsite_ad_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Onsite ad identificator'),
    '#description' => t('Enter an identificator for the ad which will be shown in the Webtrends UI. Capital letters and spaces are allowed. If left empty the profile title will be used.'),
    '#default_value' => $profile->config['webtrends']['onsite_ad_id'],
    '#states' => array(
      'disabled' => array(
        ':input[name="webtrends[onsite_ad]"]' => array('checked' => FALSE),
      ),
    ),
  );

  // Facet settings.
  $form['config']['facets'] = array(
    '#type' => 'fieldset',
    '#title' => t('Facets'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#weight' => -12,
    'use_facets' => array(
      '#type' => 'checkbox',
      '#title' => t('Use specialized facets'),
      '#description' => t('Leave unchecked to use the standard Ting search facets.'),
      '#default_value' => $profile->config['facets']['use_facets'],
    ),
  );
  // Separate the rest of the facet settings in a container, so they can be
  // easily disabled/enabled by the use_facets. The facet container will be
  // embedded into facet config group
  // This might seem like a weird construct, but for now it works ;).
  $form['facets'] = array(
    '#type' => 'container',
    '#title' => t('Facets'),
    '#tree' => TRUE,
    '#states' => array(
      'disabled' => array(
        ':input[name="config[facets][use_facets]"]' => array('checked' => FALSE),
      ),
    ),
  );
  $form['facets']['number_of_facets'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of facets'),
    '#description' => t('Enter the number of facets the search well should return.'),
    '#default_value' => $profile->config['facets']['number_of_facets'],
    '#element_validate' => array('element_validate_integer_positive'),
  );
  $form['facets']['facet_count'] = array(
    '#type' => 'select',
    '#title' => t('Visible facets amount'),
    '#description' => t('The amount of facets that will be visible on the search page by default. The rest of the facets will be hidden and the user have to click to show them.'),
    '#options' => drupal_map_assoc(range(1, 15)),
    '#default_value' => $profile->config['facets']['facet_count'],
  );
  $form['facets']['term_count'] = array(
    '#type' => 'select',
    '#title' => t('Number of terms'),
    '#description' => t('The number of facts terms to display in each facet group.'),
    '#options' => drupal_map_assoc(range(1, 25)),
    '#default_value' => $profile->config['facets']['term_count'],
  );
  $form['facets']['import'] = array(
    '#type' => 'submit',
    '#value' => t('Import standard facets'),
    '#suffix' => '<div class="description">' . t('Populate the table with the standard facets used in Ting search.') . '</div>',
    '#submit' => array('ting_field_search_import_facets'),
    '#ajax' => array(
      'callback' => 'ting_field_search_import_facets_callback',
      'wrapper' => 'facets',
    ),
  );

  // Build facet rows.
  $index = 0;
  $last_facet = NULL;
  if (!empty($profile->facets)) {
    foreach ($profile->facets as $facet) {
      _ting_field_search_prepare_facet_row($form['facets']['table'], $index, (array) $facet);
      $index++;
      $last_facet = $facet;
    }
  }
  _ting_field_search_prepare_facet_row($form['facets']['table'], $index);

  // When a new facet is added, ensure that it has a higher weight than the
  // last existing facet, if any.
  // Note: This also ensure that every facet has a different weight, and fixes
  // the ordering bug in the UI.
  // See: ding_facetbrowser.js
  if (isset($last_facet)) {
    $weight = $last_facet->weight + 1;
    $form['facets']['table'][$index]['weight']['#default_value'] = $weight;
  }

  // Form actions
  $form['actions'] = array('#type' => 'actions');

  // Save
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  // Delete
  if ($profile) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#submit' => array('ting_field_search_profile_form_delete'),
    );
  }

  // Cancel
  $form['actions']['cancel'] = array(
    '#type' => 'submit',
    '#value' => t('Back'),
    '#submit' => array('ting_field_search_profile_form_cancel'),
    // Bypass form-validation since this is a cancel-button
    '#limit_validation_errors' => array(),
    '#weight' => 40,
  );

  // Add some correcting CSS.
  $path = drupal_get_path('module', 'ting_field_search');
  $form['#attached']['css'][] = $path . '/css/ting_field_search.admin.css';

  return $form;
}

/**
 * Submit callback for the profile form.
 *
 * @see ting_field_search_profile_form()
 */
function ting_field_search_profile_form_submit($form, &$form_state) {
  $profile = $form_state['values'];
  $original_profile = (array) $form_state['original_profile'];

  // The facet settings are kept in a different container; isolate the first.
  $facets = $profile['facets']['table'];
  $facet_settings = array_intersect_key(
    $profile['facets'],
    $original_profile['config']['facets']
  );

  // Isolate the profile values.
  $profile = array_intersect_key($profile, $original_profile);
  // Save and unset the the identifying key added by vertical tabs.
  $active_tab = $profile['config']['config__active_tab'];
  unset($profile['config']['config__active_tab']);

  $profile['facets'] = $facets;
  // Mark any facet with no name to be deleted.
  foreach ($profile['facets'] as $key => $facet) {
    if (!$facet['name']) {
      unset($profile['facets'][$key]);
    }
  }
  $profile['config']['facets'] += $facet_settings;

  // If updating attach the profile id.
  if ($original_profile['pid']) {
    $profile['pid'] = $original_profile['pid'];
  }

  // Regardless, always redirect to ensure the active tab is selected.
  $form_state['redirect'] = array(
    'admin/config/ting/settings/ting-field-search-profiles/' . $profile['name'] . '/edit',
    array(
      'fragment' => $active_tab,
    ),
  );

  if (ting_field_search_profile_save($profile)) {
    drupal_set_message(t('Profile saved'));
  }
  else {
    drupal_set_message(t('Something went wrong saving profile. See log for details.'));
  }
}

/**
 * Theme function for the profile edit form.
 *
 * @see ting_field_search_profile_form().
 */
function theme_ting_field_search_profile_form($variables) {
  $form = $variables['form'];

  // Render facet table.
  $map = array('disabled' => t('Disabled'), 'enabled' => t('Enabled'));
  $header = array(t('Name'), t('Title'), t('Facet name sorting'), t('Weight'), t('Operations'));
  $rows = array();
  foreach (element_children($form['facets']['table']) as $index) {
    $facet = $form['facets']['table'][$index];
    $row = array();
    $row[] = drupal_render($facet['name']);
    $row[] = drupal_render($facet['title']);
    $row[] = drupal_render($facet['sorting']);
    $row[] = drupal_render($facet['weight']);
    $row[] = drupal_render($facet['delete']);
    $rows[] = array(
      'data' => $row,
      'class' => array('draggable'),
    );
  }
  $form['facets']['table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#attributes' => array('id' => 'facets'),
  );
  $form['config']['facets']['settings']['#markup'] = drupal_render($form['facets']);
  //$output .= drupal_render($form['facets']);
  drupal_add_tabledrag('facets', 'order', 'sibling', 'facet-weight');

  // Render action buttons and remaining elements.
  $output = drupal_render_children($form);

  return $output;
}

/**
 * Submit callback for the delete button on the context form.
 *
 * @see ting_field_search_profile_form()
 */
function ting_field_search_profile_form_delete($form, &$form_state) {
  // Pass along any destination parameter set from previous pages
  $destination = array();
  if (isset($_GET['destination'])) {
    $destination = drupal_get_destination();
    unset($_GET['destination']);
  }

  $profile = $form_state['original_profile'];
  $path = 'admin/config/ting/settings/ting-field-search-profiles/' . $profile->name .'/delete';
  $form_state['redirect'] = array($path, array('query' => $destination));
}

/**
 * Form builder for the profile delete confirm form.
 */
function ting_field_search_profile_form_delete_confirm_form($form, &$form_state, $profile) {
  // Store the profile for later use in the submit handler.
  $profile = array_shift($profile);
  $form['ting_field_search_profile'] = array(
    '#type' => 'value',
    '#value' => $profile,
  );

  return confirm_form($form,
    t('Are you sure you want to delete the @profile profile?', array(
      '@profile' => check_plain($profile->title),
    )),
    'admin/config/ting/settings/ting-field-search-profiles/' . $profile->name .'/edit',
    NULL, // This action cannot be undone.
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Submit handler for the profile delete confirm form.
 */
function ting_field_search_profile_form_delete_confirm_form_submit($form, &$form_state) {
  $profile = $form_state['values']['ting_field_search_profile'];

  if (ting_field_search_profile_delete($profile->name)) {
    drupal_set_message(t('Profile @profile deleted', array(
      '@profile' => check_plain($profile->title),
    )));
  }
  else {
    drupal_set_message(t('Something went wrong saving profile. See log for details.'));
  }

  $form_state['redirect'] = 'admin/config/ting/settings';
}

/**
 * Submit calback for the cancel callback on the context form.
 *
 * @see ting_field_search_profile_form()
 */
function ting_field_search_profile_form_cancel($form, &$form_state) {
  // Go back to ting settings
  $form_state['redirect'] = 'admin/config/ting/settings';
}

/**
 * Exists callback for the profile machine-name element.
 */
function ting_field_search_profile_exists($value) {
  // Retrieve existing profile names.
  $profiles = array_keys(ting_field_search_profiles_load());

  return in_array($value, $profiles);
}

function ting_field_search_facet_delete_confirm_form($form, &$form_state, $facet) {

}

/**
 * Helper function to prepare a row for the facet table.
 */
function _ting_field_search_prepare_facet_row(&$element, $index, $facet = NULL) {
  // Code mostly copied from Ding facetbrowser module.

  $element[$index]['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Facet id'),
    '#title_display' => 'invisible',
    '#default_value' => isset($facet) ? $facet['name'] : '',
  );

  $element[$index]['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#title_display' => 'invisible',
    '#default_value' => isset($facet) ? $facet['title'] : '',
  );

  $element[$index]['sorting'] = array(
    '#type' => 'select',
    '#title' => t('Facet name sorting'),
    '#title_display' => 'invisible',
    '#options' => array(
      'default' => t('Ranking (default)'),
      'alphabetical' => t('Alphabetic'),
      'aphabetical_reverse' => t('Alphabetic (reverse)'),
      'numeric' => t('Numeric'),
      'numeric_reverse' => t('Numeric (reverse)'),
    ),
    '#default_value' => isset($facet['sorting']) ? $facet['sorting'] : 'default',
  );

  $element[$index]['weight'] = array(
    '#type' => 'weight',
    '#title' => t('Weight'),
    '#default_value' => isset($facet) ? $facet['weight'] : 0,
    '#title_display' => 'invisible',
    '#attributes' => array('class' => array('facet-weight')),
  );

  $element[$index]['delete'] = array(
    '#type' => 'link',
    '#title' => t('delete'),
    '#href' =>  'admin/config/ting/settings/ting-field-search-profiles/create',
    '#options' => array('attributes' => array('title' => t('Delete facet.'))),
  );
}

function ting_field_search_install_confirm_form($form, &$form_state) {
  // Nothing to do here if installed correctly.
  if (ting_field_search_get_status()) {
    drupal_goto('admin/config/ting/settings');
  }

  $backend = variable_get('cache_class_cache_ting', FALSE);
  if (!$backend) {
    // A default is being used and it's not one if ours.
    $backend = variable_get('cache_default_class', 'DrupalDatabaseCache');
  }

  $message = '<p>' . t('Ting field search will <strong>NOT</strong> function correctly without the proper backend for cache_ting.') . '<//p>';
  $message .= '<p>' . t('The current backend %backend will <strong>NOT</strong> work with Ting field search. Please press install below to correct this.', array('%backend' => $backend)) . '</p>';

  return confirm_form($form,
    t('Confirm installation of Ting field search cache backend'),
    'admin/config/ting/settings',
    $message,
    t('Install'),
    t('Cancel')
  );
}

function ting_field_search_install_confirm_form_submit($form, &$form_state) {
  ting_field_search_install_backend();

  // Verify
  if (ting_field_search_get_status()) {
    drupal_set_message(t('A compatible backend was installed and Ting field search is now functioning properly.'));
  }
  else {
    drupal_set_message(t('Something went wrong. A compatible backend was NOT installed and Ting field search will NOT function properly.'));
  }

  $form_state['#redirect'] = 'admin/config/ting/settings';
}
