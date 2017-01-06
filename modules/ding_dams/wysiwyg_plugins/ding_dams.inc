<?php
/**
 * @file
 * Define the WYSIWYG browser plugin.
 */

/**
 * Implements hook_INCLUDE_plugin().
 */
function ding_dams_ding_dams_plugin() {
  // Include the required browser JS.
  // @todo: wyswiyg should allow libraries and multiple js files
  // to be defined by this hook.
  // @see http://drupal.org/node/1039076
  ding_dams_include_browser_js();

  // Insert document only plugin definition.
  $plugins['dams_document'] = array(
    'title' => t('Ding DAMS Document Plugin'),
    'icon path' => drupal_get_path('module', 'ding_dams') . '/wysiwyg_plugins/images',
    'icon file' => 'wysiwyg-dams-document.png',
    'icon title' => t('Insert document'),
    'js path' => drupal_get_path('module', 'ding_dams') . '/wysiwyg_plugins/js',
    'js file' => 'wysiwyg-dams-document.js',
    'css file' => NULL,
    'css path' => NULL,
    'settings' => array(
      'global' => array(
        'types' => array('text', 'application'),
        'id' => 'dams_document_wysiwyg',
        'activePlugins' => array(),
        'enabledPlugins' => array(
          'upload' => 'upload',
          'dams_media_browser--media_browser_5' => 'dams_media_browser--media_browser_5',
        ),
        'file_extensions' => 'doc docx ppt pptx xls xlsx txt pdf',
      ),
    ),
  );

  // Insert video only plugin definition.
  $plugins['dams_video'] = array(
    'title' => t('Ding DAMS Video Plugin'),
    'icon path' => drupal_get_path('module', 'ding_dams') . '/wysiwyg_plugins/images',
    'icon file' => 'wysiwyg-dams-video.png',
    'icon title' => t('Insert video'),
    'js path' => drupal_get_path('module', 'ding_dams') . '/wysiwyg_plugins/js',
    'js file' => 'wysiwyg-dams-video.js',
    'css file' => NULL,
    'css path' => NULL,
    'settings' => array(
      'global' => array(
        'types' => array('video'),
        'id' => 'dams_video_wysiwyg',
        'activePlugins' => array(),
        'enabledPlugins' => array(
          'upload' => 'upload',
          'dams_media_browser--media_browser_3' => 'dams_media_browser--media_browser_3',
        ),
        'file_extensions' => 'mp4 WebM Ogg',
      ),
    ),
  );

  // Insert audio only plugin definition.
  $plugins['dams_audio'] = array(
    'title' => t('Ding DAMS Audio Plugin'),
    'icon path' => drupal_get_path('module', 'ding_dams') . '/wysiwyg_plugins/images',
    'icon file' => 'wysiwyg-dams-audio.png',
    'icon title' => t('Insert audio'),
    'js path' => drupal_get_path('module', 'ding_dams') . '/wysiwyg_plugins/js',
    'js file' => 'wysiwyg-dams-audio.js',
    'css file' => NULL,
    'css path' => NULL,
    'settings' => array(
      'global' => array(
        'types' => array('audio'),
        'id' => 'dams_audio_wysiwyg',
        'activePlugins' => array(),
        'enabledPlugins' => array(
          'upload' => 'upload',
          'dams_media_browser--media_browser_4' => 'dams_media_browser--media_browser_4',
        ),
        'file_extensions' => 'mp3 wav ogg',
      ),
    ),
  );

  // Insert image only plugin definition.
  $plugins['dams_image'] = array(
    'title' => t('Ding DAMS Image Plugin'),
    'icon path' => drupal_get_path('module', 'ding_dams') . '/wysiwyg_plugins/images',
    'icon file' => 'wysiwyg-dams-image.png',
    'icon title' => t('Insert image'),
    'js path' => drupal_get_path('module', 'ding_dams') . '/wysiwyg_plugins/js',
    'js file' => 'wysiwyg-dams-image.js',
    'css file' => NULL,
    'css path' => NULL,
    'settings' => array(
      'global' => array(
        'types' => array('image'),
        'id' => 'dams_image_wysiwyg',
        'activePlugins' => array(),
        'enabledPlugins' => array(
          'upload' => 'upload',
          'dams_media_browser--media_browser_2' => 'dams_media_browser--media_browser_2',
        ),
        'file_extensions' => 'jpg gif png jpeg',
      ),
    ),
  );

  return $plugins;
}

/**
 * Prepares the page to be able to launch the media browser.
 *
 * Defines default variables.
 */
function ding_dams_include_browser_js() {
  static $included;
  if ($included) {
    return;
  }
  $included = TRUE;
  module_load_include('inc', 'media', 'includes/media.browser');
  $javascript = media_browser_js();
  foreach ($javascript as $key => $definitions) {
    foreach ($definitions as $definition) {
      $function = 'drupal_add_' . $key;
      // Since the arguments to pass are variable, use call_user_func_array().
      // This will not handle all potential drupal_add_*() functions directly
      // but covers the js and library needed here, which are unlikely to be
      // expanded since this function is only a workaround
      // for a wysiwyg limitation.
      call_user_func_array($function, $definition);
    }
  }
  // Add wysiwyg-specific settings.
  $settings = array('blacklist' => array('src', 'fid', 'view_mode', 'format'));
  drupal_add_js(array('media' => $settings), 'setting');
  $ding_dams_icons_path = '/' . drupal_get_path('module', 'ding_dams') . '/wysiwyg_plugins/images/';
  drupal_add_js(array('ding_dams' => array('icon_path' => $ding_dams_icons_path)), 'setting');
}

/**
 * Element validate callback for the media WYSIWYG button.
 */
function ding_dams_wysiwyg_button_element_validate($element, &$form_state) {
  if (!empty($element['#value'])) {
    $format = filter_format_load($form_state['build_info']['args'][0]->format);
    $filters = filter_list_format($format->format);
    if (empty($filters['media_filter']->status)) {
      form_error($element, t('The <em>Convert Media tags to markup</em> filter must be enabled for the <a href="@format-link">@format format</a> in order to use the Media browser WYSIWYG button.', array(
        '@format-link' => url('admin/config/content/formats/' . $format->format, array('query' => array('destination' => $_GET['q']))),
        '@format' => $format->name,
      )));
    }
  }

  return $element;
}
