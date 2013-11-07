<?php
/**
 * @file
 * Creates a menu with links to filter the staff based on libraries.
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
 * Implements hook_ID_content_type_render().
 */
function ding_staff_library_menu_content_type_render($subtype, $conf, $panel_args, $context = NULL) {
  $block = new stdClass();
  $selected_library = FALSE;
  $items = array();

  // Default link of 'All libraries' links to staff list page. Set active class
  // if no library is given in the context.
  $options = array('attributes' => array('class' => array('active')));
  if (isset($panel_args[0])) {
    $selected_library = $panel_args[0];
    $options = array();
  }
  $items[] = l(t('All libraries'), 'staff' , $options);

  // Select library nids and titles.
  $results = db_query("SELECT
    n.nid,
    n.title,
    fls.field_ding_library_slug_value AS slug
    FROM node n
    JOIN field_data_field_ding_library_slug fls ON n.nid = fls.entity_id 
    WHERE n.type = 'ding_library'
    AND n.status = 1
    ORDER BY n.title;");
  
  // Create links for each library found to that libraries staff page.
  foreach ($results as $row) {
    $options = array();
    if ($selected_library && $selected_library == $row->slug) {
      $options = array('attributes' => array('class' => array('active')));
    }
    $items[] = l($row->title, 'bibliotek/' . $row->slug . '/staff', $options);
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
