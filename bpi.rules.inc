<?php

/**
 * @file
 *
 * BPI rule actions.
 */

include_once drupal_get_path('module', 'bpi') . '/bpi.push.inc';

/**
 * Implements hook_rules_event_info().
 */
function bpi_rules_action_info() {
  $info = array();

  $info['bpi_rules_push'] = array(
    'label' => t('Send content to BPI'),
    'parameter' => array(
      'entity' => array(
        'type' => 'node',
        'label' => t('Content to send to BPI'),
      ),
    ),
    'group' => t('BPI'),
  );

  return $info;
}

/**
 * Rules action execution callback that will push content to BPI.
 *
 * If content can't be pushed to BPI, the workflow state will be set to 'Local
 * content' before the node is saved.
 *
 * @param object $node
 *   Node object.
 *
 * @return bool
 *   TRUE on success.
 */
function bpi_rules_push($node) {
  $wrapper = entity_metadata_wrapper('node', $node);
  $field_name = 'field_bpi_workflow';
  $transition = workflow_transition_load_single('node', $node->nid, $field_name);

  // Get workflow transitions.
  $workflows = workflow_get_workflow_names();
  $workflows_reversed = array_flip($workflows);
  $wid = $workflows_reversed['BPI'];
  $states = workflow_get_workflow_state_names($wid);
  $states_reversed = array_flip($states);
  $push_sid = $states_reversed['Sent to BPI'];

  // Don't push to BPI, if old and new sids are the same.
  if (!is_null($transition) && $transition->sid == $push_sid) {
    return FALSE;
  }

  $bpi_values = bpi_get_bpi_nodes($node->nid);
  $bpi_values = $bpi_values[$node->nid];
  $data = unserialize($bpi_values->data);

  $category = $data['category'];
  $audience = $data['audience'];
  $with_images = $data['with_images'];
  $authorship = $data['authorship'];
  $editable = $data['editable'];
  $with_refs = $data['with_refs'];

  if (empty($category) || empty($audience)) {
    $wrapper->field_bpi_workflow->set($transition->old_sid);
    drupal_set_message(t('Category and audience must be set when pushing to BPI'), 'error');
    return FALSE;
  }

  $bpi_content = bpi_convert_to_bpi($node, $category, $audience, $with_images, $authorship, $editable, $with_refs);

  $bpi = bpi_client_instance();
//  $push_result = $bpi->push($bpi_content)->getProperties();
  $push_result = NULL;
  $push_result = array('id' => '123456987');
  if (!empty($push_result['id'])) {
    $data['bid'] = $push_result['id'];
    bpi_update_syndicated($node->nid, $push_result['id'], $data);
    return TRUE;
  }
  else {
    // Content wasn't pushed, so set workflow to 'Local content', before content
    // is saved.
    $local_sid = $states_reversed['Local content'];
    $wrapper->field_bpi_workflow->set($local_sid);
    drupal_set_message(t('Error when pushing content to BPI'), 'error');
    watchdog('bpi', 'An error occurred when pushing content to BPI');
    return FALSE;
  }
}
