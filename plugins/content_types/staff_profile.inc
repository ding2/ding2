<?php
/**
 * @file
 * Wraps profile2 ding staff profile into a panels pane.
 */

$plugin = array(
  'title' => t('Ding staff profile'),
  'description' => t('Profile2 ding staff profile currently attached to the user.'),
  'single' => TRUE,
  'required context' => new ctools_context_required(t('User'), 'user'),
  'edit form' => 'ding_staff_profile_content_type_edit_form',
  'render callback' => 'ding_staff_profile_content_type_render',
  'category' => t('User'),
);

/**
 * Implements hook_ID_content_type_render().
 */
function ding_staff_profile_content_type_render($subtype, $conf, $panel_args, $context = NULL) {
  $block = new stdClass();
  $block->title = '';
  $block->content = '';

  if (!empty($context->data)) {

    // Try to load the profile and extract field values.
    $profile = profile2_load_by_user($context->data, 'ding_staff_profile');

    if ($profile) {
      // Set title based on forename and surname in staff profile.
      $forename = field_view_field('profile2', $profile, 'field_ding_staff_forename');
      if (!empty($forename)) {
        $block->title .= $forename[0]['#markup'] . ' ';
      }

      $surname = field_view_field('profile2', $profile, 'field_ding_staff_surname');
      if (!empty($surname)) {
        $block->title .= $surname[0]['#markup'];
      }

      // View profile to get render array with profile content.
      $block->content = $profile->view('account');
    }
  }

  return $block;
}

/**
 * Edit form callback for the content type.
 */
function ding_staff_profile_content_type_edit_form($form, &$form_state) {
  return $form;
}
