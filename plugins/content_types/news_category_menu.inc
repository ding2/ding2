<?php

$plugin = array(
  'title' => t('Ding news category menu'),
  'description' => t('Generates links to news category overview pages.'),
  'single' => TRUE,
  'edit form' => 'ding_news_category_menu_content_type_edit_form',
  'render callback' => 'ding_news_category_menu_content_type_render',
  'category' => t('Ding!'),
  'required context' => array(new ctools_context_optional(t('Selected category'), array('term', 'taxonomy_term')), new ctools_context_optional(t('Library'), 'node')),
);

function ding_news_category_menu_content_type_render($subtype, $conf, $panel_args, $context = NULL) {
  $block = new stdClass();
  $library = NULL;
  $selected_term = NULL;

  if (isset($context[0]->data)) {
    $selected_term = $context[0]->data;
  }
  if (isset($context[1]->data)) {
    $library = $context[1]->data;
    $uri = entity_uri('node', $library);
    $base = $uri['path'] . '/news-category';
  }
  else {
    $base = 'news-category';
  }

  $options = array();
  if (!$selected_term) {
    $options = array('attributes' => array('class' => array('active')));
  }
  // Might seem a bit odd to select 'all' when node doesn't have any category,
  // but we'll go with that for the moment being.
  $items = array(l(t('All categories'), $base . '/all', $options));

  $vocabulary = taxonomy_vocabulary_machine_name_load('news_category');
  $terms = taxonomy_get_tree($vocabulary->vid, 0, NULL, TRUE);

  foreach ($terms as $term) {
    if ($selected_term && $selected_term->tid == $term->tid) {
      $options = array('attributes' => array('class' => array('active')));
    }
    else {
      $options = array();
    }
    $uri = entity_uri('taxonomy_term', $term);
    $items[] = l($term->name, $uri['path'], $options);
  }
  $block->content = theme('item_list', array('items' => $items));

  return $block;
}

/**
 * Returns an edit form for the content type.
 *
 * We're not actually doing anything here, but we need to have this hook
 * for this content type to work.
 */
function ding_news_category_menu_content_type_edit_form($form, &$form_state) {
  return $form;
}

function ding_news_category_menu_content_type_edit_form_submit(&$form, &$form_state) {
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}

