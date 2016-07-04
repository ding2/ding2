<?php

/**
 * @file
 * Callbacks for a pushing to Mongo through REST API.
 */

/**
 * Call a REST service method.
 *
 * @param string $method
 *   Name of method.
 * @param array $body
 *   Array with request body.
 *
 * @return mixed
 *    response object or NULL.
 */
function ding_mobilesearch_rest_service_call($method, $body = array()) {
  $service_url = variable_get('mobilesearch_rest_url', '');
  $agency_id = variable_get('ting_agency', NULL);
  $key = variable_get('mobilesearch_rest_key', NULL);
  $debug = variable_get('mobilesearch_rest_debug', FALSE);
  if (empty($service_url) || empty($agency_id) || empty($key)) {
    watchdog(
      'rest_plugin',
      "Service doesn't configured. Please !configure_url it first.",
      array(
        '!configure_url' => l(
          t('configure'),
          'admin/config/ding/mobilesearch/content-export'
        ),
      ),
      WATCHDOG_ERROR
    );
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
    watchdog(
      'rest_plugin',
      'You tried to call a undefined method %method of a service.',
      array(
        '%method' => $method,
      ),
      WATCHDOG_ERROR
    );
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
    watchdog(
      'rest_plugin',
      'Method: <strong>!method</strong>. Request: <pre>!request</pre>Response: <pre>!response</pre>',
      array(
        '!method' => $method,
        '!request' => var_export($request, TRUE),
        '!response' => var_export($response, TRUE),
      ),
      WATCHDOG_DEBUG
    );
  }

  return $response;
}

/**
 * Returns differences agency ids between changed and unchanged nodes.
 *
 * @param object $node
 *    Changed node.
 * @param mixed $original
 *    Unchanged node or NULL.
 *
 * @return array
 *    An associative array with the following contents:
 *    <code>
 *    [
 *      to_add: [],
 *      to_update: [],
 *      to_delete: []
 *    ]
 *    </code>
 */
function ding_mobilesearch_rest_node_agency_diff($node, $original = NULL, $op = NULL) {
  $result = array(
    'to_add' => array(),
    'to_update' => array(),
    'to_delete' => array(),
  );

  $agency_id = variable_get('ting_agency', NULL);
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

  return $result;
}

/**
 * Config form callback for a REST plugin.
 */
function ding_mobilesearch_rest_config_form($form, &$form_state) {
  $form['mobilesearch_rest_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Service URL'),
    '#default_value' => variable_get('mobilesearch_rest_url', ''),
    '#description' => t('URL to service (trailing slash needed).'),
    '#required' => TRUE,
  );

  $form['mobilesearch_rest_agency_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Ting Agency ID'),
    '#default_value' => variable_get('ting_agency', NULL),
    '#attributes' => array('disabled' => TRUE),
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
function ding_mobilesearch_rest_config_form_validate($form, &$form_state) {
  $values = $form_state['values'];
  $test_result = ding_mobilesearch_rest_test_service($values);
  if (!$test_result) {
    form_set_error('mobilesearch_rest_url', t('Problem connecting to the service. Please check your settings.'));
  }
}

/**
 * Node editing form alter callback.
 */
function ding_mobilesearch_rest_node_form(&$form, &$form_state) {
  $types = _ding_mobilesearch_types();
  if (in_array($form['type']['#value'], array_keys($types), TRUE)) {
    $form['actions']['submit']['#submit'][] = 'ding_mobilesearch_rest_node_submit';
  }
}

/**
 * Submit handler for a node editing form.
 */
function ding_mobilesearch_rest_node_submit($form, &$form_state) {
  if (!empty($form_state['values']['flag'])) {
    $flags = $form_state['values']['flag'];
    if (isset($flags['push_to_mongo'])) {
      $node = $form_state['node'];

      $config = array(
        'mobilesearch_rest_url' => variable_get('mobilesearch_rest_url', ''),
        'mobilesearch_rest_agency_id' => variable_get('ting_agency', NULL),
        'mobilesearch_rest_key' => variable_get('mobilesearch_rest_key', NULL),
      );
      $test_result = ding_mobilesearch_rest_test_service($config);
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
          call_user_func($plugin['exec_callback'], 'hook_node_delete', 'node', $node);
        }
        if ($flags['push_to_mongo']) {
          call_user_func($plugin['exec_callback'], 'hook_node_insert', 'node', $node);
        }
      }
    }
  }
}

/**
 * Plugin execute callback.
 */
function ding_mobilesearch_rest_exec($op, $entity_type, $entity) {
  if ($entity_type == 'node') {
    switch ($op) {
      case 'hook_node_insert':
        $diff = ding_mobilesearch_rest_node_agency_diff($entity, NULL, $op);
        break;

      case 'hook_node_update':
        $original = isset($entity->original) ? $entity->original : NULL;
        $diff = ding_mobilesearch_rest_node_agency_diff($entity, $original, $op);
        break;

      case 'hook_node_delete':
        $original = clone $entity;
        $entity->field_realm = array();
        $diff = ding_mobilesearch_rest_node_agency_diff($entity, $original, $op);
        break;
    }

    $mapping = module_invoke_all('ding_mobilesearch_node_export_mapping', $entity);
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
      ding_mobilesearch_rest_service_call('addContent', $request_body);
    }
    foreach ($diff['to_update'] as $agency_id) {
      $request_body['agency'] = $agency_id;
      $response = ding_mobilesearch_rest_service_call('addContent', $request_body);
      if (!$response || (is_object($response['response']) && $response['response']->status == FALSE)) {
        ding_mobilesearch_rest_service_call('updateContent', $request_body);
      }
    }
    foreach ($diff['to_delete'] as $agency_id) {
      $request_body['agency'] = $agency_id;
      ding_mobilesearch_rest_service_call('deleteContent', $request_body);
    }
  }
  // Export content through workflow hook.
  elseif ($entity_type == 'workflow') {
    $os_nid = $entity->field_os_node[LANGUAGE_NONE][0]['nid'];
    if ($os_nid) {
      $os_node = node_load($os_nid);
      $mapping = module_invoke_all('ding_mobilesearch_node_export_mapping', $entity);
      $diff = ding_mobilesearch_rest_node_agency_diff($os_node);
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

        ding_mobilesearch_rest_service_call('addContent', $request_body);
      }
    }
  }
}

/**
 * Test service connection.
 *
 * @param array $config
 *   An array with the following keys:
 *   - mobilesearch_rest_url: Url to REST service.
 *   - mobilesearch_rest_agency_id: Agency ID.
 *   - mobilesearch_rest_key: Service key.
 *
 * @return bool
 *   Returns status of response.
 */
function ding_mobilesearch_rest_test_service($config = array()) {
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
    // @todo Should write special method for testing the service.
    // Current way (add test record in Content and then delete it) is excess.
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
