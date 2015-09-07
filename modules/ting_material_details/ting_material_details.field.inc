<?php
/**
 * @file
 * Defines fields for the ting entities and formatters for the fields.
 */

/**
 * Implements hook_field_info().
 */
function ting_material_details_field_info() {
  $ret = array(
    // Defines dc:type.
    'ting_details_type' => array(
      'label' => t('Type'),
      'description' => t('Material type'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // Defines dc:format.
    'ting_details_format' => array(
      'label' => t('Format'),
      'description' => t('Material format'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // Defines dcterms:isPartOf (Availability).
    'ting_details_ispartof' => array(
      'label' => t('Available in'),
      'description' => t('dcterms:isPartOf'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_is_part_of_search',
      'no_ui' => TRUE,
    ),
    // Defines dc:language.
    'ting_details_language' => array(
      'label' => t('Language'),
      'description' => t('Language'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // Defines dkdcplus:spoken.
    'ting_details_spoken' => array(
      'label' => t('Speech'),
      'description' => t('spoken language'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // Defines dkdcplus:subtitles.
    'ting_details_subtitles' => array(
      'label' => t('Subtitle'),
      'description' => t('Material subtitles'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // Defines dkdcplus:genre.
    'ting_details_genre' => array(
      'label' => t('Genre'),
      'description' => t('Material genre'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // Defines dc:subjects.
    'ting_details_subjects' => array(
      'label' => t('Subject'),
      'description' => t('Material subject'),
      'default_widget' => 'hidden',
      // 'default_formatter' => 'ting_details_single',
      'default_formatter' => 'ting_details_subject_search',
      'no_ui' => TRUE,
    ),
    // Defines classification (dc:subject->dkdcplus:DK5).
    'ting_details_classification' => array(
      'label' => t('Classification'),
      'description' => t('Material classification'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // Defines dcterms:spatial (geo encoding).
    'ting_details_spatial' => array(
      'label' => t('spatial'),
      'description' => t('Material spatial'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // Defines dc:contributor.
    'ting_details_contributor' => array(
      'label' => t('Reader'),
      'description' => t('Material contributor'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_creator_search',
      'no_ui' => TRUE,
    ),
    // Defines dkdcplus:mus (musician).
    'ting_details_musician' => array(
      'label' => t('Musician'),
      'description' => t('Material musician'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // Defines dkdcplus:track.
    'ting_details_tracks' => array(
      'label' => t('Contains'),
      'description' => t('Material tracks'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // Defines dcterms:isReferencedBy.
    'ting_details_referenced' => array(
      'label' => t('Referenced by'),
      'description' => t('Material referenced'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // Defines dc:description.
    'ting_details_description' => array(
      'label' => t('Description'),
      'description' => t('Material description'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // Defines dc:description (dkdcplus:series).
    'ting_details_seriesdescription' => array(
      'label' => t('Series description'),
      'description' => t('Series description'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_seriesdescription_search',
      'no_ui' => TRUE,
    ),
    // Defines dc:source (original title).
    'ting_details_source' => array(
      'label' => t('Original title'),
      'description' => t('Material original title'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // Defines dcterms:replaces.
    'ting_details_replaces' => array(
      'label' => t('Previous title'),
      'description' => t('Material previous title'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // Defines dcterms:isReplacedBy.
    'ting_details_replaced_by' => array(
      'label' => t('Later title'),
      'description' => t('Material later title'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // Defines dkdcplus:ISBN.
    'ting_details_isbn' => array(
      'label' => t('ISBN no.'),
      'description' => t('Material ISBN'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // Defines dcterms:URI.
    'ting_details_uri' => array(
      'label' => t('Host publication'),
      'description' => t('Material URI'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // Defines dkdcplus:version.
    'ting_details_version' => array(
      'label' => t('Version'),
      'description' => t('Material version'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // Defines dcterms:extent.
    'ting_details_extent' => array(
      'label' => t('Extent'),
      'description' => t('Material extent'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // Defines dc:publisher.
    'ting_details_publisher' => array(
      'label' => t('Publisher'),
      'description' => t('Material publisher'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // Defines dc:rights.
    'ting_details_rights' => array(
      'label' => t('Rights'),
      'description' => t('Material rights'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // Defines dcterms:audience.
    'ting_details_audience' => array(
      'label' => t('Audience'),
      'description' => t('Material audience'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // Defines dkdcplus:age.
    'ting_details_age' => array(
      'label' => t('Age'),
      'description' => t('Material age'),
      'default_widget' => 'hidden',
      'default_formatter' => 'ting_details_single',
      'no_ui' => TRUE,
    ),
    // Defines dkdcplus:pegi.
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
 * Implements hook_field_formatter_info().
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
    'ting_details_subject_search' => array(
      'label' => t('Subject search link'),
      'field types' => array(
        'ting_details_subjects',
      ),
    ),
    'ting_details_seriesdescription_search' => array(
      'label' => t('Series search link'),
      'field types' => array(
        'ting_details_seriesdescription',
      ),
    ),
    'ting_details_is_part_of_search' => array(
      'label' => t('Part of manifestation search link'),
      'field types' => array(
        'ting_details_is_part_of',
      ),
    ),
  );
}

/**
 * Helper function for retrieving record-field.
 *
 * It maps field name to record structure.
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
  $ret['ting_details_classification'] = 'classification';
  $ret['ting_details_spatial'] = array('dcterms:spatial');
  $ret['ting_details_contributor'] = 'contributors';
  $ret['ting_details_musician'] = array('dc:contributor' => 'dkdcplus:mus');
  $ret['ting_details_tracks'] = array('dcterms:hasPart' => 'dkdcplus:track');
  $ret['ting_details_referenced'] = array('dcterms:isReferencedBy');
  $ret['ting_details_seriesdescription'] = array('dc:description' => 'dkdcplus:series');
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

/**
 * Gets the field value of a ting record for a given field type.
 *
 * @param string $field_type
 *   The name of the field that should have its value extracted.
 * @oaram TingEntity $entity
 *   The ting entity the contains the field and value.
 *
 * @return mixed
 *   The fields value or FALSE if field do not exists or is empty.
 */
function ting_material_details_get_record_value($field_type, TingEntity $entity) {
  $rec_info = ting_material_details_record_info();
  $rec = isset($rec_info[$field_type]) ? $rec_info[$field_type] : FALSE;
  $value = FALSE;

  if ($rec) {
    // If it's a string simply use it.
    if (is_string($rec)) {
      $value = $entity->$rec;
    }

    if (is_array($rec)) {
      foreach ($rec as $key => $val) {
        if ($key) {
          $value = isset($entity->record[$key][$val]) ? $entity->record[$key][$val] : FALSE;
        }
        else {
          $value = isset($entity->record[$val]['']) ? $entity->record[$val][''] : FALSE;
        }
      }
    }
  }

  return ting_material_details_parse($field_type, $value);
}

/**
 * Parse ting entity field value based on field type.
 *
 * @param string $field_type
 *   The name of the field that should have its value extracted.
 * @oaram mixed $value
 *   The fields value.
 *
 * @return mixed
 *   The fields value or FALSE.
 */
function ting_material_details_parse($field_type, $value) {
  $ret = $value;

  if ($value) {
    switch ($field_type) {
      case 'ting_details_uri':
        foreach ($value as $val) {
          $ret[] = l($val, $val);
        }
        break;
    }
  }

  return $ret;
}

/**
 * Implements hook_field_formatter_view().
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
            $links[] = l($value, 'search/ting/phrase.creator=' . $value);
          }
          $element[$delta] = array(
            '#markup' => implode(', ', $links),
          );
          break;

        case 'ting_details_subject_search':
          if (!is_array($val)) {
            $val = array($val);
          }
          $links = array();
          foreach ($val as $value) {
            $links[] = l($value, 'search/ting/dkcclterm.em=' . $value);
          }
          $element[$delta] = array(
            '#markup' => implode(', ', $links),
          );
          break;

        case 'ting_details_seriesdescription_search':
          $element[$delta] = array(
            '#markup' => $entity->serieDescription,
          );
          break;

        // Run through all isPartOfManifestion elements of entity.
        // If the entity has a relation-uri; create a render array that
        // renders a link to the relation.
        // If not: use the text desribing the relation.
        //
        // NOTICE : Opensearch delivers one or MORE relation-uris; This
        // formatter only handles one.
        // @see #bug1109. (http://platform.dandigbib.org/issues/1109)
        case 'ting_details_is_part_of_search':
          $type = $uri = NULL;
          foreach ($entity->getRelations() as $relation) {
            $type = explode(':', $relation->getType());
            // $relation have a namespace: dbcbib:isPartOfManifestation
            if (isset($type[1]) && $type[1] == 'isPartOfManifestation') {
              $uri = $relation->getURI();
            }
          }
          $render['#prefix'] = '<span class="ting-material-detail ting-material-is-part-of">';
          $render['#suffix'] = '</span>';
          if (!is_array($val)) {
            $val = array($val);
          }
          if ($uri) {
            foreach ($val as $key => $detail) {
              $render['part_of'][$key]['#theme'] = 'link';
              $render['part_of'][$key]['#text'] = $detail;
              $render['part_of'][$key]['#path'] = 'search/ting/' . $uri;
              $render['part_of'][$key]['#options']['attributes'] = array();
              $render['part_of'][$key]['#options']['html'] = 1;
            }
          }
          else {
            foreach ($val as $key => $detail) {
              $render['part_of'][$key]['#markup'] = $detail;
            }
          }
          // for now, we only use the first item.
          $element[$delta]['part_of'] = reset($render['part_of']);
          break;
      }
    }
  }
  return $element;
}

/**
 * Process series information.
 *
 * This could be handled more elegantly if we had better structured data.
 * For now we have to work with what we got to convert titles to links
 * Series information appear in the following formats:
 * - Samhørende: [title 1] ; [title 2] ; [title 3]
 * - [volumne number]. del af: [title]
 */
function process_series_info($series) {
  $result = '';
  $parts = explode(':', $series);

  if (is_array($parts) && count($parts) >= 2) {
    $prefix = $parts[0] . ': ';

    if (stripos($prefix, 'del af:') !== FALSE) {
      $title = $parts[1];
      $result = $prefix . l($title, 'search/ting/"' . $title . '"');
    }
    elseif (stripos($prefix, 'Samhørende:') !== FALSE) {
      $titles = $parts[1];
      // Multiple titles are separated by ' ; '. Explode to iterate over them.
      $titles = explode(' ; ', $titles);
      foreach ($titles as &$title) {
        $title = trim($title);
        // Some title elements are actually volume numbers. Do not convert
        // these to links.
        if (!preg_match('/(nr.)? \d+/i', $title)) {
          $title = l($title, 'search/ting/"' . $title . '"');
        }
      }
      // Reassemble titles.
      $titles = implode(', ', $titles);
      $result = $prefix . ' ' . $titles;
    }
  }

  return $result;
}

/**
 * Implements hook_field_is_empty().
 *
 * @todo check
 */
function ting_material_details_is_empty($item, $field) {
  return FALSE;
}

/**
 * Implements hook_field_load().
 *
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
 * Implements hook_field_formatter_prepare_view().
 *
 * we could also use hook_field_load or hook_field_prepare_view
 */
function ting_material_details_field_formatter_prepare_view($entity_type, $entities, $field, $instances, $langcode, &$items, $displays) {
  foreach ($entities as $id => $entity) {
    $items[$id][0] = array(
      'id' => $id,
    );
  }
}

