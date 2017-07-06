<?php
/**
 * @file
 * Access plugin for showing the opening hours on the frontpage.
 */

/**
 * Array describing the plugin to CTools/Panels.
 */
$plugin = array(
  'title' => t('Ding opening hours frontpage'),
  'description' => t('Show all ding opening hours on the frontpage.'),
  'callback' => 'ding_opening_hours_frontpage_ctools_access_check',
);

/**
 * Check for access.
 */
function ding_opening_hours_frontpage_ctools_access_check($conf, $context) {
  return variable_get('ding_ddbasic_opening_hours_on_frontpage', FALSE);
}
