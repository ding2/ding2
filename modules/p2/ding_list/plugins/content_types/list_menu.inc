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

  $block = new stdClass();
  $block->content = array();

  if (user_is_logged_in()) {
    $block->content['links'] = array(
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
      $block->content['links']['#links']['view'] = array(
        'href' => 'list/' . $list->getId(),
        'title' => t('View list'),
        'attributes' => array('class' => array('menu-item')),
        'html' => FALSE,
      );

      if (ding_list_user_has_access($list, 'edit', $user)) {
        $block->content['links']['#links']['edit'] = array(
          'href' => 'list/' . $list->getId() . '/edit',
          'title' => t('Edit list title and note'),
          'attributes' => array('class' => array('menu-item')),
          'html' => FALSE,
        );
      }
    }
  }

  return $block;
}
