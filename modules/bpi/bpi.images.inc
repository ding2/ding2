<?php
/**
 * @file
 * Images syndication routine here.
 */

/**
 * Entry point for image syndication.
 *
 * @param string $type
 *   Whether it's an ajax call.
 *
 * @return array
 *   A set of ajax commands.
 */
function bpi_syndicate_images($type = 'ajax') {
  $assets = isset($_SESSION['bpi']['assets']) ? $_SESSION['bpi']['assets'] : array();

  if (empty($assets)) {
    return;
  }

  $form = drupal_get_form('bpi_assets_form', $assets);
  $commands = array();

  $commands[] = ajax_command_ding_popup(
    'bpi-syndicate-images',
    t('Syndicate images'),
    drupal_render($form)
  );

  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Image syndication form.
 *
 * @param array $form
 *   Form structure.
 * @param array $form_state
 *   Form state values.
 * @param array $assets
 *   Array of assets to be downloaded.
 *
 * @return array
 *   Form structure.
 *
 * @ingroup forms
 */
function bpi_assets_form($form, $form_state, $assets = array()) {
  if (!empty($assets)) {
    $form['bpi_assets'] = array(
      '#type' => 'fieldset',
      '#title' => t('Available images'),
    );

    foreach ($assets as $asset => $url) {
      $form['bpi_assets'][$asset] = array(
        '#type' => 'checkbox',
        '#default_value' => 1,
        '#prefix' => '<div class="bpi-syndicate-asset"><img src="' . $url . '" width="100" height="100" />',
        '#suffix' => '</div>',
      );
    }
  }

  $form['bpi_assets_syndicate'] = array(
    '#type' => 'submit',
    '#value' => t('Import'),
    '#ajax' => array(
      'callback' => 'bpi_asset_action_ajax_callback',
    ),
  );

  return $form;
}

/**
 * Submit handler for images form.
 *
 * @see bpi_assets_form()
 *
 * @param array $form
 *   Form structure.
 * @param array $form_state
 *   Form state values.
 *
 * @ingroup forms
 */
function bpi_assets_form_submit($form, &$form_state) {
  $input = array_keys($form_state['input']);
  $assets = array();

  // Seek the assets.
  foreach ($input as $value) {
    if (preg_match('/^asset(\d+)*/', $value) && !empty($form_state['input'][$value])) {
      if (isset($_SESSION['bpi']['assets'][$value])) {
        $assets[] = $_SESSION['bpi']['assets'][$value];
      }
    }
  }

  unset($_SESSION['bpi']['assets']);

  foreach ($assets as $path) {
    $filename = basename($path);
    $managed_file = bpi_fetch_image('public://bpi/' . $filename, $path);

    $status = TRUE;
    if (!is_object($managed_file)) {
      $status = FALSE;
    }
  }

  if (isset($status) && $status) {
    drupal_set_message(t('Images downloaded successfully.'));
  }
  else {
    drupal_set_message(t('Not all images were fetched successfully, check reports for more info.'));
  }
}

/**
 * Images form download action ajax callback.
 *
 * @see bpi_assets_form()
 *
 * @param array $form
 *   Form structure.
 * @param array $form_state
 *   Form state values.
 *
 * @return array
 *   Set of ajax commands.
 *
 * @ingroup forms
 */
function bpi_asset_action_ajax_callback($form, &$form_state) {
  $html = theme('status_messages');

  $commands = array();

  $commands[] = ajax_command_ding_popup(
    'bpi-syndicate-images',
    t('Syndicate images'),
    $html
  );

  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Images form cancel action ajax callback.
 *
 * @see bpi_assets_form()
 *
 * @param array $form
 *   Form structure.
 * @param array $form_state
 *   Form state values.
 *
 * @return array
 *   Set of ajax commands.
 *
 * @ingroup forms
 */
function bpi_asset_cancel_ajax_callback($form, &$form_state) {
  $commands = array();

  $commands[] = ajax_command_ding_popup_close(
    'bpi-syndicate-images'
  );

  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Download images to local instance.
 *
 * @param string $filename
 *   Filename, with extension. An URI is optional.
 * @param string $image_url
 *   File URL form where to download.
 *
 * @return object
 *   File object or FALSE on failure.
 */
function bpi_fetch_image($filename, $image_url) {
  $result = drupal_http_request($image_url);

  if ($result->code != 200) {
    watchdog(
      'bpi',
      'Failed to fetch image %url, with HTTP status %status', array('%url' => $image_url, '%status' => $result->code),
      WATCHDOG_ERROR
    );

    return FALSE;
  }

  $directory = dirname($filename);

  if (!file_prepare_directory($directory, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS)) {
    watchdog(
      'bpi',
      t('Failed to create directory: %directory'),
      array('%directory' => $directory),
      WATCHDOG_ERROR
    );

    return FALSE;
  }

  return file_save_data($result->data, $filename, FILE_EXISTS_REPLACE);
}
