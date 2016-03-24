<?php
/**
 * @file
 * Editorial dashboard administrative interface.
 */

/**
 * Creates an administrative block on the configuration page for grouping
 * various settings.
 *
 * @return string
 *   HTML for the block.
 */
function ding_dashboard_admin_menu_block_page() {
  $item = menu_get_item();
  $content = system_admin_menu_block($item);

  if ($content) {
    $output = theme('admin_block_content', array('content' => $content));
  }
  else {
    $output = t('You do not have any administrative items.');
  }

  return $output;
}

/**
 * Content type selection form.
 *
 * Interface for selecting node types which should be a part
 * of teh editorial system.
 */
function ding_dashboard_admin_content_types($form, $form_state) {
  $node_types = node_type_get_types();
  $node_bundles = array();

  foreach ($node_types as $type) {
    $node_bundles[$type->type] = $type->name;
  }

  $form['editorial_content_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Available node types'),
    '#description' => t('Select which nodes should be a part of editorial system'),
    '#options' => $node_bundles,
    '#default_value' => variable_get('editorial_content_types', array()),
  );
  $form['#submit'][] = 'ding_dashboard_admin_content_types_submit';

  return system_settings_form($form);
}

/**
 * Custom submit handler for content types admin form.
 *
 * Create hidden fields for selected content types that will contain
 * editorial status of the node.
 */
function ding_dashboard_admin_content_types_submit($form, $form_state) {
  $input = $form_state['input'];
  $node_types = array_filter($input['editorial_content_types']);
  $last_setting = array_filter(variable_get('editorial_content_types', array()));

  if (count($node_types) == 0) {
    return;
  }

  $instance_definition = array(
    'label' => 'Editorial status',
    'field_name' => 'field_editorial_status',
    'entity_type' => 'node',
    'default_value' => array(
      array(
        'value' => EDITORIAL_NODE_NEW,
      ),
    ),
    'display' => array(
      'default' => array(
        'label' => 'above',
        'type' => 'hidden',
        'settings' => array(),
        'module' => '',
      ),
    ),
  );

  // For each selected node bundle, create a field instance and attach it.
  foreach ($node_types as $type) {
    if (!field_read_instance('node', 'field_editorial_status', $type)) {
      $instance_definition['bundle'] = $type;

      $t = array(
        '@instance' => $instance_definition['label'],
        '@bundle' => $instance_definition['bundle'],
      );

      $error = FALSE;

      try {
        field_create_instance($instance_definition);
      }
      catch (FieldException $e) {
        $error = TRUE;
        watchdog_exception('editorial', $e, t('Exception thrown when creating field instance @instance for bundle @bundle.'), $t, WATCHDOG_CRITICAL);
        drupal_set_message(t('Error when creating field instance @instance for bundle @bundle.', $t), 'error');
      }

      if (!$error) {
        drupal_set_message(t('Field instance @instance for bundle @bundle created successfully.', $t));
      }
    }
  }

  // For node bundles that are selected first time, reset all their nodes
  // to New editorial status.
  $new_types = array_diff($node_types, $last_setting);
  $altered = ding_dashboard_prepare_nodes($new_types);
  if (is_int($altered)) {
    $t = array(
      '@count' => $altered,
    );
    drupal_set_message(t('@count nodes have been marked to editorial system.', $t));
  }
}
