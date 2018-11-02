<?php

/**
 * @file
 * Defines the administration UI for the module.
 */

/**
 * Administration settings form for the module.
 */
function ding_campaign_plus_admin_settings($form, $form_state) {
  $form = array(
    '#theme' => 'ding_campaign_plus_admin_form',
    '#tree' => TRUE,
  );

  $form['ding_campaign_plus_weight'] = array(
    '#type' => 'fieldset',
    '#title' => t('Weight'),
    '#description' => t('Set the weight for the different triggers. If more campaigns are triggered by the same triggers these weights are used to determined which should be displayed.'),
    '#weight' => -10,
  );

  // Build table options sorted by selected weight.
  $defaults = variable_get('ding_campaign_plus_weight', array());
  $options = ding_campaign_plus_ding_settings_options($defaults);
  foreach ($options as $key => $option) {
    $form['ding_campaign_plus_weight']['table'][$key] = ding_campaign_plus_admin_settings_form_add($option['title'], $option['weight']);
  }

  // Time interval for scanning campaigns for 0-hits.
  $period = drupal_map_assoc(array(
    0,
    3600,
    10800,
    21600,
    32400,
    43200,
    86400,
    172800,
    345600,
    604800,
    1209600,
    2419200,
  ), 'format_interval');

  $form['ding_campaign_plus_notification'] = array(
    '#type' => 'select',
    '#title' => t('Notification scan interval'),
    '#description' => t('Cached pages will not be re-created until at least this much time has elapsed.'),
    '#options' => $period,
    '#default_value' => variable_get('ding_campaign_plus_notification', 604800),
    '#weight' => 12,
  );

  $form['ding_campaign_plus_expire'] = array(
    '#type' => 'textfield',
    '#title' => t('Campaign cache expire'),
    '#description' => t('Campaign selection is cached to boost performance. This is the number of seconds before campaigns should be reselected base on triggers for a give context.'),
    '#default_value' => variable_get('ding_campaign_plus_expire', 900),
    '#size' => 8,
    '#weight' => 15,
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array('#type' => 'submit', '#value' => t('Save Changes'));

  return $form;
}

/**
 * Submit handler for the administration settings form.
 */
function ding_campaign_plus_admin_settings_submit($form, $form_state) {
  $weights = array();
  foreach ($form_state['values']['ding_campaign_plus_weight']['table'] as $key => $value) {
    $weights[$key] = $value['weight'];
  }

  variable_set('ding_campaign_plus_weight', $weights);
  variable_set('ding_campaign_plus_expire', $form_state['values']['ding_campaign_plus_expire']);
}

/**
 * Build options (table rows) for the administration UI.
 *
 * @param array $weights
 *   The weights used to determine the sort order of the options.
 *
 * @return array
 *   The options sorted by weight.
 */
function ding_campaign_plus_ding_settings_options(array $weights) {
  $options = array();

  foreach (module_implements('ding_campaign_plus_default_weights') as $module) {
    $types = module_invoke($module, 'ding_campaign_plus_default_weights');
    foreach ($types as $type => $info) {
      $options[$type] = array(
        'title' => $info['prefix'] . ' - ' . $info['title'],
        'weight' => isset($weights[$type]) ? $weights[$type] : $info['weight'],
      );
    }
  }

  $options += array(
    'search' => array(
      'title' => 'Search (CQL)',
      'weight' => isset($weights['object']) ? $weights['object'] : 0,
    ),
  );

  // Sort options be weight keeping the array keys.
  uasort($options, '_ding_campaign_plus_ding_settings_options_sort');

  return $options;
}

/**
 * Compare function use to sort options.
 *
 * @param array $a
 *   Single option.
 * @param array $b
 *   Single option.
 *
 * @return int
 *   The result of the comparison.
 */
function _ding_campaign_plus_ding_settings_options_sort(array $a, array $b) {
  if ($a['weight'] === $b['weight']) {
    return 0;
  }
  return ($a['weight'] < $b['weight']) ? -1 : 1;
}

/**
 * Build single row for use in the table.
 *
 * @param string $title
 *   The title to display in the table.
 * @param int $weight
 *   The weight of the row in the table.
 *
 * @return array
 *   Form element for the table.
 */
function ding_campaign_plus_admin_settings_form_add($title, $weight = 0) {
  return array(
    // We'll use a form element of type '#markup' to display the item name.
    'name' => array(
      '#markup' => check_plain($title),
    ),

    'weight' => array(
      '#type' => 'weight',
      '#title' => t('Weight'),
      '#default_value' => $weight,
      '#delta' => 10,
      '#title_display' => 'invisible',
    ),
  );
}

/**
 * Implements theme_ding_campaign_plus_admin_form().
 *
 * Themes the admin forms weight table.
 */
function theme_ding_campaign_plus_admin_form($variables) {
  $form = $variables['form'];

  $rows = array();
  foreach (element_children($form['ding_campaign_plus_weight']['table']) as $id) {
    $form['ding_campaign_plus_weight']['table'][$id]['weight']['#attributes']['class'] = array('campaign-type-weight');
    $rows[] = array(
      'data' => array(
        drupal_render($form['ding_campaign_plus_weight']['table'][$id]['name']),
        drupal_render($form['ding_campaign_plus_weight']['table'][$id]['weight']),
      ),
      'class' => array('draggable'),
    );
  }

  $header = array(t('Name'), t('Weight'));
  $table_id = 'campaign-types-table';

  $output = theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array('id' => $table_id),
  ));

  $form['ding_campaign_plus_weight']['table'] = array(
    '#type' => 'markup',
    '#markup' => $output,
  );

  $output = drupal_render_children($form);

  drupal_add_tabledrag($table_id, 'order', 'sibling', 'campaign-type-weight');

  return $output;
}
