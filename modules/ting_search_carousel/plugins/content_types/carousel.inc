<?php
/**
 * @file
 * Provides search results as a Panels content type.
 */

$plugin = array(
  'title' => t('Ting search carousel'),
  'single' => TRUE,
  'description' => t('A carousel displaying search results against the Ting system'),
  'category' => t('Ting'),
);

/**
 * Return the pane contents.
 */
function ting_search_carousel_carousel_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  if ($searches = variable_get('ting_carousel_search_queries', array())) {
    $tabs = array();
    foreach ($searches as $index => $search) {
      $chunk = _ting_search_carousel_get_frontpage_covers($index, 0, TING_SEARCH_CAROUSEL_CHUNK_SIZE, TRUE);
      $tabs[$index] = array(
        'title' => $search['title'],
        'subtitle' => $search['subtitle'],
        'path' => 'ting_search_carousel/results/ajax/' . $index,
        'content' => $chunk['collections'],
        'offset' => $chunk['next_offset'],
      );
    }

    $tab_position = variable_get('ting_search_carousel_tabs_position');

    $vars = array(
      'tabs' => $tabs,
      'tab_position' => $tab_position,
      'transition' => variable_get('ting_search_carousel_transition', 'fade'),
      'preload' => variable_get('ting_search_carousel_server_render', 5),
    );
    $block->content = theme('ting_search_carousel', $vars);
  }

  return $block;
}

/**
 * Return the pane titles.
 */
function ting_search_carousel_carousel_content_type_admin_title($subtype, $conf, $context) {
  return t('Ting search carousel');
}

/**
 * Returns an edit form for the content type.
 */
function ting_search_carousel_carousel_content_type_edit_form($form, &$form_state) {
  return $form;
}
