<?php

$plugin = array(
    'title' => t('Ting field search profile'),
    'description' => t('A Ting field search profile context.'),
    'context' => 'ting_field_search_profile_context_create',
    'edit form' => 'ting_field_search_profile_context_settings_form',
    'keyword' => 'ting_field_search_profile',
    'context name' => 'ting_field_search_profile',
    'convert list' => 'ting_field_search_profile_object_convert_list',
    'convert' => 'ting_field_search_profile_object_convert',
    'placeholder form' => array(
      '#type' => 'textfield',
      '#description' => t('Enter the profile name for this context'),
    ),
);

function ting_field_search_profile_context_create($empty, $data = NULL, $conf = FALSE) {
  $context = new ctools_context('ting_field_search_profile');
  $context->plugin = 'ting_field_search_profile';

  if ($empty) {
    return $context;
  }

  if ($conf) {
    // Nothing for now.
  }

  if (!empty($data)) {
    $context->data = $data;
    $context->title = $data->title;
    $context->argument = $data->name;

    return $context;
  }
}

function ting_field_search_profile_context_settings_form($form, &$form_state) {
  return $form;
}

function ting_field_search_profile_object_convert_list() {
  return array();
}

function ting_field_search_profile_object_convert($context, $type) {
  return '';
}
