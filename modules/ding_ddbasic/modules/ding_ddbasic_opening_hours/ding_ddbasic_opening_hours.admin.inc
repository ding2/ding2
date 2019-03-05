<?php
/**
 * @file
 * Admin for opening hours.
 */

/**
 * Settings form.
 */
function ding_ddbasic_opening_hours_settings_form($form, &$form_state) {
  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('DDBasic opening hours'),
  );

  $form['settings']['ding_ddbasic_opening_hours_extended_title'] = array(
    '#type' => 'checkbox',
    '#title' => t('Extended title'),
    '#default_value' => variable_get('ding_ddbasic_opening_hours_extended_title', FALSE),
  );

  $form['settings']['ding_ddbasic_opening_hours_expand_setting'] = array(
    '#type' => 'select',
    '#title' => t('Expand settings'),
    '#default_value' => variable_get('ding_ddbasic_opening_hours_expand_setting', 'dont_expand'),
    '#options' => array(
      'dont_expand' => t('Dont expand'),
      'expand_on_first' => t('Expand on first library'),
      'expand_all' => t('Expand all libraries'),
    ),
  );

  return system_settings_form($form);
}
