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
  $ac_source = $variables['ac_source'] = $variables['elements']['#ac_source'];

  $variables['online_url'] = FALSE;

  switch ($relation->type) {
    case 'dbcbib:isPartOfManifestation':
      ting_relations_set_url_and_title( $variables );
      $variables['content']['body'] = ting_object_view($object, 'teaser');
      break;
    case 'dbcaddi:hasReview':
      // This is so crap, but until someone figures out how to deal with this in
      // a general way..
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
    case 'dbcaddi:hasOnlineAccess':
      // This is so crap, but until someone figures out how to deal with this in
      // a general way..
      switch ($ac_source) {
        case 'Ebrary':
          ting_relations_set_online_access_ebrary($variables);
          break;
        case 'Filmstriben (fjernlån)':
          ting_relations_set_online_access_filmstriben($variables);
          break;
      }
      break;
    default:
      break;
  }
}

function ting_relations_set_online_access_ebrary(&$variables) {
  // TODO get ebrary url from somewhere
  $ebrary_url = variable_get('ting_ebrary_url');
  if( !isset($ebrary_url) ) {
    return;
  }

  $variables['type_title'] = $variables['elements']['#title'];
  $relation = $variables['relation'] = $variables['elements']['#relation'];
  $variables['classes_array'][] = 'ting-relation-' . drupal_html_class($relation->type);

  // simply set a button
  $url = str_replace('[URL]',$ebrary_url,$relation->uri);
  $variables['online_url'] = array('#markup' => l($variables['ac_source'], $url, array('attributes' => array('target'=>'_blank'))));
}

function ting_relations_set_online_access_filmstriben(&$variables) {
  $variables['type_title'] = $variables['elements']['#title'];
  $relation = $variables['relation'] = $variables['elements']['#relation'];
  $variables['classes_array'][] = 'ting-relation-' . drupal_html_class($relation->type);

  // simply set a button
  $url = $relation->uri;
  $variables['online_url'] = array('#markup' => l($variables['ac_source'], $url, array('attributes' => array('target'=>'_blank'))));
}

function ting_relation_set_author_description(&$variables) {
  $tingentity_object = $variables['object'] = $variables['elements']['#object'];
  $relation = $variables['relation'] = $variables['elements']['#relation'];

  ting_relations_set_url_and_title( $variables );

  if ($names = ting_relation_array2names($tingentity_object->creators)) {
    $variables['content']['byline'] = array(
      '#markup' => t('by @author', array('@author' => $names)),
      '#prefix' => '<div class="meta">',
      '#suffix' => '</div>',
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

  ting_relations_set_url_and_title( $variables );

  //creators
  if ($names = ting_relation_array2names($relation->object->creators)) {
    $variables['content']['byline'] = array(
      '#markup' => t('by @author', array('@author' => $names)),
      '#prefix' => '<div>',
      '#suffix' => '</div>',
    );
  }
  //ispartof
  if ($partOf = ting_relation_array2names($relation->object->isPartOf)) {
    $extent = $relation->object->extent;
    $variables['content']['isPartOf'] = array(
      '#markup' => t('Part of') . ": " . filter_xss_admin($partOf . ', ' . $extent),
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

  ting_relations_set_url_and_title( $variables );

  $variables['content']['meta'] = array(
    '#prefix' => '<div class="meta">',
    '#suffix' => '</div>',
  );
  $names = ting_relation_array2names($relation->object->contributors);
  if (!empty($relation->object->contributors) && sizeof($relation->object->contributors) > 0) {
    $names = ting_relation_array2names($relation->object->contributors);
    $variables['content']['meta']['byline'] = array(
      '#markup' => t('by @author', array('@author' => $names)),
    );
  }

  $variables['content']['meta']['date'] = array(
    '#markup' => t('Year') . ": " . filter_xss_admin($relation->object->date),
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

  ting_relations_set_url_and_title( $variables );

  //creators
  if ($tingentity_object->creators) {
    $variables['content']['byline'] = array(
      '#markup' => t('by @author', array('@author' => ting_relation_array2names($tingentity_object->creators))),
    '#prefix' => '<div class="meta">',
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

function ting_relations_set_url_and_title( &$variables ) {
  $variables['type_title'] = $variables['elements']['#title'];
  $tingentity_object = $variables['object'] = $variables['elements']['#object'];
  $relation = $variables['relation'] = $variables['elements']['#relation'];

  $variables['classes_array'][] = 'ting-relation-' . drupal_html_class($relation->type);

  if( is_object($tingentity_object) ) {
    $variables['title'] = check_plain($tingentity_object->title);
    $variables['online_url'] = $tingentity_object->online_url ? l($tingentity_object->ac_source, $tingentity_object->online_url, array('attributes'=>array('target'=>'_blank') ) ): FALSE;
  }
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



