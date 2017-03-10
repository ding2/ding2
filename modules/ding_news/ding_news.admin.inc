<?php
/**
 * @file
 * Ding news configurations.
 */

/**
 * Admin form.
 */
function ding_news_admin_setting_form(array $form, array &$form_state) {
  $form['ding_news_list_items_per_page'] = array(
    '#type' => 'select',
    '#title' => t('Number of news'),
    '#description' => t('Choose how many news items you want on each page in the news list'),
    '#default_value' => variable_get('ding_news_list_items_per_page', 10),
    '#options' => array(
      '10' => '10',
      '12' => '12',
      '14' => '14',
      '16' => '16',
      '18' => '18',
      '20' => '20',
    ),
  );

  return system_settings_form($form);
}
