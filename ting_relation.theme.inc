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

  //print_r($relation);

  $variables['classes_array'][] = 'ting-relation-' . drupal_html_class($relation->type);
  //  $variables['type_title'] = $variables['elements']['#title'];
  $variables['title'] = check_plain($object->title);
  $variables['online_url'] = $object->online_url ? l($object->online_url, $object->online_url) : FALSE;

  switch( $relation->type ) {
  case 'dbcbib:isPartOfManifestation' :
    $variables['content']['body'] = ting_object_view($object, 'teaser');
    break;
  case 'dbcaddi:hasReview' :
    //   print_r( $relation  );
    // if( $object->ac_source
    echo $object->ac_source;
    ting_relation_set_review( $variables );
    break;
  case 'dbcaddi:hasSubjectDescription' :
    ting_relation_set_subject( $variables );
    break;    
  default :
    $variables['content']['body'] = array( '#markup' => filter_xss_admin($object->abstract), );
    break;
  }  
} 

/**
 * Set review part
 */
function ting_relation_set_review( &$variables ) {
  
   $tingentity_object = $variables['object'] = $variables['elements']['#object'];
  $relation = $variables['relation'] = $variables['elements']['#relation'];
    $variables['content']['contributor'] =
    array(
	  '#markup' => t('relation_contributor : ').filter_xss_admin( ($names = ting_relation_get_contributors($relation)) ? $names : '' ),
	  '#prefix' => '<div class="ting-relation-meta">',
	  '#suffix' => '</div>',
	  );
  
  $variables['content']['date'] =
    array(
	  '#markup' => t('relation_date : ').filter_xss_admin( $relation->object->date ),
	  '#prefix' => '<div class="ting-relation-meta">',
	  '#suffix' => '</div>',
	  );
  
  
  if (!empty($object->reply->record['dc:description'][''][0])) {
    $variables['content']['body'] = 
      array(
	    '#markup' => filter_xss_admin($object->reply->record['dc:description'][''][0]),
	    );     
    
  }
   
  /*  $variables['content']['HEST'] = 
    array(
    '#markup' => t('TESTHEST'),
    '#prefix' => '<div>',
    '#suffix' => '</div>',
    ); */
}

/**
 * Set subject part
 */
function ting_relation_set_subject( &$variables ) {  
   $tingentity_object = $variables['object'] = $variables['elements']['#object'];
  $relation = $variables['relation'] = $variables['elements']['#relation'];
  //creators
  if ($tingentity_object->creators){
    $variables['content']['byline'] = 
      array(
	    '#markup' => t('by @author', array('@author' => $tingentity_object->creators)),
	    '#prefix' => '<div>',
	    '#suffix' => '</div>',
	    );
  }
  // abstract
  $variables['content']['body'] = 
    array(
	  '#markup' => filter_xss_admin($tingentity_object->abstract),
	  '#prefix' => '<div>',
	  '#suffix' => '</div>',
	  );
  // description
  $variables['content']['description'] = 
    array(
	  '#markup' => filter_xss_admin($tingentity_object->description),
	  '#prefix' => '<div>',
	  '#suffix' => '</div>',
	  );
  
  
 
}
