<?php

/**
 * @file
 * Ding user complete CTools plugin file.
 */

/**
 * Plugin description.
 */
$plugin = array(
  'title' => t('Ding user complete barometer pane'),
  'description' => t('Displays a barometer displaying how complete the profile of a user is.'),
  'single' => TRUE,
  'render callback' => 'ding_user_complete_content_type_render',
  'category' => t('Ding!'),
);


/**
 * Implements hook_content_type_render().
 */
function ding_user_complete_content_type_render($subtype, $conf, $panel_args, $context) {
  $data = ding_user_complete_get_content();
  $output = new stdClass();
  if ($data) {
    $output->title = t('Ding user completeness');

    // Completed in procent.
    $procent = ($data['completed'] / $data['total']) * 100;

    // Select random markup to show.
    $markup = '';
    if ($procent != 100) {
      $key = array_rand($data['markup'], 1);
      $markup = $data['markup'][$key];
    }
    $output->content = theme('user_complete_barometer', array('procent' => $procent, 'markup' => $markup));
  }
  return $output;
}
