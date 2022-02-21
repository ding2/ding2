<?php
/**
 * @file
 * Administration interface for the module, which allows configuration of
 * ting_netarchive cache lifetime.
 */

/**
 * Admin settings form for Ting covers.
 */
function ting_netarchive_admin_settings_form($form, &$form_state) {
  $form = array();

  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Moreinfo netarchive settings'),
  );

  $form['settings']['ting_netarchive_cache_lifetime'] = array(
    '#type' => 'select',
    '#title' => t('Cover cache lifetime'),
    '#options' => array(
      '0' => t('Disable cache'),
      '86400' => t("24 hours"),
      '604800' => t("1 week"),
      '2592000' => t("1 month"),
    ),
    '#default_value' => variable_get('ting_netarchive_cache_lifetime', TING_NETARCHIVE_DEFAULT_CACHE_LIFETIME),
  );

  return system_settings_form($form);
}
