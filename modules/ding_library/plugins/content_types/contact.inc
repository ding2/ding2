<?php

$plugin = array(
  'title' => t('Ding library contact info'),
  'description' => t('Display lbirary contact info'),
  'single' => TRUE,
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'edit form' => 'ding_library_contact_content_type_edit_form',
  'render callback' => 'ding_library_contact_content_type_render',
  'category' => t('Ding!'),
);

function ding_library_contact_content_type_render($subtype, $conf, $panel_args, $context = NULL) {
  $block = new stdClass();
  if (empty($context->data)) {
    return $block;
  }
  $node = $context->data;

  $content = ' <div class="library-contact">';
  if (!empty($node->field_ding_library_phone_number['und'])) {
    $content .= '
      <div class="library-contact-phone">
        <span class="library-contact-phone-label">' . t('Phone:') . '</span>
        <span class="library-contact-phone">' . $node->field_ding_library_phone_number['und'][0]['value'] . '</span>
      </div>';
  }
  if (!empty($node->field_ding_library_mail['und'])) {
    $content .= '
        <div class="library-contact-email">
          <span class="library-contact-email-label">' . t('Email:') . '</span>
          <span class="library-contact-phone">' . l($node->field_ding_library_mail['und'][0]['email'], 'mailto:' . $node->field_ding_library_mail['und'][0]['email']) . '</span>
        </div>
    ';
  }
  $content .= '</div>';

  $block->title = t('Contact');
  $block->content = $content;

  return $block;
}

/**
 * Edit form callback for the content type.
 */
function ding_library_contact_content_type_edit_form($form, &$form_state) {
  return $form;
}


