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

function ting_field_search_field_form($form, &$form_state, $profile, $field_index = FALSE) {
  $form = array();

  // Field defaults.
  $field = array(
    'type' => 'textfield',
    'title' => '',
    'title_display' => FALSE,
    'description' => '',
    'description_display' => TRUE,
    'prefix' => '',
    'suffix' => '',
    'placeholder' => 1,
    'options' => array(),
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

  $options = array();
  foreach (ting_field_search_field_types() as $type => $labels) {
    $options[$type] = $labels['single'];
  }

  $form['type'] = array(
    '#type' => 'select',
    '#title' => t('Field type'),
    '#description' => t('Select a field type.'),
    '#options' => $options,
    '#default_value' => $field['type'],
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
    '#description' => t('Enter a key|value pair pr. line. Key is used in the search query and values is shown to the user.'),
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
    '#submit' => array('ting_field_search_field_form_cancel'),
    // Bypass form-validation since this is a cancel-button.
    '#limit_validation_errors' => array(),
    '#weight' => 40,
  );

  return $form;
}

function ting_field_search_field_form_validate($form, &$form_state) {
  $index = $form_state['values']['suffix'];
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

function ting_field_search_field_form_cancel($form, &$form_state) {
  $profile = $form_state['profile'];
  $path = 'admin/config/ting/ting-field-search-profiles/list/' . $profile->name . '/edit';
  $form_state['redirect'] = array($path, array('fragment' => '#edit-config-fields'));
}

function ting_field_search_field_form_delete($form, &$form_state) {
  $profile = $form_state['profile'];
  $field = $form_state['field'];
  $path = 'admin/config/ting/ting-field-search-profiles/list/';
  $path .= $profile->name . '/fields/' . $field['index'] . '/delete';
  $form_state['redirect'] = $path;
}

function ting_field_search_field_delete_confirm_form($form, &$form_state, $profile, $field_index) {
  $form_state['profile'] = $profile;
  $form_state['field_index'] = $field_index;
  $path = 'admin/config/ting/ting-field-search-profiles/list/';
  $path .= $profile->name . '/fields/' . $field_index . '/edit';

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
