<?php
/**
 * @file
 *
 */

$plugin = array(
  'title' => t('Ding staff library menu'),
  'description' => t('Generates links to library staff overview pages.'),
  'single' => TRUE,
  'edit form' => 'ding_staff_library_menu_content_type_edit_form',
  'render callback' => 'ding_staff_library_menu_content_type_render',
  'category' => t('Ding!'),
  'required context' => new ctools_context_optional(t('Library'), 'node'),
);

/**
 * @TODO ?
 */
function ding_staff_library_menu_content_type_render($subtype, $conf, $panel_args, $context = NULL) {
  $block = new stdClass();
  $selected_library = FALSE;
  $items = array();

  // Default link of 'All libraries' links to staff list page. Set active class
  // if no library is given in the context.
  $options = array('attributes' => array('class' => array('active')));
  if (isset($context->data)) {
    $selected_library = $context->data;
    $options = array();
  }
  $items[] = l(t('All libraries'), 'staff' , $options);

  // Select libray nids and titles.
  $results = db_select('node', 'n')
    ->fields('n', array('nid', 'title'))
    ->condition('n.type', 'ding_library')
    ->condition('n.status',   1)
    ->execute();

  // Create links for each library found to that libraries staff page.
  foreach ($results as $row) {
    $options = array();
    if ($selected_library && $selected_library->nid == $row->nid) {
      $options = array('attributes' => array('class' => array('active')));
    }
    $items[] = l($row->title, 'bibliotek/' . $row->nid . '/staff', $options);
  }

  $block->content = array(
    '#theme' => 'item_list',
    '#items' => $items,
    '#attributes' => array(
      'class' => array('sub-menu'),
    ),
  );

  return $block;
}

/**
 * Returns an edit form for the content type.
 *
 * We're not actually doing anything here, but we need to have this hook
 * for this content type to work.
 */
function ding_staff_library_menu_content_type_edit_form($form, &$form_state) {
  return $form;
}
