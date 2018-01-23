<?php

$plugin = array(
  'title' => t('Profile page'),
  'description' => t('A pane to show the page for a profile, which includes fields and search tips.'),
  'single' => TRUE,
  'content_types' => array('ting_field_search_profile_page'),
  'render callback' => 'ting_field_search_profile_page_render',
  'required context' => new ctools_context_optional(t('Keywords'), 'string'),
  'category' => t('Ting'),
);

/**
 * Render callback.
 */
function ting_field_search_profile_page_render($subtype, $conf, $panel_args, $context) {
  if (empty($context) || empty($context->data)) {
    $search_query = '';
  }
  else {
    $search_query = $context->data;
  }

  $block = new stdClass();
  $block->module = 'ting_field_search';

  $profile = ting_field_search_get_active_profile();

  if (!$profile || empty($profile->fields)) {
    $block->content = '';
    return $block;
  }

  $block->title = t('Continue search in @profile', array(
    '@profile' => $profile->title,
  ));
  $block->content['fields_form'] = drupal_get_form('ting_field_search_fields_form', $profile, $search_query);

  return $block;
}

function ting_field_search_ting_field_search_profile_page_content_type_edit_form($form, &$form_state) {
  return $form;
}
