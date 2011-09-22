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

/**
 * Get rules edit form.
 *
 * @param $node
 *   Campaign node object whose rules are edited
 * @return
 *   Campaign rules edit form
 */
function ding_campaign_rules_admin($node) {
  return drupal_get_form('ding_campaign_edit_rules_form', $node);
}

/**
 * Campaign rules edit form.
 *
 * @param $form
 *   Rules form
 * @param $form_state
 *   Form state
 * @param $node
 *   Campaign node object whose rules are edited
 * @return
 *   Campaign rules edit form
 */
function ding_campaign_edit_rules_form($form, &$form_state, $node = NULL) {
  $form = array();

  $form['ding_campaign_rules'] = array(
    '#type' => 'fieldset',
    '#title' => t('Campaign rules'),
    '#description' => t('Assign display rules to this campaign.'),
    '#collapsible' => FALSE,
    '#collapsed' => TRUE,
    '#prefix' => '<div id="ding-campaign-rules">',
    '#suffix' => '</div>',
  );

  // Display already created rules
  if (isset($node->camp_rule)) {
    for ($i = 0; $i < count($node->camp_rule); $i++) {
      $form['ding_campaign_rules']['rules'][] = ding_campaign_rule_form(
        isset($node->camp_rule[$i]) ? $node->camp_rule[$i] : NULL,
        isset($node->camp_type[$i]) ? $node->camp_type[$i] : NULL
      );
    }
  }
  else {
    $form['ding_campaign_rules']['rules'][] = ding_campaign_rule_form();
  }
  
  
  $form['ding_campaign_rules']['add_rule'] = array(
    '#type' => 'button',
    '#value' => 'Add another rule',
    '#attributes' => array('class' => array('ding-campaign-button-add')),
    '#ajax' => array(
      'callback' => 'ding_campaign_add_rule',
      'wrapper' => 'edit-add-rule',
      'method' => 'before',
      'effect' => 'slide',
    )
  );

  $form['ding_campaign_rules_save'] = array(
    '#type' => 'submit',
    '#value' => 'Save rules',
  );

  $form['#submit'] = array('ding_campaign_campaign_rule_form_submit');

  return $form;
}

/**
 * Appends rule form via AJAX.
 *
 * @param $form
 *   Form
 * @param $form_state
 *   Form state
 * @return
 *   Form element - rule fields
 */
function ding_campaign_add_rule($form, $form_state) {
  return $form['ding_campaign_rules']['rules'][0];
}

/**
 * Implements hook_FORM_ID_submit().
 */
function ding_campaign_campaign_rule_form_submit($form, &$form_state) {
  $c = count($form_state['input']['rule_type']);

  if ($c > 0) {
    // Delete existing rules
    db_delete('ding_campaign_rules')
      ->condition('cid', $form_state['build_info']['args'][0]->nid)
      ->execute();

    // Add new rules
    for ($i = 0; $i < $c; $i++) {
      if ($form_state['input']['rule_value'][$i] != '' || $form_state['input']['rule_type'][$i] == 'rule_generic') {

        $nid = NULL;
        if ($form_state['input']['rule_type'][$i] == 'rule_page') {
          $nid = array();
          preg_match('/\d{1,9}/', $form_state['input']['rule_value'][$i], $nid);
        }

        $dt = array(
          'nid' => $nid,
          'cid' => $form_state['build_info']['args'][0]->nid,
          'rule' => ($form_state['input']['rule_type'][$i] == 'rule_generic') ? '' : $form_state['input']['rule_value'][$i],
          'type' => $form_state['input']['rule_type'][$i],
        );

        db_insert('ding_campaign_rules')
          ->fields($dt)
          ->execute();
      }
    }
  }
}

/**
 * Rule form fields chunk.
 *
 * @param $rule
 *   Current rule.
 * @param $type
 *   Current type.
 * @return
 *   Rule fields structure.
 */
function ding_campaign_rule_form($rule = NULL, $type = NULL) {
  $form['rule_type[]'] = array(
    '#type' => 'select',
    '#title' => t('Rule type'),
    '#default_value' => ($type) ? $type : 'rule_page',
    '#options' => array(
      'rule_page' => 'Page',
      'rule_path' => 'Path',
      'rule_term' => 'Search term',
      'rule_generic' => 'Generic',
    ),
    '#prefix' => '<div class="ding-campaign-rule"><div class="rule-type">',
    '#suffix' => '</div>',
  );

  $form['rule_value[]'] = array(
    '#type' => 'textfield',
    '#title' => t('Rule value'),
    '#default_value' => ($rule) ? $rule : '',
    '#size' => 24,
    '#maxlength' => 24,
    '#prefix' => '<div class="rule-value">',
    '#suffix' => '</div><div class="clear"></div></div>',
  );

  return $form;
}
