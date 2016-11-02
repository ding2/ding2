<?php
/**
 * @file
 * Content type plugin for all opening hours.
 */

/**
 * Array describing the plugin to CTools/Panels.
 */
$plugin = array(
  'title' => t('All opening hours'),
  'description' => t('Show todays opening hours for all libraries.'),
  'single' => TRUE,
  'content_types' => array('list'),
  'category' => t('Ding!'),
);

/**
 * Render the block.
 */
function ding_ddbasic_opening_hours_all_opening_hours_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  $block->title = t('Opening hours');
  $block->content = theme('ding_ddbasic_opening_hours_all') . '<div class="more-link">' . l(t('View all opening hours'), '/libraries') . '</div>';

  return $block;
}
