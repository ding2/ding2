<?php

/**
 * @file
 * Information about list info pane.
 */

$plugin = array(
  'title' => t('Ding list info'),
  'description' => t('Ding list.'),
  'single' => TRUE,
  'category' => t('Dinglist'),
  'render callback' => 'ding_list_list_info_content_type_render',
  'required context' => new ctools_context_required(t('Ding list'), 'ding_list_list'),
);

/**
 * Implements hook_content_type_render().
 */
function ding_list_list_info_content_type_render($subtype, $conf, $panel_args, $context) {
  $list = $context->data;
  $block = new stdClass();
  $block->title = check_plain($list->getTitle());
  $block->content[] = array(
    '#theme' => 'ding_list_info',
    '#list' => $list,
  );
  if ($list->isOwner()) {
    if ($list->getType() !== DING_LIST_TYPE_LOAN_HISTORY) {
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
