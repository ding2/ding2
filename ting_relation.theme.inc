<?php
/**
 * @file
 * Theming functions for ting_relation.
 */

/**
 * Preprocess variables for ting_relation.tpl.php.
 */
function template_preprocess_ting_relation(&$variables) {
  $relation = $variables['object'] = $variables['elements']['#object'];

  $variables['classes_array'][] = 'ting-relation-' . drupal_html_class($relation->relationType);
  $variables['type_title'] = $variables['elements']['#title'];
  $variables['title'] = check_plain($relation->title);
  if ($relation->relationType == 'isPartOfManifestation') {
    $variables['content']= ting_object_view($relation, 'search_result');
  }
  elseif ($relation->relationType == 'hasReview') {
    $variables['content'] = filter_xss_admin($relation->reply->record['dc:description'][''][0]);
  }
  else {
    $variables['content'] = filter_xss_admin($relation->abstract);
  }

  if (in_array('docbook', $relation->reply->formatsAvailable)) {
    $variables['docbook_link'] = l(t('Full-text version'), 'ting/object/' . $relation->ding_entity_id . '/fulltext');
  }
  else {
    $variables['docbook_link'] = '';
  }

  $variables['online_url'] = isset($relation->online_url) ? l($relation->online_url, $relation->online_url) : FALSE;
}

