<?php
/**
 * @file
 * Widget for displaying Christmas calendar.
 */

$plugin = array(
  'single' => TRUE,
  'title' => t('Full-page Christmas calendar'),
  'description' => t('Represents widget for displaying Christmas calendar.'),
  'category' => t('Christmas calendar'),
  'render callback' => 'ding_christmas_calendar_render',
  'all contexts' => TRUE,
);

/**
 * Render callback of Christmas calendar widget.
 */
function ding_christmas_calendar_render($subtype, $conf, $args, $contexts) {
  $block = new stdClass();
  $block->title = t('Christmas calendar');
  $quiz_id = variable_get('ding_christmas_calendar_quiz_id', NULL);
  $vars = ding_christmas_calendar_generate_content($quiz_id);
  $block->content = array(
    '#markup' => theme('ding_christmas_calendar_widget', $vars),
    '#attached' => array(
      'css' => array(
        drupal_get_path('module', 'ding_christmas_calendar') . '/css/ding_christmas_calendar.css',
      ),
    ),
  );
  return $block;
}
