<?php

$plugin = array(
  'title' => t('Ding library list (selectbox)'),
  'description' => t('Display a select box with available libraries.'),
  'single' => TRUE,
  'edit form' => 'ding_library_librarylist_content_type_edit_form',
  'render callback' => 'ding_library_librarylist_content_type_render',
  'category' => t('Ding!'),
);

function ding_library_librarylist_content_type_render($subtype, $conf, $context = NULL) {
  $path = explode('/', trim($_SERVER['REQUEST_URI'], '/'));
  $page_type = array_shift($path);
  $block = new stdClass();
  $groups = og_load_multiple(FALSE, array('entity_type' => 'node'));
  $items = array($page_type . ((!isset($context[1]) || $context[1] == 'all') ? '' : '/all/' . $context[1]) => t('All libraries'));

  $nids = array();
  foreach ($groups as $group) {
    $nids[$group->gid] = $group->etid;
  }

  $nodes = node_load_multiple($nids, array('type' => 'ding_library'));

  if (empty($nodes)) {
    return $block;
  }

  foreach ($nodes as $node) {
    $items[$page_type . '/' . $node->field_slug['und'][0]['value'] . '/' . (isset($context[1]) ? $context[1] : 'all')] = $node->title;
  }

  $block->content = drupal_get_form('ding_library_librarylist_select_library', $items, $context, $page_type);
  return $block;
}

/**
 * 'Edit form' callback for the content type.
 */
function ding_library_librarylist_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Form which creates a select box with available libraries.
 */
function ding_library_librarylist_select_library($form, &$form_state, $items, $context, $page_type) {
  $form = array();
  $form['labe_select_library'] = array(
    '#markup' => t('Choose library'),
    '#prefix' => '<div class="label">',
    '#suffix' => '</div>',
  );
  $form['select_library'] = array(
    '#type' => 'select',
    '#prefix' => '<div class="rightcontainer">',
    '#title' => NULL,
    '#options' => $items,
    '#attributes' => array('onchange' => "form.submit('select_library');"),
    '#default_value' => $page_type . '/' . (isset($context[1]) && !isset($context[0]) || !isset($context[0]) && !isset($context[1]) ? 'all' : $context[0]) . '/' . (isset($context[0]) && !isset($context[1]) || !isset($context[0]) && !isset($context[1]) ? 'all' : $context[1]),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#suffix' => '</div>',
    '#value' => t('Show'),
  );
  return $form;
}

/**
 * Submit handler for the libraries list form.
 */
function ding_library_librarylist_select_library_submit($form, &$form_state) {
  drupal_goto($form_state['values']['select_library']);
}
