<?php
/**
 * @file
 * Serendipity inspiration list ctools content_type.
 */

$plugin = array(
  'title' => t('General purpose ding_object serendipity panel'),
  'description' => t('Provide serendipity based on a current ding_object.'),
  'admin info' => 'ding_serendipity_ting_entity_inspiration_list_admin_info',
  'single' => TRUE,
  'category' => t('Ding!'),
);

/**
 * Returns a summary for the administration information in panels.
 */
function ding_serendipity_ting_entity_inspiration_list_admin_info($subtype, $conf, $context) {
  return ding_serendipity_get_default_admin_info($subtype, $conf, $context);
}

/**
 * Implements hook_content_type_edit_form().
 */
function ding_serendipity_ting_entity_inspiration_list_content_type_edit_form($form, &$form_state) {
  module_load_include('inc', 'ding_serendipity', 'plugins/content_types/serendipity');
  $base = ding_serendipity_form_base($form_state);
  $form += $base;

  $form['limit'] = array(
    '#type' => 'textfield',
    '#title' => t('Serendipity limit'),
    '#description' => t('The maximum number of items to display in the initial list.'),
    '#default_value' => (isset($form_state['conf']['limit'])) ? $form_state['conf']['limit'] : 4,
    '#size' => 2,
    '#maxlength' => 2,
  );

  return $form;
}

/**
 * Implements hook_content_type_edit_form_submit().
 */
function ding_serendipity_ting_entity_inspiration_list_content_type_edit_form_submit($form, &$form_state) {
  ding_serendipity_form_base_submit($form_state);
  $form_state['conf']['limit'] = $form_state['values']['limit'];
}

/**
 * Implements hook_content_type_render().
 */
function ding_serendipity_ting_entity_inspiration_list_content_type_render($subtype, $conf, $args, $context) {
  $context = array(
    'entity_type' => 'ding_object',
    'bundle' => 'ding_object',
    // TODO: Why do we use an argument here instead of a context?
    'ting_object_id' => $args[0],
    'view_mode' => !empty($conf['view_mode']) ? $conf['view_mode'] : 'big_teaser',
    'sort_weight' => !empty($conf['sort_weight']) ? $conf['sort_weight'] : FALSE,
    'max' => !empty($conf['max']) ? $conf['max'] : 4,
    'min' => !empty($conf['min']) ? $conf['min'] : 4,
    'random' => !empty($conf['random']) ? TRUE : FALSE,
  );

  $limit = !empty($conf['limit']) ? $conf['limit'] : 4;
  $content = array(
    // TODO This theme entry does not seem to appear anywhere in the codebase?
    '#theme' => 'ding_tabs',
    '#name' => 'related_material',
    '#title' => t('Related material'),
    '#navigation' => 'My navigation',
    '#tabs' => array(
      'object' => array(
        '#title' => 'Related material',
        '#theme' => 'ding_tabs_content',
        '#type' => 'serendipity',
        '#ajax' => TRUE,
        '#options' => array(
          'context' => $context,
        ),
        '#limit' => $limit,
      ),
    ),
  );
  $output['content'] = $content;

  $block = new stdClass();
  $block->title = t('Related material');
  $block->content = $output;

  return $block;
}
