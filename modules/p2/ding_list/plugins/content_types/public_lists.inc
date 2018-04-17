<?php

/**
 * @file
 * View all lists.
 */

use DingList\DingList;

$plugin = array(
  'title' => t('Public lists'),
  'description' => t('Public lists'),
  'single' => TRUE,
  'category' => t('Dinglist'),
  'render callback' => 'ding_list_public_lists_content_type_render',
  'edit form' => 'ding_list_public_lists_content_type_edit_form',
);

/**
 * Implements hook_content_type_render().
 */
function ding_list_public_lists_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  $block->title = t('Public lists');
  $block->content = array();

  try {
    $lists = ding_provider_invoke('openlist', 'call_module', 'ListPermission', 'v2_getPublicLists');

    foreach ($lists as $list) {
      $list = new DingList($list);
      if (ding_list_user_has_access($list)) {
        $block->content[$list->id] = array(
          '#theme' => 'ding_list_list',
          '#list' => $list,
          '#display' => 'public list',
        );
      }
    }
  }
  catch (Exception $e) {
    watchdog_exception('ding_entity_rating', $e);
  }

  return $block;
}

/**
 * Edit form.
 */
function ding_list_public_lists_content_type_edit_form($form, &$form_state) {
  return $form;
}
