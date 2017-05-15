<?php

/**
 * @file
 * Information about list followers pane.
 */

$plugin = array(
  'title' => t('Ding list followers'),
  'description' => t('Ding list.'),
  'single' => TRUE,
  'content_types' => array('ding_type'),
  'category' => t('Dinglist'),
  'render callback' => 'ding_list_list_followers_content_type_render',
  'required context' => new ctools_context_required(t('Dinglist'), 'ding_type'),
);

/**
 * Implements hook_content_type_render().
 */
function ding_list_list_followers_content_type_render($subtype, $conf, $panel_args, $context) {
  $list = $context->data;

  $block = new stdClass();

  $block->content = array(
    // Panels run the title through translation, so we add it to the content.
    array(
      '#theme' => 'html_tag',
      '#tag' => 'h2',
      '#attributes' => array(
        'class' => array('pane-title'),
      ),
      '#value' => check_plain(entity_label('ding_type', $list)),
    ),
    array('#theme' => 'ding_list_followers', '#list' => $list),
    array(
      '#prefix' => '<div>',
      '#suffix' => '</div>',
      '#markup' => t('Read more about how you use the lists !help', array(
        '!help' => l(t('Here'), 'help/lists'),
      )),
    ),
  );

  if (ding_list_allowed($list, DING_LIST_OPERATION_SHARE)) {
    $block->content[] = array('#theme' => 'ding_list_followers', '#list' => $list);
  }

  return $block;
}
