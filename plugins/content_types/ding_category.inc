<?php

$plugin = array(
  'title' => t('Ding category menu'),
  'description' => t('Display a list of term link from a selected taxonomy vocabolary'),
  'single' => TRUE,
  'edit form' => 'ding_content_category_content_type_edit_form',
  'render callback' => 'ding_content_category_content_type_render',
  'category' => t('Ding!'),
);

function ding_content_category_content_type_render($subtype, $conf, $context = NULL) {
  $vocab = taxonomy_vocabulary_machine_name_load($conf['vocab']);
  $terms = taxonomy_term_load_multiple(FALSE, array('vid' => $vocab->vid));

  $items = array();
  // @Todo, make these links context sensitive per active library.
  foreach ($terms as $term) {
    $items[] = l($term->name, 'taxonomy/term/' . $term->tid);
  }
  
  $block = new stdClass();
  $block->content = theme('item_list', array('items' => $items));
  return $block;
}

/**
* 'Edit form' callback for the content type.
*/
function ding_content_category_content_type_edit_form($form, &$form_state) {
  $vocabs = array();
  foreach (taxonomy_vocabulary_get_names() as $name => $vocab) {
    $vocabs[$name] = $vocab->name;
  };

  $form['vocab'] = array(
    '#type' => 'select',
    '#title' => t('Select vocabolary'),
    '#options' => $vocabs,
    '#default_value' => $form_state['conf']['vocab'],
    '#required' => TRUE,
  );

  return $form;
}

/**
 * Submit handler for ding_content_category_content_type_edit_form().
 */
function ding_content_category_content_type_edit_form_submit(&$form, &$form_state) {
  $form_state['conf']['vocab'] = $form_state['values']['vocab'];
}
