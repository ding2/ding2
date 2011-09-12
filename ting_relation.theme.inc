<?php
/**
 * @file
 * Theming functions for ting_relation.
 */

/**
 * Preprocess variables for ting_relation.tpl.php.
 */
function template_preprocess_ting_relation(&$variables) {
  $object = $variables['object'] = $variables['elements']['#object'];
  $relation = $variables['relation'] = $variables['elements']['#relation'];

  $variables['classes_array'][] = 'ting-relation-' . drupal_html_class($relation->type);
  $variables['type_title'] = $variables['elements']['#title'];
  $variables['title'] = check_plain($object->title);
  if ($relation->type == 'isPartOfManifestation') {
    $variables['content']['body'] = ting_object_view($object, 'teaser');
  }
  elseif ($relation->type == 'hasReview') {
    if (!empty($object->reply->record['dc:description'][''][0])) {
      $variables['content']['body'] = array(
        '#markup' => filter_xss_admin($object->reply->record['dc:description'][''][0]),
      );
    }
  }
  else {
    $variables['content']['body'] = array(
      '#markup' => filter_xss_admin($object->abstract),
    );
  }

  $variables['online_url'] = isset($object->online_url) ? l($object->online_url, $object->online_url) : FALSE;
}
