<?php

/**
 * @file
 * Information about list followers pane.
 */

$plugin = array(
  'title' => t('Ding list data'),
  'description' => t('Ding list.'),
  'single' => TRUE,
  'content_types' => array('ding_type'),
  'category' => t('Dinglist'),
  'render callback' => 'ding_list_list_data_content_type_render',
  'required context' => new ctools_context_required(t('Dinglist'), 'ding_type'),
);

/**
 * Implements hook_content_type_render().
 */
function ding_list_list_data_content_type_render($subtype, $conf, $panel_args, $context) {
  global $user;

  $list = $context->data;
  $list_user = user_load($list->uid);
  $list_status = $list->field_ding_list_status['und'][0]['value'];
  $block = new stdClass();

  $block->content['info'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'ding-list-data',
      ),
    ),
  );

  if ($user->uid != $list->uid) {
    $block->content['info']['user'] = array(
      '#theme' => 'ding_list_label_value',
      '#label' => t('Created by'),
      '#value' => ding_list_list_username($list),
    );
  }

  if (ding_list_allowed($list, DING_LIST_OPERATION_SHARE) && $list_status != 'private') {
    $block->content['info'][] = array(
      '#theme' => 'ding_list_followers',
      '#list' => $list,
    );
  }

  $items = field_get_items('ding_type', $list, 'field_ding_content_tags');
  if (!empty($items)) {
    $tids = array();
    foreach ($items as $item) {
      $tids[] = $item['tid'];
    }

    $links = array(
      '#theme' => 'links',
      '#links' => array(),
      '#attributes' => array(
        'class' => array('filter-links')
      ),
    );
    foreach (taxonomy_term_load_multiple($tids) as $term) {
      $links['#links'][] = array(
        'title' => $term->name,
        'href' => 'public-lists/all/' . $term->tid,
        // 'attributes' => array('
      );
    }

    $block->content['info']['tags'] = array(
      '#theme' => 'ding_list_label_value',
      '#label' => t('Tags'),
      '#value' => $links,
    );
  }
  return $block;
}
