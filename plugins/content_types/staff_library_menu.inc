<?php

$plugin = array(
  'title' => t('Ding staff library menu'),
  'description' => t('Generates links to library staff overview pages.'),
  'single' => TRUE,
  'edit form' => 'ding_staff_library_menu_content_type_edit_form',
  'render callback' => 'ding_staff_library_menu_content_type_render',
  'category' => t('Ding!'),
  'required context' => new ctools_context_optional(t('Library'), 'node'),
);

function ding_staff_library_menu_content_type_render($subtype, $conf, $panel_args, $context = NULL) {
  $block = new stdClass();
  $selected_library = NULL;
  
  // TODO: Set the selected library
  if (isset($context->data)) {
    $selected_library = $context->data;
  }

  $options = array();
  if ($selected_library == NULL) {
    $options = array('attributes' => array('class' => array('active')));
  }

  // default link of 'All libraries' links to staff list page 
  $items = array(l(t('All libraries'), 'staff' , $options));

  // Get all library nids
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'ding_library')
    ->propertyCondition('status', 1);
  $result = $query->execute();

  if (isset($result['node'])) {
    $library_items_nids = array_keys($result['node']);
    $lib_nodes = node_load_multiple($library_items_nids);
    
    foreach ($lib_nodes as $lib) {
      // Lookup in path checking if this is the library staff page shown
      //$alias = drupal_lookup_path('alias', 'bibliotek/' . $nid);
      if ($selected_library && $selected_library->nid == $lib->nid) {
        $options = array('attributes' => array('class' => array('active')));
      }
      else {
        $options = array();
      }

      $uri = 'bibliotek/' . $lib->nid . '/staff' ;

      $items[] = l($lib->title, $uri, $options);
    }

  }

  $block->content = theme('item_list', array('items' => $items, 'attributes' => array('class' => array('sub-menu'))));
    
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

