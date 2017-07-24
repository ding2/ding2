<?php
/**
 * @file
 * Represents configuration and settings form.
 */

/**
 * Form handler of configuration page.
 */
function ding_mkws_service_settings_form($form, $form_state) {
  $settings = variable_get('ding_mkws_settings', array());

  $form['pz2'] = array(
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#title' => t('Pazpar2 settings'),
    '#tree' => TRUE,
  );

  $form['pz2']['url'] = array(
    '#type' => 'textfield',
    '#title' => t('Url of service'),
    '#description' => t('Full url of remote service'),
    '#required' => TRUE,
    '#default_value' => isset($settings['url']) ? $settings['url'] : NULL,
  );

  $form['pz2']['user'] = array(
    '#type' => 'textfield',
    '#title' => t('Service Proxy username'),
    '#description' => t('Service Proxy username'),
    '#required' => TRUE,
    '#default_value' => isset($settings['user']) ? $settings['user'] : NULL,
  );

  $form['pz2']['password'] = array(
    '#type' => 'textfield',
    '#title' => t('Service Proxy password'),
    '#description' => t('Service Proxy password'),
    '#required' => TRUE,
    '#default_value' => isset($settings['password']) ? $settings['password'] : NULL,
  );

  $form['pz2']['proxy'] = array(
    '#type' => 'textfield',
    '#title' => t('Pazpar2/Service Proxy URL or path'),
    '#description' => t('URL that takes Pazpar2 commands via HTTP, can be a relative path eg. for httpd proxying'),
    '#required' => TRUE,
    '#default_value' => isset($settings['proxy']) ? $settings['proxy'] : NULL,
  );

  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#validate' => array('ding_mkws_service_settings_form_validate'),
    '#submit' => array('ding_mkws_service_settings_form_submit'),
  );

  return $form;
}

/**
 * Validate handler for pz2 settings form.
 */
function ding_mkws_service_settings_form_validate($form, &$form_state) {
  $pz2 = $form_state['values']['pz2'];

  if (!valid_url($pz2['url'], TRUE)) {
    form_set_error('pz2][url', t('Enter valid url.'));
  }

  if (!valid_url($pz2['proxy'], FALSE)) {
    form_set_error('pz2][proxy', t('Enter valid url for proxy.'));
  }
}

/**
 * Submit handler for saving pz2 settings.
 */
function ding_mkws_service_settings_form_submit($form, &$form_state) {
  $pz2 = $form_state['values']['pz2'];
  variable_set('ding_mkws_settings', $pz2);
  drupal_set_message(t('Your settings have been saved.'));
}

/**
 * Form handler of widget configuration.
 */
