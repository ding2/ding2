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

  $form['settings']['ding_ddbasic_opening_hours_expand_on_library'] = array(
    '#type' => 'checkbox',
    '#title' => t('Expand on library'),
    '#default_value' => variable_get('ding_ddbasic_opening_hours_expand_on_library', FALSE),
  );

  $form['settings']['ding_ddbasic_opening_hours_on_frontpage'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show opening hours on frontpage'),
    '#default_value' => variable_get('ding_ddbasic_opening_hours_on_frontpage', FALSE),
  );

  return system_settings_form($form);
}
