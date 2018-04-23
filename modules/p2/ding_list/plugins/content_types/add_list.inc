<?php

/**
 * @file
 * Add list form pane.
 */

$plugin = array(
  'title' => t('Add list to list'),
  'description' => t('Add list to list.'),
  'single' => TRUE,
  'required context' => new ctools_context_required(t('Ding list'), 'ding_list_list'),
  'category' => t('Ding!'),
  'render callback' => 'ding_list_add_list_content_type_render',
);

/**
 * Implements hook_content_type_render().
 */
function ding_list_add_list_content_type_render($subtype, $conf, $panel_args, $context) {
  $list = $context->data;

  $block = new stdClass();
  $block->content = array();

  // Users can only add lists they don't own.
  if (!$list->isOwner() && user_access('use personalisation')) {
    $follow_list = ding_list_get_list(DING_LIST_TYPE_LISTS);
    if ($element = $follow_list->hasElement($list->getId())) {
      // If we have more than 1 remove form on a page Drupal will use the first
      // occoring remove form everytime, unless they all got a unique ID, which
      // is why the element ID is appended.
      // See the ding_list_forms() hook in ding_list/include/form.inc.
      $block->content = drupal_get_form('ding_list_remove_element_form__' . $element->getId(), $element, t('Unfollow list'));
    }
    else {
      $block->content = drupal_get_form('ding_list_add_element_form', 'ding_list', $list->getId(), t('Add to lists I follow'));
    }
  }

  return $block;
}
