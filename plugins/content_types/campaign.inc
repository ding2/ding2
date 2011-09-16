<?php

/**
 * @file campaign.inc
 * 
 * Ding Campaign CTools plugin file
 *
 */

$plugin = array(
  'title' => t('Relevant campaigns'),
  'description' => t('Display ad-like campaigns'),
  'single' => TRUE,
  'defaults' => array('ding_campaign_count' => 3, 'ding_campaign_offset' => 0),
  'required context' => array(
      new ctools_context_optional(t('Page node'), 'node'),
      new ctools_context_optional(t('Search term'), 'string')),
  'category' => t('Ding!'),
);

/**
 * Implements hook_content_type_render().
 */
function ding_campaign_campaign_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $context_data = array(
    'page' => isset($context[0]->data) ? $context[0]->data : NULL,
    'search_term' => isset($context[1]->data) ? $context[1]->data : NULL,
  );
  $count = $conf['ding_campaign_count'];
  $offset = $conf['ding_campaign_offset'];
  
  $block->content = ding_campaign_display($context_data, $count, $offset);

  return $block;
}

/**
 * Implements hook_content_type_edit_form().
 */
function ding_campaign_campaign_content_type_edit_form($form, &$form_state) {

  $form['ding_campaign_count'] = array(
    '#type' => 'textfield',
    '#title' => t('Campaign count'),
    '#description' => t('The maximum number of campaigns to display'),
    '#default_value' => (isset($form_state['conf']['ding_campaign_count'])) ? $form_state['conf']['ding_campaign_count'] : DING_CAMPAIGN_DEFAULT_COUNT,
    '#size' => 2,
    '#maxlength' => 2,
  );

  $form['ding_campaign_offset'] = array(
    '#type' => 'textfield',
    '#title' => t('Campaign offset'),
    '#description' => t('Which campaign should we count from when returning campaigns. This is used to avoid displaying the same campaigns when using multiple campaign panes on the same panel. Use 0 to return the most relevant campaigns.'),
    '#default_value' => (isset($form_state['conf']['ding_campaign_offset'])) ? $form_state['conf']['ding_campaign_offset'] : 0,
    '#size' => 3,
    '#maxlength' => 3,
  );

  return $form;
}

/**
 * Implements hook_content_type_edit_form_submit().
 */
function ding_campaign_campaign_content_type_edit_form_submit(&$form, &$form_state) {
  $form_state['conf']['ding_campaign_count'] = $form_state['values']['ding_campaign_count'];
  $form_state['conf']['ding_campaign_offset'] = $form_state['values']['ding_campaign_offset'];
}