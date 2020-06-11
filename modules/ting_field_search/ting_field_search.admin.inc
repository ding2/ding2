<?php

/**
 * @file
 * Admin page callbacks for the Ting field search module.
 */

/**
 * Implements hook_form().
 */
function ting_field_search_settings_form($form, &$form_state) {
  $form = array();

  return $form;
}

function ting_field_search_field_form($form, &$form_state, $profile, $group_name, $field_index = FALSE) {
  $form = array();

  // Field defaults.
  $field = array(
    'type' => 'textfield',
    'title' => '',
    'title_display' => TRUE,
    'description' => '',
    'description_display' => TRUE,
    'prefix' => '',
    'suffix' => '',
    'group_name' => $group_name,
    'placeholder' => 1,
    'options' => array(),
    'column_count' => 1,
  );

  if ($field_index) {
    $field = array_merge($field, $profile->fields[$field_index]);
    // Convert index to prefix/suffix.
    $index = explode('.', $field['index']);
    $field['prefix'] = $index[0];
    $field['suffix'] = $index[1];
  }
  $form_state['field'] = $field;
  $form_state['profile'] = $profile;

  $type_options = array();
  foreach (ting_field_search_field_types() as $type => $labels) {
    $type_options[$type] = $labels['single'];
  }
  $group_options = array();
  foreach ($profile->groups as $group_name => $group) {
    $group_options[$group_name] = $group['title'];
  }

  $form['type'] = array(
    '#type' => 'select',
    '#title' => t('Field type'),
    '#description' => t('Select a field type.'),
    '#options' => $type_options,
    '#default_value' => $field['type'],
  );
  $form['column_count'] = array(
    '#type' => 'select',
    '#title' => t('Column count'),
    '#description' => t('Select the number of columns for the options.'),
    '#options' => drupal_map_assoc(range(1, 5)),
    '#default_value' => $field['column_count'],
    '#states' => array(
      'visible' => array(
        ':input[name="type"]' => array(
          array('value' => 'checkboxes'),
          array('value' => 'radios'),
        ),
      ),
    ),
  );
  $form['group_name'] = array(
    '#type' => 'select',
    '#title' => t('Field group'),
    '#description' => t('Select a field group.'),
    '#options' => $group_options,
    '#default_value' => $field['group_name'],
  );
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#description' => t('Enter the field title.'),
    '#maxlength' => 128,
    '#default_value' => $field['title'],
    '#required' => TRUE,
  );
  $form['title_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display title'),
    '#default_value' => $field['title_display'],
  );
  $form['description'] = array(
    '#type' => 'textfield',
    '#title' => t('Description'),
    '#description' => t('Describe the purpose of the field to the user (e.g. "Search after an author...")'),
    '#maxlength' => 128,
    '#default_value' => $field['description'],
  );
  $form['description_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display description'),
    '#default_value' => $field['description_display'],
  );
  $form['placeholder'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show description as placeholder text (only applies to textfields)'),
    '#default_value' => TRUE,
    '#states' => array(
      'visible' => array(
        ':input[name="type"]' => array('value' => 'textfield'),
        ':input[name="description_display"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['index'] = array(
      '#type' => 'fieldset',
      '#title' => t('Index'),
      '#tree' => FALSE,
    );
  $form['index']['prefix'] = array(
    '#type' => 'select',
    '#title' => t('Prefix'),
    '#description' => t('Select a prefix for the index.'),
    '#options' => array(
      'term' => 'term',
      'facet' => 'facet',
      'dkcclterm' => 'dkcclterm',
      'holdingsitem' => 'holdingsitem',
      'phrase' => 'phrase',
      'dkcclphrase' => 'dkcclphrase',
    ),
    '#default_value' => $field['prefix'],
  );
  $form['index']['suffix'] = array(
    '#type' => 'textfield',
    '#title' => t('Suffix'),
    '#description' => t('Enter the suffix of the index (single word e.g. "title").'),
    '#maxlength' => 128,
    '#default_value' => $field['suffix'],
    '#required' => TRUE,
  );
  $form['index']['options'] = array(
    '#type' => 'textarea',
    '#title' => t('Options'),
    '#description' => t('Enter a key|value pair pr. line. Key is used in the search query and values is shown to the user. For radios and select type fields, use the key "all" as default value (e.g. "all|All").'),
    '#cols' => 30,
    '#rows' => 6,
    '#default_value' => $field['options'],
    '#states' => array(
      'visible' => array(
        ':input[name="type"]' => array(
          array('value' => 'checkboxes'),
          array('value' => 'radios'),
          array('value' => 'select'),
        ),
      ),
    ),
  );

  // Form actions.
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  // Delete button
  if (!empty($field['index'])) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#submit' => array('ting_field_search_field_form_delete'),
    );
  }
  $form['actions']['cancel'] = array(
    '#type' => 'submit',
    '#value' => t('Back'),
    '#submit' => array('ting_field_search_form_cancel'),
    // Bypass form-validation since this is a cancel-button.
    '#limit_validation_errors' => array(),
    '#weight' => 40,
  );

  return $form;
}

