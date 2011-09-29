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

  $variables['online_url'] = $object->online_url ? l($object->ac_source, $object->online_url, array('attributes'=>array('target'=>'_blank') ) ): FALSE;

  switch ($relation->type) {
  case 'dbcbib:isPartOfManifestation':
    $variables['content']['body'] = ting_object_view($object, 'teaser');
    break;
  case 'dbcaddi:hasReview':
    // different types of reviews - more switch?
    if ($relation->object->ac_source == 'Anmeldelser') {
      ting_relation_set_review_anmeldelser($variables);
    }
    else {
      ting_relation_set_review($variables);
    }
    break;
  case 'dbcaddi:hasSubjectDescription':
    ting_relation_set_subject($variables);
    break;
  case 'dbcaddi:hasCreatorDescription':
    ting_relation_set_author_description($variables);
    break;
  default :
    break;
  }
}

function ting_relation_set_author_description(&$variables) {
  $tingentity_object = $variables['object'] = $variables['elements']['#object'];
  $relation = $variables['relation'] = $variables['elements']['#relation'];
  if ($names = ting_relation_array2names($relation->object->creators)) {
    $variables['content']['creator'] = array(
      '#markup' => t('relation_author_portrait_creator : ') . filter_xss_admin($names),
      '#prefix' => '<div style="border-bottom:1px solid #CCCCCC; margin-bottom:0.5em">',
      '#suffix' => '</div >',
    );
  }

  $variables['content']['abstract'] = array(
    '#markup' => filter_xss_admin($tingentity_object->abstract),
    '#prefix' => '<div>',
    '#suffix' => '</div>',
  );
}

function ting_relation_set_review_anmeldelser(&$variables) {
  $tingentity_object = $variables['object'] = $variables['elements']['#object'];
  $relation = $variables['relation'] = $variables['elements']['#relation'];

  //creators
  if ($names = ting_relation_array2names($relation->object->creators)) {
    $variables['content']['creator'] = array(
      '#markup' => t('relation_review_creator : ') . filter_xss_admin($names),
      '#prefix' => '<div>',
      '#suffix' => '</div>',
    );
  }
  //ispartof
  if($partOf = ting_relation_array2names($relation->object->isPartOf)) {
    $extent = $relation->object->extent;
    $variables['content']['isPartOf'] = array(
      '#markup' => t('relation_isPartOf : ') . filter_xss_admin($partOf . ', ' . $extent),
      '#prefix' => '<div style="padding-bottom:0.5em">',
      '#suffix' => '</div>',
    );
  }
}

/**
 * Set review part
 */
function ting_relation_set_review(&$variables) {
  $tingentity_object = $variables['object'] = $variables['elements']['#object'];
  $relation = $variables['relation'] = $variables['elements']['#relation'];

  $variables['content']['contributor'] = array(
    '#markup' => t('relation_contributor : ') . filter_xss_admin(($names = ting_relation_array2names($relation->object->contributors)) ? $names : ''),
    '#prefix' => '<div>',
    '#suffix' => '</div>',
  );

  $variables['content']['date'] = array(
    '#markup' => t('relation_date : ') . filter_xss_admin($relation->object->date),
    '#prefix' => '<div style="border-bottom:1px solid #CCCCCC; margin-bottom:0.5em" >',
    '#suffix' => '</div>',
  );


  if (!empty($tingentity_object->reply->record['dc:description'][''][0])) {
    $variables['content']['body'] = array(
      '#markup' => filter_xss_admin($tingentity_object->reply->record['dc:description'][''][0]),
    );
  }
}

/**
 * Set subject part
 */
function ting_relation_set_subject(&$variables) {
  $tingentity_object = $variables['object'] = $variables['elements']['#object'];
  $relation = $variables['relation'] = $variables['elements']['#relation'];
  //creators
  if ($tingentity_object->creators) {
    $variables['content']['byline'] = array(
      '#markup' => t('by @author', array('@author' => $tingentity_object->creators)),
      '#prefix' => '<div>',
      '#suffix' => '</div>',
    );
  }
  // abstract
  $variables['content']['body'] = array(
    '#markup' => filter_xss_admin($tingentity_object->abstract),
    '#prefix' => '<div>',
    '#suffix' => '</div>',
  );
  // description
  $variables['content']['description'] = array(
    '#markup' => filter_xss_admin($tingentity_object->description),
    '#prefix' => '<div>',
    '#suffix' => '</div>',
  );
}

function ting_relation_array2names($array) {
  if ( !isset($array) || empty($array)) {
    return false;
  }

  $ret = '';
  foreach($array as $key => $name) {
    if (strlen($ret) > 0) {
      $ret .= ', ';
    }
    $ret .= $name;
  }
  return $ret;
}



