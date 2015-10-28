<?php
/**
 * @file
 * Theming functions for ting_relation.
 */

/**
 * Implements hook_preprocess_ting_relation_groups().
 *
 * Default implementation of the preprocess function, which simple copies some
 * values from element into variables.
 */
function template_preprocess_ting_relation_groups(&$variables) {
  $element = $variables['elements'];

  // Find information about the field.
  $variables['label_hidden'] = $element['#label_display'] == 'hidden' ? TRUE : FALSE;
  $variables['title'] = $element['#title'];
  $variables['view_mode'] = $element['#view_mode'];

  // Get relations for easier access in the tpl.
  $variables['groups'] = $element['#groups'];
}

/**
 * Implements hook_preprocess_ting_relations().
 *
 * Ensures that attributes are formatted correctly.
 */
function template_preprocess_ting_relations(&$variables) {
  $variables['attributes_array'] += $variables['attributes'];
  $variables['attributes'] = drupal_attributes($variables['attributes']);
}

/**
 * Implements hook_preprocess_ting_relation().
 *
 * Ensures that attributes are formatted correctly.
 */
function template_preprocess_ting_relation(&$variables) {
  $variables['attributes_array'] += $variables['attributes'];
  $variables['attributes'] = drupal_attributes($variables['attributes']);
}
