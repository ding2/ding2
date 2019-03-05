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

  $phone = ding_base_get_value('node', $node, 'field_ding_library_phone_number');
  $fax = ding_base_get_value('node', $node, 'field_ding_library_fax_number');
  $mail = ding_base_get_value('node', $node, 'field_ding_library_mail', 'email');

  $content = ' <div class="library-contact">';

  if (!empty($phone)) {
    $content .= '
      <div class="library-contact-phone">
        <span class="library-contact-phone-label">' . t('Phone:') . '</span>
        <span class="library-contact-phone">' . $phone . '</span>
      </div>';
  }
  if (!empty($fax)) {
    $content .= '
        <div class="library-contact-fax">
          <span class="library-contact-fax-label">' . t('Fax:') . '</span>
          <span class="library-contact-fax">' . $fax . '</span>
        </div>
    ';
  }
  if (!empty($mail)) {
    $content .= '
        <div class="library-contact-email">
          <span class="library-contact-email-label">' . t('Email:') . '</span>
          <span class="library-contact-phone">' . l($mail, 'mailto:' . $mail) . '</span>
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
