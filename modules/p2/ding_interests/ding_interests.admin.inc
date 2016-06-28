<?php

/**
 * @file
 * Ding interests administation
 */

/**
 * Form builder; Configure ding interests
 */
function ding_interests_admin_form($form, $form_state) {

  $form['ding_interests'] = array(
    '#type' => 'fieldset',
    '#title' => t('No configuration available'),
  );


  return system_settings_form($form);
}
