<?php
/**
 * @file
 * Ding eresource configurations.
 */

/**
 * Admin form.
 */
function ding_eresource_admin_setting_form(array $form, array &$form_state) {
  $default_category_text_overwrite = variable_get('ding_eresource_default_category_text_overwrite');
  $form['ding_eresource_default_category_text_overwrite'] = array(
    '#type' => 'text_format',
    '#title' => t('Overwrite the default e-resource category text'),
    '#description' => t('Overwrite the default e-resource category text shown above e-resource list when no category is selected.'),
    '#default_value' => $default_category_text_overwrite['value'],
  );

  return system_settings_form($form);
}
