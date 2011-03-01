<?php

/**
 * @file
 * Entity classes for ting objects and collections.
 */

/**
 * Ting object entity.
 */
class TingEntity extends DingEntity {
  function __construct() {
    parent::__construct();
    $this->properties += array(
      'type' => FALSE,
      'record' => FALSE,
      'relations' => FALSE,
      'localId' => FALSE,
      'creators' => FALSE,
      'subjects' => FALSE,
      'language' => FALSE,
      'relationType' => FALSE,
      'relationUri' => FALSE,
    );
  }

  function getLocalId() {
    return $this->localId = $this->reply->localId;
  }

  function getType() {
    return $this->type = !empty($this->reply->record['dc:type']) ? $this->reply->record['dc:type']['dkdcplus:BibDK-Type'][0] : FALSE;
  }

  function getTitle() {
    return $this->title = !empty($this->reply->record['dc:title']) ? $this->reply->record['dc:title'][''][0] : FALSE;
  }

  function getAbstract() {
    return $this->abstract = !empty($this->reply->record['dcterms:abstract'][''][0]) ? $this->reply->record['dcterms:abstract'][''][0] : FALSE;;
  }

  function getRecord() {
    return $this->reply->record;
  }

  function getRelations() {
    $this->relations = array();
    if (isset($this->reply->relations)) {
      $entity_ids = array();
      foreach ($this->reply->relations as $record) {
        if (isset($record->id)) {
          $entity_ids[] = $record->id;
        }
      }
      if ($entity_ids){
        $this->relations = entity_load('ting_object', array(), array('ding_entity_id' => $entity_ids));
      }
    }
    return $this->relations;
  }

  function getCreators() {
    $this->creators = array();
    if (!empty($this->reply->record['dc:creator'])) {
      foreach ($this->reply->record['dc:creator'] as $type => $dc_creator) {
        if ($type != 'oss:sort') {
          $this->creators = array_merge($this->creators, $dc_creator);
        }
      }
    }
    return $this->creators;
  }

  function getSubjects() {
    $this->subjects = array();
    if (!empty($this->reply->record['dc:subject'])) {
      foreach ($this->reply->record['dc:subject'] as $type => $dc_subject) {
        if (in_array($type, array('dkdcplus:DBCF', 'dkdcplus:DBCS', 'dkdcplus:DBCM', 'dkdcplus:DBCO', 'dkdcplus:DBCN'))) {
          $this->subjects = array_merge($this->subjects, $dc_subject);
        }
      }
    }
    return $this->subjects;
  }

  function getLanguage() {
    return $this->language = !empty($this->reply->record['dc:language'][''][0]) ? $this->reply->record['dc:language'][''][0] : FALSE;
  }

  function getRelationType() {
    return $this->relationType = $this->reply->relationType;
  }

  function getRelationUri() {
    return $this->relationUri = $this->reply->relationUri;
  }
}

/**
 * Ting collection entity.
 */
class TingCollection extends DingEntityCollection {
  function __construct($id) {
    $this->ding_entity_id = $id;
    parent::__construct();
    $this->properties += array(
      'title' => FALSE,
      'types' => FALSE,
      'primary_object' => FALSE,
    );
  }

  function getTitle() {
    return $this->title = !empty($this->reply->objects[0]->record['dc:title']) ? $this->reply->objects[0]->record['dc:title'][''][0] : FALSE;
  }

  function getEntities() {
    $this->entities = array();
    if (isset($this->reply->objects)) {
      foreach ($this->reply->objects as $record) {
        $entity_ids[] = $record->id;
      }
      $entities = entity_load('ting_object', array(), array('ding_entity_id' => $entity_ids));
      // Can't pass overloaded $this->types as reference to
      // _ting_type_lang_sort(), so we're using a temporary var.
      $types_tmp = array();
      $this->entities = _ting_type_lang_sort($entities, $types_tmp);
      $this->types = $types_tmp;
    }
    return $this->entities;
  }

  function getTypes() {
    $types = array();
    foreach ($this->entities as $object) {
      $types[] = $object->type;
      foreach ($object->subjects as $subject) {
        if (!isset($subject_count[$subject])) {
          $subject_count[$subject] = 0;
        }
        $subject_count[$subject]++;
      }
    }
    return $collection->types = array_unique($types);
  }

  function getPrimary_object() {
    $this->primary_object = NULL;
    if (isset($this->reply->objects)) {
      $this->primary_object = reset(entity_load('ting_object', array(), array('ding_entity_id' => array($this->reply->objects[0]->id))));
    }
    return $this->primary_object;
  }
}
