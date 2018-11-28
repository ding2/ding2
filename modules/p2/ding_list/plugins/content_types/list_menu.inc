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

      if ($list->allowed(DING_LIST_OPERATION_SHARE)) {
        $title = FALSE;

        // Check if user owns the list.
        if ($list->isOwner($user)) {
          $title = t('Share list');
        }
        else {
          // Check if user already follows list.
          $user_follow_list = ding_list_get_list(DING_LIST_TYPE_LISTS);
          if ($user_follow_list->hasElement($list->getId())) {
            $title = t('Unfollow list');
          }
        }

        if ($title !== FALSE) {
          $block->content['links']['#links']['share'] = array(
            'href' => 'list/' . $list->getId() . '/share',
            'title' => $title,
            'attributes' => array('class' => array('menu-item')),
            'html' => FALSE,
          );
        }
        else {
          $block->content['addform'] = drupal_get_form('ding_list_add_element_form', 'ding_list', $list->getId(), t('Add to lists I follow'));
        }

        if (user_access('ding_list administer public lists')) {
          $block->content['links']['#links']['toggle_not_public'] = array(
            'href' => 'list/' . $list->getId() . '/toggle-not-public',
            'title' => $list->getData('not_public', FALSE) ? t('Enable public sharing') : t('Disable public sharing'),
            'attributes' => array('class' => array('menu-item')),
            'html' => FALSE,
          );
        }
      }
    }
  }

  return $block;
}
