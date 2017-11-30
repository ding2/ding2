<?php
/**
 * @file
 * Hooks provided by Ding Campaign plus.
 */

/**
 * @addtogroup hooks
 * @{
 */


/**
 * Tells campaign plus that the modules provides campaign triggers.
 *
 * @return array
 *   The array contains node edit form elements, the title for the tab and
 *   the type that identifies this group of campaign triggers.
 */
function hook__ding_campaign_plus_info() {
  return array(
    'title' => t('Test'),
    'type' => 'test',
    'form' => 'ding_campaign_plus_test_admin_form',
    'auto' => 'ding_campaign_plus_test_auto_admin_form',
  );
}

/**
 * Used to find the campaigns that is trigger by current context.
 *
 * @param $contexts
 *   Panel pane contexts for the current page.
 * @param $style
 *   The style set in the pane - ribbon or box.
 *
 * @return array
 *   The camping node id's keyed by type (here the weight type).
 */
function hook_ding_campaign_plus_matches($contexts, $style) {
  $matches = array();

  foreach ($contexts as $key => $context) {
    switch ($key) {
      case 'path':
        $matches['path'] = _ding_campaign_plus_basic_match('path', $context->path);
        break;
    }
  }

  return $matches;
}

/**
 * Defines default weight for the trigger that the module provides.
 */
function hook_ding_campaign_plus_default_weights() {
  return array(
    'search' => array(
      'prefix' => t('Search'),
      'title' => t('CQL statement'),
      'weight' => 10,
    )
  );
}

/**
 * Defines the rules for a given trigger for auto generated campaigns.
 *
 * @param $config
 *   The auto generate administration configuration.
 * @param $campaign_node
 *   The campaign node that the rules should be generated for.
 * @param $values
 *   The values from the node edit form submit for the content that the auto
 *   generated campaign is build.
 *
 * @return array
 *   Matching the modules rules format for the module.
 */
function hook_ding_campaign_plus_auto_trigger($config, $campaign_node, $values) {
  return array('TYPE' => array('rules' => array()));
}

/**
 * @} End of "addtogroup hooks".
 */
