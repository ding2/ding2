<?php

$plugin = array(
  'title' => t('Profile page'),
  'description' => t('A pane to show the page for a profile, which includes fields and search tips.'),
  'single' => TRUE,
  'content_types' => array('ting_field_search_profile_page'),
  'render callback' => 'ting_field_search_profile_page_render',
  'required context' => array(
    new ctools_context_optional(t('Keywords'), 'string'),
    new ctools_context_optional(t('Ting field search profile'), 'ting_field_search_profile'),
  ),
  'category' => t('Ting'),
);

/**
 * Render callback.
 */
function ting_field_search_profile_page_render($subtype, $conf, $panel_args, $context) {
  $search_query = '';
  $profile = FALSE;

  if (!empty($context[0]) && !empty($context[0]->data)) {
    $search_query = $context[0]->data;
  }
  if (!empty($context[1]) && !empty($context[1]->data)) {
    $profile = $context[1]->data;
  }

  // If we still don't have a profile context, support the old method of URL
  // query parameter input.
  if (!$profile) {
    $profile = ting_field_search_get_active_profile();
  }

  $block = new stdClass();
  $block->module = 'ting_field_search';

  if (!$profile) {
    $block->content = '';
    return $block;
  }

  if (!empty($search_query)) {
    $block->title = t('Continue search in @profile', array(
      '@profile' => $profile->title,
    ));
  }
  else {
    $block->title = t('Search in @profile', array(
      '@profile' => $profile->title,
    ));
  }
  $block->content['fields_form'] = drupal_get_form('ting_field_search_fields_form', $profile, $search_query);

  return $block;
}

function ting_field_search_ting_field_search_profile_page_content_type_edit_form($form, &$form_state) {
  return $form;
}
