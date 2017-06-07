<?php

/**
 * @file
 *
 * Admin page callbacks for the Ting field search module.
 */

function ting_field_search_settings_form($form, &$form_state) {
  $form = array();
  // Show a message to the administrator if the module isn't installed
  // correctly. We provide a callback to correct this.
  if (!ting_field_search_get_status()) {
    drupal_set_message(t('Ting field search is NOT installed correctly and will not work properly. Please go to <a href="@install">Installation</a> to correct this.', array(
        '@install' => url('admin/config/ting-field-search/install', array(
          'query' => drupal_get_destination()
        )),
      )
    ), 'error');
  }

  return $form;
}

function ting_field_search_install_confirm_form($form, &$form_state) {
  // Nothing to do here if installed correctly.
  if (ting_field_search_get_status()) {
    drupal_goto('admin/config/ting/settings');
  }

  $backend = variable_get('cache_class_cache_ting', FALSE);
  if (!$backend) {
    // A default is being used and it's not one if ours.
    $backend = variable_get('cache_default_class', 'DrupalDatabaseCache');
  }

  $message = '<p>' . t('Ting field search will <strong>NOT</strong> function correctly without the proper backend for cache_ting.') . '<//p>';
  $message .= '<p>' . t('The current backend %backend will <strong>NOT</strong> work with Ting field search. Please press install below to correct this.', array('%backend' => $backend)) . '</p>';

  return confirm_form($form,
    t('Confirm installation of Ting field search cache backend'),
    'admin/config/ting/settings',
    $message,
    t('Install'),
    t('Cancel')
  );
}

function ting_field_search_install_confirm_form_submit($form, &$form_state) {
  ting_field_search_install_backend();

  // Verify
  if (ting_field_search_get_status()) {
    drupal_set_message(t('A compatible backend was installed and Ting field search is now functioning properly.'));
  }
  else {
    drupal_set_message(t('Something went wrong. A compatible backend was NOT installed and Ting field search will NOT function properly.'));
  }

  $form_state['#redirect'] = 'admin/config/ting/settings';
}
