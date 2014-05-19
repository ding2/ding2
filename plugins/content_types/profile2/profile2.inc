<?php
/**
 * @file
 * Wrappers profile2 provider profile into a panels pane.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
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
    if ($user->data['blocked']) {
      $link = variable_get('ding_user_blocked_user_node', 'node/1');
      drupal_set_message(t('Your user account is blocked in the library system. See <a href="@link">this</a> page for more information.', array('@link' => $link)), 'error');
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
