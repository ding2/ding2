<?php
/**
 * @file
 * Handle theme settings form for the theme.
 */
 
/**
 * Implements form_system_theme_settings_alter().
 */
function ddbasic_form_system_theme_settings_alter(&$form, $form_state) {
  // CSS class and markup.
  // Colors
  $form['ddbasic_settings']['colors'] = array(
    '#type' => 'fieldset',
    '#title' => t('Colors'),
  );

  $form['ddbasic_settings']['colors']['color_primary'] = array(
    '#type' => 'textfield',
    '#title' => t('Primary color'),
    '#description' => t('Use hex (4d898e)') . '<br />' . t('Is used e.g. as background-color for the main menu, checkboxes and radio-buttons'),
    '#default_value' => ddbasic_theme_setting('color_primary', '4d898e'),
  );

  $form['ddbasic_settings']['colors']['color_secondary'] = array(
    '#type' => 'textfield',
    '#title' => t('Secondary color'),
    '#description' => t('Use hex (f66d70)')  . '<br />' . t('Is used e.g. as background-color for the log-in button, read-more buttons'),
    '#default_value' => ddbasic_theme_setting('color_secondary', 'f66d70'),
  );

  $form['ddbasic_settings']['colors']['color_text'] = array(
    '#type' => 'select',
    '#title' => t('Text color'),
    '#description' => t('Choose a color that is legible on a white background')  . '<br />' . t('Is used e.g. for text-links and panel headers'),
    '#default_value' => ddbasic_theme_setting('color_text', 'primary'),
    '#options' => array(
      'primary' => t('Primary'),
      'secondary' => t('Secondary'),
      '000000' => t('black'),
    )
  );

  $form['ddbasic_settings']['colors']['color_text_on_primary'] = array(
    '#type' => 'select',
    '#title' => t('Text on primary color'),
    '#description' => t('Choose a color that is legible on the primary color'),
    '#default_value' => ddbasic_theme_setting('color_text_on_primary', 'white'),
    '#options' => array(
      'ffffff' => t('white'),
      '000000' => t('black'),
    )
  );
  $form['ddbasic_settings']['colors']['color_text_on_secondary'] = array(
    '#type' => 'select',
    '#title' => t('Text on secondary color'),
    '#description' => t('Choose a color that is legible on the secondary color'),
    '#default_value' => ddbasic_theme_setting('color_text_on_secondary', 'white'),
    '#options' => array(
      'ffffff' => t('white'),
      '000000' => t('black'),
    )
  );
  
  // Number of news in list
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
    )
  );
  
  // Number of events in list
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
    )
  );
  
  // Social links
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
  
  $form['#validate'][] = 'ddbasic_form_system_theme_settings_validate';
  $form['#submit'][] = 'ddbasic_form_system_theme_settings_submit';
}

/**
 * Custom validation for the theme_settings form.
 */
function ddbasic_form_system_theme_settings_validate($form, &$form_state) {
  $pattern_hex = '/^[a-f0-9]{6}$/i';
  if (!preg_match($pattern_hex, $form_state['values']['color_primary'])) {
    form_set_error('color_primary', t('Only hex colors is allowed'));
  }
  if (!preg_match($pattern_hex, $form_state['values']['color_secondary'])) {
    form_set_error('color_primary', t('Only hex colors is allowed'));
  }
  
  $form_state['color_path'] = drupal_get_path('theme', 'ddbasic') . '/sass/configuration/_colors.scss';
  if (!is_writable($form_state['color_path'])) {
    form_set_error('ddbasic_settings', t('Please make the color file (%path) writable', array('%path' => $form_state['color_path'])));
  }
}

/**
 * Custom submit for the theme_settings form.
 */
function ddbasic_form_system_theme_settings_submit($form, &$form_state) {
  file_put_contents($form_state['color_path'], ddbasic_create_colors_config($form_state['values']));
  exec('cd ' . __DIR__ . ' && gulp sass');
}

/**
 * Get sass containing the color settings.
 */
function ddbasic_create_colors_config($values) {
  $color_text = $values['color_text'];
  switch ($color_text) {
    case 'primary': $color_text = $values['color_primary']; break;
    case 'secondary': $color_text = $values['color_secondary']; break;
  }
  
  return '// Autogenerated file.
$color-primary: #' . $values['color_primary'] . ';
$color-secondary: #' . $values['color_secondary'] . ';

$color-text: #' . $color_text . ';
$color-text-on-primary: #' . $values['color_text_on_primary'] . ';
$color-text-on-secondary: #' . $values['color_text_on_secondary'] . ';
';
}
