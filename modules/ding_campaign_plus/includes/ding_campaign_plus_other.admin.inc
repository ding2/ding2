<?php
/**
 * @file
 * Contains the form functions used to build the "Other triggers" tabs.
 */

/**
 * Builds the from rule selection elements.
 *
 * This are the rules known from the ding campaign module.
 */
function _ding_campaign_plus_other_triggers_form($form, &$form_state) {
  $values = isset($form_state['values']['tabs']['other']['rules']) ? $form_state['values']['tabs']['other']['rules'] : array();
  $count = !empty($values['count']) ? $values['count'] : 0;

  // Check if remove button has been pressed. If so remove element from
  // form_state values.
  if (isset($form_state['triggering_element'])) {
    if ($form_state['triggering_element']['#op'] === 'remove') {
      $rule = 'rule_' . $form_state['triggering_element']['#rule'];
      unset($values[$rule]);
      unset($form_state['values']['tabs']['other']['rules'][$rule]);
    }
  }

  $triggers = array(
    '#title' => '',
    '#prefix' => '<div id="ding-campaign-triggers">',
    '#suffix' => '</div>',
    '#description' => '',
  );

  // If this form is "add another" or "remove" build rules already form_state
  // values.
  foreach ($values as $key => $value) {
    if (substr($key, 0, 4) === "rule") {
      $triggers[$key] = _ding_campaign_plus_rule_form(substr($key, 5), NULL, 'page');
    }
  }

  // If not a remove operation add one more element.
  if (!isset($form_state['triggering_element']) || $form_state['triggering_element']['#op'] !== 'remove') {
    $triggers['rule_' . $count] = _ding_campaign_plus_rule_form($count, NULL, 'page');
  }
  $count++;

  $triggers['count'] = array(
    '#type' => 'hidden',
    '#value' => $count,
  );

  $triggers['add_rule'] = array(
    '#type' => 'button',
    '#value' => t('Add another'),
    '#ajax' => array(
      'callback' => '_ding_campaign_plus_rule_ajax_callback',
      'wrapper' => 'ding-campaign-triggers',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  return $triggers;
}

/**
 * Return the other rules part of the form.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 *
 * @return array
 *   Form element - rule fields.
 */
function _ding_campaign_plus_rule_ajax_callback(array $form, array $form_state) {
  return $form['triggers']['tabs']['other']['rules'];
}

/**
 * Rule form fields chunk.
 *
 * @param int $number
 *   The rule number (used for UI numbering).
 * @param string $rule
 *   Current rule machine name.
 * @param string $type
 *   Current type.
 *
 * @return array
 *   Rule fields structure.
 */
function _ding_campaign_plus_rule_form($number = 0, $rule = NULL, $type = NULL) {
  $form = array(
    '#type' => 'fieldset',
    '#title' => t('Rule %num',array('%num' => $number)),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $form['rule_type'] = array(
    '#type' => 'select',
    '#title' => t('Rule type'),
    '#default_value' => ($type) ? $type : 'rule_page',
    '#options' => array(
      'page' => 'Page',
      'event' => 'Event',
      'news' => 'News',
      'path' => 'Path',
      'taxonomy' => 'Taxonomy term',
      'og_group' => 'Library or group',
    ),
  );

  $form['rule_value'] = array(
    '#type' => 'textfield',
    '#title' => t('Rule value'),
    '#default_value' => ($rule) ? $rule : '',
    '#size' => 64,
    '#maxlength' => 255,
    '#autocomplete_path' => 'ding_campaign_plus/autocomplete/' . $type,
  );

  $form['remove_rule_' . $number] = array(
    '#type' => 'button',
    '#value' => t('Remove'),
    '#name' => 'remove_rule_' . $number,
    '#op' => 'remove',
    '#rule' => $number,
    '#ajax' => array(
      'callback' => '_ding_campaign_plus_rule_ajax_callback',
      'wrapper' => 'ding-campaign-triggers',
      'method' => 'replace',
      'effect' => 'fade'
    ),
  );

  return $form;
}

/**
 * @param $form
 * @param $form_state
 */
function _ding_campaign_plus_other_triggers_form_submit($form, &$form_state) {

}