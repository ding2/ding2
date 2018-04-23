<?php

/**
 * @file
 * View all lists.
 */

$plugin = array(
  'title' => t('Lists'),
  'description' => t('Lists.'),
  'single' => TRUE,
  'content_types' => array('user'),
  'required context' => new ctools_context_required(t('User'), 'user'),
  'category' => t('Dinglist'),
  'render callback' => 'ding_list_lists_content_type_render',
);

/**
 * Implements hook_content_type_render().
 */
function ding_list_lists_content_type_render($subtype, $conf, $panel_args, $context) {
  $account = $context->data;
  $lists = ding_list_get_lists(array(), $account, TRUE);

  $block = new stdClass();
  $block->content = array(
    'lists' => array(
      '#theme' => 'item_list',
      '#title' => t('My library'),
      '#items' => array(),
      '#type' => 'ul',
      '#attributes' => array('class' => array('list-links', 'userlists')),
    ),
    'actions' => array(
      '#theme' => 'item_list',
      '#items' => array(),
      '#type' => 'ul',
      '#attributes' => array('class' => array('bottom-links')),
    ),
  );

  foreach ($lists as $list) {
    $notifications = ding_message_get_ding_list_notification($list);

    $notification_out = '';
    if (!empty($notifications)) {
      $text = '<span class="notification-label">' . t('New:', array(), array('context' => 'Ding list')) . '</span>' . $notifications;
      $notification_out = l($text, 'list/' . $list->getId(), array('html' => TRUE, 'attributes' => array('class' => array('notification-link'))));
    }

    $block->content['lists']['#items'][] = array(
      'data' =>
      l('<span class="icon"></span>' . $list->getTitle(), 'list/' . $list->getId(), array(
        'html' => TRUE,
        'attributes' => array('class' => 'signature-label'),
      )) . $notification_out,
    );
  }

  if (ding_message_get_message_count()) {
    $block->content['actions']['#items'][] = l(t("Mark all notifications as read"), "ding_message/clear_user_messages", array('attributes' => array('class' => array('button'))));
  }

  $block->content['actions']['#items'][] = l(t("Create new list"), "list/create", array('attributes' => array('class' => array('button'))));
  $block->content['actions']['#items'][] = l(t('View all public lists'), 'public-lists', array('attributes' => array('class' => array('button'))));

  return $block;
}
