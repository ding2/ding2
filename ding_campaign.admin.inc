<?php
/**
 * @file
 * Contains admin backend related code.
 */

/**
 * Module main settings lay here.
 *
 * @param $form
 *   Form
 * @param $form_state
 *   Form state
 * @return
 *   Form structure array
 */
function ding_campaign_configure($form, $form_state) {

  $types = node_type_get_names();

  // Some key renaming routine, required in further module checks
  foreach ($types as $k => $v) {
    $types[$k . '_node_form'] = $v;
    unset($types[$k]);
  }

  $form['ding_campaign_node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('CAMPAIGN SELECTION NODE TYPES') . ':',
    '#default_value' => variable_get('ding_campaign_node_types', array()),
    '#options' => $types,
    '#description' => t('Select node types which shall have campaign selector present in their editing form.'),
  );

  // Prevent campaigns to be assigned to campaigns
  unset($form['ding_campaign_node_types']['#options']['campaign_node_form']);

  return system_settings_form($form);
}
