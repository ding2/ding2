<?php

/**
 * @file
 * Callbacks for a pushing to Mongo through REST API.
 */

/**
 * Call a REST service method.
 *
 * @param  string $method
 * @param  array  $body
 * @return mixed  response object or NULL.
 */
function mobilesearch_rest_service_call($method, $body = array()) {
  $service_url = variable_get('mobilesearch_rest_url', '');
  $agency_id = variable_get('mobilesearch_rest_agency_id', '100000');
  $key = variable_get('mobilesearch_rest_key', NULL);
  $debug = variable_get('mobilesearch_rest_debug', FALSE);
  if (empty($service_url) || empty($agency_id) || empty($key)) {
    watchdog('rest_plugin', "Service doesn't configured. Please !configure_url it first.", array('!configure_url' => l(t('configure'), 'admin/config/mobilesearch/content-export/plugin')), WATCHDOG_ERROR);
    return NULL;
  }
  $instance = new \NationalStorageComponent\NationalStorage($service_url);

  $request = array(
    'credentials' => array(
      'agencyId' => $agency_id,
      'key' => sha1($agency_id . $key),
    ),
    'body' => $body,
  );
  if (!method_exists($instance, $method)) {
    watchdog('rest_plugin', 'You tried to call a undefined method %method of a service.', array('%method' => $method), WATCHDOG_ERROR);
    return NULL;
  }
  try {
    $instance->$method($request);
    $response = $instance->getResponse();
  }
  catch (Exception $e) {
    watchdog_exception('rest_service', $e);
  }

  if ($debug) {
    watchdog('rest_plugin', 'Method: <strong>!method</strong>. Request: <pre>!request</pre>Response: <pre>!response</pre>', array('!method' => $method, '!request' => var_export($request, TRUE), '!response' => var_export($response, TRUE)), WATCHDOG_DEBUG);
  }

  return $response;
}

/**
 * Returns differences agency ids between changed and unchanged nodes.
 *
 * @param  object $node     Changed node.
 * @param  mixed  $original Unchanged node or NULL.
 * @return array
 *  An associative array with the following contents:
 *  <code>
 *  [
 *    to_add: [],
 *    to_update: [],
 *    to_delete: []
 *  ]
 *  </code>
 */
function mobilesearch_rest_node_agency_diff($node, $original = NULL, $op = NULL) {
  $result = array(
    'to_add' => array(),
    'to_update' => array(),
    'to_delete' => array(),
  );

  $agency_id = variable_get('mobilesearch_rest_agency_id', '100000');
  if ($agency_id && $op) {
    switch ($op) {
      case 'hook_node_insert':
        $result['to_add'][] = $agency_id;
        return $result;
      case 'hook_node_update':
        $result['to_update'][] = $agency_id;
        return $result;
      case 'hook_node_delete':
        $result['to_delete'][] = $agency_id;
        return $result;
    }
  }

  $node_realm = array();
  if (!empty($node->field_realm[LANGUAGE_NONE])) {
    foreach ($node->field_realm[LANGUAGE_NONE] as $row) {
      $term = taxonomy_term_load($row['tid']);
      if (!empty($term->field_agency_id[LANGUAGE_NONE][0]['value'])) {
        $agency_id = $term->field_agency_id[LANGUAGE_NONE][0]['value'];
        $node_realm[] = $agency_id;
      }
    }
  }
  $orig_realm = array();
  if (is_object($original)) {
    if (!empty($original->field_realm[LANGUAGE_NONE])) {
      foreach ($original->field_realm[LANGUAGE_NONE] as $row) {
        $term = taxonomy_term_load($row['tid']);
        if (!empty($term->field_agency_id[LANGUAGE_NONE][0]['value'])) {
          $agency_id = $term->field_agency_id[LANGUAGE_NONE][0]['value'];
          $orig_realm[] = $agency_id;
        }
      }
    }
  }

  $result['to_add'] = array_diff($node_realm, $orig_realm);
  $result['to_update'] = array_diff($node_realm, $result['to_add']);
  $result['to_delete'] = array_diff($orig_realm, $node_realm);

  return $result;
}

/**
 * Config form callback for a REST plugin.
 */
