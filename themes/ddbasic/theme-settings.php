<?php
/**
 * @file
 * Handle theme settings form for the theme.
 */

/**
 * Implements form_system_theme_settings_alter().
 */
function ddbasic_form_system_theme_settings_alter(&$form, $form_state) {
  // Number of news in list.
  $form['ddbasic_settings']['news_list'] = array(
    '#type' => 'fieldset',
    '#title' => t('News list'),
  );

  $form['ddbasic_settings']['news_list']['number_of_news'] = array(
    '#type' => 'select',
    '#title' => t('Number of news'),
    '#description' => t('Choose how many news items you want on each page in the news list'),
    '#default_value' => ddbasic_theme_setting('number_of_news', '10'),
    '#options' => array(
      '10' => '10',
      '12' => '12',
      '14' => '14',
      '16' => '16',
      '18' => '18',
      '20' => '20',
    ),
  );

  // Number of events in list.
  $form['ddbasic_settings']['event_list'] = array(
    '#type' => 'fieldset',
    '#title' => t('Event list'),
  );

  $form['ddbasic_settings']['event_list']['number_of_events'] = array(
    '#type' => 'select',
    '#title' => t('Number of events'),
    '#description' => t('Choose how many events items you want on each page in the event list'),
    '#default_value' => ddbasic_theme_setting('number_of_events', '10'),
    '#options' => array(
      '10' => '10',
      '12' => '12',
      '14' => '14',
      '16' => '16',
      '18' => '18',
      '20' => '20',
    ),
  );

  $form['ddbasic_settings']['event_list']['group_events_by_date'] = array(
    '#type' => 'checkbox',
    '#title' => t('Group events by date'),
    '#description' => t('Group events by date instead of month'),
    '#default_value' => ddbasic_theme_setting('group_events_by_date', FALSE),
  );

  // Disable overlay on Ting object teasers.
  $form['ddbasic_settings']['ting_object_overlay'] = array(
    '#type' => 'fieldset',
    '#title' => t('Ting object overlay'),
  );
  $form['ddbasic_settings']['ting_object_overlay']['ting_object_disable_overlay'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable overlay'),
    '#description' => t('Disable gradient overlay with text on Ting object teasers'),
    '#default_value' => ddbasic_theme_setting('ting_object_disable_overlay', FALSE),
  );

  // Social links.
  $form['ddbasic_settings']['social_links'] = array(
    '#type' => 'fieldset',
    '#title' => t('Social links'),
    '#description' => t('These are used for social links in the footer'),
  );

  $form['ddbasic_settings']['social_links']['social_link_facebook'] = array(
    '#type' => 'textfield',
    '#title' => t('Facebook link'),
    '#default_value' => ddbasic_theme_setting('social_link_facebook', ''),
  );

  $form['ddbasic_settings']['social_links']['social_link_twitter'] = array(
    '#type' => 'textfield',
    '#title' => t('Twitter link'),
    '#default_value' => ddbasic_theme_setting('social_link_twitter', ''),
  );

  $form['ddbasic_settings']['social_links']['social_link_instagram'] = array(
    '#type' => 'textfield',
    '#title' => t('Instagram link'),
    '#default_value' => ddbasic_theme_setting('social_link_instagram', ''),
  );

  // User signup link.
  $form['ddbasic_settings']['signup_link'] = array(
    '#type' => 'fieldset',
    '#title' => t('User signup link'),
  );

  $form['ddbasic_settings']['signup_link']['user_signup_link'] = array(
    '#type' => 'textfield',
    '#title' => t('Link'),
    '#default_value' => ddbasic_theme_setting('user_signup_link', ''),
    '#description' => t('The link is used in the text next to the log-in form'),
  );

  $form['#validate'][] = 'ddbasic_form_system_theme_settings_validate';
  $form['#submit'][] = 'ddbasic_form_system_theme_settings_submit';
}

/**
 * Custom validation for the theme_settings form.
 */
function ddbasic_form_system_theme_settings_validate($form, &$form_state) {
  if (!empty($form_state['values']['user_signup_link'])) {
    if (!(0 === strpos($form_state['values']['user_signup_link'], 'http'))) {
      form_set_error('user_signup_link', t('User signup link must start with "http"'));
    }
  }

  switch ($form_state['values']['palette']['text']) {
    case 'primary': $form_state['values']['palette']['text'] = $form_state['values']['palette']['primary'];
      break;

    case 'secondary': $form_state['values']['palette']['text'] = $form_state['values']['palette']['secondary'];
      break;
  }
}

/**
 * Custom submit for the theme_settings form.
 */
function ddbasic_form_system_theme_settings_submit($form, &$form_state) {
  $theme_name = $form_state['build_info']['args'][0];

  // Add all the css files to the color module info array.
  $theme_path = drupal_realpath(drupal_get_path('theme', $theme_name)) . '/';
  $cssfiles = array_merge(
    file_scan_directory($theme_path . '/sass_css', '/\.css$/')
  );
  $form_state['values']['info']['css'] = array();
  foreach ($cssfiles as $cssfile) {
    $form_state['values']['info']['css'][] = str_replace($theme_path, '', drupal_realpath($cssfile->uri));
  }
}
