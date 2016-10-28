<?php
/**
 * @file
 * Administration interface for the module, which allows configuration of
 * moreinfo end-points and cache lifetime.
 */

/**
 * Admin settings form for Ting covers.
 */
function ting_covers_admin_settings_form($form, &$form_state) {
  $form = array();

  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Cover settings'),
  );

  $form['settings']['ting_covers_cache_lifetime'] = array(
    '#type' => 'select',
    '#title' => t('Cover cache lifetime'),
    '#options' => array(
      '0' => t('Disable cache'),
      '86400' => t("24 hours"),
      '604800' => t("1 week"),
      '2592000' => t("1 month"),
    ),
    '#default_value' => variable_get('ting_covers_cache_lifetime', TING_COVERS_DEFAULT_CACHE_LIFETIME),
  );

  return system_settings_form($form);
}
