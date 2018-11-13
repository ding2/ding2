<?php
/**
 * @file
 * Administration interface for nodelist configuration.
 */

/**
 * General settings form.
 */
function ding_nodelist_settings_form() {
  $options = node_type_get_names();

  if (empty($options)) {
    drupal_set_message(t('No content types were found, please add one first.'), 'error', FALSE);
  }

  $form['ding_nodelist_node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Available content types'),
    '#options' => $options,
    '#default_value' => variable_get('ding_nodelist_node_types', array()),
    '#description' => t('Choose content types avaialable for display'),
  );
  // Options as defined by panels/plugins/cache/simple.inc
  $options = drupal_map_assoc(
    array(
      0, 15, 30, 60, 120, 180, 240, 300, 600, 900, 1200, 1800, 3600,
      7200, 14400, 28800, 43200, 86400, 172800, 259200, 345600, 604800),
    'format_interval');

  $form['ding_nodelist_cache_default_time'] = array(
    '#type' => 'select',
    '#options' => $options,
    '#empty' => '<' . t('none') . '>',
    '#title' => t('Default cache life time'),
    '#default_value' => variable_get('ding_nodelist_cache_default_time', DING_NODELIST_CACHE_LIFETIME),
    '#description' => t('Lists will be cached by default for this period of time (seconds)'),
  );

  $form['ding_nodelist_autoscroll_delay'] = array(
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#title' => t('Autoscroll delay'),
    '#description' => t('The delay to show an item for various nodelist widgets (in milliseconds).'),
  );

  $autoscrolling_widgets = array(
    DING_NODELIST_WIDGET_CAROUSEL => array('Carousel', 3000),
  );

  foreach ($autoscrolling_widgets as $widget => $conf) {
    $title = isset($conf[0]) ? check_plain($conf[0]) : '';
    $form['ding_nodelist_autoscroll_delay']['ding_nodelist_' . $widget . '_delay'] = array(
      '#type' => 'textfield',
      '#title' => filter_xss($title),
      '#default_value' => variable_get('ding_nodelist_' . $widget . '_delay', $conf[1]),
      '#size' => 5,
    );
  }

  return system_settings_form($form);
}

/**
 * Template settings form.
 */
function ding_nodelist_templates_form($form, &$form_state) {
  $form['templates'] = array(
    '#type' => 'fieldset',
    '#title' => t('Templates'),
    '#tree' => TRUE,
    '#theme' => 'ding_nodelist_templates_table',
  );

  $templates = _ding_nodelist_get_templates();

  foreach ($templates as $template_name => $template) {
    $form['templates'][$template_name]['template_name'] = array(
      '#type' => 'hidden',
      '#value' => $template_name,
    );

    $form['templates'][$template_name]['title'] = array(
      '#type' => 'textfield',
      '#default_value' => isset($template['title']) ? $template['title'] : '',
      '#size' => 40,
    );

    $ct = node_type_get_names();
    $form['templates'][$template_name]['content_type'] = array(
      '#markup' => isset($ct[$template['content_type']]) ?
      $ct[$template['content_type']] : t('Missing (@ctname)', array('@ctname' => $template['content_type'])),
    );

    $widgets = _ding_nodelist_get_widget_types();
    $form['templates'][$template_name]['widget'] = array(
      '#type' => 'select',
      '#empty_value' => '',
      '#required' => FALSE,
      '#default_value' => isset($template['widget']) ? $template['widget'] : '',
      '#options' => $widgets,
    );

    // Visible in list of templates?
    $form['templates'][$template_name]['visible'] = array(
      '#type' => 'checkbox',
      '#default_value' => $template['status'] == DING_NODELIST_TPL_ACTIVE ? TRUE : FALSE,
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Writes details about found templates.
 */
function ding_nodelist_templates_form_submit($form, &$form_state) {
  foreach ($form_state['values']['templates'] as $template) {
    $tpl_record = array(
      'title' => $template['title'],
      'status' => $template['visible'] ? DING_NODELIST_TPL_ACTIVE : DING_NODELIST_TPL_HIDDEN,
      'widget' => $template['widget'],
    );
    db_update('ding_nodelist_templates')->fields($tpl_record)
      ->condition('filename', $template['template_name'])->execute();
  }

  drupal_set_message(t('Template settings have been saved.'));
}

/**
 * Trim content settings form.
 */
function ding_nodelist_trim_content($form, &$form_state) {
  $form['trim_content'] = array(
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#title' => t('Text truncation in widgets'),
    '#description' => t('Define amount of chars to be shown in each widget type'),
    '#theme' => 'ding_nodelist_trim_text_table',
    '#tree' => TRUE,
  );
  $widgets = _ding_nodelist_widgets_content_trim();
  foreach ($widgets as $widget) {
    $form['trim_content'][$widget]['widget'] = array(
      '#type' => 'hidden',
      '#value' => _ding_nodelist_get_widget_human_name($widget),
    );

    $form['trim_content'][$widget]['title_trim'] = array(
      '#type' => 'textfield',
      '#size' => 3,
      '#default_value' => variable_get('ding_nodelist_' . $widget . '_title_trim', DING_NODELIST_TITLE_SIZE),
    );

    $form['trim_content'][$widget]['teaser_trim'] = array(
      '#type' => 'textfield',
      '#size' => '3',
      '#default_value' => variable_get('ding_nodelist_' . $widget . '_teaser_trim', DING_NODELIST_BODY_SIZE),
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Trim content form submit.
 */
function ding_nodelist_trim_content_submit($form, &$form_state) {
  foreach ($form_state['input']['trim_content'] as $widget => $trim) {
    variable_set('ding_nodelist_' . $widget . '_title_trim', $trim['title_trim']);
    variable_set('ding_nodelist_' . $widget . '_teaser_trim', $trim['teaser_trim']);
  }
  drupal_set_message(t('Trim settings have been saved.'));
}
