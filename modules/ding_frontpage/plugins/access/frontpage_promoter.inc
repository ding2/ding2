<?php
/**
 * @file
 * Plugin to provide access control based upon the selected front page
 * element(s). The Search Carousel or the tab-roll
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Ding frontpage promoter'),
  'description' => t('Ding front page promoted'),
  'callback' => 'ding_frontpage_promoter_ctools_access_check',
  'default' => array(
    'promoter' => 'ting_search_carousel',
  ),
  'settings form' => 'ding_frontpage_promoter_ctools_access_settings',
  'summary' => 'ding_frontpage_promoter_ctools_access_summary',
);

/**
 * Check for access.
 */
function ding_frontpage_promoter_ctools_access_check($conf, $context) {
  return $conf['promoter'] == variable_get('ding_frontpage_promoter', 'ting_search_carousel');
}

/**
 * Settings form for the 'library count' access plugin.
 */
function ding_frontpage_promoter_ctools_access_settings($form, &$form_state, $conf) {
  $form['settings']['promoter'] = array(
    '#type' => 'radios',
    '#title' => t('Promoter'),
    '#description' => t('Select the promoter this access rule is attached to.'),
    '#options' => ding_frontpage_promoters(),
    '#default_value' => $conf['promoter'],
  );

  return $form;
}

/**
 * Provide a summary description based upon the configuration.
 */
function ding_frontpage_promoter_ctools_access_summary($conf, $context) {
  return t('Limit access to !promoter', array('!promoter' => $conf['promoter']));
}

