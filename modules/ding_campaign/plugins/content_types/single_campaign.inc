<?php
/**
 * @file
 * Ding single campaign CTools plugins file.
 */

$plugin = array(
  'title' => t('Single campaigns'),
  'description' => t('Display single campaigns'),
  'single' => TRUE,
  'edit form' => 'ding_campaign_single_campaign_content_type_edit_form',
  'render callback' => 'ding_campaign_single_campaign_content_type_render',
  'category' => t('Ding!'),
);

/**
 * Implements hook_content_type_edit_form().
 */
function ding_campaign_single_campaign_content_type_edit_form($form, &$form_state) {
  $available_campaigns = ding_campaign_get_list();

  $form['ding_campaign']['single_campaign'] = array(
    '#type' => 'select',
    '#title' => t('Select campaign'),
    '#options' => $available_campaigns,
    '#default_value' => reset($available_campaigns),
  );

  return $form;
}

/**
 * Submit function for configuration form.
 *
 * @see ding_campaign_single_campaign_content_type_edit_form().
 */
function ding_campaign_single_campaign_content_type_edit_form_submit($form, &$form_state) {
  $form_state['conf']['single_campaign'] = $form_state['values']['single_campaign'];
}

/**
 * Implements hook_content_type_render().
 */
function ding_campaign_single_campaign_content_type_render($subtype, $conf, $panel_args, $context) {
  $campaign = entity_load('node', array($conf['single_campaign']));
  $content = array(
    '#theme' => 'ding_campaign_wrapper',
    '#content' => array(
      0 => ding_campaign_prepare_display(reset($campaign), 'medium')
    ),
  );
  $block = new stdClass();
  $block->content = $content;

  return $block;
}

