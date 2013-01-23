<?php

$plugin = array(
  'title' => t('Ding library selectbox'),
  'description' => t('Display a select box with available libraries.'),
  'single' => TRUE,
  'edit form' => 'ding_content_library_list_content_type_edit_form',
  'render callback' => 'ding_content_library_list_content_type_render',
  'category' => t('Ding!'),
  'required context' => array(new ctools_context_optional(t('Selected category'), array('term', 'taxonomy_term')), new ctools_context_optional(t('Library'), 'node')),
  'defaults' => array(
    'type' => 'news',
  ),
);

function ding_content_library_list_content_type_render($subtype, $conf, $panel_args, $context = NULL) {
  $block = new stdClass();
  $library = NULL;
  $selected_term = NULL;
  $selected_url = NULL;
  $suffix = '';
  
  if ($conf['type'] == 'news') {
      $node_type = 'nyheder';
  } elseif ($conf['type'] == 'events') {
    $node_type = 'arrangementer';
  }

  if (isset($context[0]->data)) {
    $selected_term = $context[0]->data;
    $suffix = '/' . $selected_term->tid;
  }
  if (isset($context[1]->data)) {
    $library = $context[1]->data;
    $uri = 'bibliotek/' . $library->nid;
    $base = $uri['path'] . '/' . $node_type  . $suffix;
    $selected_url =  $node_type . '/' .  $uri . $suffix;
  }
  else {
    $base = $conf['type'];
  }

  $groups = og_load_multiple(FALSE, array('entity_type' => 'node'));

  $nids = array();
  foreach ($groups as $group) {
    $nids[$group->gid] = $group->etid;
  }

  $nodes = node_load_multiple($nids, array('type' => 'ding_library'));
  if (empty($nodes)) {
    return $block;
  }

  uasort($nodes, 'ding_content_library_list_sort_title');
  
  $items = array($node_type  . $suffix => t('All libraries'));  

  foreach ($nodes as $node) {
    $uri = 'bibliotek/' . $node->nid;
    $items[ $node_type . '/' . $uri  . $suffix] = $node->title;
  }

  // Generate the select box form.
  $block->content = drupal_get_form('ding_content_library_list_select_library', $items, $context, $selected_url);
  return $block;
}

function ding_content_library_list_sort_title($a, $b) {
  if (!isset($b->title)) {
    return -1;
  }
  if (!isset($a->title)) {
    return 1;
  }
  return strcasecmp($a->title, $b->title);
}


/**
 * Form which creates a select box with available libraries.
 */
function ding_content_library_list_select_library($form, &$form_state, $items, $context, $selected_url) {
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
    '#default_value' => $selected_url,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#prefix' => '<div class="library-list-show">',
    '#suffix' => '</div></div>',
    '#value' => t('Show'),
  );
  return $form;
}

/**
 * Submit handler for the libraries list form.
 */
function ding_content_library_list_select_library_submit($form, &$form_state) {
  drupal_goto($form_state['values']['select_library']);
}

/**
 * 'Edit form' callback for the content type.
 */
function ding_content_library_list_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $form['type'] = array(
    '#type' => 'select',
    '#title' => t('Type of list to link to'),
    '#options' => array(
      'news' => t('News'),
      'events' => t('Events'),
    ),
    '#default_value' => !empty($conf['type']) ? $conf['type'] : 'news',
    '#required' => TRUE,
  );

  return $form;
}

/**
 * Submit handler for the admin edit form.
 */
function ding_content_library_list_content_type_edit_form_submit(&$form, &$form_state) {
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}

