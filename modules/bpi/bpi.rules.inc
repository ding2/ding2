<?php

/**
 * @file
 *
 * BPI rule actions.
 */

include_once drupal_get_path('module', 'bpi') . '/bpi.push.inc';
include_once drupal_get_path('module', 'bpi') . '/bpi.delete.inc';

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
  $info['bpi_rules_delete'] = array(
    'label' => t('Delete content from BPI'),
    'parameter' => array(
      'entity' => array(
        'type' => 'node',
        'label' => t('Delete content from BPI'),
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
  if (!user_access('bpi push content')) {
    drupal_set_message(t('You are not allowed to push content to BPI'), 'error');
    return FALSE;
  }

  // Don't push to BPI if new sid (workflow state id) is the same as old sid.
  if ($node->workflow_transitions['field_bpi_workflow']->old_sid == $node->workflow_transitions['field_bpi_workflow']->new_sid) {
    return;
  }

  $wrapper = entity_metadata_wrapper('node', $node);
  $field_name = 'field_bpi_workflow';

  // Get BPI values for this node.
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
    // If category or audience isn't set, we set the state back to the old state.
    $old_sid = $node->workflow_transitions[$field_name]->getOldState();
    $old_sid = $old_sid->sid;
    $node->workflow_transitions[$field_name]->delete();
    $wrapper->field_bpi_workflow->set($old_sid);
    $wrapper->save();
    drupal_set_message(t('Category and audience must be set when pushing to BPI'), 'error');
    return FALSE;
  }

  $bpi_content = bpi_convert_to_bpi($node, $category, $audience, $with_images, $authorship, $editable, $with_refs);

  $bpi = bpi_client_instance();
  $push_result = $bpi->push($bpi_content)->getProperties();
  if (!empty($push_result['id'])) {
    $data['bid'] = $push_result['id'];
    bpi_update_syndicated($node->nid, $push_result['id'], $data);
    drupal_set_message(t('Node %title was successfully pushed to BPI well.', array('%title' => $node->title)));
    return TRUE;
  }
  else {
    // Content wasn't pushed, so delete transition and set workflow to old state.
    $old_sid = $node->workflow_transitions[$field_name]->getOldState();
    $old_sid = $old_sid->sid;
    $node->workflow_transitions[$field_name]->delete();
    $wrapper->field_bpi_workflow->set($old_sid);
    $wrapper->save();
    drupal_set_message(t('Error when pushing content to BPI. Workflow set to old state.'), 'error');
    watchdog('bpi', 'An error occurred when pushing content to BPI');
    return FALSE;
  }
}

/**
 * Rules action execution callback for deleting content from BPI.
 *
 * @param object $node
 *   Node object.
 *
 * @return bool
 *   TRUE on success
 */
function bpi_rules_delete($node) {
  $node = node_load($node->nid);
  if (!user_access('delete bpi content')) {
    drupal_set_message(t('You are not allowed to delete content from BPI'), 'error');
    return FALSE;
  }

  bpi_well_delete($node->bpi_id);
}
