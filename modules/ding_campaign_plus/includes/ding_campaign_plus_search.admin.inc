<?php
/**
 * @file
 * Contains the form functions used to build the "Other triggers" tabs.
 */

/**
 * Builds the search rule selection form.
 */
function _ding_campaign_plus_search_triggers_form($form, &$form_state) {
  $triggers = array();

  $triggers['limit'] = array(
    '#type' => 'textfield',
    '#title' => t('Percent of the results'),
    '#size' => 4,
    '#description' => t('The percent of the results in the search result'),
    '#default_value' => '30',
  );

  $triggers['query'] = array(
    '#type' => 'textfield',
    '#title' => t('Search query'),
    '#description' => t('Search query that should trigger the campaign'),
    '#default_value' => '',
    '#maxlength' => 2048
  );

  return $triggers;
}
