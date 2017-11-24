<?php

/**
 * @file
 * Information about list followers pane.
 */

$plugin = array(
  'title' => t('Ding list data'),
  'description' => t('Ding list.'),
  'single' => TRUE,
  'content_types' => array('ding_type'),
  'category' => t('Dinglist'),
  'render callback' => 'ding_list_list_data_content_type_render',
  'required context' => new ctools_context_required(t('Dinglist'), 'ding_type'),
);

/**
 * Implements hook_content_type_render().
 */
function ding_list_list_data_content_type_render($subtype, $conf, $panel_args, $context) {
  global $user;

  $list = $context->data;
  $list_user = user_load($list->uid);
  $list_status = $list->field_ding_list_status['und'][0]['value'];
  $block = new stdClass();

  $block->content['info'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'ding-list-data',
      ),
    ),
  );
  
  if ($user->uid != $list->uid) {
    $block->content['info']['user'] = array(
      '#theme' => 'ding_list_label_value',
      '#label' => t('Created by'),
      '#value' => $list_user->data['display_name'],
    );
  }

  if (ding_list_allowed($list, DING_LIST_OPERATION_SHARE) && $list_status != 'private') {
    $block->content['info'][] = array(
      '#theme' => 'ding_list_followers', 
      '#list' => $list,
    );
  }

  return $block;
}
