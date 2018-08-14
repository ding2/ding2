<?php

/**
 * @file
 * List menu pane.
 */

$plugin = array(
  'title' => t('Ding list menu'),
  'description' => t('Ding menu.'),
  'single' => TRUE,
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
  $user_follow_list = ding_list_get_list(DING_LIST_TYPE_LISTS);

  $block = new stdClass();
  $block->content = array();

  if (user_is_logged_in()) {
    $uri = entity_uri('ding_type', $list);

    $block->content['links'] = array(
      '#theme' => 'links',
      '#links' => array(
        'to-lists' => array(
          'href' => 'user/' . $user->uid . '/dinglists',
          'title' => t('To your lists'),
          'attributes' => array('class' => array('menu-item')),
          'html' => TRUE,
        ),
        'view' => array(
          'href' => $uri['path'],
          'title' => t('View list'),
          'attributes' => array('class' => array('menu-item')),
          'html' => TRUE,
        ),
      ),
      '#attributes' => array('class' => 'sub-menu'),
    );

    if (ding_list_user_has_access($list, 'edit', $user)) {
      $block->content['links']['#links']['edit'] = array(
        'href' => $uri['path'] . '/edit',
        'title' => t('Edit list title and note'),
        'attributes' => array('class' => array('menu-item')),
        'html' => TRUE,
      );
    }

    if (ding_list_allowed($list, DING_LIST_OPERATION_SHARE)) {
      // Check if user owns the list.
      if (ding_list_user_has_access($list, 'owner', $user)) {
        $title = t('Share list');
      }
      else {
        // Check if user already follows list.
        if (ding_list_has_ding_list_element($user_follow_list, 'ding_list', $list->id)) {
          $title = t('Unfollow list');
        }
        else {
          $title = '';
        }
      }
      if ($title) {
        $block->content['links']['#links']['share'] = array(
          'href' => $uri['path'] . '/share',
          'title' => $title,
          'attributes' => array('class' => array('menu-item')),
          'html' => TRUE,
        );
      }
      else {
        $block->content['addform'] = drupal_get_form('ding_list_add_element_form', 'ding_list', $list->id, t('Add to lists I follow'));
      }
    }
  }

  return $block;
}
