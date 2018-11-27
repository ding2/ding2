<?php

/**
 * @file
 * Wrappers profile2 provider profile into a panels pane.
 */

/**
 * Plugin definition.
 */
$plugin = array(
  'title' => t('Provider profile'),
  'description' => t('Profile2 provider profile currently attched to the user.'),
  'single' => TRUE,
  'content_types' => array('profile2'),
  'render callback' => 'ding_user_profile2_type_render',
  'required context' => new ctools_context_required(t('User'), 'user'),
  'category' => t('User'),
);

/**
 * Render callback function.
 */
function ding_user_profile2_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $block->content = '';

  if (isset($context->data)) {
    $account = $context->data;
    $profile = ding_user_provider_profile($account);

    // Change the label for this profile type.
    $profile->label = t('Your information');

    // View profile to get render array with profile content.
    $block->content = $profile->view('account');

    global $user;
    if ($user->data['blocks']) {
      $link = variable_get('ding_user_blocked_user_node', variable_get('site_404', 'customerror/404'));
      foreach ($user->data['blocks'] as $block_code) {
        drupal_set_message(ding_user_block_reason($block_code), 'warning');
      }
      drupal_set_message(t('See <a href="@link">this</a> page for more information about block types.', array('@link' => $link)), 'error');
    }
  }

  return $block;
}

/**
 * Plugin settings form.
 */
function ding_user_profile2_content_type_edit_form($form, &$form_state) {
  return $form;
}
