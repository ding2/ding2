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
 * Implements template_preprocess_ting_relation().
 *
 * @see ting_relation.tpl.php
 */
function template_preprocess_ting_relation(&$variables) {
//  $relation = $variables['relation'];
//  switch ($relation->type) {
//    case 'dbcaddi:hasReview':
//      $variables['content'][$ns] = ting_relation_reviews($relations);
//      break;
//
//    case 'dbcaddi:hasSubjectDescription':
//      $variables['content'][$ns] = ting_relation_subjects($relations);
//      break;
//
//    case 'dbcaddi:hasCreatorDescription':
//      $variables['content'][$ns] = ting_relation_creator_description($relations);
//      break;
//
//    case 'isPartOfManifestation':
//      $variables['content'][$ns] = ting_relation_is_part_of_manifestation($relations);
//      break;
//  }
}

function ting_relation_creator_description($relations) {
  $ret = array();

  foreach ($relations as $relation) {
    $ting = $relation['#object'];
    $rel = $relation['#relation'];

    $content = array(
      'type' => $relation['#title'],
      'title' => $rel->object->title,
      'abstract' => filter_xss_admin($ting->abstract),
    );

    if ($ting->creators) {
      $content['byline'] = t('by @author', array('@author' => ting_relation_array2names($ting->creators)));
    }

    // @todo online_url.
    if ($url = $rel->object->online_url) {
      $content['online_url'] = array(
        '#markup' => l($rel->object->ac_source, $url, array('attributes' => array('target' => '_blank'))),
      );
    }

    $ret[] = $content;
  }

  return $ret;
}

function ting_relation_is_part_of_manifestation($relations) {
  $ret = array();
  foreach ($relations as $relation_id => $relation) {
    $content = array();
    $content['type'] = $relation['#title'];
    $related_object = $relation['#relation'];
    $rendered_item = ting_object_view($related_object->object, 'user_list');
    $content['text'] = render($rendered_item);
    $ret[] = $content;
  }

  return $ret;
}

function ting_relation_subjects($relations) {
  $ret = array();

  foreach ($relations as $relation) {
    $content = array();
    $ting = $relation['#object'];
    $rel = $relation['#relation'];

    $content['type'] = $relation['#title'];
    $content['title'] = $rel->object->title;

    if ($ting->creators) {
      $content['byline'] = t('by @author', array('@author' => ting_relation_array2names($ting->creators)));
    }

    $content['abstract'] = filter_xss_admin($ting->abstract);
    $content['text'] = filter_xss_admin($ting->description);

    if ($url = $rel->object->online_url) {
      $content['online_url'] = array(
        '#markup' => l($rel->object->ac_source, $url, array('attributes' => array('target' => '_blank'))),
      );
    }

    $ret[] = $content;
  }

  return $ret;
}

/**
 * two variants sofar - review(ac:source=Anmeldelser) and all the others (sofar only ac:source=bibliotekets materialer)
 */
function ting_relation_reviews($relations) {
  $ret = array();
  foreach ($relations as $relation) {
    $ac_source = $relation['#relation']->object->ac_source;
    if ($ac_source == 'Anmeldelser') {
      $ret[] = ting_relation_review_other($relation);
    }
    else {
      $ret[] = ting_relation_review($relation);
    }
  }
  return $ret;
}

/**
 * a variant of a review (ac:source = 'bibliotekets materialer'
 */
function ting_relation_review_other($relation) {
  $ting = $relation['#object'];
  $rel = $relation['#relation'];

  // Type title.
  $content['type'] = $relation['#title'];

  // Title.
  global $base_url;
  $relation_title_link = l($rel->object->title, $base_url . '/ting/object/' . $ting->ding_entity_id);
  $content['title'] = $relation_title_link;

  // Creators.
  if ($names = ting_relation_array2names($rel->object->creators)) {
    $content['byline'] = t('by @author', array('@author' => $names));
  }

  // Ispartof.
  if ($partOf = ting_relation_array2names($rel->object->isPartOf)) {
    $extent = $rel->object->extent;
    $content['isPartOf'] = filter_xss_admin($partOf . ', ' . $extent);
  }

  // @todo online_url.
  if ($url = $rel->object->online_url) {
    $content['online_url'] = array('#markup' => l($rel->object->ac_source, $url, array('attributes' => array('target' => '_blank'))));
  }

  return $content;
}

/**
 * a variant of a review (ac:source = 'Anmeldelser'
 */
function ting_relation_review($relation) {
  $ting = $relation['#object'];
  $rel = $relation['#relation'];
  // Type title ; generel.
  $content['type'] = $relation['#title'];

  // Title ; generel.
  global $base_url;
  $relation_title_link = l($rel->object->title, $base_url . '/ting/object/' . $ting->ding_entity_id);
  $content['title'] = $relation_title_link;

  // Year.
  $content['year'] = $rel->object->date;

  // Creator.
  $content['creator'] = ting_relation_array2names($ting->creators);

  // Text.
  $content['text'] = isset($ting->reply->record['dc:description'][''][0]) ? $ting->reply->record['dc:description'][''][0] : FALSE;

  if ($url = $rel->object->online_url) {
    $content['online_url'] = array('#markup' => l($rel->object->ac_source, $url, array('attributes' => array('target' => '_blank'))));
  }

  return $content;
}

/**
 * helper function
 */
function ting_relation_array2names($array) {
  if (!isset($array) || empty($array)) {
    return false;
  }

  $ret = '';
  foreach ($array as $key => $name) {
    if (strlen($ret) > 0) {
      $ret .= ', ';
    }
    $ret .= $name;
  }
  return $ret;
}
