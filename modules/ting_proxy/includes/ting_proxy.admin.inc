<?php
/**
 * @file
 * The administration interface for the module.
 */

/**
 * Administration UI for ting proxy backend
 */
function ting_proxy_settings_form($form, &$form_state) {
  // Load saved settings.
  $values = variable_get('ting_proxy', array());

  // Build the form.
  $form = array(
    '#after_build' => array('ting_proxy_settings_form_after_build'),
    '#attributes' => array('class' => array('ting-proxy-settings')),
  );

  $form['ting_proxy'] = array(
    '#type' => 'fieldset',
    '#title' => t('Proxy service'),
    '#required' => TRUE,
    '#description' => t("Restricted-access resources referenced by Ting may be accessed through the library's proxy server"),
    '#tree' => TRUE,
  );

  $form['ting_proxy']['prefix'] = array(
    '#type' => 'textfield',
    '#title' => t('Proxy server URL prefix'),
    '#default_value' => isset($values['prefix']) ? $values['prefix'] : '',
    '#description' => t('E.g. <em>http://proxy.example.com/?url=</em>.'),
  );

  // Wrapper, so that the ahah callback have some place to put new elements.
  $form['ting_proxy']['hostnames'] = array(
    '#type' => 'fieldset',
    '#title' => t('Hostnames'),
    '#prefix' => '<div id="hostnames-wrapper">',
    '#suffix' => '</div>',
  );

  // First determine how many to build based on current values. Always show at
  // least one.
  if (empty($form_state['num_hostnames'])) {
    $form_state['num_hostnames'] = (isset($values['hostnames'])) ? count($values['hostnames']) : 1;
  }

  // Add the hostname elements with default value if defined.
  // Wrap each hostname in a div to support hiding during removal.
  for ($i = 0; $i < $form_state['num_hostnames']; $i++) {
    $form['ting_proxy']['hostnames'][$i] = array(
      '#type' => 'ting_proxy_hostname',
      '#default_value' => (isset($values['hostnames'][$i])) ? $values['hostnames'][$i] : array(),
      '#prefix' => '<div class="hostname ' . (($i == 0) ? 'first' : '') . '">',
      '#suffix' => '</div>',
    );
  }

  // Add AHAH button to add hostnames.
  $form['ting_proxy']['add_hostname'] = array(
    '#type' => 'submit',
    '#value' => t('Add another hostname'),
    '#weight' => 1,
    '#submit' => array('ting_proxy_hostname_add'),
    '#ajax' => array(
      'callback' => 'ting_proxy_hostname_callback',
      'wrapper' => 'hostnames-wrapper',
    ),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Callback for both ajax-enabled buttons.
 *
 * Selects and returns the field set with the names in it.
 */
function ting_proxy_hostname_callback($form, $form_state) {
  return $form['ting_proxy']['hostnames'];
}

/**
 * Handels addition of extra ting_proxy_hostname elements via AJAX to the
 * adminitration UI.
 */
function ting_proxy_hostname_add($form, &$form_state) {
  // Add another hostname.
  $form_state['num_hostnames']++;

  $form_state['rebuild'] = TRUE;
}

/**
 * Submit handler for the administration forms.
 *
 * It preforms basic clean up and hands the form to system settings submit.
 */
function ting_proxy_settings_form_submit($form, &$form_state) {
  // Remove add hostname button.
  unset($form_state['values']['ting_proxy']['add_hostname']);

  // Remove elements that have been marked.
  foreach ($form_state['values']['ting_proxy']['hostnames'] as $key => &$value) {
    if ($value['removed']) {
      unset($form_state['values']['ting_proxy']['hostnames'][$key]);
    }
  }

  // Reset keys after filtering.
  $form_state['values']['ting_proxy']['hostnames'] = array_values($form_state['values']['ting_proxy']['hostnames']);

  variable_set('ting_proxy', $form_state['values']['ting_proxy']);
}

/**
 * Adds custom ccs and js script to the administration form.
 *
 * It's done this way as it's add to the forms validation as well.
 */
function ting_proxy_settings_form_after_build($form, &$form_state) {
  // Add form styling.
  drupal_add_css(drupal_get_path('module', 'ting_proxy') . '/css/ting_proxy.admin.css', 'module', 'all', FALSE);

  // Add js.
  drupal_add_js(drupal_get_path('module', 'ting_proxy') . '/js/ting_proxy.admin.js');

  return $form;
}
