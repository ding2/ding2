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
  $url_placeholder_all_categories = $conf['url_settings_all_categories'];
  $url_placeholder = $conf['url_settings'];
  $path = explode('/', trim(request_uri(), '/'));
  $page_type = array_shift($path);
  $block = new stdClass();
  $vocabulary = taxonomy_vocabulary_machine_name_load('category');
  $terms = taxonomy_get_tree($vocabulary->vid);

  $url_path_placeholders = array(
    '%page_type',
    '%library',
    '%category',
  );

  $items = array(l(t('All categories'), str_replace($url_path_placeholders, array($page_type, isset($context[0]) ? $context[0] : '', FALSE), $url_placeholder_all_categories)));

  if (empty($terms)) {
    return $block;
  }

  foreach ($terms as $term) {
    $url_path = array(
      $page_type,
      !isset($context[0]) && !isset($context[1]) || (!isset($context[0]) && isset($context[1])) ? 'all' : $context[0],
      $term->name
    );
    $url = str_replace($url_path_placeholders, $url_path, $url_placeholder);
    $items[] = l($term->name, $url);
  }
  $block->content = theme('item_list', array('items' => $items));

  return $block;
}

/**
 * 'Edit form' callback for the content type.
 */
function ding_library_category_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  $form['url_settings_all_categories'] = array(
    '#type' => 'textfield',
    '#title' => t('Define which url to redirect to, when showing all categories.'),
    '#description' => t('Placeholders in the url %page_type, %library, %category.<br /><code>Ex. %page_type/%library/%category</code>'),
    '#default_value' => !empty($conf['url_settings_all_categories']) ? $conf['url_settings_all_categories'] : '',
  );
  $form['url_settings'] = array(
    '#type' => 'textfield',
    '#title' => t('Define which url to redirect to, when selecting a category.'),
    '#description' => t('Placeholders in the url %page_type, %library, %category.<br /><code>Ex. %page_type/%library/%category</code>'),
    '#default_value' => !empty($conf['url_settings']) ? $conf['url_settings'] : '',
  );
  return $form;
}

function ding_library_category_content_type_edit_form_submit(&$form, &$form_state) {
  $form_state['conf']['url_settings_all_categories'] = $form_state['values']['url_settings_all_categories'];
  $form_state['conf']['url_settings'] = $form_state['values']['url_settings'];
}

