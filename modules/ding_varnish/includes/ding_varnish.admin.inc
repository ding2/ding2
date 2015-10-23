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
  $form = array(
    '#tree' => FALSE,
  );

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
    '#description' => t("Angiv sider ved at bruge deres stier. Indtast én sti pr. linje. '*'-tegnet er joker. Eksempler på stier er blog for blogsiden og blog/* for alle personlige blogs. &lt;front&gt; er forsiden."),
    '#default_value' => variable_get('ding_varnish_paths', ''),
  );

  return system_settings_form($form);
}
