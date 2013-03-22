<?php

/**
 * Implements hook_field_info()
 */

function ting_material_details_field_info() {
  $ret = array(
     //dc:type
    'ting_details_type' => array(
      'label' => t('Type'),
      'description' => t('Material type'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // dc:format
    'ting_details_format' => array(
      'label' => t('Format'),
      'description' => t('Material format'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // dcterms:isPartOf (Availability)
    'ting_details_ispartof' => array(
      'label' => t('Available in'),
      'description' => t('dcterms:isPartOf'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // dc:language
    'ting_details_language' => array(
      'label' => t('Language'),
      'description' => t('Language'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // dkdcplus:spoken
    'ting_details_spoken' => array(
      'label' => t('Speech'),
      'description' => t('spoken language'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // dkdcplus:subtitles
    'ting_details_subtitles' => array(
      'label' => t('Subtitle'),
      'description' => t('Material subtitles'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // dkdcplus:genre
    'ting_details_genre' => array(
      'label' => t('Genre'),
      'description' => t('Material genre'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // dc:subjects
    'ting_details_subjects' => array(
      'label' => t('Subject'),
      'description' => t('Material subject'),
      'default_widget' => 'hidden',
      // 'default_formatter' => 'ting_details_single',
      'default_formatter' => 'ting_details_subject_search',
      'no_ui' => TRUE,
    ),
    // Classification (dc:subject->dkdcplus:DK5)
    'ting_details_classification' => array(
      'label' => t('Classification'),
      'description' => t('Material classification'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    //dcterms:spatial ??
    'ting_details_spatial' => array(
      'label' => t('spatial'),
      'description' => t('Material spatial'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    //dc:contributor
    'ting_details_contributor' => array(
      'label' => t('Reader'),
      'description' => t('Material contributor'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_creator_search',
      'no_ui' => TRUE,
    ),
    //dkdcplus:mus (musician)
    'ting_details_musician' => array(
      'label' => t('Musician'),
      'description' => t('Material musician'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    //dkdcplus:track
    'ting_details_tracks' => array(
      'label' => t('Contains'),
      'description' => t('Material tracks'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    //dcterms:isReferencedBy
    'ting_details_referenced' => array(
      'label' => t('Referenced by'),
      'description' => t('Material referenced'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // dc:description
    'ting_details_description' => array(
      'label' => t('Description'),
      'description' => t('Material description'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    //dc:source (original title)
    'ting_details_source' => array(
      'label' => t('Original title'),
      'description' => t('Material original title'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // dcterms:replaces
    'ting_details_replaces' => array(
      'label' => t('Previous title'),
      'description' => t('Material previous title'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // dcterms:isReplacedBy
    'ting_details_replaced_by' => array(
      'label' => t('Later title'),
      'description' => t('Material later title'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // dkdcplus:ISBN
    'ting_details_isbn' => array(
      'label' => t('ISBN no.'),
      'description' => t('Material ISBN'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // dcterms:URI
    'ting_details_uri' => array(
      'label' => t('Host publication'),
      'description' => t('Material URI'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // dkdcplus:version
    'ting_details_version' => array(
      'label' => t('Version'),
      'description' => t('Material version'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // dcterms:extent
    'ting_details_extent' => array(
      'label' => t('Extent'),
      'description' => t('Material extent'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // dc:publisher
    'ting_details_publisher' => array(
      'label' => t('Publisher'),
      'description' => t('Material publisher'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // dc:rights
    'ting_details_rights' => array(
      'label' => t('Rights'),
      'description' => t('Material rights'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
     // dcterms:audience
    'ting_details_audience' => array(
      'label' => t('Audience'),
      'description' => t('Material audience'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    //dkdcplus:age
    'ting_details_age' => array(
      'label' => t('Age'),
      'description' => t('Material age'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),

    //dkdcplus:pegi
    'ting_details_pegi' => array(
      'label' => t('Pegi'),
      'description' => t('Material PEGI-mark'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
  );

  return $ret;
}

/**
 * Implements hook_field_formatter_info
 *
 * Notes; 'field types' are passed on to hook_field_formatter_view
 */
function ting_material_details_field_formatter_info() {
  return array(
    'ting_details_single' => array(
      'label' => t('Default'),
      'field types' => array(
	'ting_details_type',
	'ting_details_format',
	'ting_details_ispartof',
	'ting_details_language',
	'ting_details_spoken',
	'ting_details_subtitles',
	'ting_details_classification',
	'ting_details_spatial',
	'ting_details_musician',
	'ting_details_referenced',
	'ting_details_description',
	'ting_details_source',
	'ting_details_replaces',
	'ting_details_replaced_by',
	'ting_details_isbn',
	'ting_details_uri',
	'ting_details_version',
	'ting_details_extent',
	'ting_details_publisher',
	'ting_details_rights',
	'ting_details_age',
	'ting_details_audience',
	'ting_details_subjects',
	'ting_details_tracks',
	'ting_details_genre',
	'ting_details_contributor',
	'ting_details_pegi',
      ),
    ),
    'ting_details_creator_search' => array(
      'label' => t('Creator search link'),
      'field types' => array(
	'ting_details_contributor',
      ),
    ),
    'ting_details_subject_search' =>  array(
      'label' => t('Subject search link'),
      'field types' => array(
	'ting_details_subjects',
      ),
    ),
					
  );
}

/*
 * helper function for retrieving record-field,
 * maps field name to record structure
 */
function ting_material_details_record_info() {
  $ret = array();
  $ret['ting_details_type'] = 'type';
  $ret['ting_details_format'] = array('dc:format');
  $ret['ting_details_ispartof'] = array('dcterms:isPartOf');
  $ret['ting_details_language'] = 'language';
  $ret['ting_details_spoken'] = array('dc:language' => 'dkdcplus:spoken');
  $ret['ting_details_subtitles'] = array('dc:language' => 'dkdcplus:subtitles');
  $ret['ting_details_genre'] = array('dc:subject' => 'dkdcplus:genre');
  $ret['ting_details_subjects'] = 'subjects';
  $ret['ting_details_classification'] = 'classification'; //array('dc:subject'=>'dkdcplus:DK5-Text');
  $ret['ting_details_spatial'] = array('dcterms:spatial');
  $ret['ting_details_contributor'] =  'contributors'; //array('dc:contributor'=>'dkdcplus:cmp');
  $ret['ting_details_musician'] = array('dc:contributor' => 'dkdcplus:mus');
  $ret['ting_details_tracks'] = array('dcterms:hasPart' => 'dkdcplus:track');
  $ret['ting_details_referenced'] = array('dcterms:isReferencedBy');
//  $ret['ting_details_description'] = array('dc:description'=>'dkdcplus:series');
  $ret['ting_details_description'] = array('dc:description');
  $ret['ting_details_source'] = array('dc:source');
  $ret['ting_details_replaces'] = array('dcterms:replaces');
  $ret['ting_details_replaced_by'] = array('dcterms:replacedBy');
  $ret['ting_details_isbn'] = array('dc:identifier' => 'dkdcplus:ISBN');
  $ret['ting_details_uri'] = array('dc:identifier' => 'dcterms:URI');
  $ret['ting_details_version'] = array('dkdcplus:version');
  $ret['ting_details_extent'] = array('dcterms:extent');
  $ret['ting_details_publisher'] = array('dc:publisher');
  $ret['ting_details_rights'] = array('dc:rights');
  $ret['ting_details_age'] = array('dcterms:audience' => 'dkdcplus:age');
  $ret['ting_details_audience'] = array('dcterms:audience');
  $ret['ting_details_pegi'] = array('dcterms:audience' => 'dkdcplus:pegi');
  return $ret;
}


/*
 * helper function
 * return array
 */
function ting_material_details_get_record_value( $field_type, $entity ) {
  $rec_info = ting_material_details_record_info();
  $rec =  isset($rec_info[$field_type]) ? $rec_info[$field_type] : FALSE;

  if ( !$rec ) {
    return FALSE;
  }

  if ( is_string($rec) ) {
    $value = $entity->$rec;
  }

  if ( is_array($rec) ) {
    foreach ( $rec as $key => $val ) {
      if ( $key ) {
        $value = isset($entity->record[$key][$val]) ? $entity->record[$key][$val] : FALSE;
      }
      else {
        $value =  isset( $entity->record[$val][''] ) ? $entity->record[$val][''] : FALSE;
      }
    }
  }
  return ting_material_details_parse( $field_type, $value );
}

/*
 * helper function
 * handle special cases
 */
function ting_material_details_parse($field_type, $value) {
  if (!$value) {
    return FALSE;
  }

  switch ($field_type) {
    case 'ting_details_uri':
      foreach ($value as $key => $val) {
        $ret[] = l($val, $val);
      }
      break;
    default:
      $ret = $value;
  }

  return $ret;
}

/**
 * Implements hook_field_formatter_view()
 */
function ting_material_details_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  foreach ($items as $delta => $items) {
    if ($val = ting_material_details_get_record_value($field['type'], $entity)) {
      switch ($display['type']) {
        case 'ting_details_single':
          $details = '';
          if (is_array($val)) {
            foreach ($val as $detail) {
              $details .= '<span class="ting-material-detail">' . $detail . '</span>';
            }
          }
          else {
            $details = $val;
          }
          $element[$delta] = array(
            '#markup' => $details,
          );
          break;
        case 'ting_details_creator_search':
          if (!is_array($val)) {
            $val = array($val);
          }
          $links = array();
          foreach ($val as $value) {
            $links[] = l($value, 'search/ting/dc.creator=' . $value);
          }
          $element[$delta] = array(
            '#markup' => implode(', ', $links),
          );
          break;
        case 'ting_details_subject_search':
          if ( !is_array($val) ) {
            $val = array($val);
          }
          $links = array();
          foreach ($val as $value) {
            $links[] = l($value, 'search/ting/dc.subject=' . $value);
          }
          $element[$delta] = array(
            '#markup' => implode(', ', $links),
          );
          break;
      }
    }
  }
  return $element;
}


/**
 * Implements hook_field_validate
 * TODO is some kind of validation needed?
 */
function ting_material_details_field_validate($entity_type, $entity, $field, $instance, $langcode, $items, &$errors) {
  // do nothing
}

/**
 * Implements hook_field_is_empty
 * TODO; check
 */
function ting_material_details_is_empty($item, $field) {
  return false;
}

/**
 * Implements hook_field_load().
 * Notes: Define custom load behavior for this module's field types.
 */
function ting_material_details_field_load($entity_type, $entities, $field, $instances, $langcode, &$items, $age) {
  foreach ($entities as $id => $entity) {
    $items[$id][0] = array(
      'id' => $id,
    );
  }
}

/**
 * Implements hook_field_formatter_prepare_view
 * we could also use hook_field_load or hook_field_prepare_view
 */

function ting_material_details_field_formatter_prepare_view($entity_type, $entities, $field, $instances, $langcode, &$items, $displays) {
  foreach ($entities as $id => $entity) {
    $items[$id][0] = array(
      'id' => $id,
    );
  }
}

