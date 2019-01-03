<?php

/**
 * @file
 * Ding Campaign CTools plugin file.
 */

$plugin = array(
  'title' => t('Relevant campaign plus'),
  'description' => t('Display ad-like campaigns'),
  'single' => TRUE,
  'defaults' => array(
    'style' => 'ribbon',
  ),
  'edit form' => 'ding_campaign_plus_relevant_content_type_edit_form',
  'render callback' => 'ding_campaign_plus_relevant_content_type_render',
  'required context' => array(
    new ctools_context_optional(t('Page node'), 'node'),
    new ctools_context_optional(t('Related library'), 'node'),
    new ctools_context_optional(t('Search term'), 'string'),
    new ctools_context_optional(t('Taxonomy term'), array('entity:taxonomy_term', 'taxonomy_term')),
  ),
  'category' => t('Ding!'),
);

/**
 * Implements hook_content_type_render().
 */
function ding_campaign_plus_relevant_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $context_data = array(
    'page' => isset($context[0]->data) ? $context[0]->data : NULL,
    'library' => isset($context[1]->data) ? $context[1]->data : NULL,
    'search_term' => isset($context[2]->data) ? $context[2]->data : NULL,
    'taxonomy_term' => isset($context[3]->data) ? $context[3]->data : NULL,
    'path' => (object) array(
      'raw' => arg(),
      'path' => drupal_get_path_alias($_GET['q']),
    ),
  );
  $style = !empty($conf['style']) ? $conf['style'] : 'ribbon';

  // Check cache to see if campaign trigger has been calculated for this
  // context.
  $cid = _ding_campaign_plus_cache_id($context_data, $style);
  $cache = cache_get($cid);
  $content = '';
  if (isset($cache->data) && REQUEST_TIME < $cache->expire) {
    $content = $cache->data;
  }
  else {
    cache_set($cid . '-context', array($context_data, $style));
    $content = '<div data-ding-campaign-plus-cid="' . $cid . '"></div>';
    drupal_add_js(drupal_get_path('module', 'ding_campaign_plus') . '/js/ding_campaign_plus.js');
  }

  $block->content = $content;

  return $block;
}

/**
 * Implements hook_content_type_edit_form().
 */
function ding_campaign_plus_relevant_content_type_edit_form($form, &$form_state) {

  $form['style'] = array(
    '#type' => 'select',
    '#title' => t('Campaign style'),
    '#description' => t('The display type of the campaigns in this pane.'),
    '#options' => array(
      'ribbon' => t('Ribbon'),
      'box' => t('Box'),
    ),
    '#default_value' => $form_state['conf']['style'],
  );

  return $form;
}

/**
 * Implements hook_content_type_edit_form_validate().
 */
function ding_campaign_plus_relevant_content_type_edit_form_validate($form, &$form_state) {
  return $form;
}

/**
 * Implements hook_content_type_edit_form_submit().
 */
function ding_campaign_plus_relevant_content_type_edit_form_submit($form, &$form_state) {
  $form_state['conf']['style'] = $form_state['values']['style'];
}
