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

  if ($conf['show_in_tabs'] == 1) {
    $block->content = theme('ding_ddbasic_opening_hours_all_tabbed');
  }
  else {
    $block->content = theme('ding_ddbasic_opening_hours_all');
  }

  $block->content = $block->content . '<div class="more-link">' . l(t('View all opening hours'), '/libraries') . '</div>';

  return $block;
}

/**
 * Pane configuration settings form.
 */
function ding_ddbasic_opening_hours_all_opening_hours_content_type_edit_form($form, &$form_state) {
  $form['show_in_tabs'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show opening hours in tabs?'),
    '#default_value' => (isset($form_state['conf']['show_in_tabs'])) ? $form_state['conf']['show_in_tabs'] : 0,
  );

  return $form;
}

/**
 * Form submit processing.
 */
function ding_ddbasic_opening_hours_all_opening_hours_content_type_edit_form_submit($form, &$form_state) {
  $form_state['conf']['show_in_tabs'] = $form_state['values']['show_in_tabs'];
}
