<?php
/**
 * @file
 * An example field using the Field API.
 *
 * This is updated from Barry Jaspan's presentation at Drupalcon Paris,
 * @link http://acquia.com/community/resources/acquia-tv/intro-field-api-module-developers Video Presentation @endlink
 *
 * Providing a field requires:
 * - Defining a field
 *   - hook_field_info()
 *   - hook_field_schema()
 *   - hook_field_validate()
 *   - hook_field_is_empty()
 *
 * - Defining a formatter for the field (the portion that outputs the field for
 *   display)
 *   - hook_field_formatter_info()
 *   - hook_field_formatter_view()
 *
 * - Defining a widget for the edit form
 *   - hook_field_widget_info()
 *   - hook_field_widget_form()
 *
 * *

 /**
 * Implements hook_field_info()

 * description of field
*/
 
function ting_infomedia_field_info() {
  $ret = array(
	       'ting_infomedia' =>
	       array('label' => t('A link to infomedia articles'),
		     'description' => t('This field links to infomedia articles'),
		     // optional (for database)
		     'settings' => array('max_length'=>255),
		     // optional
		     // 'instance_settings' => array('text_processing' => 0),
		     // see hook_widget_info
		     'default_widget' => 'hidden',
		     // see hook formatter_info
		     'default_formatter' => 'ting_infomedia_default',
		     // A boolean specifying that users should not be allowed to 
		     // create fields and instances of this field type through the UI. 
		     // Such fields can only be created programmatically with 
		     // field_create_field() and field_create_instance().
		     'no_ui' => TRUE,),
	       );
  return $ret;
}

/**
 * Implements hook_field_formatter_info
 *
 * pjo notes; 'field types' are passed on to hook_file_formatter_view
 */
function ting_infomedia_field_formatter_info() {
  return array(
	       'ting_infomedia_default' => 
	       array('label' => t('Default'),
		     'field types' => 
		     array('ting_infomedia',), )
	       );
  }


/**
 * Implements hook_field_formatter_view
 *
 * only one formatter is supported
 * - ting_infomedia
 */

/*function ting_infomedia_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  // krumo($entity);
  $element = array();
  $relation_types = ting_infomedia_get_ting_relations();
  foreach ($items as $delta => $item) {
   foreach ($entity->relations as $relation) {
    if (isset($relation_types[$relation->relationType])) {
        $element[$delta][] = 
	  array(
		'#theme' => 'ting_relation',
		'#object' => $relation->object,
		'#title' => $relation_types[$relation->relationType],
		// '#attached' => array(
		//  'css' => array(drupal_get_path('module', 'ting_relation') . '/ting_relation.css'),
		//),
		);
    }
   }
  }
  return $element;
  }*/



function ting_infomedia_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  $relation_types = ting_infomedia_get_ting_relations();
  switch($display['type']) {
  case 'ting_infomedia_default' :
    foreach($items as $delta=>$items) {
      foreach ($entity->relations as $relation) {
	//	krumo($relation->type);
	if( isset($relation_types[$relation->type]) ) {
	  //	  print_r($relation);
	  $element[$delta] = array('#markup' => '<div style="color:green; font-size:2em"><a href="'.ting_infomedia_get_article_link().'">'.t('Read article').'</a></div>');
	}
      }
    }
    break;
  default:
    krumo('ERROR');    
  }
  return $element;
  }

function ting_infomedia_get_article_link() {
  //global $base_path;
  return '?q=ting/infomedia';
  //$ret.=$base_path.'?q=ting/ting_infomedia';
  //return $ret;
}



/**
 * Implements hook_field_validate
 * TODO is some kind of validation needed?
 */
function ting_infomedia_field_validate($entity_type, $entity, $field, $instance, $langcode, $items, &$errors) {
  // do nothing
}

/**
 * Implements hook_field_is_empty
 *
 */
function ting_infomedia_is_empty($item, $field) {
  // TODO; check 
  return false;
}


/**
 * Implements hook_field_load().
 * pjo notes Define custom load behavior for this module's field types.
 */
function ting_infomedia_field_load($entity_type, $entities, $field, $instances, $langcode, &$items, $age) {
   foreach ($entities as $id => $entity) {
    // We could create relations as multiple values here, but it's
    // cached after this hook, so we don't.
    $items[$id][0] = array(
      'id' => $id,
    );
  } 
  }
/**
Implements hook_field_formatter_prepare_view
*
* 
* pjo notes; add the field to given item(s)
* we could also use hook_field_load or hook_field_prepare_view
 */

function ting_infomedia_field_formatter_prepare_view($entity_type, $entities, $field, $instances, $langcode, &$items, $displays) {
foreach ($entities as $id => $entity) {
    // We could create relations as multiple values here, but it's
    // cached after this hook, so we don't.
    $items[$id][0] = array(
      'id' => $id,
    );
   
  } 
}








