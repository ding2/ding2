<?php
/**
 * @file
 * Ding user complate admin pages
 */

/**
 * Get an overview of the current registered interaction functions and keys.
 */
function ding_user_complete_admin_overview($form, &$form_state) {
  $status = ding_user_complete_hook();

  // Instead of checking multiple strings how about just using a constant
  // with a sufficiently unique value?
  if (isset($status['not_set']) && $status['not_set']['title'] == 'ding_user_complete_not_set') {
    drupal_set_message(t('No modules implement the user complete hook yet.'), 'warning');
    return;
  }

  $active = variable_get('ding_user_complete_callbacks', array());

  $form['ding_user_complete_callbacks'] = array(
    '#type' => 'tableselect',
    '#header' => array(
      'title' => t('Title'),
      'weight' => t('Points'),
    ),
    '#options' => array(),
    '#default_value' => $active,
  );

  $weights = variable_get('ding_user_complete_weights', array());
  $form['ding_user_complete_callbacks']['#process'][] = 'ding_user_complete_process_options';
  foreach ($status as $key => $value) {
    $default = isset($value['weight']) ? $value['weight'] : $value['points'];
    $form['ding_user_complete_callbacks']['#options'][$key] = array(
      'title' => $value['title'],
      'weight' => array(
        'data' => array(
          '#type' => 'select',
          '#title' => '',
          '#options' => range(1, 20),
          '#value' => (isset($weights[$key])) ? array($weights[$key]) : array($default),
          '#description' => t('Choose the amount of points this function gives when completed.'),
          '#name' => 'ding_user_complete_weights[' . $key . ']',
        ),
      ),
    );
  }
  $form['ding_user_complete_weights'] = array(
    '#type' => 'value',
  );

  $activated = 0;
  $total = 0;
  foreach ($weights as $key => $value) {
    $total += $value;
    if ($active[$key]) {
      $activated += $value;
    }
  }

  $form['ding_user_complete_overview'] = array(
    '#type' => 'item',
    '#title' => 'Overview',
    '#markup' => 'Total points: ' . $total . '<br />' . 'Total activated points: ' . $activated,
  );

  return system_settings_form($form);
}

/**
 * Process each option.
 */
function ding_user_complete_process_options($element) {
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
      // Do not override manually created children.
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
  return $element;
}
