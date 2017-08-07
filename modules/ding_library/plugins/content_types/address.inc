<?php

$plugin = array(
  'title' => t('Ding library address info'),
  'description' => t('Display library address info'),
  'single' => TRUE,
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'edit form' => 'ding_library_address_content_type_edit_form',
  'render callback' => 'ding_library_address_content_type_render',
  'category' => t('Ding!'),
);

function ding_library_address_content_type_render($subtype, $conf, $panel_args, $context = NULL) {
  $block = new stdClass();
  if (empty($context->data)) {
    return $block;
  }
  $node = $context->data;

  $content = ' <div class="library-address">';
  if (!empty($node->field_ding_library_addresse['und'])) {
    $content .= '
      <div class="library-address-street">' . $node->field_ding_library_addresse['und'][0]['thoroughfare'] . '</div>
      <div class="library-address-city-wrapper">
        <span class="library-address-postal-code">' . $node->field_ding_library_addresse['und'][0]['postal_code'] . '</span><span class="library-address-city">' . $node->field_ding_library_addresse['und'][0]['locality'] . '</span>
      </div>';
  }

  $content .= '</div>';
  $block->title = t('Address');
  $block->content = $content;

  return $block;
}

/**
 * Edit form callback for the content type.
 */
function ding_library_address_content_type_edit_form($form, &$form_state) {
  return $form;
}
