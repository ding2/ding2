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
  $url_placeholder_all_categories = $conf['url_settings_all_libraries'];
  $url_placeholder = $conf['url_settings_library'];
  $path = explode('/', trim(request_uri(), '/'));
  $page_type = array_shift($path);
  $block = new stdClass();
  $groups = og_load_multiple(FALSE, array('entity_type' => 'node'));

  $nids = array();
  foreach ($groups as $group) {
    $nids[$group->gid] = $group->etid;
  }

  $nodes = node_load_multiple($nids, array('type' => 'ding_library'));

  if (empty($nodes)) {
    return $block;
  }

  $url_path_placeholders = array(
    '%page_type',
    '%library_id',
    '%library_slug',
    '%category',
  );

  // Generate the url for the selected library.
  $selected_url = str_replace($url_path_placeholders, array($page_type, isset($context[0]) ? $context[0] : NULL, FALSE, isset($context[1]) ? $context[1] : NULL), $url_placeholder);
  // Generate the url for when selecting 'show all libraries'.
  $default_url = str_replace($url_path_placeholders, array($page_type, isset($context[0]) ? $context[0] : NULL, FALSE, isset($context[1]) ? $context[1] : NULL), $url_placeholder_all_categories);

  $items = array($default_url => t('All libraries'));

  foreach ($nodes as $node) {
    $url_path = array(
      $page_type,
      $node->nid,
      $node->field_slug['und'][0]['value'],
      isset($context[1]) ? $context[1] : 'all',
    );
    // Parse the url placeholder settings, set in the panel pane settings.
    $url = str_replace($url_path_placeholders, $url_path, $url_placeholder);
    $items[$url] = $node->title;
  }

  // Generate the select box form.
  $block->content = drupal_get_form('ding_library_librarylist_select_library', $items, $context, $selected_url);
  return $block;
}

/**
 * Form which creates a select box with available libraries.
 */
function ding_library_librarylist_select_library($form, &$form_state, $items, $context, $selected_url) {
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

/**
 * 'Edit form' callback for the content type.
 */
function ding_library_librarylist_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  $form['url_settings_all_libraries'] = array(
    '#type' => 'textfield',
    '#title' => t('Define which url to redirect to, when showing all libraries.'),
    '#description' => t('Placeholders in the url %page_type, %library_slug, %library_id, %category.<br /><code>Ex. %page_type/%library/%category</code>'),
    '#default_value' => !empty($conf['url_settings_all_libraries']) ? $conf['url_settings_all_libraries'] : '',
  );
  $form['url_settings_library'] = array(
    '#type' => 'textfield',
    '#title' => t('Define which url to redirect to, when selecting a library.'),
    '#description' => t('Placeholders in the url %page_type, %library_slug, %library_id, %category.<br /><code>Ex. %page_type/%library/%category</code>'),
    '#default_value' => !empty($conf['url_settings_library']) ? $conf['url_settings_library'] : '',
  );
  return $form;
}

/**
 * Submit handler for the admin edit form.
 */
function ding_library_librarylist_content_type_edit_form_submit(&$form, &$form_state) {
  $form_state['conf']['url_settings_all_libraries'] = $form_state['values']['url_settings_all_libraries'];
  $form_state['conf']['url_settings_library'] = $form_state['values']['url_settings_library'];
}

