<?php

$plugin = array(
  'title' => t('Ding staff contact info'),
  'description' => t('Display staff contact info to a staff member page'),
  'single' => TRUE,
  'required context' => new ctools_context_required(t('User'), 'user'),
  'edit form' => 'ding_staff_contact_content_type_edit_form',
  'render callback' => 'ding_staff_contact_content_type_render',
  'category' => t('Ding!'),
);

function ding_staff_contact_content_type_render($subtype, $conf, $panel_args, $context = NULL) {
  $block = new stdClass();
  if (empty($context->data)) {
    return $block;
  }
  $account = $context->data;
  $profile = profile2_load_by_user($account, 'staff');
  
  $content = ' <div class="pane-content">';
  if (!empty($profile->field_ding_staff_phone['und'])) {
    $content .= '<div class="phone field-label-inline clearfix">
          <div class="field-label">' . t('Phone:') . '</div>
          <div class="field-items">' . $profile->field_ding_staff_phone['und'][0]['value']. '</div></div>';
  }
  if (!empty($profile->field_ding_staff_email['und'])) {
    $content .= '
        <div class="phone field-label-inline clearfix">
          <div class="field-label">' . t('Email:') . '</div>
          <div class="field-items">' . l($profile->field_ding_staff_email['und'][0]['email'], 'mailto:' . $profile->field_ding_staff_email['und'][0]['email']) . '</div>
        </div>
    ';
  }
  $content .= '</div>';
  $block->title= t('Contact');
  $block->content = $content;

  return $block;
}

/**
 * 'Edit form' callback for the content type.
 */
function ding_staff_contact_content_type_edit_form($form, &$form_state) {
  return $form;
}


