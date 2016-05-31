<?php
/**
 * @file
 * Admin related backend.
 */

/**
 * System settings form.
 */
function ding_ting_frontend_local_config_admin_settings($form_state) {

  $form['ting_object'] = array(
    '#type' => 'fieldset',
    '#title' => t('Ting Object settings'),
    '#description' => t('Modifications to ting objects when they are being displayed'),
    '#tree' => FALSE,
  );

  // Choose how 'group holdings available' should be formatted for Ting Objects.
  $form['ting_object']['ding_ting_frontend_group_holdings_available'] = array(
    '#type' => 'select',
    '#title' => t('Group holdings available'),
    '#options' => array(
      'default' => t("Default (don't change)"),
      'open' => t('Open'),
      'collapsed' => t('Collapsed'),
      'collapsible' => t('Collapsible'),
    ),
    '#default_value' => variable_get('ding_ting_frontend_group_holdings_available', ''),
  );

  return system_settings_form($form);

}
