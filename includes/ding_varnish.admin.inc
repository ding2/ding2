<?php
/**
 * @file
 * The modules administration interface, which allows the admin to configure the
 * module behaviour.
 */

/**
 * Defines the administration form for this module.
 */
function ding_varnish_settings_form() {
  $form = array();

  // Which role is the library user and should be cacheable.
  $roles = user_roles(TRUE);
  $form['ding_varnish_role'] = array(
    '#type' => 'radios',
    '#title' => t('Library user role'),
    '#description' => t('Select the role that should be cached in varnish for logged in library users.'),
    '#options' => $roles,
    '#default_value' => variable_get('ding_varnish_role', 2),
  );

  // Which node views should be cacheable.
  $options = array();
  $types = node_type_get_types();
  foreach ($types as $machine_name => $type) {
    $options[$machine_name] = $type->name;
  }
  $form['ding_varnish_content_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Content types'),
    '#description' => t('Select the content types that should be cacheable in varnish for logged in users.'),
    '#options' => $options,
    '#default_value' => variable_get('ding_varnish_content_types', array()),
  );

  // Cacheable paths e.g. views and panel pages.
  $form['ding_varnish_paths'] = array(
    '#type' => 'textarea',
    '#title' => t('Paths'),
    '#description' => t('Enter a comma sperated list of paths that should be cached by varnish.'),
    '#default_value' => variable_get('ding_varnish_paths', ''),
  );

  return system_settings_form($form);
}