function mobilesearch_rest_config_form($form, &$form_state) {
  $form['mobilesearch_rest_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Service URL'),
    '#default_value' => variable_get('mobilesearch_rest_url', ''),
    '#description' => t('URL to service (trailing slash needed).'),
    '#required' => TRUE,
  );
  $ting_agency = variable_get('ting_agency', '100000');
  $agency_id = variable_get('mobilesearch_rest_agency_id', '');
  if ($ting_agency != $agency_id) {
    drupal_set_message(t('T!NG agency ID %ting_agency does not match REST plugin agency ID %agency_id', array(
      '%ting_agency' => $ting_agency,
      '%agency_id' => $agency_id,
    )), 'warning');
  }
  $form['mobilesearch_rest_agency_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Agency ID'),
    '#default_value' => variable_get('mobilesearch_rest_agency_id', $ting_agency),
    '#required' => TRUE,
  );
  $form['mobilesearch_rest_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Key'),
    '#default_value' => variable_get('mobilesearch_rest_key', NULL),
    '#required' => TRUE,
  );
  $form['mobilesearch_rest_debug'] = array(
    '#type' => 'checkbox',
    '#title' => t('Debug'),
    '#default_value' => variable_get('mobilesearch_rest_debug', FALSE),
    '#description' => t('Store debug data in watchdog.'),
  );

  return $form;
}

/**
 * Validate handler for REST plugin configuration form.
 */
function mobilesearch_rest_config_form_validate($form, &$form_state) {
  $values = $form_state['values'];
  $test_result = mobilesearch_rest_test_service($values);
  if (!$test_result) {
    form_set_error('mobilesearch_rest_url', t('Problem connecting to the service. Please check your settings.'));
  }
}

/**
 * Node editing form alter callback.
 */
function mobilesearch_rest_node_form(&$form, &$form_state) {
  $types = _ding_mobilesearch_types();
  if (in_array($form['type']['#value'], array_keys($types), TRUE)) {
    $form['actions']['submit']['#submit'][] = 'mobilesearch_rest_node_submit';
  }
}

/**
 * Submit handler for a node editing form.
 */
function mobilesearch_rest_node_submit($form, &$form_state) {
  if (!empty($form_state['values']['flag'])) {
    $flags = $form_state['values']['flag'];
    if (isset($flags['push_to_mongo'])) {
      $node = $form_state['node'];

      $config = array(
        'mobilesearch_rest_url' => variable_get('mobilesearch_rest_url', ''),
        'mobilesearch_rest_agency_id' => variable_get('mobilesearch_rest_agency_id', '100000'),
        'mobilesearch_rest_key' => variable_get('mobilesearch_rest_key', NULL),
      );
      $test_result = mobilesearch_rest_test_service($config);
      if (!$test_result) {
        drupal_set_message(t('Problem connecting to the REST service. We have unchecked your "Push to Mongo" flag. Please check your !settings.',
          array('!settings' => l(t('settings'), 'admin/config/mobilesearch/content-export/plugin'))), 'warning');
        global $user;
        $flag = flag_get_flag('push_to_mongo');
        $flag->remember_content($node->nid, $node);
        flag('unflag', 'push_to_mongo', $node->nid, $user);
      }

      $is_new = is_null($form_state['values']['vid']);
      $types = _ding_mobilesearch_types();
      $plugin = $types[$node->type];
      if (!empty($plugin['exec_callback']) && function_exists($plugin['exec_callback'])) {
        if (!$is_new) {
          $plugin['exec_callback']('hook_node_delete', 'node', $node);
        }
        if ($flags['push_to_mongo']) {
          $plugin['exec_callback']('hook_node_insert', 'node', $node);
        }
      }
    }
  }
}

/**
 * Plugin execute callback.
 */
