<?php

/**
 * @file
 * View all lists.
 */

use DingList\DingList;

/**
 * The default lists per page.
 */
define('DING_LIST_PUBLIC_LISTS_PER_PAGE', 10);

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
    $total = count($lists);

    $elements_per_page = !empty($conf['elements_per_page']) ? $conf['elements_per_page'] : DING_LIST_PUBLIC_LISTS_PER_PAGE;
    $current_page = pager_default_initialize($total, $elements_per_page);

    foreach (array_slice($lists, $current_page * $elements_per_page, $elements_per_page) as $list) {
      $list = DingList::fromDataArray($list);

      if (ding_list_user_has_access($list)) {
        $block->content[$list->getId()] = array(
          '#theme' => 'ding_list_list',
          '#list' => $list,
          '#display' => 'public list',
        );
      }
    }

    $block->content['pager'] = array(
      '#theme' => 'pager',
    );
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
  $form['elements_per_page'] = array(
    '#type' => 'textfield',
    '#title' => t('Elements per page'),
    '#default_value' => isset($form_state['conf']['elements_per_page']) ? $form_state['conf']['elements_per_page'] : DING_LIST_PUBLIC_LISTS_PER_PAGE,
  );
  return $form;
}

/**
 * Edit form submit.
 */
function ding_list_public_lists_content_type_edit_form_submit($form, &$form_state) {
  $form_state['conf']['elements_per_page'] = $form_state['values']['elements_per_page'];
}
