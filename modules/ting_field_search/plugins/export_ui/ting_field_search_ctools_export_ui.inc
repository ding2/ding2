<?php

/**
 * @file
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
    'submit' => 'ting_field_search_profile_export_form_submit',
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
    '#element_validate' => array('ting_field_search_machine_name_validate'),
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
    '#description' => t("Determines the profile's position when shown in the admin UI and to the user in the select box."),
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
    '#description' => '<strong>' . t('Settings related to the search request') . '</strong>',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#weight' => -15,
  );
  $form['config']['search_request']['agency'] = array(
    '#type' => 'textfield',
    '#title' => t('Library code'),
    '#description' => t('Use an alternative library code. Leave empty to use the <strong>%standard</strong> code configured at <a href="!url"> Ting search settings</a>.', array(
      '%standard' => variable_get('ting_agency', ''),
      '!url' => url('admin/config/ting/settings'),
    )),
  );
  $form['config']['search_request']['well_profile'] = array(
    '#type' => 'textfield',
    '#title' => t('Well profile'),
    '#description' => t('Enter the name of the well profile from VIP to use with this profile. Leave empty to use the <strong>%standard</strong> profile configured at <a href="!url">OpenSearch settings</a>.', array(
      '%standard' => variable_get('opensearch_search_profile', ''),
      '!url' => url('admin/config/ding/provider/opensearch'),
    )),
    '#default_value' => $profile->config['search_request']['well_profile'],
  );
  $form['config']['search_request']['query'] = array(
    '#type' => 'textfield',
    '#title' => t('Query'),
    '#description' => t('Enter a base search query that is appended to every search request, when using this profile.'),
    '#maxlength' => 1024,
    '#default_value' => $profile->config['search_request']['query'],
    '#size' => 100,
  );
  $form['config']['search_request']['new_materials'] = array(
    '#type' => 'textfield',
    '#title' => t('New materials'),
    '#description' => t('Enter a number of days to restrict the search result to only contain new materials.'),
    '#default_value' => $profile->config['search_request']['new_materials'],
    '#element_validate' => array('element_validate_integer_positive'),
  );

  // User interaction.
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

  $form['config']['user_interaction']['grouping'] = array(
    '#type' => 'textfield',
    '#title' => t('Profile grouping'),
    '#description' => t('Which group of search profiles should be shown when this profile is used.'),
    '#default_value' => !empty($profile->config['user_interaction']['grouping']) ? $profile->config['user_interaction']['grouping'] : 'default',
  );
  $form['config']['user_interaction']['visibility'] = array(
    '#type' => 'radios',
    '#title' => t('Show search profiles on specific pages'),
    '#options' => array(
      'all' => t('Show on all pages.'),
      'except' => t('All pages except those listed'),
      'only' => t('Only the listed pages'),
    ),
    '#default_value' => !empty($profile->config['user_interaction']['visibility']) ? $profile->config['user_interaction']['visibility'] : 'all',
  );
  $form['config']['user_interaction']['pages'] = array(
    '#type' => 'textarea',
    '#title' => 'Pages',
    '#default_value' => $profile->config['user_interaction']['pages'],
    '#description' => t("Specify pages by using their paths. Enter one path per line. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.",
      array(
        '%blog' => 'blog',
        '%blog-wildcard' => 'blog/*',
        '%front' => '<front>',
      )),
    '#states' => array(
      'invisible' => array(
        ':input[name="config[user_interaction][visibility]"]' => array('value' => 'all'),
      ),
    ),
  );
  $form['config']['user_interaction']['search_box'] = array(
    '#type' => 'checkbox',
    '#title' => 'Expand search box',
    '#default_value' => $profile->config['user_interaction']['search_box'],
    '#description' => t('If checked the search box is expanded as default on the matching pages.'),
    '#states' => array(
      'invisible' => array(
        ':input[name="config[user_interaction][visibility]"]' => array('value' => 'all'),
      ),
    ),
  );
  $form['config']['user_interaction']['default_profile'] = array(
    '#type' => 'checkbox',
    '#title' => 'Default profile',
    '#default_value' => $profile->config['user_interaction']['default_profile'],
    '#description' => t('If checked this profile is pre-selected on the pages selected above.'),
    '#states' => array(
      'invisible' => array(
        ':input[name="config[user_interaction][visibility]"]' => array('value' => 'all'),
      ),
    ),
  );

  // Search result fieldset.
  $form['config']['search_result'] = array(
    '#type' => 'fieldset',
    '#title' => t('Search result'),
    '#description' => '<strong>' . t('Control how the search result is presented to the user') . '</strong>',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#weight' => -13,
  );
  $form['config']['search_result']['default_sort'] = array(
    '#type' => 'select',
    '#title' => t('Default sorting'),
    '#description' => t('Select the default sorting'),
    // Use a helper function from ting_search to get available sort options.
    '#options' => ting_search_sort_form_options(),
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

  $header = array(
    t('Name'),
    t('Title'),
    t('Facet name sorting'),
    t('Weight'),
    t('Operations'),
  );
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
  // See: ding_facetbrowser.js.
  if (isset($last_facet)) {
    $weight = $last_facet['weight'] + 1;
    $form['facets']['table'][$index]['weight']['#default_value'] = $weight;
  }

  // Field settings.
  $form['config']['fields'] = array(
    '#type' => 'fieldset',
    '#title' => t('Fields'),
    '#description' => '<strong>' . t('Field settings') . '</strong>',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#weight' => -10,
  );

  // Base path for group and field config.
  $base = 'admin/config/ting/ting-field-search-profiles/' . $profile->name;

  // Need a profile machine_name to add groups.
  // TODO: Find out how we can determine if a profile is being imported. This
  // only protects against profiles being created.
  if (!empty($profile->name)) {
    $form['config']['fields']['add_group'] = array(
      '#prefix' => '<ul class="action-links"><li>',
      '#type' => 'link',
      '#title' => t('Add field group'),
      '#href' => $base . '/groups/add',
      '#suffix' => '</li></ul>',
    );
  }

  // Ensure fields and fields groups are displayed sorted by weight.
  ting_field_search_profile_fields_sort($profile);

  // Build field groups if present.
  if (!empty($profile->groups)) {
    foreach ($profile->groups as $group_name => $group) {
      $form['config']['fields'][$group_name] = array(
        '#type' => 'fieldset',
        '#title' => check_plain($group['title']),
        '#collapsible' => TRUE,
      );

      // Field group information.
      if (!empty($group['description'])) {
        $form['config']['fields'][$group_name]['description'] = array(
          '#type' => 'item',
          '#title' => t('Description'),
          '#markup' => check_plain($group['description']),
        );
      }
      $form['config']['fields'][$group_name]['columns'] = array(
        '#type' => 'item',
        '#title' => t('Columns'),
        '#markup' => check_plain($group['columns']),
      );
      $form['config']['fields'][$group_name]['weight'] = array(
        '#type' => 'select',
        '#title' => t('Weight'),
        '#options' => drupal_map_assoc(range(-15, 15)),
        '#default_value' => $group['weight'],
      );

      // Edit field group link.
      $form['config']['fields'][$group_name]['edit_group'] = array(
        '#type' => 'item',
        '#markup' => l(
          t('Edit field group'),
          $base . '/groups/' . $group_name .  '/edit',
          array('attributes' => array('class' => array('edit-field-group')))
        ),
      );

      // Add field link.
      $form['config']['fields'][$group_name]['add_field'] = array(
        '#prefix' => '<ul class="action-links add-field"><li>',
        '#type' => 'link',
        '#title' => t('Add field'),
        '#href' => $base . '/fields/' . $group_name . '/add',
        '#suffix' => '</li></ul>',
      );

      // Prepare the table render array for the fields in the group.
      $header = array(t('Title'), t('Type'), t('Index') , t('Weight'), t('Operations'));
      $table_id = 'fields-' . $group_name;
      $form['config']['fields'][$group_name]['table'] = array(
        '#theme' => 'table',
        '#header' => $header,
        '#attributes' => array('id' => $table_id),
        '#empty' => t('No fields added to this group'),
      );
      drupal_add_tabledrag($table_id, 'order', 'sibling', 'field-weight');
    }
  }

  // Build field rows and add them to their field group table.
  if (!empty($profile->fields)) {
    $rows = array();
    $row_elements = array();
    foreach ($profile->fields as $index => $field) {
      $row = _ting_field_search_build_field_row($field, $base . '/fields');
      $group_name = $field['group_name'];
      $row_elements[$group_name][$index] = array(
        // We only allow field value to be manipulated in the table, so that is
        // the only element we need outside the table.
        'weight' => &$row['data'][3]['data'],
      );
      $rows[$group_name][$index] = $row;
    }

    foreach (array_keys($rows) as $group_name) {
      $form['config']['fields'][$group_name]['table'] += array(
        'elements' => $row_elements[$group_name],
        '#rows' => $rows[$group_name],
      );
    }
  }

  // Profile page config.
  $form['config']['profile_page'] = array(
    '#type' => 'fieldset',
    '#title' => t('Profile page'),
    '#description' => '<strong>' . t('Profile page settings') . '</strong>',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#weight' => -10,
  );
  $form['config']['profile_page']['enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable profile page'),
    '#description' => t('Enable the dedicated page for this profile'),
    '#default_value' => $profile->config['profile_page']['enabled'],
  );
  $form['config']['profile_page']['profile_page_link'] = array(
    '#type' => 'item',
    '#description' => t('Profile page enabled at <a href="!url">!url</a>', array(
      '!url' => url('ting-field-search/profile/' . $profile->name),
    )),
    '#access' => $profile->config['profile_page']['enabled'],
  );

  // Add some correcting CSS.
  $path = drupal_get_path('module', 'ting_field_search');
  $form['#attached']['css'][] = $path . '/css/ting_field_search.admin.css';

  unset($form['info']);
}

/**
 * Submit handler for the profile save form.
 */
