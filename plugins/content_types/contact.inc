<?php

$plugin = array(
  'title' => t('Ding library contact info'),
  'description' => t('Display a list contact info to the library page'),
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

  $content = ' <div class="pane-content">';
  if (!empty($node->ding_library_phone['und'])) {
  $content = '<div class="phone field-label-inline clearfix">
          <div class="field-label">' . t('Phone:') . '</div>
          <div class="field-items">' . $node->ding_library_phone['und'][0]['value']. '</div>';
  }
  if (!empty($node->ding_library_email['und'])) {
     $content = '</div>
        <div class="phone field-label-inline clearfix">
          <div class="field-label">' . t('Email:') . '</div>
          <div class="field-items">' . l($node->ding_library_email['und'][0]['email'], 'mailto:' . $node->ding_library_email['und'][0]['email']) . '</div>
        </div>
  </div>';
  }
  $block->title= t('Contact');
  $block->content = $content;

  return $block;
}

/**
 * 'Edit form' callback for the content type.
 */
function ding_library_contact_content_type_edit_form($form, &$form_state) {
  return $form;
}


