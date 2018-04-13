<?php

/**
 * @file
 * This file contains admin forms and functionality.
 */

/**
 * Get system settings form with serendipity specific settings.
 */
function ding_serendipity_admin_form($form, &$form_state) {
  $form['ding_serendipity_enable_cache'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable cache'),
    '#description' => t('Allow the serendipity functionality to cache results to boost performance.'),
    '#default_value' => variable_get('ding_serendipity_enable_cache', 0),
  );

  $form['ding_serendipity_cache_lifetime'] = array(
    '#type' => 'textfield',
    '#title' => t('Cache lifetime'),
    '#description' => t('Enter the amount of seconds you want the serendipity cache to last.'),
    '#default_value' => variable_get('ding_serendipity_cache_lifetime', 600),
  );

  $form['ding_serendipity_isslow_timeout'] = array(
    '#type' => 'textfield',
    '#title' => t('Is slow limit'),
    '#description' => t('Enter the amount of seconds you want the serendipity functionality to be limited to.'),
    '#default_value' => variable_get('ding_serendipity_isslow_timeout', 10),
  );

  $form['ding_serendipity_search_string_final'] = array(
    '#type' => 'textfield',
    '#title' => t('Serendipity final fallback search string'),
    '#description' => t('Should all other serendipity plugins fail to deliver enough materials, this search string provides a final list of materials'),
    '#default_value' => variable_get('ding_serendipity_search_string_final', DING_SERENDIPITY_DEFAULT_FALLBACK_STRING),
    '#size' => 160,
    '#maxlength' => 300,
  );

  $form['test_cql'] = array(
    '#type' => 'button',
    '#value' => t('Test CQL'),
    '#ajax' => array(
      'wrapper' => 'test-cql-container',
      'callback' => 'ding_serendipity_test_cql_callback',
    ),
    '#suffix' => '<div id="test-cql-container"></div>',
    '#cql_element' => 'ding_serendipity_search_string_final',
  );

  $form['ding_serendipity_search_string_final_description'] = array(
    '#type' => 'textfield',
    '#title' => t('Serendipity final fallback description'),
    '#description' => t('Let the user know why they get suggestions from this final fallback. Keep it very short.'),
    '#default_value' => variable_get('ding_serendipity_search_string_final_description', t('The library recommends this')),
    '#size' => 100,
    '#maxlength' => 100,
  );

  return system_settings_form($form);
}

/**
 * Get an overview of the current registered serendipity functions and keys.
 */
function ding_serendipity_admin_overview($form, &$form_state) {
  $info = ding_serendipity_get_info();

  $form['ding_serendipity_callbacks'] = array(
    '#type' => 'tableselect',
    '#header' => array(
      'title' => t('Title'),
      'keys' => t('Context Keys'),
      'weight' => t('Weight'),
      'settings' => t('Settings'),
    ),
    '#options' => array(),
    '#default_value' => variable_get('ding_serendipity_callbacks', array()),
  );

  $weights = variable_get('ding_serendipity_weights', array());
  foreach ($info as $key => $value) {

    $weight = isset($value['weight']) ? $value['weight'] : 30;
    $form['ding_serendipity_callbacks']['#options'][$key] = array(
      'title' => $value['title'] . '<div class="description">' . $value['description'] . '<br/>(' . $value['module'] . ')</div>',
      'keys' => isset($value['keys']) ? implode(', ', $value['keys']) : '',
      'weight' => array(
        'data' => array(
          '#type' => 'select',
          '#title' => '',
          '#options' => drupal_map_assoc(ding_serendipity_weight_options()),
          '#value' => (isset($weights[$key])) ? array($weights[$key]) : array($weight),
          '#description' => t('Choose a weight for this serendipity function.'),
          '#name' => 'ding_serendipity_weights[' . $key . ']',
        ),
      ),
      'settings' => '',
    );

    if (isset($value['settings']) && $value['settings']) {
      $settings = $value['settings'];
      $form['ding_serendipity_callbacks']['#options'][$key]['settings'] = array(
        'data' => $settings,
      );
    }
  }

  $form['ding_serendipity_weights'] = array(
    '#type' => 'value',
  );

  return system_settings_form($form);
}

/**
 * Default serendipity options.
 */
function ding_serendipity_weight_options() {
  return array(10, 20, 30, 40, 50);
}
