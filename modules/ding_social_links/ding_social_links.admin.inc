<?php
/**
 * @file
 * Social links settings.
 */

/**
 * Social links admin.
 */
function ding_social_links_admin_setting_form($form, &$form_state) {
  $form['ding_social_links_facebook'] = array(
    '#type' => 'textfield',
    '#title' => t('Facebook link'),
    '#default_value' => variable_get('ding_social_links_facebook', ''),
  );

  $form['ding_social_links_twitter'] = array(
    '#type' => 'textfield',
    '#title' => t('Twitter link'),
    '#default_value' => variable_get('ding_social_links_twitter', ''),
  );

  $form['ding_social_links_instagram'] = array(
    '#type' => 'textfield',
    '#title' => t('Instagram link'),
    '#default_value' => variable_get('ding_social_links_instagram', ''),
  );

  return system_settings_form($form);
}
