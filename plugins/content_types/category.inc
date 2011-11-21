<?php

$plugin = array(
  'title' => t('Ding library category menu'),
  'description' => t('Display a list of links to the library category pages'),
  'single' => TRUE,
  'edit form' => 'ding_library_category_content_type_edit_form',
  'render callback' => 'ding_library_category_content_type_render',
  'category' => t('Ding!'),
);

function ding_library_category_content_type_render($subtype, $conf, $context = NULL) {
  $path = explode('/', trim($_SERVER['REQUEST_URI'], '/'));
  $page_type = array_shift($path);
  $block = new stdClass();
  $items = array(l(t('All categories'), $page_type . (!isset($context[0]) || $context[0] == 'all' ? '' : '/' . $context[0] . '/all')));
  $vocabulary = taxonomy_vocabulary_machine_name_load('category');
  $terms = taxonomy_get_tree($vocabulary->vid);

  if (empty($terms)) {
    return $block;
  }

  foreach ($terms as $term) {
    $items[] = l($term->name, $page_type . '/' . (!isset($context[0]) && !isset($context[1]) || (!isset($context[0]) && isset($context[1])) ? 'all' : $context[0]) . '/' . $term->name);
  }
  $block->content = theme('item_list', array('items' => $items));

  return $block;
}

/**
 * 'Edit form' callback for the content type.
 */
function ding_library_category_content_type_edit_form($form, &$form_state) {
  return $form;
}

