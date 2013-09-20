<?php
/**
 * @file
 * Creates pane with contact informatio for a give staff profile.
 */

$plugin = array(
  'title' => t('Ding staff contact info'),
  'description' => t('Display staff contact info to a staff member page'),
  'single' => TRUE,
  'required context' => new ctools_context_required(t('User'), 'user'),
  'edit form' => 'ding_staff_contact_content_type_edit_form',
  'render callback' => 'ding_staff_contact_content_type_render',
  'category' => t('Ding!'),
);

/**
 * Implements hook_ID_content_type_render().
 */
function ding_staff_contact_content_type_render($subtype, $conf, $panel_args, $context = NULL) {
  $block = new stdClass();
  if (!empty($context->data)) {

    // Try to load the profile and extract field values.
    $profile = profile2_load_by_user($context->data, 'ding_staff_profile');
  
    if ($profile) {

      $block->title = t('Contact');
      $block->content = array();

      // Get phone as render array.
      $phone = field_view_field('profile2', $profile, 'field_ding_staff_phone');
      if (!empty($phone)) {
        $block->content[] = $phone;
      }

      // Get mail as render array.
      $mail = field_view_field('profile2', $profile, 'field_ding_staff_email');
      if (!empty($mail)) {
        $block->content[] = $mail;
      }
    }
  }

  return $block;
}

/**
 * 'Edit form' callback for the content type.
 */
function ding_staff_contact_content_type_edit_form($form, &$form_state) {
  return $form;
}


