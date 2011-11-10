<?php

$plugin = array(
  'title' => t('Menu title'),
  'description' => t('The title of the currently active menu item.'),
  'single' => TRUE,
  'edit form' => 'ding_library_menu_title_content_type_edit_form',
  'render callback' => 'ding_library_menu_title_content_type_render',
  'category' => t('Ding!'),
);

function ding_library_menu_title_content_type_render($subtype, $conf, $panel_args, $context = NULL) {
  $block = new stdClass();
  $block->content = '<h2>' . menu_get_active_title() . '</h2>';

  return $block;
}

/**
 * 'Edit form' callback for the content type.
 */
function ding_library_menu_title_content_type_edit_form($form, &$form_state) {
  return $form;
}


