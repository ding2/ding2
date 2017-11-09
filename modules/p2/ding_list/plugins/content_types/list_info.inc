<?php

/**
 * @file
 * Information about list info pane.
 */

$plugin = array(
  'title' => t('Ding list info'),
  'description' => t('Ding list.'),
  'single' => TRUE,
  'content_types' => array('ding_type'),
  'category' => t('Dinglist'),
  'render callback' => 'ding_list_list_info_content_type_render',
  'required context' => new ctools_context_required(t('Dinglist'), 'ding_type'),
);

/**
 * Implements hook_content_type_render().
 */
function ding_list_list_info_content_type_render($subtype, $conf, $panel_args, $context) {
  global $user;
  $list = $context->data;
  $block = new stdClass();
  $block->title = check_plain(entity_label('ding_type', $list));
  $block->content[] = array(
    '#theme' => 'ding_list_info',
    '#list' => $list,
  );
  if ($user->uid == $list->uid) {
    if (ding_base_get_value('ding_type', $list, 'field_list_type') !== DING_LIST_TYPE_LOAN_HISTORY) {
      $block->content[] = array(
        '#prefix' => '<div class="ding-list-help">',
        '#suffix' => '</div>',
        '#markup' => t('Read more about how you use the lists !help', array(
          '!help' => l(t('Here'), 'help/lists'),
        )),
      );
    }
  }

  return $block;
}
