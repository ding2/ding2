<?php
/**
 * Implement hook_form_FORM_ID_alter (ding_event_admin_currency_setting_form)
 *
 * place2book does not accept currencies other kr. abort if ding_place2book is enabled
 */

function ding_place2book_form_ding_event_admin_currency_setting_form_alter(&$form, $form_state){
  $form['#validate'][] = 'ding_place2book_form_ding_event_admin_currency_setting_validate';
}

function ding_place2book_form_ding_event_admin_currency_setting_validate($form, &$form_state){
  $currency = $form_state['values']['ding_event_currency_type'];
  if (module_exists('ding_place2book') && $currency != 'kr') {
    drupal_set_message(t('place2book does not support currencies other than Kr. disable ding_place2book module to continue'), 'warning');
    $form_state['input']['ding_event_currency_type'] = 'kr';
    $form_state['rebuild'] = TRUE;
    return;
  }
}
