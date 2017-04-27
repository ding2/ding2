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
  $form['ding_serendipity_callbacks']['#process'][] = 'ding_serendipity_process_options';
  foreach ($info as $key => $value) {
    if (!isset($form[$value['module']])) {
      $form['ding_serendipity_callbacks']['#options'][$value['module']] = array(
        'title' => '<h2>' . $value['module'] . '</h2>',
        'keys' => '',
        'weight' => '',
        'settings' => '',
        '#attributes' => array('disabled' => TRUE, 'header' => TRUE),
      );
    }

    $weight = isset($value['weight']) ? $value['weight'] : 30;
    $form['ding_serendipity_callbacks']['#options'][$key] = array(
      'title' => $value['title'] . '<div class="description">' . $value['description'] . '</div>',
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
        'data' => l(
          t('Settings'),
          'admin/config/ding/serendipity/key_overview/' . $settings,
          array('query' => array('destination' => 'admin/config/ding/serendipity/key_overview'))
        ),
      );
    }
  }

  $form['ding_serendipity_weights'] = array(
    '#type' => 'value',
  );

  $form['context'] = array(
    '#type' => 'fieldset',
    '#title' => t('keys'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  foreach ($info as $key => $value) {
    foreach ($value['keys'] as $context) {
      if (empty($form['context'][$context])) {
        $form['context'][$context] = array(
          '#type' => 'checkbox',
          '#title' => check_plain($context),
          '#default_value' => (!empty($form_state[$context])) ? $form_state[$context] : 1,
        );
      }
    }
  }

  return system_settings_form($form);
}

/**
 * Process options for the ding_serendipity_admin_overview.
 */
function ding_serendipity_process_options($element) {
  if ($element['#multiple']) {
    $value = is_array($element['#value']) ? $element['#value'] : array();
  }
  else {
    // Advanced selection behavior makes no sense for radios.
    $element['#js_select'] = FALSE;
  }

  $element['#tree'] = TRUE;

  if (count($element['#options']) > 0) {
    if (!isset($element['#default_value']) || $element['#default_value'] === 0) {
      $element['#default_value'] = array();
    }

    // Create a checkbox or radio for each item in #options in such a way that
    // the value of the tableselect element behaves as if it had been of type
    // checkboxes or radios.
    foreach ($element['#options'] as $key => $choice) {
      // Do not overwrite manually created children.
      if (!isset($element[$key])) {
        if ($element['#multiple']) {
          $title = '';
          if (!empty($element['#options'][$key]['title']['data']['#title'])) {
            $title = t('Update @title', array(
                '@title' => $element['#options'][$key]['title']['data']['#title'],
              ));
          }
          $element[$key] = array(
            '#type' => 'checkbox',
            '#title' => $title,
            '#title_display' => 'invisible',
            '#return_value' => $key,
            '#default_value' => isset($value[$key]) ? $key : NULL,
            '#attributes' => $element['#attributes'],
          );
        }
        else {
          // Generate the parents as the autogenerator does, so we will have a
          // unique id for each radio button.
          $parents_for_id = array_merge($element['#parents'], array($key));
          $element[$key] = array(
            '#type' => 'radio',
            '#title' => '',
            '#return_value' => $key,
            '#default_value' => ($element['#default_value'] == $key) ? $key : NULL,
            '#attributes' => $element['#attributes'],
            '#parents' => $element['#parents'],
            '#id' => drupal_html_id('edit-' . implode('-', $parents_for_id)),
            '#ajax' => isset($element['#ajax']) ? $element['#ajax'] : NULL,
          );
        }
        if (isset($element['#options'][$key]['#weight'])) {
          $element[$key]['#weight'] = $element['#options'][$key]['#weight'];
        }
      }
    }
  }
  else {
    $element['#value'] = array();
  }

  $info = ding_serendipity_get_info();
  foreach ($info as $key => $value) {
    $element[$value['module']]['#disabled'] = TRUE;
  }

  return $element;
}

/**
 * Default serendipity options.
 */
function ding_serendipity_weight_options() {
  return array(10, 20, 30, 40, 50);
}
