<?php

/**
 * @file
 * Field hook implementations.
 */

/**
 * Implements hook_field_info().
 */
function ting_covers_field_info() {
  return array(
    'ting_cover' => array(
      'label' => t('Ting cover'),
      'description' => t('Cover image from the ADDI service, if any.'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_cover_default',
      'no_ui' => TRUE,
    ),
  );
}

/**
 * Implements hook_field_load().
 */
function ting_covers_field_load($entity_type, $entities, $field, $instances, $langcode, &$items, $age) {
  foreach ($entities as $id => $entity) {
    $items[$id][0] = array(
      'local_id' => $entity->localId,
    );
  }
}

/**
 * Implements hook_widget_info_alter().
 */
function ting_covers_widget_info_alter(&$info) {
  if (isset($info['hidden'])) {
    $info['hidden']['field types'][] = 'ting_cover';
  }
}

/**
 * Implements hook_field_formatter_info().
 */
function ting_covers_field_formatter_info() {
  return array(
    'ting_cover_default' => array(
      'label' => t('Default'),
      'field types' => array('ting_cover'),
      'settings' => array(
        'image_style' => 'medium',
      ),
    )
  );
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function ting_covers_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $element = array();
  
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $image_styles = image_style_options(FALSE);
  $element['image_style'] = array(
    '#title' => t('Image style'),
    '#type' => 'select',
    '#default_value' => $settings['image_style'],
    '#empty_option' => t('None (original image)'),
    '#options' => $image_styles,
  );

  return $element;
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function ting_covers_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $image_styles = image_style_options(FALSE);
  // Unset possible 'No defined styles' option.
  unset($image_styles['']);
  // Styles could be lost because of enabled/disabled modules that defines
  // their styles in code.
  if (isset($image_styles[$settings['image_style']])) {
    $summary = t('Image style: @style', array('@style' => $image_styles[$settings['image_style']]));
  }
  else {
    $summary = t('Original image');
  }
  return $summary;
}

/**
 * Implements hook_field_formatter_view().
 */
function ting_covers_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  foreach ($items as $delta => $item) {
    $element[$delta] = array(
      '#theme' => 'ting_object_cover',
      '#object' => $entity,
      '#image_style' => $display['settings']['image_style'],
      '#attached' => array(
    	'js' => array(drupal_get_path('module', 'ting_covers') . '/js/ting-covers.js'),
    ),
  );

  }
  return $element;
}
