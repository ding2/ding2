<?php

/**
 * @file
 * Ding Campaign CTools plugin file.
 */

$plugin = array(
  'title' => t('Relevant campaign plus'),
  'description' => t('Display ad-like campaigns'),
  'single' => TRUE,
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
  );

  $style = (!empty($conf['ding_campaign_style'])) ? $conf['ding_campaign_style'] : 'ding_campaign_full_width';

  $block->content = ding_campaign_plus_display($context_data, $style);

  return $block;
}

/**
 * Implements hook_content_type_edit_form().
 */
function ding_campaign_plus_relevant_content_type_edit_form($form, &$form_state) {

  $form['ding_campaign_style'] = array(
    '#type' => 'select',
    '#title' => t('Campaign width'),
    '#description' => t('Applicable for campaigns. Content will be resized to selected width.'),
    '#options' => array(
      'ding_campaign_medium_width' => t('Medium width'),
      'ding_campaign_full_width' => t('Full width'),
    ),
    '#default_value' => (isset($form_state['conf']['ding_campaign_style'])) ? $form_state['conf']['ding_campaign_style'] : 'ding_campaign_full_width',
  );

  drupal_add_css(drupal_get_path('module', 'ding_campaign') . '/css/ding_campaign.admin.css');

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
  $form_state['conf']['ding_campaign_style'] = $form_state['values']['ding_campaign_style'];
}