function ting_field_search_field_form_validate($form, &$form_state) {
  $index = $form_state['values']['suffix'];
  $index = str_replace(array('æ', 'ø', 'å'), '', $index);
  if (!ctype_alpha(trim($index))) {
    form_set_error('suffix',
      t('Suffix must be one word and only contain alphabetic characters.')
    );
  }
}

function ting_field_search_field_form_submit($form, &$form_state) {
  $profile = $form_state['profile'];
  $field = $form_state['field'];
  $existing = !empty($field['index']) ? $field['index'] : FALSE;

  $values = array_intersect_key($form_state['values'], $field);
  $field = array_merge($field, $values);

  // Build the index of the field. The index is unique on the profile and will
  // function as a machine_name for the field.
  $field['index'] = $field['prefix'] . '.' . $field['suffix'];
  unset($field['prefix']);
  unset($field['suffix']);

  // Determine the weight for new fields.
  if ($existing === FALSE) {
    $field['weight'] = 0;
    foreach ($profile->fields as $current) {
      if ($current['weight'] > $field['weight']) {
        $field['weight'] = $current['weight'];
      }
    }
    $field['weight']++;
  }

  if ($existing) {
    unset($profile->fields[$existing]);
  }
  $profile->fields[$field['index']] = $field;

  // Save, set message and go back,.
  $operation = $existing ? t('updated on') : t('added to');
  if (ting_field_search_profile_save($profile)) {
    drupal_set_message(t('Field @operation %profile successfully!', array(
      '@operation' => $operation,
      '%profile' => $profile->name,
    )));
  }
  else {
    drupal_set_message(t('Something went wrong. No field was @operation %profile.', array(
      '@operation' => $operation,
      '%profile' => $profile->name,
    )), 'error');
  }

  $path = 'admin/config/ting/ting-field-search-profiles/list/' . $profile->name . '/edit';
  $form_state['redirect'] = array($path, array('fragment' => '#edit-config-fields'));
}

function ting_field_search_form_cancel($form, &$form_state) {
  $profile = $form_state['profile'];
  $path = 'admin/config/ting/ting-field-search-profiles/list/' . $profile->name . '/edit';
  $form_state['redirect'] = array($path, array('fragment' => 'edit-config-fields'));
}

function ting_field_search_field_form_delete($form, &$form_state) {
  $profile = $form_state['profile'];
  $field = $form_state['field'];
  $path = 'admin/config/ting/ting-field-search-profiles/' . $profile->name;
  $path .= '/fields/' . $field['index'] . '/delete';
  $form_state['redirect'] = $path;
}

