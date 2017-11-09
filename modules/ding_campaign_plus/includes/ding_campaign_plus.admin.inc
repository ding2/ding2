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
    '#description' => t('Set the weight for the different triggers. If more campaigns are triggered by the same triggers these weights are used to determined which should be displayed. ')
  );

  // Build table options sorted by selected weight.
  $defaults = variable_get('ding_campaign_plus_weight', array());
  $options = ding_campaign_plus_ding_settings_options($defaults);
  foreach ($options as $key => $option) {
    $form['ding_campaign_plus_weight']['table'][$key] = ding_campaign_plus_admin_settings_form_add($option['title'], $option['weight']);
  }

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array('#type' => 'submit', '#value' => t('Save Changes'));

  return $form;
}

/**
 * Submit handler for the administration settings form.
 */
function ding_campaign_plus_admin_settings_submit($form, $form_state) {
  $values = $form_state['values']['ding_campaign_plus_weight']['table'];

  $weights = array();
  foreach ($values as $key => $value) {
    $weights[$key] = $value['weight'];
  }

  variable_set('ding_campaign_plus_weight', $weights);
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
function ding_campaign_plus_ding_settings_options($weights) {
  $options = array();

  $facets = variable_get('ding_facetbrowser_facets', array());
  foreach ($facets as $facet) {
    $options[$facet['name']] =  array(
      'title' => 'Facet - ' . $facet['title'],
      'weight' => isset($weights[$facet['name']]) ? $weights[$facet['name']] : 0,
    );
  }

  $types = _ding_campaign_plus_get_other_triggers();
  foreach ($types as $id => $title) {
    $options[$id] = array(
      'title' => 'Other - ' . $title,
      'weight' => isset($weights[$id]) ? $weights[$id] : 0,
    );
  }

  $options += array(
    'object' => array(
      'title' => 'Ting object view',
      'weight' => isset($weights['object']) ? $weights['object'] : 0,
    ),
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
function _ding_campaign_plus_ding_settings_options_sort($a, $b) {
  if ($a['weight'] == $b['weight']) {
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
    '#markup' => $output
  );

  $output = drupal_render_children($form);

  drupal_add_tabledrag($table_id, 'order', 'sibling', 'campaign-type-weight');

  return $output;
}