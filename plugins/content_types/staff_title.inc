<?php
/**
 * @file
 * Creates pane with contact informatio for a give staff profile.
 */

$plugin = array(
  'title' => t('Ding staff title'),
  'description' => t('Display title (header) on a staff member page'),
  'single' => TRUE,
  'required context' => new ctools_context_required(t('User'), 'user'),
  'edit form' => 'ding_staff_title_content_type_edit_form',
  'render callback' => 'ding_staff_title_content_type_render',
  'category' => t('Ding!'),
);

/**
 * Implements hook_ID_content_type_render().
 */
function ding_staff_title_content_type_render($subtype, $conf, $panel_args, $context = NULL) {
  $block = new stdClass();
  if (!empty($context->data)) {

    // Try to load the profile and extract field values.
    $profile = profile2_load_by_user($context->data, 'ding_staff_profile');
  
    if ($profile) {

      $block->title = '';
      // We leave the content array empty - the title of the block display what we need
      $block->content = array();

      // Get forename as render array.
      $forename = field_view_field('profile2', $profile, 'field_ding_staff_forename');
      if (!empty($forename)) {
        $block->title .= $forename[0]['#markup'] . ' ';
      }

      // Getsurname as render array.
      $surname = field_view_field('profile2', $profile, 'field_ding_staff_surname');
      if (!empty($surname)) {
        $block->title .= $surname[0]['#markup'];
      }
    }
  }

  return $block;
}

/**
 * 'Edit form' callback for the content type.
 */
function ding_staff_title_content_type_edit_form($form, &$form_state) {
  return $form;
}


