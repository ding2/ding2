<?php

/**
 * @file
 * Information about list followers pane.
 */

$plugin = array(
  'title' => t('Ding list data'),
  'description' => t('Ding list.'),
  'single' => TRUE,
  'category' => t('Dinglist'),
  'render callback' => 'ding_list_list_data_content_type_render',
  'required context' => new ctools_context_required(t('Ding list'), 'ding_list_list'),
);

/**
 * Implements hook_content_type_render().
 */
function ding_list_list_data_content_type_render($subtype, $conf, $panel_args, $context) {
  global $user;
  $block = new stdClass();

  $list = $context->data;
  $note = $list->getNote();

  // If no note isset, get the default note for the list type.
  if (!$note) {
    $list_information = ding_list_list_operations();
    $list_type = $list->getType();
    if (isset($list_information[$list_type])) {
      $list_information = $list_information[$list_type];
      if (isset($list_information['_data']['description'])) {
        $note = $list_information['_data']['description'];
      }
    }
  }

  $block->content['note'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'ding-list-data--note',
      ),
    ),
  );
  
  $block->content['note']['note'] = array(
    '#markup' => $note,
  );

  $block->content['info'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'ding-list-data--info',
      ),
    ),
  );

  $block->content['info']['user'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'list-info',
      ),
    ),
  );

  if (!$list->isOwner()) {
    $block->content['info']['user']['user'] = array(
      '#theme' => 'ding_list_label_value',
      '#label' => t('Created by'),
      '#value' => $list->getOwnerName(),
    );
  }

  if ($list->allowed(DING_LIST_OPERATION_SHARE) && $list->getData('visibility', 'private') != 'private') {
    $followers_count = $list->getFollowersCount();

    $block->content['info']['user']['followers'] = array(
      '#theme' => 'ding_list_label_value',
      '#label' => t('Number of followers'),
      '#value' => format_plural($followers_count, '1 user following this list', '@count users following this list'),
    );
  }

  $block->content['info']['follow'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'list-buttons',
      ),
    ),
  );
  
  // Users can only add lists they don't own.
  if (!$list->isOwner() && user_access('use personalisation')) {
    $follow_list = ding_list_get_list(DING_LIST_TYPE_LISTS);
    if ($element = $follow_list->hasElement($list->getId())) {
      // If we have more than 1 remove form on a page Drupal will use the first
      // occoring remove form everytime, unless they all got a unique ID, which
      // is why the element ID is appended.
      // See the ding_list_forms() hook in ding_list/include/form.inc.
      $block->content['info']['follow']['button'] = drupal_get_form('ding_list_remove_element_form__' . $element->getId(), $element, t('Unfollow list'));
    }
    else {
      $block->content['info']['follow']['button'] = drupal_get_form('ding_list_add_element_form', 'ding_list', $list->getId(), t('Add to lists I follow'));
    }
  }
  elseif ($list->allowed(DING_LIST_OPERATION_SHARE)) {
    $block->content['info']['follow']['button'] = array(
      '#markup' => l(t('Share list'), 'list/' . $list->getId() . '/share', array('attributes' => array('class' => array('button')))),
    );
  }  

  return $block;
}
