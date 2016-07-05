<?php
/**
 * @file
 * Admin page callback file for the ting module.
 */

/**
 * Form builder; Configure ting settings for this site.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function ding_facetbrowser_settings($form_state) {
  form_load_include($form_state, 'inc', 'ding_facetbrowser', 'ding_facetbrowser.admin');
  $form = array();
  $facets = variable_get('ding_facetbrowser_facets', array());

  $form['description'] = array(
    '#markup' => '<p>' . t('Configure facets shown in the facetbrowser. Facet names can be found at <a href="http://oss.dbc.dk/wiki/bin/view/Databroend/OpenSearchDocIndexes">DBC wiki</a> and is usually named <em>facet.something</em>.') . '</p>',
  );

  $showcount = variable_get('ding_facetbrowser_showcount', 5);
  $form['ding_facetbrowser_showcount'] = array(
    '#type' => 'select',
    '#title' => t('Visible facets amount'),
    '#description' => t('The amount of facets that will be visible on the search page by default. The rest of the facets will be hidden and the user have to click to show them.'),
    '#options' => drupal_map_assoc(range(1, 15)),
    '#default_value' => $showcount,
  );

  $number_of_terms = variable_get('ding_facetbrowser_number_of_terms', 5);
  $form['ding_facetbrowser_number_of_terms'] = array(
    '#type' => 'select',
    '#title' => t('Number of terms'),
    '#description' => t('The number of facets terms to display in each facet group.'),
    '#options' => drupal_map_assoc(range(1, 15)),
    '#default_value' => $number_of_terms,
  );

  $form['ding_facetbrowser_facets'] = array(
    '#tree' => TRUE,
    '#weight' => -20,
  );

  $i = 0;
  foreach ($facets as $facet) {
    $form['ding_facetbrowser_facets'][$i]['name'] = array(
      '#type' => 'textfield',
      '#title' => t('Facet id'),
      '#title_display' => 'invisible',
      '#default_value' => $facet['name'],
    );

    $form['ding_facetbrowser_facets'][$i]['title'] = array(
      '#type' => 'textfield',
      '#title' => t('Title'),
      '#title_display' => 'invisible',
      '#default_value' => $facet['title'],
    );

    $form['ding_facetbrowser_facets'][$i]['sorting'] = array(
      '#type' => 'select',
      '#title' => t('Facet name sorting'),
      '#title_display' => 'invisible',
      '#options' => array(
        'default' => t('Ranking (default)'),
        'alphabetical' => t('Alphabetic'),
        'aphabetical_reverse' => t('Alphabetic (reverse)'),
        'numeric' => t('Numeric'),
        'numeric_reverse' => t('Numeric (reverse)'),
      ),
      '#default_value' => isset($facet['sorting']) ? $facet['sorting'] : 'default',
    );

    $form['ding_facetbrowser_facets'][$i]['weight'] = array(
      '#type' => 'weight',
      '#title' => t('Weight'),
      '#default_value' => $facet['weight'],
      '#title_display' => 'invisible',
      '#attributes' => array('class' => array('facet-weight')),
    );

    $form['ding_facetbrowser_facets'][$i]['delete'] = array(
      '#type' => 'link',
      '#title' => t('delete'),
      '#href' =>  'admin/config/ting/facets/' . $facet['name'] . '/delete',
      '#options' => array('attributes' => array('title' => t('Delete facet.'))),
    );

    $i++;
  }

  $form['ding_facetbrowser_facets'][$i]['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Facet id'),
    '#default_value' => '',
  );

  $form['ding_facetbrowser_facets'][$i]['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => '',
  );

  $form['ding_facetbrowser_facets'][$i]['sorting'] = array(
    '#type' => 'select',
    '#title' => t('Facet name sorting'),
    '#options' => array(
      'default' => t('Ranking (default)'),
      'alphabetical' => t('Alphabetic'),
      'aphabetical_reverse' => t('Alphabetic (reverse)'),
      'numeric' => t('Numeric'),
      'numeric_reverse' => t('Numeric (reverse)'),
    ),
    '#default_value' => 'default',
  );

  $form['ding_facetbrowser_facets'][$i]['weight'] = array(
    '#type' => 'weight',
    '#title' => t('Weight'),
    '#default_value' => 10,
    '#attributes' => array('class' => array('facet-weight')),
  );
  $i++;

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save changes'),
  );

  return $form;
}

/**
 * Submit handler for ding_facetbrowser_settings();
 */
function ding_facetbrowser_settings_submit($form, &$form_state) {
  $facets = $form_state['values']['ding_facetbrowser_facets'];
  foreach ($facets as $key => $facet) {
    if (empty($facet['name'])) {
      unset($facets[$key]);
    }
  }
  usort($facets, 'drupal_sort_weight');
  variable_set('ding_facetbrowser_facets', $facets);
  variable_set('ding_facetbrowser_showcount', $form_state['values']['ding_facetbrowser_showcount']);
  variable_set('ding_facetbrowser_number_of_terms', $form_state['values']['ding_facetbrowser_number_of_terms']);
  drupal_set_message(t('The configuration options have been saved.'));
}

/**
 * Returns HTML for facets admin form.
 */
function theme_ding_facetbrowser_settings($variables) {
  $form = $variables['form'];
  $map = array('disabled' => t('Disabled'), 'enabled' => t('Enabled'));

  $rows = array();

  drupal_add_tabledrag('facets', 'order', 'sibling', 'facet-weight');

  foreach (element_children($form['ding_facetbrowser_facets']) as $key) {
    $facet = &$form['ding_facetbrowser_facets'][$key];
    $row = array();
    $row[] = drupal_render($facet['name']);
    $row[] = drupal_render($facet['title']);
    $row[] = drupal_render($facet['sorting']);
    $row[] = drupal_render($facet['weight']);
    $row[] = drupal_render($facet['delete']);
    $rows[] = array(
      'data' => $row,
      'class' => array('draggable'),
    );
  }

  $header = array(t('Name'), t('Title'), t('Facet name sorting'), t('Weight'), t('Operations'));
  $output = theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'facets')));
  $output .= drupal_render($form['actions']);
  $output = drupal_render_children($form) . $output;

  return $output;
}

/**
 *
 */
function ding_facetbrowser_delete_facet($form_id, $form_state, $facet_id) {
  $form['facet_id'] = array(
    '#type' => 'value',
    '#value' => $facet_id,
  );
  return confirm_form($form, t("Are you sure you want to delete @facet?", array('@facet' => $facet_id)), 'admin/config/ting/facets');
}

/**
 *
 */
function ding_facetbrowser_delete_facet_submit($form, &$form_state) {
  $facets = variable_get('ding_facetbrowser_facets', array());
  foreach ($facets as $key => $facet) {
    if ($facet['name'] == $form_state['values']['facet_id']) {
      unset($facets[$key]);
    }
  }
  variable_set('ding_facetbrowser_facets', $facets);
  drupal_set_message(t('@facet deleted.', array('@facet' => $form_state['values']['facet_id'])));
  $form_state['redirect'] = 'admin/config/ting/facets';
}
