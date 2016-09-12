<?php

/**
 * @file
 * MKWS Widget for inserting on a panel.
 */

/**
 * General ctools plugin settings.
 */
$plugin = array(
  'single' => TRUE,
  'title' => t('MKWS widget pane'),
  'description' => t('Add MKWS wiget as a pane.'),
  'category' => t('Ding!'),
  'render callback' => 'ding_mkws_panel_widget_render',
  'edit form' => 'ding_mkws_panel_widget_edit_form',
);

/**
 * MKWS pane widget settings form.
 */
function ding_mkws_panel_widget_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $form['term'] = array(
    '#type' => 'textfield',
    '#title' => t('Search term'),
    '#default_value' => $conf['term'],
    '#description' => t('Search term to search.'),
  );

  $form['amount'] = array(
    '#type' => 'textfield',
    '#title' => t('Amount of items'),
    '#default_value' => $conf['amount'],
    '#description' => t('Amount of items to display.'),
  );

  $resources = _ding_mkws_process_resources();
  $form['resources'] = array(
    '#type' => 'select',
    '#title' => t('Resources:'),
    '#default_value' => $conf['resources'],
    '#options' => $resources,
    '#empty_option' => t('Choose LBRs'),
  );

  return $form;
}

/**
 * The submit form stores the data in $conf.
 */
function ding_mkws_panel_widget_edit_form_submit($form, &$form_state) {
  foreach (element_children($form) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
}

/**
 * MKWS pane widget renderer.
 */
function ding_mkws_panel_widget_render($subtype, $conf, $args, $context) {
  $pane = new stdClass();

  $params = array(
    'type' => $subtype,
    'term' => (!empty($conf)) ? $conf['term'] : '',
    'amount' => (!empty($conf)) ? $conf['amount'] : '0',
    'resources' => (!empty($conf)) ? $conf['resources'] : array(),
  );

  $hash = md5(implode('', $params));

  $pane->content['#markup'] = "<div data-hash='{$hash}' 
                                data-process='ProcessDataForPaneWidget' 
                                data-template='dingMkwsPaneWidget' 
                                class='ding-mkws-widget ding-mkws-panel-widget'>
                               </div>";
  $pane->content['#attached'] = array(
    'css' => array(
      drupal_get_path('module', 'ding_mkws') . '/css/ding_mkws.css',
    ),
    'js' => array(
      drupal_get_path('module', 'ding_mkws') . '/js/ding_mkws.js',
      array(
        'type' => 'setting',
        'data' => array(
          $hash => $params,
        ),
      ),
    ),
  );

  return $pane;
}
