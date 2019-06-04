<?php

/**
 * @file
 * Private share.
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
  'required context' => new ctools_context_required(t('Ding list'), 'ding_list_list'),
);

/**
 * Implements hook_content_type_render().
 */
function ding_list_private_share_content_type_render($subtype, $conf, $panel_args, $context) {
  $list = $context->data;

  if (!$list->allowed(DING_LIST_OPERATION_SHARE)) {
    return FALSE;
  }

  $output = new stdClass();
  $output->content = '';

  if ($list->hasData('visibility')) {
    if ($list->isOwner() && $list->getData('visibility') !== 'public') {
      foreach ($conf['communities'] as $community) {
        $title = ucfirst($community);
        $output->content .= l(
          t('Share on @community', array('@community' => $title)),
          'ding-list/private-share-message/' . $list->getId() . '/' . $community,
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
    elseif ($list->getData('visibility') === 'public') {
      $output->content = array(
        '#theme' => 'ding_sharer',
        '#label' => t('Share this list'),
        '#communities' => array_map('ucfirst', $conf['communities']),
      );
    }
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
  $form_state['conf']['communities'] = array_filter($form_state['values']['communities']);
}
