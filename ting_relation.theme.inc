<?php

/**
 * @file
 * Theming functions for ting_relation.
 */

/**
 *
 */
function template_preprocess_ting_relation(&$variables) {
  $relation = $variables['object'] = $variables['elements']['#object'];

  $variables['classes_array'][] = 'ting-relation-' . drupal_html_class($relation->relationType);
  $variables['type_title'] = $variables['elements']['#title'];
  $variables['title'] = check_plain($relation->title);
  $variables['content'] = filter_xss_admin($relation->abstract);

  $variables['online_url'] = l($relation->online_url, $relation->online_url);
}