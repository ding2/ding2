<?php

/**
 * @file
 * List menu pane.
 */

$plugin = array(
  'title' => t('Ding list menu'),
  'description' => t('Ding menu.'),
  'single' => TRUE,
  'content_types' => array('ding_type'),
  'category' => t('Dinglist'),
  'render callback' => 'ding_list_list_menu_content_type_render',
  'required context' => new ctools_context_optional(t('Ding list'), 'ding_list_list'),
);

/**
 * Implements hook_content_type_render().
 */
function ding_list_list_menu_content_type_render($subtype, $conf, $panel_args, $context) {
  global $user;

  $list = $context->data;

  $block = new stdClass();
  $block->content = array();

  if (user_is_logged_in()) {
    $block->content = array(
      '#theme' => 'links',
      '#links' => array(
        'to-lists' => array(
          'href' => 'user/' . $user->uid . '/my-library',
          'title' => t('To your lists'),
          'attributes' => array('class' => array('menu-item')),
          'html' => FALSE,
        ),
      ),
      '#attributes' => array('class' => 'sub-menu'),
    );

    if ($list) {
      $block->content['#links']['view'] = array(
        'href' => 'list/' . $list['list_id'],
        'title' => check_plain($list['title']),
        'attributes' => array('class' => array('menu-item')),
        'html' => FALSE,
      );

      if (ding_list_user_has_access($list, 'edit', $user)) {
        $block->content['#links']['edit'] = array(
          'href' => 'list/' . $list['list_id'] . '/edit',
          'title' => t('Rename / Delete list'),
          'attributes' => array('class' => array('menu-item')),
          'html' => FALSE,
        );
      }

      if (ding_list_allowed($list, DING_LIST_OPERATION_SHARE)) {
        $title = FALSE;

        if (ding_list_is_owner($list, $user)) {
          $title = t('Share list');
        }
        else {
          $lists_list = ding_list_get_list(DING_LIST_TYPE_LISTS);
          if (ding_list_has_element($lists_list, $list['list_id'])) {
            $title = t('Unfollow list');
          }
        }

        if ($title !== FALSE) {
          $block->content['#links']['share'] = array(
            'href' => 'list/' . $list['list_id'] . '/share',
            'title' => $title,
            'attributes' => array('class' => array('menu-item')),
            'html' => FALSE,
          );
        }
      }
    }
  }

  return $block;
}
