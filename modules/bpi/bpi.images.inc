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
    drupal_render($form),
    // We need to reload the main content page after syndicating assets to
    // place the assets in the content.
    array('refresh' => TRUE)
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
 *   Array of assets to be downloaded. The keys are asset types (list_image,
 *   title_image, …) and the values are arrays of asset information.
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

    foreach ($assets as $type => $items) {
      foreach ($items as $index => $asset) {
        $form['bpi_assets']['asset::' . $type . '::' . $index] = array(
          '#type' => 'checkbox',
          '#default_value' => 1,
          '#prefix' => '<div class="bpi-syndicate-asset"><img src="' . $asset['path'] . '" width="100" height="100" />' . '<br/> (' . bpi_get_image_display_name($asset['type']) . ')',
          '#suffix' => '</div>',
        );
      }
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
  $bpi_assets = $_SESSION['bpi']['assets'];

  $assets = array();

  // Find syndicated assets in posted data.
  foreach ($form_state['input'] as $name => $value) {
    if (preg_match('/^asset::(?<type>[^:]+)::(?<index>[^_]+)$/', $name, $matches) && !empty($value)) {
      $type = $matches['type'];
      $index = $matches['index'];
      if (isset($bpi_assets[$type][$index])) {
        $assets[] = $bpi_assets[$type][$index];
      }
    }
  }

  unset($_SESSION['bpi']['assets']);

  // Group syndicated images by type.
  $syndicated_images = array();
  $status = TRUE;
  foreach ($assets as $asset) {
    $filename = $asset['type'] . '/' . uniqid() . '.' . $asset['extension'];
    $managed_file = bpi_fetch_image('public://bpi/' . $filename, $asset['path']);

    if (!is_object($managed_file)) {
      $status = FALSE;
    }
    else {
      if (!isset($syndicated_images[$asset['type']])) {
        $syndicated_images[$asset['type']] = array();
      }
      $syndicated_images[$asset['type']][] = $asset + array('@managed_file' => $managed_file);
    }
  }

  if (isset($status) && $status) {
    drupal_set_message(t('Images downloaded successfully.'));
    // Store syndicated images for use in content edit form.
    bpi_set_syndicated_images($syndicated_images);
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

/**
 * Compute the image type from a field name on a node.
 *
 * @param string $image_field_name
 *   The image field name.
 * @param object $node
 *   The node.
 *
 * @return NULL|string
 *   The image type.
 */
function bpi_get_image_type($image_field_name, $node) {
  /*
   * We assume that the image type is the last part of the field name, i.e.
   *   field_{{node type}}_{{image type}}
   */
  $pattern = '/field_' . preg_quote($node->type, '/') . '_(?<image_type>.+)/';
  if (preg_match($pattern, $image_field_name, $matches)) {
    return $matches['image_type'];
  }
  return NULL;
}

/**
 * Store syndicated images in session.
 *
 * @param mixed $syndicated_images
 *   The value to store.
 */
function bpi_set_syndicated_images($syndicated_images) {
  $_SESSION['bpi']['syndicated_images'] = $syndicated_images;
}

/**
 * Get syndicated images from session.
 *
 * @return mixed
 *   The value if any.
 */
function bpi_get_syndicated_images() {
  return isset($_SESSION['bpi']['syndicated_images']) ? $_SESSION['bpi']['syndicated_images'] : NULL;
}

/**
 * Clear any syndicated images in session.
 */
function bpi_clear_syndicated_images() {
  unset($_SESSION['bpi']['syndicated_images']);
}

/**
 * Get translated display name for an image type.
 *
 * @param string $image_type
 *   The image type.
 *
 * @return string
 *   The translated display name.
 */
function bpi_get_image_display_name($image_type) {
  $types = array(
    'body' => t('Inline image'),
    'list_image' => t('List image'),
    'title_image' => t('Title image'),
  );
  return isset($types[$image_type]) ? $types[$image_type] : t($image_type);
}