function mobilesearch_rest_exec($op, $entity_type, $entity) {
  // Export menu links.
  if ($entity_type == 'menu_link') {
    $method_mapping = array(
      'hook_menu_link_insert' => 'addMenu',
      'hook_menu_link_update' => 'updateMenu',
      'hook_menu_link_delete' => 'deleteMenu',
    );

    if (!preg_match('/(main|left)/', $entity['menu_name'], $matches)) {
      return;
    }
    $type = $matches[1] . '_menu';

    $agency_id = variable_get('mobilesearch_menu_agency_id__' . $entity['menu_name'], 0);
    $request_body = array(
      'mlid' => $entity['mlid'],
      'agency' => $agency_id,
      'type' => $type,
      'name' => $entity['link_title'],
      'url' => '/' . $entity['link_path'],
      'order' => $entity['weight'],
    );
    mobilesearch_rest_service_call($method_mapping[$op], $request_body);
  }
  // Export content through node hooks.
  elseif ($entity_type == 'node') {
    switch ($op) {
      case 'hook_node_insert':
        $diff = mobilesearch_rest_node_agency_diff($entity, NULL, $op);
        break;
      case 'hook_node_update':
        $original = isset($entity->original) ? $entity->original : NULL;
        $diff = mobilesearch_rest_node_agency_diff($entity, $original, $op);
        break;
      case 'hook_node_delete':
        $original = clone $entity;
        $entity->field_realm = array();
        $diff = mobilesearch_rest_node_agency_diff($entity, $original, $op);
        break;
    }

    $mapping = module_invoke_all('mobilesearch_node_export_mapping', $entity);
    $request_body = array(
      'nid' => $entity->nid,
      'agency' => NULL,
      'type' => $entity->type,
    );
    if (isset($mapping['special']) && is_array($mapping['special'])) {
      $request_body = array_merge($request_body, $mapping['special']);
    }
    $request_body['fields'] = $mapping['fields'];
    $request_body['taxonomy'] = $mapping['taxonomy'];

    foreach ($diff['to_add'] as $agency_id) {
      $request_body['agency'] = $agency_id;
      mobilesearch_rest_service_call('addContent', $request_body);
    }
    foreach ($diff['to_update'] as $agency_id) {
      $request_body['agency'] = $agency_id;
      $response = mobilesearch_rest_service_call('addContent', $request_body);
      if (!$response || (is_object($response['response']) && $response['response']->status == FALSE)) {
        mobilesearch_rest_service_call('updateContent', $request_body);
      }
    }
    foreach ($diff['to_delete'] as $agency_id) {
      $request_body['agency'] = $agency_id;
      mobilesearch_rest_service_call('deleteContent', $request_body);
    }
  }
  // Export content through workflow hook.
  elseif ($entity_type == 'workflow') {
    $os_nid = $entity->field_os_node[LANGUAGE_NONE][0]['nid'];
    if ($os_nid) {
      $os_node = node_load($os_nid);
      $mapping = module_invoke_all('mobilesearch_node_export_mapping', $entity);
      $diff = mobilesearch_rest_node_agency_diff($os_node);
      foreach ($diff['to_add'] as $agency_id) {
        $request_body = array(
          'nid' => $os_node->nid,
          'agency' => $agency_id,
          'type' => $os_node->type,
        );
        if (isset($mapping['special']) && is_array($mapping['special'])) {
          $request_body = array_merge($request_body, $mapping['special']);
        }
        $request_body['fields'] = $mapping['fields'];
        $request_body['taxonomy'] = $mapping['taxonomy'];

        mobilesearch_rest_service_call('addContent', $request_body);
      }
    }
  }
}

/**
 * Test service connection.
 * @param array $config
 *   An array with the following keys:
 *   - mobilesearch_rest_url: Url to REST service.
 *   - mobilesearch_rest_agency_id: Agency ID.
 *   - mobilesearch_rest_key: Service key.
 * @return boolean
 */
function mobilesearch_rest_test_service($config = array()) {
  $service_url = $config['mobilesearch_rest_url'];
  $agency_id = $config['mobilesearch_rest_agency_id'];
  $key = $config['mobilesearch_rest_key'];

  $instance = new \NationalStorageComponent\NationalStorage($service_url);

  $body = array(
    'nid' => -1,
    'agency' => $agency_id,
    'type' => 'ding_news',
  );
  $request = array(
    'credentials' => array(
      'agencyId' => $agency_id,
      'key' => sha1($agency_id . $key),
    ),
    'body' => $body,
  );
  $method = 'addContent';
  if (!method_exists($instance, $method)) {
    return FALSE;
  }
  try {
    /**
     * @todo Should write special method for testing the service.
     * Current way (add test record in Content and then delete it) is excess.
     */
    $instance->$method($request);
    $response = $instance->getResponse();
    $method = 'deleteContent';
    $instance->$method($request);
  }
  catch (Exception $e) {
    watchdog_exception('rest_service_test', $e);
    return FALSE;
  }
  return $response['status'];
}