function ting_field_search_field_delete_confirm_form($form, &$form_state, $profile, $field_index) {
  $form_state['profile'] = $profile;
  $form_state['field_index'] = $field_index;
  $field = $profile->fields[$field_index];
  $path = 'admin/config/ting/ting-field-search-profiles/' . $profile->name;
  $path .= '/fields/' . $field['group_name'] . '/' . $field_index . '/edit';

  return confirm_form(
    $form,
    t('Confirm deletion of %field on %profile', array(
      '%field' => $field_index,
      '%profile' => $profile->name,
    )),
    $path,
    NULL,
    t('Delete'),
    t('Cancel')
  );
}

function ting_field_search_field_delete_confirm_form_submit($form, &$form_state) {
  $profile = $form_state['profile'];
  $field_index = $form_state['field_index'];

  // Remove field and update profile.
  unset($profile->fields[$field_index]);
  if (ting_field_search_profile_save($profile)) {
    drupal_set_message(t('The field %field was removed from %profile', array(
      '%field' => $field_index,
      '%profile' => $profile->name,
    )));
  }
  else {
    drupal_set_message(t('Something went wrong removing %field from %profile', array(
      '%field' => $field_index,
      '%profile' => $profile->name,
    )), 'error');
  }

  $path = 'admin/config/ting/ting-field-search-profiles/list/' . $profile->name . '/edit';
  $form_state['redirect'] = array($path, array('fragment' => '#edit-config-fields'));
}

function ting_field_search_group_form($form, &$form_state, $profile, $group_name = FALSE) {
  $form = array();

  // Group defaults.
  $group = array(
    'name' => '',
    'title' => '',
    'title_display' => TRUE,
    'description' => '',
    'description_display' => FALSE,
    'collapsible' => TRUE,
    'collapsed' => TRUE,
    'columns' => 3,
    'weight' => 15,
  );

  if ($group_name) {
    $group = array_merge($group, $profile->groups[$group_name]);
  }
  $form_state['existing'] = $group_name;
  $form_state['group'] = $group;
  $form_state['profile'] = $profile;

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#description' => t('Enter the field group title.'),
    '#maxlength' => 128,
    '#default_value' => $group['title'],
    '#required' => TRUE,
  );
  $form['name'] = array(
    '#type' => 'machine_name',
    '#title' => t('Group machine-name'),
    '#description' => t('Enter a unique group machine-name.'),
    '#maxlength' => 64,
    '#default_value' => $group['name'],
    '#disabled' => !empty($group['name']),
    '#machine_name' => array(
      'exists' => 'ting_field_search_group_exists',
      'source' => array('title'),
      'label' => t('Name'),
    ),
  );
  $form['title_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display title'),
    '#default_value' => $group['title_display'],
  );
  $form['description'] = array(
    '#type' => 'textfield',
    '#title' => t('Description'),
    '#description' => t('Enter a general description of the field group and the fields it contains.'),
    '#maxlength' => 128,
    '#default_value' => $group['description'],
  );
  $form['description_display'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display description'),
    '#default_value' => $group['description_display'],
  );
  $form['collapsible'] = array(
    '#type' => 'checkbox',
    '#title' => t('Collapsible'),
    '#default_value' => $group['collapsible'],
  );
  $form['collapsed'] = array(
    '#type' => 'checkbox',
    '#title' => t('Collapsed'),
    '#default_value' => $group['collapsed'],
  );
  $form['columns'] = array(
    '#type' => 'select',
    '#title' => t('Columns'),
    '#description' => t('Number of fields in each row.'),
    '#options' => drupal_map_assoc(range(2, 5)),
    '#default_value' => $group['columns'],
    '#size' => 4,
  );
  $form['weight'] = array(
    '#type' => 'select',
    '#title' => t('Weight'),
    '#description' => t('Determines the position of the group on the search form.'),
    '#options' => drupal_map_assoc(range(-15, 15)),
    '#default_value' => $group['weight'],
  );

  // Form actions.
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  // Delete button
  if (!empty($group['name'])) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#submit' => array('ting_field_search_group_form_delete'),
    );
  }
  $form['actions']['cancel'] = array(
    '#type' => 'submit',
    '#value' => t('Back'),
    '#submit' => array('ting_field_search_form_cancel'),
    // Bypass form-validation since this is a cancel-button.
    '#limit_validation_errors' => array(),
    '#weight' => 40,
  );

  $path = drupal_get_path('module', 'ting_field_search');
  $form['#attached']['css'][] = $path . '/css/ting_field_search.admin.css';

  return $form;
}

