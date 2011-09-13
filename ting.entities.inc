<?php

/**
 * @file
 * Entity classes for ting objects and collections.
 */

/**
 * Object representing a relation between TingEntites.
 */
class TingRelation extends DingEntityBase {
  public $type = DingEntityBase::NULL;
  public $uri = DingEntityBase::NULL;
  public $object = DingEntityBase::NULL;

  public function __construct($type, $uri, $object = NULL) {
    parent::__construct();
    $this->properties['type'] = $type;
    $this->properties['uri'] = $uri;
    if ($object) {
      $this->properties['object'] = $object;
    }
  }

  function getObject() {
    $object = entity_load('ting_object', array(), array('ding_entity_id' => array($this->properties['uri'])));
    return reset($object);
  }
}

/**
 * Ting object entity.
 */
class TingEntity extends DingEntity {
  public $type = DingEntityBase::NULL;
  public $serieTitle = DingEntityBase::NULL;
  public $record = DingEntityBase::NULL;
  public $relations = DingEntityBase::NULL;
  public $localId = DingEntityBase::NULL;
  public $ownerId = DingEntityBase::NULL;
  public $creators = DingEntityBase::NULL;
  public $subjects = DingEntityBase::NULL;
  public $language = DingEntityBase::NULL;
  public $date = DingEntityBase::NULL;
  public $online_url = DingEntityBase::NULL;
  public $ac_source = DingEntityBase::NULL;

  function getLocalId() {
    return !empty($this->reply->localId) ? $this->reply->localId : FALSE;
  }

  function getOwnerId() {
    return !empty($this->reply->ownerId) ? $this->reply->ownerId : FALSE;
  }

  function getType() {
    return !empty($this->reply->record['dc:type']['dkdcplus:BibDK-Type'][0]) ? $this->reply->record['dc:type']['dkdcplus:BibDK-Type'][0] : FALSE;
  }

  function getTitle() {
    return !empty($this->reply->record['dc:title']) ? $this->reply->record['dc:title'][''][0] : FALSE;
  }

  function getSerieTitle() {
    $titleObj = ( $this->reply && $this->reply->record['dc:title'] ) ? $this->reply->record['dc:title'] : '';
    return !empty($titleObj) && !empty($titleObj['oss:series']) ? $titleObj['oss:series'][0] : FALSE;
  }

  function getAbstract() {
    return !empty($this->reply->record['dcterms:abstract'][''][0]) ? $this->reply->record['dcterms:abstract'][''][0] : FALSE;;
  }

  function getRecord() {
    return $this->reply->record;
  }

  function getRelations() {

    echo "HEST";
    //print_r($this);

    $this->relations = array();
    $relation_objects = array();
    
    // pjo: lazy load here; check if relationsdata is set; if not do a request
    if(isset($this->reply->relationsData) ) {
      //77easy way : 
      $this->reply = ting_get_object($this->ding_entity_id);
      // $reply->realationsData = ting_get_relation_data()
      //
    }


    if (isset($this->reply->relationsData)) {
      $entity_ids = array();
      foreach ($this->reply->relationsData as $record) {
        if (isset($record->relationUri)) {
          $entity_ids[] = $record->relationUri;
        }
      }
      if ($entity_ids) {
        $objects = entity_load('ting_object', array(), array('ding_entity_id' => $entity_ids));
        foreach ($objects as $object) {
          $relation_objects[$object->id] = $object;
        }
      }
      foreach ($this->reply->relationsData as $record) {
        $this->relations[] = new TingRelation($record->relationType, $record->relationUri, isset($relation_objects[$record->relationUri]) ? $relation_objects[$record->relationUri] : NULL);
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
    return !empty($this->reply->record['dc:language'][''][0]) ? $this->reply->record['dc:language'][''][0] : FALSE;
  }

  function getDate() {
    return !empty($this->reply->record['dc:date']) ? $this->reply->record['dc:date'][''][0] : FALSE;
  }

  function getOnline_url() {
    if (isset($this->reply->record['dc:identifier']['dcterms:URI'])) {
      $url = $this->reply->record['dc:identifier']['dcterms:URI'][0];
      drupal_alter('ting_online_url', $url, $this);
      return $url;
    }
  }

  function getAc_source() {
    return !empty($this->reply->record['ac:source'][''][0]) ? $this->reply->record['ac:source'][''][0] : FALSE;
  }
}

/**
 * Ting collection entity.
 */
class TingCollection extends DingEntityCollection {
  public $title = DingEntityBase::NULL;
  public $types = DingEntityBase::NULL;
  public $primary_object = DingEntityBase::NULL;

  function __construct($id) {
    $this->ding_entity_id = $id;
    parent::__construct();
  }

  function getTitle() {
    foreach ($this->reply->objects as &$object) {
      // Find the title of the object that was used to fetch this collection.
      if ($object->id == $this->ding_entity_id && !empty($object->record['dc:title'])) {
        return $object->record['dc:title'][''][0];
      }
    }
    // If we couldn't find the object, use the title of the first object.
    return !empty($this->reply->objects[0]->record['dc:title']) ? $this->reply->objects[0]->record['dc:title'][''][0] : FALSE;
  }

  function getEntities() {
    $this->entities = array();
    if (isset($this->reply->objects)) {
      $entity_ids = array();
      foreach ($this->reply->objects as $record) {
        // Pull the entity with the same id at the top.
        if ($record->id == $this->id) {
          array_unshift($entity_ids, $record->id);
        }
        else {
          $entity_ids[] = $record->id;
        }
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
    return $this->types = array_unique($types);
  }

  function getPrimary_object() {
    if ($entities = $this->entities) {
      return reset($entities);
    }
  }
}
