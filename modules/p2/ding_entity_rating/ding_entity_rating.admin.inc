<?php

/**
 * @file
 * Admin forms.
 */

/**
 * Admin form.
 */
function ding_entity_rating_admin_form($form, &$form_state) {
  $form['ding_entity_rating_get_limit'] = array(
    '#type' => 'textfield',
    '#title' => t('Get request limit'),
    '#description' => t('When the number of IDs being checked for a rating exceeds this number a POST request is used instead of GET.'),
    '#default_value' => variable_get('ding_entity_rating_get_limit', DING_ENTITY_RATING_DEFAULT_GET_LIMIT),
  );

  return system_settings_form($form);
}
