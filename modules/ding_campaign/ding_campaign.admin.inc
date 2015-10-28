<?php
/**
 * @file
 * Contains admin backend related code.
 */

/**
 * Module main settings lay here.
 */
function ding_campaign_admin_settings($form, $form_state) {
  $types = node_type_get_names();

  // Some key renaming routine, required in further module checks.
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

  // Prevent campaigns to be assigned to campaigns.
  unset($form['ding_campaign_node_types']['#options']['ding_campaign_node_form']);

  return system_settings_form($form);
}

/**
 * Get rules edit form.
 *
 * @param $node
 *   Campaign node object whose rules are edited.
 *
 * @return
 *   Campaign rules edit form.
 */
function ding_campaign_rules_admin($node) {
  drupal_add_js(array('ding_campaing_init' => array(
    'autocompleteUrl' => url('ding_campaign/autocomplete/'),
  )), 'setting');
  return drupal_get_form('ding_campaign_edit_rules_form', $node);
}

/**
 * Campaign rules edit form.
 *
 * @param $form
 *   Rules form.
 * @param $form_state
 *   Form state.
 * @param $node
 *   Campaign node object whose rules are edited.
 *
 * @return
 *   Campaign rules edit form.
 */
function ding_campaign_edit_rules_form($form, &$form_state, $node = NULL) {
  $num_rules = !empty($form_state['values']['howmany_select']) ? $form_state['values']['howmany_select'] : 0;

  $form['ding_campaign_rules'] = array(
    '#title' => '',
    '#prefix' => '<div id="ding-campaign-rules">',
    '#suffix' => '</div>',
    '#description' => '',
  );

  $i = 0;
  $c = 1;
  if (isset($node->camp_rule) && is_array($node->camp_rule)) {
    $c = count($node->camp_rule);
    for ($i = 0; $i < $c; $i++) {
      $form['ding_campaign_rules']['rules']['rule_' . $i] = ding_campaign_rule_form(
              isset($node->camp_rule[$i]) ? $node->camp_rule[$i] : NULL,
              isset($node->camp_type[$i]) ? $node->camp_type[$i] : 'rule_page');
    }
  }

  for (; $i < $num_rules + $c; $i++) {
    $form['ding_campaign_rules']['rules']['rule_' . $i] = ding_campaign_rule_form(NULL, 'rule_page');
  }

  $form['ding_campaign_rules']['howmany_select'] = array(
    '#type' => 'hidden',
    '#value' => $num_rules += 1,
  );

  $form['ding_campaign_rules']['rule_add'] = array(
    '#type' => 'button',
    '#value' => t('Add another rule'),
    '#ajax' => array(
      'callback' => 'ding_campaign_add_rule',
      'wrapper' => 'edit-rule-add',
      'method' => 'before',
      'effect' => 'fade',
    ),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save rules'),
  );

  $form['#submit'] = array('ding_campaign_campaign_rule_form_submit');

  drupal_add_js(
    drupal_get_path('module', 'ding_campaign') . '/js/ding_campaign_scripts.js',
    array('weight' => 10)
  );

  return $form;
}

/**
 * Appends rule form via AJAX.
 *
 * @param $form
 *   Form.
 * @param $form_state
 *   Form state.
 *
 * @return
 *   Form element - rule fields.
 */
function ding_campaign_add_rule($form, $form_state) {
  $c = count(element_children($form['ding_campaign_rules']['rules']));
  return $form['ding_campaign_rules']['rules']['rule_' . ($c - 1)];
}

/**
 * Implements hook_form_id_submit().
 */
function ding_campaign_campaign_rule_form_submit($form, &$form_state) {
  $c = count($form_state['input']['rule_type']);

  if ($c > 0) {
    // Delete existing rules.
    db_delete('ding_campaign_rules')
      ->condition('cid', $form_state['build_info']['args'][0]->nid)
      ->execute();

    // Add new rules.
    for ($i = 0; $i < $c; $i++) {
      if ($form_state['input']['rule_value'][$i] != '' || $form_state['input']['rule_type'][$i] == 'rule_generic') {

        $nid = NULL;
        if (in_array($form_state['input']['rule_type'][$i], array('rule_page', 'rule_news', 'rule_event', 'rule_taxonomy', 'rule_library'))) {
          preg_match('/\d{1,9}/', $form_state['input']['rule_value'][$i], $matches);
          if (!empty($matches[0])) {
            $nid = $matches[0];
          }
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
 *
 * @return
 *   Rule fields structure.
 */
function ding_campaign_rule_form($rule = NULL, $type = NULL) {
  $form = array();

  $form['rule_type[]'] = array(
    '#type' => 'select',
    '#title' => t('Rule type'),
    '#default_value' => ($type) ? $type : 'rule_page',
    '#options' => array(
      'rule_page' => 'Page',
      'rule_event' => 'Event',
      'rule_news' => 'News',
      'rule_path' => 'Path',
      'rule_term' => 'Search term',
      'rule_taxonomy' => 'Taxonomy term',
      'rule_generic' => 'Generic',
      'rule_library' => 'Library',
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
    '#autocomplete_path' => 'ding_campaign/autocomplete/' . $type,
  );

  return $form;
}

/**
 * Autocomplete handler.
 *
 * @param $type
 *   Type.
 * @param $input
 *   Input.
 */
function ding_campaign_admin_autocomplete($type, $input) {
  $matches = array();

  switch ($type) {
    case 'rule_page':
      $q = db_query_range("SELECT nid, title FROM {node} WHERE title LIKE(:term)", 0, 5, array(':term' => '%%' . $input . '%%'))->fetchAll();

      foreach ($q as $k => $v) {
        $matches['[nid:' . $v->nid . ']'] = $v->title;
      }
      break;

    case 'rule_taxonomy':
      $q = db_query_range("SELECT tid, name FROM {taxonomy_term_data} WHERE name LIKE(:term)", 0, 5, array(':term' => '%%' . $input . '%%'))->fetchAll();

      foreach ($q as $k => $v) {
        $matches['[tid:' . $v->tid . ']'] = $v->name;
      }
      break;

    case 'rule_library':
      $q = db_query_range("SELECT nid, title FROM {node} WHERE type='ding_library' AND title LIKE(:term)", 0, 5, array(':term' => '%%' . $input . '%%'))->fetchAll();

      foreach ($q as $k => $v) {
        $matches['[nid:' . $v->nid . ']'] = $v->title;
      }
      break;

    case 'rule_event':
      $q = db_query_range("SELECT nid, title FROM {node} WHERE type='ding_event' AND title LIKE(:term)", 0, 5, array(':term' => '%%' . $input . '%%'))->fetchAll();

      foreach ($q as $k => $v) {
        $matches['[nid:' . $v->nid . ']'] = $v->title;
      }
      break;

    case 'rule_news':
      $q = db_query_range("SELECT nid, title FROM {node} WHERE type='ding_news' AND title LIKE(:term)", 0, 5, array(':term' => '%%' . $input . '%%'))->fetchAll();

      foreach ($q as $k => $v) {
        $matches['[nid:' . $v->nid . ']'] = $v->title;
      }
      break;
  }

  drupal_json_output($matches);
}
