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
  'required context' => new ctools_context_required(t('Dinglist'), 'ding_type'),
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

    $uri = entity_uri('ding_type', $list);

    $block->content = array(
      '#theme' => 'links',
      '#links' => array(
        'to-lists' => array(
          'href' => 'user/' . $user->uid . '/my-library',
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
      $block->content['#links']['edit'] = array(
        'href' => $uri['path'] . '/edit',
        'title' => t('Edit list title and note'),
        'attributes' => array('class' => array('menu-item')),
        'html' => TRUE,
      );
    }

    if (ding_list_allowed($list, DING_LIST_OPERATION_SHARE)) {
      if (ding_list_user_has_access($list, 'owner', $user)) {
        $title = t('Share list');
      }
      else {
        $title = t('Unfollow list');
      }

      $block->content['#links']['share'] = array(
        'href' => $uri['path'] . '/share',
        'title' => $title,
        'attributes' => array('class' => array('menu-item')),
        'html' => TRUE,
      );
    }
  }

  return $block;
}