function ting_field_search_profile_export_form_submit($form, &$form_state) {
  $profile = &$form_state['item'];

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

  // Enable direct editing of field groups on the profile form.
  if (isset($form_state['values']['config']['fields'])) {
    $group_config = $form_state['values']['config']['fields'];
    // We don't wan't these carried over to profile config.
    unset($form_state['values']['config']['fields']);
    foreach ($group_config as $group_name => $group_config) {
      $profile->groups[$group_name]['weight'] = $group_config['weight'];
    }
  }

  // Update field weights.
  if (isset($form_state['values']['field-weights'])) {
    foreach ($form_state['values']['field-weights'] as $index => $value) {
      if (isset($profile->fields[$index])) {
        $profile->fields[$index]['weight'] = $value['weight'];
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
  $path = 'admin/config/ting/ting-field-search-profiles/list/' . $profile->name;

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

  if ($value == 'node') {
    $profiles[] = 'node';
  }

  return in_array($value, $profiles);
}

/**
 * Custom validation callback for machine name field.
 */
function ting_field_search_machine_name_validate($element, &$form_state, $form) {
  if ($element['#value'] == 'node') {
    form_error($element, t("You can't use <strong>'node'</strong> as machine name for profile."));
  }
}

/**
 * Helper function to prepare a row for the facet table.
 */
function _ting_field_search_build_facet_row($index, $facet = NULL) {
  return array(
    'data' => array(
      array(
        'data' => array(
          '#type' => 'textfield',
          '#title' => t('Facet id'),
          '#title_display' => 'invisible',
          '#default_value' => isset($facet) ? $facet['name'] : '',
          '#parents' => array('facets', $index, 'name'),
        ),
      ),
      array(
        'data' => array(
          '#type' => 'textfield',
          '#title' => t('Title'),
          '#title_display' => 'invisible',
          '#default_value' => isset($facet) ? $facet['title'] : '',
          '#parents' => array('facets', $index, 'title'),
        ),
      ),
      array(
        'data' => array(
          '#type' => 'select',
          '#title' => t('Facet name sorting'),
          '#title_display' => 'invisible',
          '#options' => ding_facetbrowser_sort_terms_options(),
          '#default_value' => isset($facet['sorting']) ? $facet['sorting'] : 'default',
          '#parents' => array('facets', $index, 'sorting'),
        ),
      ),
      array(
        'data' => array(
          '#type' => 'weight',
          '#title' => t('Weight'),
          '#default_value' => isset($facet) ? $facet['weight'] : 0,
          '#title_display' => 'invisible',
          '#attributes' => array('class' => array('facet-weight')),
          '#parents' => array('facets', $index, 'weight'),
        ),
      ),
      array(
        'data' => array(
          '#type' => 'link',
          '#title' => t('delete'),
          '#href' => 'admin/config/ting/settings/ting-field-search-profiles/create',
          '#options' => array('attributes' => array('title' => t('Delete facet.'))),
        ),
      ),
    ),
    'class' => array('draggable'),
  );
}

/**
 * Helper function to prepare a field row for tabledrag.
 */
function _ting_field_search_build_field_row($field, $base) {
  return array(
    'data' => array(
      array('data' => array(
        '#markup' => $field['title'],
      )),
      array('data' => array(
        '#markup' => $field['type'],
      )),
      array('data' => array(
        '#markup' => $field['index'],
      )),
      array('data' => array(
        '#type' => 'weight',
        '#title' => t('Weight'),
        '#default_value' => $field['weight'],
        '#title_display' => 'invisible',
        '#attributes' => array('class' => array('field-weight')),
        '#parents' => array('field-weights', $field['index'], 'weight'),
      )),
      array('data' => array(
        '#theme' => 'links',
        '#attributes' => array('class' => array('inline')),
        '#links' => array(
          array(
            'title' => t('Edit'),
            'href' => $base . '/' . $field['group_name'] . '/' . $field['index'] . '/edit',
          ),
          array(
            'title' => t('Delete'),
            'href' => $base . '/' . $field['index'] . '/delete',
          ),
        ),
      )),
    ),
    'class' => array('draggable'),
  );
}
