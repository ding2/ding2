<?php

/**
 * @file
 *
 * BPI actions.
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
  $category = 'Indenrigspolitik';
  $audience = 'Voksne';
  $with_images = 1;
  $authorship = 1;
  $editable = 1;
  $with_refs = 1;

  $bpi_content = bpi_convert_to_bpi($node, $category, $audience, $with_images, $authorship, $editable, $with_refs);

  $bpi = bpi_client_instance();
//  $push_result = $bpi->push($bpi_content)->getProperties();
  $push_result = NULL;
  $wrapper = entity_metadata_wrapper('node', $node);
  if (!empty($push_result['id'])) {
    $wrapper->field_bpi_id->set($push_result['id']);
    return TRUE;
  }
  else {
    // Content wasn't pushed, so set workflow to 'Local content', before content
    // is saved.
    $workflows = workflow_get_workflow_names();
    $workflows_reversed = array_flip($workflows);
    $wid = $workflows_reversed['BPI'];
    $states = workflow_get_workflow_state_names($wid);
    $states_reversed = array_flip($states);
    $tid = $states_reversed['Local content'];
    $wrapper->field_bpi_workflow->set($tid);
    drupal_set_message(t('Error when pushing content to BPI'), 'error');
    watchdog('bpi', 'An error occurred when pushing content to BPI');
    return FALSE;
  }
}
