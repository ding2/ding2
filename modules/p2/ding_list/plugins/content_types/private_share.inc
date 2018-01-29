<?php

/**
 * @file
 * Ding Serendipity CTools plugin file.
 */

/**
 * Plugin description.
 */
$plugin = array(
  'title' => t('Private list sharer'),
  'description' => '',
  'single' => TRUE,
  'edit form' => 'ding_list_private_share_edit_form',
  'render callback' => 'ding_list_private_share_content_type_render',
  'category' => t('Ding!'),
  'required context' => new ctools_context_required(t('Dinglist'), 'ding_type'),
);

/**
 * Implements hook_content_type_render().
 */
function ding_list_private_share_content_type_render($subtype, $conf, $panel_args, $context) {
  $list = $context->data;

  if (!ding_list_allowed($list, DING_LIST_OPERATION_SHARE)) {
    return FALSE;
  }

  drupal_add_js(drupal_get_path('module', 'ding_sharer') . '/ding-sharer.js');

  $output = new stdClass();

  $output->content = '';

  // Check if anonymous users have access to current page,
  // if not, then not much point in being able to share it.
  $item = menu_get_item();
  $item['map'][1]->data->uid = 0;
  _menu_check_access($item, $item['map']);
  $access = $item['access'];

  if ($access) {
    foreach ($conf['communities'] as $community) {
      $title = ucfirst($community);
      $output->content .= l(
        t('Share on @community', array('@community' => $title)),
        'ding-list/private-share-message/' . $list->id . '/' . $community,
        array(
          'attributes' => array(
            'class' => array(
              'sharer-button', 'sharer-' . $community, 'use-ajax',
            ),
          ),
        )
      );
    }

    $output->content = '<div class="sharer">' . $output->content . '</div>';
  }

  return $output;
}

/**
 * Implements hook_content_type_edit_form().
 */
function ding_list_private_share_edit_form($form, &$form_state) {
  $form['communities'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Communities'),
    '#options' => array(
      'facebook' => 'Facebook',
      'twitter' => 'Twitter',
    ),
    '#default_value' => $form_state['conf']['communities'],
  );

  return $form;
}

/**
 * Implements hook_content_type_edit_form_submit().
 */
function ding_list_private_share_edit_form_submit($form, &$form_state) {
  $form_state['conf']['communities'] = $form_state['values']['communities'];
}
