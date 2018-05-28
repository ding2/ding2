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
    $lists = ding_provider_invoke('openlist', 'call_module', 'ListPermission', 'getPublicLists');

    foreach ($lists as $list) {
      $list = DingList::fromDataArray($list);

      if (ding_list_user_has_access($list) && $list->allowed(DING_LIST_OPERATION_SHARE)) {
        $block->content[$list->getId()] = array(
          '#theme' => 'ding_list_list',
          '#list' => $list,
          '#display' => 'public list',
        );
      }
    }
  }
  catch (Exception $e) {
    watchdog_exception('ding_list', $e);
    drupal_set_message(t("An error occurred fetching the public lists. Please contact the administrator if this problem persists."), 'error');
  }

  return $block;
}

/**
 * Edit form.
 */
function ding_list_public_lists_content_type_edit_form($form, &$form_state) {
  return $form;
}
