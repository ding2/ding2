<?php

/**
 * Defines the Ting field search profile export UI.
 */
$plugin = array(
  'schema' => 'ting_field_search_profile',
  'access' => 'administer site configuration',

  'menu' => array(
    'menu prefix' => 'admin/config/ting',
    'menu item' => 'ting-field-search-profiles',
    'menu title' => 'Ting Field Search Profiles',
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

  'handler' => array(
    'class' => 'ting_field_search_ctools_export_ui',
    'parent' => 'ctools_export_ui',
  ),
);

/**
 * Form builder for the profile edit form.
 */
function ting_field_search_profile_export_form(&$form, &$form_state) {
  $profile = $form_state['item'];

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
    // Profiles can live in code and db, or both. In any case, we can't allow
    // editing of a profile's machine-name, when it also has a definition in
    // code. Use a bit-wise operator to catch all these cases.
    // See ctools export.inc for more info.
    '#disabled' => $profile->export_type & EXPORT_IN_CODE,
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
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#weight' => -15,
  );
  $form['config']['search_request']['agency'] = array(
    '#type' => 'textfield',
    '#title' => t('Library code'),
    '#description' => t('Use an alternative library code. Leave empty to use the <strong>%standard</strong> code configured at <a href="!url"> Ting search settings</a>.', array(
      '%standard' => variable_get('ting_agency', ''),
      '!url' => url('admin/config/ting/settings')
    )),
  );
  $form['config']['search_request']['well_profile'] = array(
    '#type' => 'textfield',
    '#title' => t('Well profile'),
    '#description' => t('Enter the name of the well profile from VIP to use with this profile. Leave empty to use the <strong>%standard</strong> profile configured at <a href="!url">Ting search settings</a>.', array(
        '%standard' => variable_get('ting_search_profile', ''),
        '!url' => url('admin/config/ting/settings'),
    )),
    '#default_value' => $profile->config['search_request']['well_profile'],
  );
  $form['config']['search_request']['query'] = array(
    '#type' => 'textfield',
    '#title' => t('Query'),
    '#description' => t('Enter a base search query that is appended to every search request, when using this profile.'),
    '#maxlength' => 256,
    '#default_value' => $profile->config['search_request']['query'],
    '#size' => 100,
  );
  $form['config']['search_request']['new_materials'] = array(
    '#type' => 'textfield',
    '#title' => t('New materials'),
    '#description' => t('Restrict the search result to only contain new materials acquired whitin the specified number of days.'),
    '#default_value' => $profile->config['search_request']['new_materials'],
    '#element_validate' => array('element_validate_integer_positive'),
  );
  $form['config']['search_request']['allow_empty'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow empty'),
    '#description' => t('Remove the default requirement for a search key.'),
    '#default_value' => $profile->config['search_request']['allow_empty'],
  );

  // User interaction
  $form['config']['user_interaction'] = array(
    '#type' => 'fieldset',
    '#title' => t('User interaction'),
    '#description' => '<strong>' . t('Control how the profile behaves in the UI') . '</strong>',
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

  // Facet settings.
  $form['config']['facets'] = array(
    '#type' => 'fieldset',
    '#title' => t('Facets'),
    '#description' => '<strong>' . t('Facet settings') . '</strong>',
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
  // Nest the rest of the facet settings in a container, so they can be
  // easily disabled/enabled by the use_facets.
  $form['config']['facets']['facets'] = array(
    '#type' => 'container',
    '#title' => t('Facets'),
    '#states' => array(
      'disabled' => array(
        ':input[name="config[facets][use_facets]"]' => array('checked' => FALSE),
      ),
    ),
  );
  $form['config']['facets']['facets']['number_of_facets'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of facets'),
    '#description' => t('Enter the number of facets the search well should return.'),
    '#default_value' => $profile->config['facets']['number_of_facets'],
    '#element_validate' => array('element_validate_integer_positive'),
    '#parents' => array('config', 'facets', 'number_of_facets'),
  );
  $form['config']['facets']['facets']['facet_count'] = array(
    '#type' => 'select',
    '#title' => t('Visible facets amount'),
    '#description' => t('The amount of facets that will be visible on the search page by default. The rest of the facets will be hidden and the user have to click to show them.'),
    '#options' => drupal_map_assoc(range(1, 15)),
    '#default_value' => $profile->config['facets']['facet_count'],
    '#parents' => array('config', 'facets', 'facet_count'),
  );
  $form['config']['facets']['facets']['term_count'] = array(
    '#type' => 'select',
    '#title' => t('Number of terms'),
    '#description' => t('The number of facts terms to display in each facet group.'),
    '#options' => drupal_map_assoc(range(1, $profile->config['facets']['number_of_facets'])),
    '#default_value' => $profile->config['facets']['term_count'],
    '#parents' => array('config', 'facets', 'term_count'),
  );

  $rows = array();
  $row_elements = array();

  // Build facet rows.
  $index = 0;
  $last_facet = NULL;
  if (!empty($profile->facets)) {
    foreach ($profile->facets as $facet) {
      $row = _ting_field_search_build_facet_row($index, $facet);
      $row_elements[$index] = array(
        'name' => &$row['data'][0]['data'],
        'title' => &$row['data'][1]['data'],
        'sorting' => &$row['data'][2]['data'],
        'weight' => &$row['data'][3]['data'],
      );
      $rows[$index] = $row;
      $index++;
      $last_facet = $facet;
    }
  }
  $row = _ting_field_search_build_facet_row($index);
  $row_elements[$index] = array(
    'name' => &$row['data'][0]['data'],
    'title' => &$row['data'][1]['data'],
    'sorting' => &$row['data'][2]['data'],
    'weight' => &$row['data'][3]['data'],
  );
  $rows[$index] = $row;

  $header = array(t('Name'), t('Title'), t('Facet name sorting'), t('Weight'), t('Operations'));
  $form['config']['facets']['facets']['table'] = array(
    '#theme' => 'table',
    'elements' => $row_elements,
    '#header' => $header,
    '#rows' => $rows,
    '#attributes' => array('id' => 'facets'),
  );

  drupal_add_tabledrag('facets', 'order', 'sibling', 'facet-weight');

  // When a new facet is added, ensure that it has a higher weight than the
  // last existing facet, if any.
  // Note: This also ensure that every facet has a different weight, and fixes
  // the ordering bug in the UI.
  // See: ding_facetbrowser.js
  if (isset($last_facet)) {
    $weight = $last_facet['weight'] + 1;
    $form['facets']['table'][$index]['weight']['#default_value'] = $weight;
  }

  // Add some correcting CSS.
  $path = drupal_get_path('module', 'ting_field_search');
  $form['#attached']['css'][] = $path . '/css/ting_field_search.admin.css';

  unset($form['info']);
}

function ting_field_search_profile_export_form_submit($form, &$form_state) {
  $profile = $form_state['item'];

  // Mark any input facet with an empty name to be deleted.
  $profile->facets = array();
  if ($facets = $form_state['values']['facets']) {
    foreach ($facets as $key => $facet) {
      $current = $facets[$key];
      if ($current['name']) {
        $profile->facets[] = $current;
      }
    }
  }

  // There's a 'redirect' option in the export plugin definition, but we need
  // to dynamically insert a fragment so the current tab will be open after
  // redirect. So here we construct the path and set the active tab as fragment
  // manually.
  $active_tab = $form_state['values']['config']['config__active_tab'];
  // Remove it so it doesn't get saved in the DB.
  unset($form_state['values']['config']['config__active_tab']);
  $path ='admin/config/ting/ting-field-search-profiles/list/' . $profile->name;
  // Setup the parameters for drupal_goto().
  $form_state['object']->plugin['redirect']['edit'] = array();
  $form_state['object']->plugin['redirect']['edit'][0] = $path;
  $form_state['object']->plugin['redirect']['edit'][1] = array('fragment' => $active_tab);
}

/**
 * Exists callback for the profile machine-name element.
 */
function ting_field_search_profile_exists($value) {
  // Retrieve existing profile names.
  $profiles = array_keys(ting_field_search_profiles_load_all());

  return in_array($value, $profiles);
}

/**
 * Helper function to prepare a row for the facet table.
 */
function _ting_field_search_build_facet_row($index, $facet = NULL) {
  return array(
    'data' => array(
      array('data' => array(
        '#type' => 'textfield',
        '#title' => t('Facet id'),
        '#title_display' => 'invisible',
        '#default_value' => isset($facet) ? $facet['name'] : '',
        '#parents' => array('facets', $index, 'name'),
      )),
      array('data' => array(
        '#type' => 'textfield',
        '#title' => t('Title'),
        '#title_display' => 'invisible',
        '#default_value' => isset($facet) ? $facet['title'] : '',
        '#parents' => array('facets', $index, 'title'),
      )),
      array('data' => array(
        '#type' => 'select',
        '#title' => t('Facet name sorting'),
        '#title_display' => 'invisible',
        '#options' => ding_facetbrowser_sort_terms_options(),
        '#default_value' => isset($facet['sorting']) ? $facet['sorting'] : 'default',
        '#parents' => array('facets', $index, 'sorting'),
      )),
      array('data' => array(
        '#type' => 'weight',
        '#title' => t('Weight'),
        '#default_value' => isset($facet) ? $facet['weight'] : 0,
        '#title_display' => 'invisible',
        '#attributes' => array('class' => array('facet-weight')),
        '#parents' => array('facets', $index, 'weight'),
      )),
      array('data' => array(
        '#type' => 'link',
        '#title' => t('delete'),
        '#href' =>  'admin/config/ting/settings/ting-field-search-profiles/create',
        '#options' => array('attributes' => array('title' => t('Delete facet.'))),
      )),
    ),
    'class' => array('draggable'),
  );
}