function ding_mkws_widget_settings_form($form, $form_state) {
  $form['#tree'] = TRUE;
  $settings = variable_get('ding_mkws_global', array());

  $resources = _ding_mkws_process_resources();
  $form['resources'] = array(
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#title' => t('Available resources'),
  );
  $form['resources']['values'] = array(
    '#type' => 'checkboxes',
    '#options' => $resources,
    '#default_value' => !empty($settings['resources']['values']) ? $settings['resources']['values'] : array(),
  );

  $form['opac'] = array(
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#title' => t('OPAC'),
  );

  $items = variable_get('ding_mkws_panes', array());
  foreach ($items as $key => $item) {
    $form['opac'][$key] = array(
      '#type' => 'fieldset',
      '#collapsible' => FALSE,
      '#title' => t('@title widget on @item', array('@title' => $item['title'], '@item' => $item['location'])),
    );

    $form['opac'][$key]['show'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show @title widget on @item', array('@title' => drupal_strtolower($item['title']), '@item' => drupal_strtolower($item['location']))),
      '#default_value' => !empty($settings['opac'][$key]['show']) ? $settings['opac'][$key]['show'] : NULL,
    );

    $form['opac'][$key]['toggle_title'] = array(
      '#type' => 'checkbox',
      '#title' => t('Change widget headline'),
      '#default_value' => !empty($settings['opac'][$key]['toggle_title']) ? $settings['opac'][$key]['toggle_title'] : NULL,
    );

    $form['opac'][$key]['widget_headline'] = array(
      '#type' => 'textfield',
      '#title' => t('Widget headline'),
      '#default_value' => !empty($settings['opac'][$key]['widget_headline']) ? $settings['opac'][$key]['widget_headline'] : '',
      '#states' => array(
        'visible' => array(
          'input[name="opac[' . $key . '][toggle_title]"]' => array(
            'checked' => TRUE,
          ),
        ),
      ),
    );

    $form['opac'][$key]['amount'] = array(
      '#type' => 'textfield',
      '#title' => t('Amount items in the widget'),
      '#default_value' => !empty($settings['opac'][$key]['amount']) ? $settings['opac'][$key]['amount'] : 10,
      '#element_validate' => array('element_validate_integer_positive'),
    );

    $options = array();
    if (!empty($settings)) {
      foreach ($settings['resources']['values'] as $value) {
        if ($value) {
          $options[$value] = $resources[$value];
        }
      }
    }
    $form['opac'][$key]['resources'] = array(
      '#type' => 'select',
      '#multiple' => TRUE,
      '#options' => $options,
      '#title' => t("LBR's to search for this widget"),
      '#default_value' => !empty($settings['opac'][$key]['resources']) ? $settings['opac'][$key]['resources'] : NULL,
    );

    $form['opac'][$key]['maxrecs'] = array(
      '#type' => 'textfield',
      '#title' => t('Maxrecs'),
      '#default_value' => !empty($settings['opac'][$key]['maxrecs']) ? $settings['opac'][$key]['maxrecs'] : '',
    );
  }

  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Submit handler of widget configuration.
 */
function ding_mkws_widget_settings_form_submit($form, $form_state) {
  $items = variable_get('ding_mkws_panes', array());

  ctools_include('plugins');
  ctools_get_plugins('page_manager', 'task_handlers', 'panel_context');

  $values = $form_state['values'];
  foreach ($values['opac'] as $key => $variable) {
    $task = page_manager_get_task($items[$key]['task_name']);
    $handlers = page_manager_load_task_handlers($task);
    foreach ($handlers as $handler_name => &$handler) {
      if (strpos($handler_name, $items[$key]['task_name'] . '_panel_context') !== FALSE) {
        $display = panels_panel_context_get_display($handler);
        foreach ($display->content as &$pane) {
          $pane_scope = (!empty($pane->configuration['scope'])) ? $pane->configuration['scope'] : NULL;
          $scope = $items[$key]['scope'];
          if ($pane->type == 'ding_mkws_item_list' && $pane_scope == $scope) {
            // Enable panes.
            if ($values['opac'][$key]['show'] && !$pane->shown) {
              $pane->shown = TRUE;
              panels_save_display($display);
            }
            // Disable panes.
            elseif (!$values['opac'][$key]['show'] && $pane->shown) {
              $pane->shown = FALSE;
              panels_save_display($display);
            }
          }
        }
      }
    }

    $values['opac'][$key]['title'] = $items[$key]['title'];
    if ($values['opac'][$key]['toggle_title']) {
      $values['opac'][$key]['title'] = $values['opac'][$key]['widget_headline'];
    }
    $values['opac'][$key]['task_name'] = $items[$key]['task_name'];
    $values['opac'][$key]['scope'] = $items[$key]['scope'];
  }

  variable_set('ding_mkws_global', $values);
  drupal_set_message(t('Your settings have been saved.'));
}

/**
 * Form handler of content types configuration page.
 */
function ding_mkws_types_settings_form($form, &$form_state) {
  $settings = variable_get('ding_mkws_types', array());
  $allowed = array(
    'ding_page',
    'ding_news',
    'ding_event',
    'ding_campaign',
  );
  $options = array();
  $types = node_type_get_types();
  foreach ($types as $key => $type) {
    if (in_array($key, $allowed)) {
      $options[$key] = $type->name;
    }
  }
  $form['types'] = array(
    '#type' => 'checkboxes',
    '#options' => $options,
    '#default_value' => $settings,
    '#title' => t('Choose content types.'),
    '#description' => t('Content types which should have MKWS node widget.'),
  );

  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  return $form;
}

/**
 * Submit handler for  content types configuration page.
 */
function ding_mkws_types_settings_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  $base = field_info_field('field_mkws_node_widget');
  if (!$base) {
    $base = array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_mkws_node_widget',
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => 0,
      'module' => 'ding_mkws',
      'settings' => array(
        'profile2_private' => FALSE,
      ),
      'translatable' => 0,
      'type' => 'ding_mkws_node',
    );
    field_create_field($base);
  }

  foreach ($values['types'] as $type => $value) {
    $instance = field_info_instance('node', 'field_mkws_node_widget', $type);
    if ($value) {
      if (!$instance) {
        $instance = array(
          'bundle' => $type,
          'deleted' => 0,
          'description' => '',
          'display' => array(
            'default' => array(
              'label' => 'above',
              'module' => 'ding_mkws',
              'settings' => array(),
              'type' => 'ding_mkws_node_formatter_default',
              'weight' => 11,
            ),
            'full' => array(
              'label' => 'hidden',
              'module' => 'ding_mkws',
              'settings' => array(),
              'type' => 'ding_mkws_node_formatter_default',
              'weight' => 11,
            ),
            'search_result' => array(
              'label' => 'hidden',
              'settings' => array(),
              'type' => 'hidden',
              'weight' => 0,
            ),
            'teaser' => array(
              'label' => 'hidden',
              'settings' => array(),
              'type' => 'hidden',
              'weight' => 0,
            ),
            'teaser_highlight' => array(
              'label' => 'hidden',
              'settings' => array(),
              'type' => 'hidden',
              'weight' => 0,
            ),
          ),
          'entity_type' => 'node',
          'field_name' => 'field_mkws_node_widget',
          'label' => 'Content for LBR',
          'required' => 0,
          'settings' => array(
            'user_register_form' => FALSE,
          ),
          'widget' => array(
            'active' => 0,
            'module' => 'ding_mkws',
            'settings' => array(),
            'type' => 'ding_mkws_node_widget_default',
            'weight' => 41,
          ),
        );
        field_create_instance($instance);
      }
    }
    elseif ($instance) {
      field_delete_instance($instance);
    }
  }
  variable_set('ding_mkws_types', $values['types']);
  drupal_set_message(t('Your settings have been saved.'));
  $form_state['rebuild'] = TRUE;
}
