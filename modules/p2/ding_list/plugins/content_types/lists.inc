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
  drupal_add_css(drupal_get_path('module', 'ding_list') . '/css/ding-list-view.css');
  $account = $context->data;

  $block = new stdClass();
  $block->content = '';

  $groups = array(
    'userlists' => array(
      'title' => t('My library'),
      'lists' => array(
        DING_LIST_TYPE_SEARCHES => array(),
        DING_LIST_TYPE_LISTS => array(),
        DING_LIST_TYPE_FOLLOW_AUTHOR => array(),
        DING_LIST_TYPE_BOOKS_READ => array(),
        DING_LIST_TYPE_REMEMBER => array(),
        DING_ENTITY_RATING_LIST => array(),
        DING_LIST_TYPE_USER_LIST => array(),
      ),
      'sort' => 'ding_list_custom_sort_changed',
    ),
  );

  $lists = ding_list_get_lists(NULL, $account);
  if ($lists !== FALSE) {
    foreach ($lists as $list) {
      if (!ding_list_user_has_access($list, 'view')) {
        continue;
      }
      $list_type = ding_base_get_value('ding_type', $list, 'field_list_type');
      $list_label = check_plain(entity_label('ding_type', $list));

      foreach ($groups as $group_name => $group) {
        if (isset($group['lists'][$list_type])) {
          $uri = entity_uri('ding_type', $list);
          switch ($group_name) {
            case 'users':
              $groups[$group_name]['lists'][$list_type][] = array(
                'data' =>
                '<a href="' . url($uri['path']) . '" class="signature-label"><span class="icon"></span>' . $list_label . '</a>',
                'class' => array(drupal_html_class($list_type)),
                '#list' => $list,
              );
              break;

            case 'userlists':
              $notifications = ding_message_get_ding_list_notification($list);
              $notout = '';
              if (!empty($notifications)) {
                $text = '<span class="notification-label">' . t('New:', array(), array('context' => 'Ding list')) . '</span>' . $notifications;
                $notout =  l($text, 'list/' . $list->id, array('html' => TRUE, 'attributes' => array('class' => array('notification-link'))));
              }

              $groups[$group_name]['lists'][$list_type][] = array(
                'data' =>
                '<a href="' . url($uri['path']) . '" class="signature-label"><span class="icon"></span>' . $list_label . '</a>' . $notout,
                'class' => array(drupal_html_class($list_type)),
                '#list' => $list,
              );
              break;
          }
        }
      }
    }
  }

  // Remove groups with no list, and sort groups.
  foreach ($groups as $group_key => $group) {
    if (count($group['lists']) == 0) {
      unset($groups[$group_key]);
    }

    if (isset($group['sort']) && function_exists($group['sort'])) {
      uasort($groups[$group_key]['lists'], $group['sort']);
    }
  }

  reset($groups);

  $block->content = array(
    '#theme' => 'ding_list_lists',
    '#groups' => $groups,
    '#uid' => $account->uid,
  );
  return $block;
}

/**
 * A custom sorting function.
 */
function ding_list_custom_sort_changed($a, $b) {
  if ($a && $b) {
    if ($a[0]['#list']->changed == $b[0]['#list']->changed) {
      return 0;
    }
    return ($a[0]['#list']->changed > $b[0]['#list']->changed) ? -1 : 1;
  }
}
