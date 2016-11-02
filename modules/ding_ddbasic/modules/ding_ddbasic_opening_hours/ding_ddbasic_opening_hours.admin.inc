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

  return system_settings_form($form);
}
