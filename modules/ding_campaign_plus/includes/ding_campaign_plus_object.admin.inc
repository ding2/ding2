<?php
/**
 * @file
 * Contains the form functions used to build the "Object triggers" tabs.
 */

/**
 * Builds the object rule selection form.
 */
function _ding_campaign_plus_object_triggers_form($form, &$form_state) {
  $triggers = array();

  $default = array();
  if (isset($form_state['node']->ding_campaign_plus)) {
    $default = _ding_campaign_plus_filter_rules($form_state['node']->nid, 'object', $form_state['node']->ding_campaign_plus);
  }

  $triggers['query'] = array(
    '#type' => 'textfield',
    '#title' => t('Search query'),
    '#description' => t('Search query that should trigger the campaign'),
    '#default_value' => isset($default['query']) ? $default['query'] : '',
    '#maxlength' => 2048
  );

  return $triggers;
}
