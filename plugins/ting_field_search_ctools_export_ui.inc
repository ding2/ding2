<?php

/**
 * Defines the Ting field search profile export UI.
 */
$plugin = array(
  'schema' => 'ting_field_search_profile',
  'access' => 'administer site configuration',

  'menu' => array(
    'menu prefix' => 'admin/config/ting/ting-field-search',
    'menu item' => 'profiles',
    'menu title' => 'Ting field search profiles',
    'menu description' => 'Manage Ting field search profiles',
  ),

  // Provide proper strings for reffering to a profile exportable.
  'title singular' => t('Profile'),
  'title singular proper' => t('Ting field search profile'),
  'title plural' => t('Profiles'),
  'title plural proper' => t('Ting field search profiles'),

  'form' => array(
    'settings' => 'ting_field_search_profile_export_form',
    'submit' => 'ting_field_search_profile_export_form_submit'
  ),
);

function ting_field_search_profile_export_form(&$form, &$form_state) {
  $profile = $form_state['item'];

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
    '#disabled' => !empty($profile->pid),
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

  // Search request settings.
  $form['config']['search_request'] = array(
    '#type' => 'fieldset',
    '#title' => t('Search request'),
    '#description' => '<strong>' .  t('Settings related to the search request') . '</strong>',
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#weight' => -15,
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
    '#size' => 150,
  );
  $form['config']['search_request']['new_materials'] = array(
    '#type' => 'textfield',
    '#title' => t('New materials'),
    '#description' => t('Restrict the search result to only contain new materials acquired whitin the specified number of days.'),
    '#default_value' => $profile->config['search_request']['new_materials'],
    '#element_validate' => array('element_validate_integer_positive'),
  );

  // User interaction
  $form['config']['user_interaction'] = array(
    '#type' => 'fieldset',
    '#title' => t('User interaction'),
    '#description' => '<strong>' . t('Control how the profile behaves in the UI') . '</strong>',
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#weight' => -14,
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

  // Search result fieldset.
 $form['config']['search_result'] = array(
    '#type' => 'fieldset',
    '#title' => t('Search result'),
    '#description' => '<strong>'. t('Control how the search result is presented to the user') . '</strong>',
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
    '#description' => '<strong>'. t('Settings for webtrends integration') . '</strong>',
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
    '#description' => '<strong>' . t('Facet settings') . '</strong>',
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
    '#options' => drupal_map_assoc(range(1, $profile->config['facets']['number_of_facets'])),
    '#default_value' => $profile->config['facets']['term_count'],
  );

  // Build facet rows.
  /*$index = 0;
  $last_facet = NULL;
  if (!empty($profile->facets)) {
    foreach ($profile->facets as $facet) {
      _ting_field_search_prepare_facet_row($form['facets']['table'], $index, $facet);
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
    $weight = $last_facet['weight'] + 1;
    $form['facets']['table'][$index]['weight']['#default_value'] = $weight;
  }*/

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
}

function ting_field_search_profile_export_form_submit($form, &$form_state) {

}
