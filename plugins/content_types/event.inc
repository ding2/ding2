<?php

$plugin = array(
  'title' => t('Ding library event menu'),
  'description' => t('Display a list of links to the library event pages'),
  'single' => TRUE,
  'edit form' => 'ding_library_event_content_type_edit_form',
  'render callback' => 'ding_library_event_content_type_render',
  'category' => t('Ding!'),
);

function ding_library_event_content_type_render($subtype, $conf, $context = NULL) {
  $block = new stdClass();
  $groups = og_load_multiple(FALSE, array('entity_type' => 'node'));
  $nids = array();
  foreach ($groups as $group) {
    $nids[$group->etid] = $group->gid;
  }
  
  $nodes = node_load_multiple(array_keys($nids), array('type' => 'ding_library'));
  if (empty($nodes)) {
    return $block;
  }

  $items = array();
  foreach ($nodes as $node) {
    $items[] = l($node->title, 'library/' . $nids[$node->nid] . '/events');
  }

  $block->content = theme('item_list', array('items' => $items));
  return $block;
}

/**
* 'Edit form' callback for the content type.
*/
function ding_library_event_content_type_edit_form($form, &$form_state) {return $form;}

/**
 * Submit handler for ding_library_event_content_type_edit_form().
 */
function ding_library_event_content_type_edit_form_submit(&$form, &$form_state) {}
