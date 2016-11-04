<?php
/**
 * @file
 * Content type plugin for weekly opening hours.
 */

/**
 * Array describing the plugin to CTools/Panels.
 */
$plugin = array(
  'title' => t('Weekly opening hours'),
  'description' => t('Show weekly opening hours for a library.'),
  'single' => TRUE,
  'content_types' => array('list'),
  'category' => t('Ding!'),
  'required context' => new ctools_context_optional(t('Node'), 'node'),
);

/**
 * Render the block.
 */
function ding_ddbasic_opening_hours_weekly_opening_hours_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  if (!empty($context->data)) {
    $node = $context->data;
  }
  else {
    $node = node_load($conf['node']);
  }

  if (empty($node)) {
    return $block;
  }

  $block->title = t('Opening hours');
  $block->content = theme('ding_ddbasic_opening_hours_week', array(
    'node' => $node,
    'categories' => $conf['categories'],
  ));

  return $block;
}

/**
 * Settings form for the content type.
 */
function ding_ddbasic_opening_hours_weekly_opening_hours_content_type_edit_form($form, &$form_state) {
  $nodes = db_select('node', 'n')
    ->fields('n', array('nid', 'title'))
    ->condition('n.type', 'ding_library')
    ->execute()->fetchAllKeyed();

  $form['node'] = array(
    '#type' => 'select',
    '#title' => t('Node ID'),
    '#options' => $nodes,
    '#default_value' => !(empty($form_state['conf']['node'])) ? $form_state['conf']['node'] : NULL,
    '#states' => array(
      'visible' => array(
        ':input[name="context"]' => array('value' => 'empty'),
      ),
      'required' => array(
        ':input[name="context"]' => array('value' => 'empty'),
      ),
    ),
  );

  $options = array(
    '_null' => t('Opening hours'),
  );
  $machine_name = variable_get('opening_hours_category_vocabulary_' . 'ding_library', 0);
  if (!empty($machine_name)) {
    $vocabulary = taxonomy_vocabulary_machine_name_load($machine_name);

    if ($vocabulary) {
      foreach (taxonomy_get_tree($vocabulary->vid, 0, 1) as $term) {
        $options[$term->tid] = $term->name;
      }
    }
  }

  $form['categories'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Categories tid'),
    '#options' => $options,
    '#default_value' => !(empty($form_state['conf']['categories'])) ? $form_state['conf']['categories'] : NULL,
  );

  return $form;
}

/**
 * Submit handler for the admin form.
 */
function ding_ddbasic_opening_hours_weekly_opening_hours_content_type_edit_form_submit($form, &$form_state) {
  $form_state['conf']['node'] = $form_state['values']['node'];
  $form_state['conf']['categories'] = array_filter($form_state['values']['categories']);
}
