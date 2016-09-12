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

  /**
   * Keys of the array $items represent name of the page manager tasks
   *
   * They are created during module install.
   * @see _ding_mkws_create_pane.
   */
  $items = array(
    'search' => t('Search result'),
    'ting_collection' => t('Collection view'),
    'ting_object' => t('Item page'),
  );

  foreach ($items as $key => $title) {
    $form['opac'][$key] = array(
      '#type' => 'fieldset',
      '#collapsible' => FALSE,
      '#title' => $title,
    );

    $form['opac'][$key]['show'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show the widget on @item', array('@item' => drupal_strtolower($title))),
      '#default_value' => !empty($settings['opac'][$key]['show']) ? $settings['opac'][$key]['show'] : NULL,
    );

    $form['opac'][$key]['amount'] = array(
      '#type' => 'textfield',
      '#title' => t('Amount items in the widget'),
      '#default_value' => !empty($settings['opac'][$key]['amount']) ? $settings['opac'][$key]['amount'] : 10,
      '#element_validate' => array('element_validate_integer_positive'),
    );

    $form['opac'][$key]['resources'] = array(
      '#type' => 'select',
      '#multiple' => TRUE,
      '#options' => $resources,
      '#title' => t("LBR's to search for this widget"),
      '#default_value' => !empty($settings['opac'][$key]['resources']) ? $settings['opac'][$key]['resources'] : NULL,
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
  $values = $form_state['values'];
  variable_set('ding_mkws_global', $values);

  ctools_include('plugins');
  ctools_get_plugins('page_manager', 'task_handlers', 'panel_context');

  foreach ($values['opac'] as $key => $variable) {
    $task = page_manager_get_task($key);
    $handlers = page_manager_load_task_handlers($task);
    foreach ($handlers as $handler_name => &$handler) {
      if (strpos($handler_name, $key . '_panel_context') !== FALSE) {
        $display = panels_panel_context_get_display($handler);
        foreach ($display->content as &$pane) {
          if ($pane->type == 'ding_mkws_item_list') {
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
  }
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
  $form_state['rebuild'] = TRUE;
}
