<?php

/**
 * @file
 * Administration config form.
 */

/**
 * Module settings form.
 */
function ding_app_smartbanner_settings_form($form, &$form_state) {
  $configs = variable_get('smartbanner_config', array());

  $form['#tree'] = TRUE;

  $form['smartbanner']['base_config'] = array(
    '#type' => 'fieldset',
    '#title' => t('Base settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['smartbanner']['base_config']['days_hidden'] = array(
    '#type' => 'textfield',
    '#title' => t('Days hidden'),
    '#description' => t('Days to hide banner after close button clicked.'),
    '#default_value' => !empty($configs['base_config']['days_hidden']) ? $configs['base_config']['days_hidden'] : 15,
    '#size' => 30,
    '#maxlength' => 30,
    '#required' => TRUE,
  );

  $form['smartbanner']['base_config']['days_reminder'] = array(
    '#type' => 'textfield',
    '#title' => t('Days hidden'),
    '#description' => t('Days to hide banner after VIEW button is clicked.'),
    '#default_value' => !empty($configs['base_config']['days_reminder']) ? $configs['base_config']['days_reminder'] : 90,
    '#size' => 30,
    '#maxlength' => 30,
    '#required' => TRUE,
  );

  $form['smartbanner']['base_config']['app_store_language'] = array(
    '#type' => 'select',
    '#title' => t('iTunes store language'),
    '#description' => t('Select language for iTunes store'),
    '#options' => array(
      'en' => t('En'),
      'dk' => t('Dk'),
    ),
    '#default_value' => !empty($configs['base_config']['app_store_language']) ? $configs['base_config']['app_store_language'] : 'dk',
  );

  $form['smartbanner']['base_config']['app_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#description' => t('Application title.'),
    '#default_value' => !empty($configs['base_config']['app_title']) ? $configs['base_config']['app_title'] : '',
    '#size' => 30,
    '#maxlength' => 30,
    '#required' => TRUE,
  );

  $form['smartbanner']['base_config']['app_author'] = array(
    '#type' => 'textfield',
    '#title' => t('Author'),
    '#description' => t('Application author.'),
    '#default_value' => !empty($configs['base_config']['app_author']) ? $configs['base_config']['app_author'] : '',
    '#size' => 30,
    '#maxlength' => 30,
    '#required' => TRUE,
  );

  $form['smartbanner']['base_config']['button_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Button value'),
    '#description' => t('Value for button.'),
    '#default_value' => !empty($configs['base_config']['button_name']) ? $configs['base_config']['button_name'] : '',
    '#size' => 30,
    '#maxlength' => 30,
    '#required' => TRUE,
  );

  $form['smartbanner']['base_config']['app_icon'] = array(
    '#type' => 'fieldset',
    '#title' => t('App Icon'),
    '#weight' => 1,
  );

  $icon = !empty($configs['base_config']['app_icon']['icon']) ? $configs['base_config']['app_icon']['icon'] : FALSE;
  $form['smartbanner']['base_config']['app_icon']['icon'] = array(
    '#type' => 'value',
    '#value' => $icon,
  );

  if ($icon) {
    $image = array(
      'style_name' => 'thumbnail',
      'path' => $icon->uri,
      'width' => '',
      'height' => '',
      'alt' => !empty($icon->alt) ? $icon->alt : '',
      'title' => !empty($icon->title) ? $icon->title : '',
    );
    $form['smartbanner']['base_config']['app_icon']['picture_current'] = array(
      '#markup' => theme('image_style', $image),
    );
  }
  $form['smartbanner']['base_config']['app_icon']['icon_delete'] = array(
    '#type' => 'checkbox',
    '#title' => t('Delete picture'),
    '#access' => !empty($icon->fid),
    '#description' => t('Check this box to delete the current icon.'),
  );
  $form['smartbanner']['base_config']['app_icon']['icon_upload'] = array(
    '#type' => 'file',
    '#title' => t('Upload picture'),
    '#size' => 48,
    '#description' => t('Application icon.'),
  );

  $os = array(
    'ios' => 'iOS',
    'android' => 'Android',
  );

  // Configuration for Apple and Android.
  foreach ($os as $os_mach_name => $os_name) {
    $os_config = $os_mach_name . '_app_config';
    $app_config = $configs['app_configs'][$os_config];

    $form['smartbanner']['app_configs'][$os_config] = array(
      '#type' => 'fieldset',
      '#title' => t("@os_name application configuration", array('@os_name' => $os_name)),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['smartbanner']['app_configs'][$os_config]['app_enabled'] = array(
      '#type' => 'checkbox',
      '#title' => t("Enable @os_name app banner.", array('@os_name' => $os_name)),
      '#default_value' => !empty($app_config['app_enabled']) ? $app_config['app_enabled'] : '',
    );

    $form['smartbanner']['app_configs'][$os_config]['app_id'] = array(
      '#type' => 'textfield',
      '#title' => t("@os_name app id", array('@os_name' => $os_name)),
      '#size' => 30,
      '#maxlength' => 60,
      '#required' => FALSE,
      '#default_value' => !empty($app_config['app_id']) ? $app_config['app_id'] : '',
    );

    $form['smartbanner']['app_configs'][$os_config]['app_price'] = array(
      '#type' => 'textfield',
      '#title' => t("@os_name app price", array('@os_name' => $os_name)),
      '#size' => 30,
      '#maxlength' => 30,
      '#required' => FALSE,
      '#default_value' => !empty($app_config['app_price']) ? $app_config['app_price'] : '',
    );

    $form['smartbanner']['app_configs'][$os_config]['app_description'] = array(
      '#type' => 'textfield',
      '#title' => t("@os_name app description", array('@os_name' => $os_name)),
      '#size' => 60,
      '#maxlength' => 255,
      '#required' => FALSE,
      '#default_value' => !empty($app_config['app_description']) ? $app_config['app_description'] : '',
    );
  }

  // Configuration for windows.
  $os_config = 'windows_app_config';
  $win_app_config = $configs['app_configs'][$os_config];

  $form['smartbanner']['app_configs'][$os_config] = array(
    '#type' => 'fieldset',
    '#title' => t("Windows application configuration"),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['smartbanner']['app_configs'][$os_config]['app_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t("Enable Windows app banner."),
    '#default_value' => !empty($win_app_config['app_enabled']) ? $win_app_config['app_enabled'] : '',
  );

  $form['smartbanner']['app_configs'][$os_config]['app_id'] = array(
    '#type' => 'textfield',
    '#title' => t("Windows app id"),
    '#size' => 30,
    '#maxlength' => 30,
    '#required' => FALSE,
    '#default_value' => !empty($win_app_config['app_id']) ? $win_app_config['app_id'] : '',
  );

  $form['smartbanner']['app_configs'][$os_config]['package'] = array(
    '#type' => 'textfield',
    '#title' => t("Windows package name"),
    '#size' => 30,
    '#maxlength' => 30,
    '#required' => FALSE,
    '#default_value' => !empty($win_app_config['package']) ? $win_app_config['package'] : '',
  );

  $form['smartbanner']['app_configs'][$os_config]['app_price'] = array(
    '#type' => 'textfield',
    '#title' => t("Windows app price"),
    '#size' => 30,
    '#maxlength' => 30,
    '#required' => FALSE,
    '#default_value' => !empty($win_app_config['app_price']) ? $win_app_config['app_price'] : '',
  );

  $form['smartbanner']['app_configs'][$os_config]['app_description'] = array(
    '#type' => 'textfield',
    '#title' => t("Windows app description"),
    '#size' => 60,
    '#maxlength' => 255,
    '#required' => FALSE,
    '#default_value' => !empty($win_app_config['app_description']) ? $win_app_config['app_description'] : '',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  $form['#validate'][] = 'ding_app_smartbanner_settings_form_validate';
  $form['#submit'] = array('ding_app_smartbanner_settings_form_submit');

  return $form;
}

/**
 * Fields validation.
 */
function ding_app_smartbanner_settings_form_validate($form, &$form_state) {
  $file = file_save_upload('smartbanner', array(
    'file_validate_is_image' => array(),
    'file_validate_extensions' => array('png gif jpg jpeg'),
  ));

  if ($file === FALSE) {
    form_set_error('smartbanner', t("Failed to upload the picture image; the %directory directory doesn't exist or is not writable.", array('%directory' => variable_get('user_picture_path', 'pictures'))));
  }
  elseif ($file !== NULL) {
    $form_state['values']['smartbanner']['base_config']['app_icon']['icon_upload'] = $file;
  }
}

/**
 * Custom fields manipulations before save.
 */
function ding_app_smartbanner_settings_form_submit($form, &$form_state) {
  $values = $form_state['values']['smartbanner'];

  $icon = $values['base_config']['app_icon']['icon'];
  $icon_upload = $values['base_config']['app_icon']['icon_upload'];
  if (!empty($icon_upload->fid)) {
    if (!$icon_upload->status) {
      $info = image_get_info($icon_upload->uri);
      $picture_directory = file_default_scheme() . '://ding_app_smartbanner';

      // Prepare the pictures directory.
      file_prepare_directory($picture_directory, FILE_CREATE_DIRECTORY);
      $destination = file_stream_wrapper_uri_normalize($picture_directory . '/icon-' . $icon_upload->uid . '-' . REQUEST_TIME . '.' . $info['extension']);

      // Move the temporary file into the final location.
      if ($icon_upload = file_move($icon_upload, $destination, FILE_EXISTS_RENAME)) {
        $icon_upload->status = FILE_STATUS_PERMANENT;
        $values['base_config']['app_icon']['icon'] = file_save($icon_upload);
        $values['base_config']['app_icon']['picture_current'] = $values['base_config']['app_icon']['icon'];
        file_usage_add($icon_upload, 'user', 'user', $icon_upload->uid);
      }
    }
    // Delete the previous picture if it was deleted or replaced.
    if (!empty($icon->fid)) {
      file_usage_delete($icon, 'user', 'user', $icon->uid);
      file_delete($icon);
      $values['base_config']['app_icon']['icon_upload'] = '';
    }
  }
  elseif (isset($values['base_config']['app_icon']['icon_delete']) && $values['base_config']['app_icon']['icon_delete']) {
    file_usage_delete($icon, 'user', 'user', $icon->uid);
    file_delete($icon);
    $values['base_config']['app_icon']['icon'] = '';
  }

  variable_set('smartbanner_config', $values);
}