function ting_field_search_group_form_submit($form, &$form_state) {
  $profile = $form_state['profile'];
  $group = $form_state['group'];
  $existing = $form_state['existing'];

  $values = array_intersect_key($form_state['values'], $group);
  $group = array_merge($group, $values);

  if ($existing) {
    unset($profile->groups[$existing]);
  }
  $profile->groups[$group['name']] = $group;

  // Save, set message and go back,.
  $operation = $existing ? t('updated on') : t('added to');
  if (ting_field_search_profile_save($profile)) {
    drupal_set_message(t('Group @operation %profile successfully!', array(
      '@operation' => $operation,
      '%profile' => $profile->name,
    )));
  }
  else {
    drupal_set_message(t('Something went wrong. No group was @operation %profile.', array(
      '@operation' => $operation,
      '%profile' => $profile->name,
    )), 'error');
  }

  $path = 'admin/config/ting/ting-field-search-profiles/list/' . $profile->name . '/edit';
  $form_state['redirect'] = array($path, array('fragment' => 'edit-config-fields'));
}

function ting_field_search_group_form_delete($form, &$form_state) {
  $profile = $form_state['profile'];
  $group = $form_state['group'];
  $path = 'admin/config/ting/ting-field-search-profiles/' . $profile->name;
  $path .= '/groups/' . $group['name'] . '/delete';
  $form_state['redirect'] = $path;
}

function ting_field_search_group_delete_confirm_form($form, &$form_state, $profile, $group_name) {
  $form_state['profile'] = $profile;
  $form_state['group_name'] = $group_name;
  $group = $profile->groups[$group_name];
  $path = 'admin/config/ting/ting-field-search-profiles/' . $profile->name;
  $path .= '/groups/' . $group_name . '/edit';

  $fields = ting_field_search_field_group_fields($profile, $group_name);

  if (!empty($fields)) {
    $form['warning'] = array(
      '#type' => 'item',
      '#title' => t('%group contains fields. Theese fields will be deleted too!', array(
        '%group' => $group['title'],
      )),
    );
  }

  return confirm_form(
    $form,
    t('Confirm deletion of %group on %profile', array(
      '%group' => $group['title'],
      '%profile' => $profile->name,
    )),
    $path,
    NULL,
    t('Delete'),
    t('Cancel')
  );
}

function ting_field_search_group_delete_confirm_form_submit($form, &$form_state) {
  $profile = $form_state['profile'];
  $group_name = $form_state['group_name'];
  $group = $profile->groups[$group_name];

  // Remove fields in the field group, so that we don't have any orphaned
  // fields.
  foreach (ting_field_search_field_group_fields($profile, $group_name) as $index => $field) {
    unset($profile->fields[$index]);
  }

  // Remove group and update profile.
  unset($profile->groups[$group_name]);

  if (ting_field_search_profile_save($profile)) {
    drupal_set_message(t('The group %group was removed from %profile', array(
      '%group' => $group['title'],
      '%profile' => $profile->title,
    )));
  }
  else {
    drupal_set_message(t('Something went wrong removing %group from %profile', array(
      '%group' => $group['title'],
      '%profile' => $profile->title,
    )), 'error');
  }

  $path = 'admin/config/ting/ting-field-search-profiles/list/' . $profile->name . '/edit';
  $form_state['redirect'] = array($path, array('fragment' => '#edit-config-fields'));
}

function ting_field_search_group_exists($group_name) {
  $profile_name = arg(4);
  // Load the profile from the argument.
  $profile = ting_field_search_profiles_load($profile_name);

  return array_key_exists($group_name, $profile->groups);
}
