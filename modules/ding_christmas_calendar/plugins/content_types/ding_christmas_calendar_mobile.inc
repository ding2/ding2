<?php
/**
 * @file
 * Widget for displaying Christmas calendar for mobile device.
 */

$plugin = array(
  'single' => TRUE,
  'title' => t('Mobile Christmas calendar'),
  'description' => t('Represents widget for displaying Christmas calendar for mobile devices.'),
  'category' => t('Christmas calendar'),
  'render callback' => 'ding_christmas_calendar_mobile_render',
  'all contexts' => TRUE,
);

/**
 * Render callback of Christmas calendar widget on mobile devices.
 */
function ding_christmas_calendar_mobile_render($subtype, $conf, $args, $contexts) {
  $block = new stdClass();
  $block->title = t('Christmas calendar');
  $quiz_id = variable_get('ding_christmas_calendar_quiz_id', NULL);
  $vars = ding_christmas_calendar_generate_content($quiz_id, TRUE);
  $path = drupal_get_path('module', 'ding_christmas_calendar');
  $block->content = array(
    '#markup' => theme('ding_christmas_calendar_widget', $vars),
    '#attached' => array(
      'js' => array(
        $path . '/js/ding_christmas_calendar.js',
      ),
    ),
  );
  libraries_load('slick');
  libraries_load('notify');
  return $block;
}
