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

  public function getObject() {
    return $this->properties['object'];
  }

  public function getURI() {
    return $this->properties['uri'];
  }

  public function getType() {
    return $this->properties['type'];
  }
}

/**
 * Ting object entity.
 */
class TingEntity extends DingEntity {
  public $type = DingEntityBase::NULL;
  public $serieNumber = DingEntityBase::NULL;
  public $serieTitle = DingEntityBase::NULL;
  public $serieDescription = DingEntityBase::NULL;
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
  public $description = DingEntityBase::NULL;
  public $contributors = DingEntityBase::NULL;
  public $isPartOf = DingEntityBase::NULL;
  public $extent = DingEntityBase::NULL;
  public $classification = DingEntityBase::NULL;
  public $isbn = DingEntityBase::NULL;

  public function getExtent() {
    return !empty($this->reply->record['dcterms:extent'][''][0]) ? $this->reply->record['dcterms:extent'][''][0] : FALSE;
  }

  function getClassification() {
    $dk5 = '';
    if (!empty($this->reply->record['dc:subject']['dkdcplus:DK5'][0])) {
      $dk5 = $this->reply->record['dc:subject']['dkdcplus:DK5'][0];

      if ($dk5 == 'sk') {
        return '';
      }

      return $dk5;
    }

    return FALSE;
  }

  function getClassificationText() {
    $dk5_text = !empty($this->reply->record['dc:subject']['dkdcplus:DK5-Text'][0]) ? $this->reply->record['dc:subject']['dkdcplus:DK5-Text'][0] : '';

    return $dk5_text;
  }

  function getIsPartOf() {
    $this->isPartOf = array();
    if( !empty($this->reply->record['dcterms:isPartOf']) ) {
      foreach($this->reply->record['dcterms:isPartOf'] as $type => $dcterms_ispartof ) {
        if( $type != 'oss:sort' ) {
          $this->isPartOf = array_merge($this->isPartOf, $dcterms_ispartof);
        }
      }
    }
    return $this->isPartOf;
  }

  // pjo 26-09-11 ; getmethod contributor
  function getContributors() {
    $this->contributors = array();
    if( !empty($this->reply->record['dc:contributor']) ) {
      foreach($this->reply->record['dc:contributor'] as $type => $dc_contributor ) {
        if( $type != 'oss:sort' ) {
          $this->contributors = array_merge($this->contributors, $dc_contributor);
        }
      }
    }
    return $this->contributors;
  }


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
    $title = FALSE;
    if (!empty($this->reply->record['dc:title'])) {
      // Use first title with dkdcplus:full if available.
      if (isset($this->reply->record['dc:title']['dkdcplus:full'])) {
        $title = $this->reply->record['dc:title']['dkdcplus:full'][0];
      }
      else {
        $title = $this->reply->record['dc:title'][''][0];
      }
    }
    return $title;
  }


  private function splitSerie() {
    $series = !empty($this->reply->record['dc:title']['dkdcplus:series']) ? $this->reply->record['dc:title']['dkdcplus:series'] : array();
    $serie_titles = array();
    foreach ($series as $serie) {
      $serie_titles[] = explode(';', $serie);
    }
    return $serie_titles;
  }

  function getSerieTitle() {
    return $this->splitSerie();
  }

 function getSerieDescription() {
    $serie = !empty($this->reply->record['dc:description']['dkdcplus:series'][0]) ? $this->reply->record['dc:description']['dkdcplus:series'][0] : '';
    return $this->process_series_description($serie);
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
  private function process_series_description($series) {
    $result = '';
    $parts = explode(':', $series);

    if (is_array($parts) && count($parts) >= 2) {
      $prefix = $parts[0] . ': ';

      if (stripos($prefix, 'del af:') !== FALSE) {
        $title = trim($parts[1]);
        $path = str_replace('@serietitle', drupal_strtolower($title), variable_get('ting_search_register_serie_title', 'phrase.titleSeries="@serietitle"'));
        $link = l($title, 'search/ting/' . $path, array('attributes' => array('class' => array('series'))));
        $result = $prefix . $link;
      } else if (stripos($prefix, 'Samhørende:') !== FALSE) {
        $titles = $parts[1];
        // Multiple titles are separated by ' ; '. Explode to iterate over them
        $titles = explode(' ; ', $titles);
        foreach ($titles as &$title) {
          $title = trim($title);
          // Some title elements are actually volumne numbers. Do not convert these to links
          if (!preg_match('/(nr.)? \d+/i', $title)) {
            $title = l($title, 'search/ting/' . '"' . $title . '"');
          }
        }
        // Reassemple titles
        $titles = implode(', ', $titles);
        $result = $prefix . ' ' . $titles;
      }
      else {
        return $series;
      }
    }

    return $result;
  }

  function getAbstract() {
    return !empty($this->reply->record['dcterms:abstract'][''][0]) ? $this->reply->record['dcterms:abstract'][''][0] : FALSE;
  }

  function getRecord() {
    return !empty($this->reply->record) ? $this->reply->record : false;
  }

  function getRelations() {
    // If relations are not set; do another request to get relations
    if (!isset($this->reply->relationsData)) {
      $tingClientObject = ting_get_object($this->ding_entity_id, FALSE, TRUE);
      if (isset($tingClientObject->relationsData)) {
        $this->reply->relationsData = $tingClientObject->relationsData;
      }
    }

    $this->relations = array();
    $relation_objects = array();
    if (isset($this->reply->relationsData)) {
      $entity_ids = array();
      foreach ($this->reply->relationsData as $record) {
        if (isset($record->relationUri) && isset($record->relationObject)) {
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

  /**
   * Get the creators field with inverted fields.
   *
   * @return array
   *   List of item creators with inverted fields.
   */
  public function getInvertedCreators() {
    $this->creator = array();
    if (!empty($this->reply->record['dc:creator']['oss:sort'])) {
      $this->creator = $this->reply->record['dc:creator']['oss:sort'];
    }

    return $this->creator;
  }

  function getSubjects() {
    $this->subjects = array();
    if (!empty($this->reply->record['dc:subject'])) {
      foreach ($this->reply->record['dc:subject'] as $type => $dc_subject) {
        if (!in_array($type, array('dkdcplus:genre', 'dkdcplus:DK5', 'dkdcplus:DK5-Text', 'dkdcplus:DBCO', 'dkdcplus:DBCN'))) {
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

  /**
   * Try to find the online url.
   *
   * @param bool $get_relations
   *   If TRUE relations will be fetched from the data well else "dc:identifier"
   *   will be checked.
   *
   * @return mixed
   *   URL to the online resource or the empty string if not found.
   */
  function getOnline_url($get_relations = TRUE) {
    $url = '';
    if ($get_relations) {
      // Try to find the online url from relation data, which requires us to get
      // relations. First check if relations are set; if not do another request
      // to get relations
      if (!isset($this->reply->relationsData)) {
        $tingClientObject = ting_get_object($this->ding_entity_id, FALSE, TRUE);
        if (isset($tingClientObject->relationsData)) {
          $this->reply->relationsData = $tingClientObject->relationsData;
        }
      }
      if (isset($this->reply->relationsData)) {
        foreach ($this->reply->relationsData as $data) {
          if ($data->relationType == 'dbcaddi:hasOnlineAccess') {
            $url = preg_replace('/^\[URL\]/', '', $data->relationUri);
            // Check for correct url or leading token - some uri is only an id.
            if (stripos($url, 'http') === 0 || strpos($url, '[') === 0) {
              // Give other modules a chance to rewrite the url.
              drupal_alter('ting_online_url', $url, $this);
            }
          }
        }
      }
    }

    // No hasOnlineAccess found so fallback to dc:identifier.
    if (empty($url) && isset($this->reply->record['dc:identifier']['dcterms:URI'])) {
      $url = $this->reply->record['dc:identifier']['dcterms:URI'][0];
      // Give ting_proxy a change to rewrite the url.
      drupal_alter('ting_online_url', $url, $this);
    }

    return $url;
  }

  function getAc_source() {
    return !empty($this->reply->record['ac:source'][''][0]) ? $this->reply->record['ac:source'][''][0] : FALSE;
  }

  function getDescription() {
    return !empty($this->reply->record['dc:description'][''][0]) ? $this->reply->record['dc:description'][''][0] : FALSE;
  }

  /**
   * Get ISBN numbers of the object.
   *
   * @return array
   */
  function getIsbn() {
    $isbn = array();

    // Nothing to do.
    if (empty($this->reply->record['dc:identifier']['dkdcplus:ISBN'])) {
      return $isbn;
    }

    // Get ISBN numbers.
    $isbn = $this->reply->record['dc:identifier']['dkdcplus:ISBN'];
    foreach ($isbn as $k => $number) {
      $isbn[$k] = str_replace(array(' ', '-'), '', $number);
    }
    rsort($isbn);
    return $isbn;
  }

}

/**
 * Ting collection entity.
 */
class TingCollection extends DingEntityCollection {
  public $title = DingEntityBase::NULL;
  public $types = DingEntityBase::NULL;
  public $types_count = DingEntityBase::NULL;
  public $primary_object = DingEntityBase::NULL;

  function __construct($id) {
    $this->ding_entity_id = $id;
    parent::__construct();
  }

  function getTitle() {
    foreach ($this->reply->objects as &$object) {
      // Find the title of the object that was used to fetch this collection. We
      // don't look at dkdcplus:full as it might be too specific ("1Q84. Book 1"
      // for instance).
      if ($object->id == $this->ding_entity_id && !empty($object->record['dc:title'])) {
        return $object->record['dc:title'][''][0];
      }
    }

    // If we couldn't find the object, use the title of the first object.
    $title = FALSE;
    if (isset($this->reply->objects[0]->record['dc:title'])) {
      $title = $this->reply->objects[0]->record['dc:title'][''][0];
    }

    return $title;
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

  function getTypes_count() {
    $types = array();
    foreach ($this->entities as $object) {
      if ( !isset($types[$object->type] ) ) {
        $types[$object->type] = 1;
      } else {
        $types[$object->type]++;
      }
    }
    return $this->types_count = $types;
  }

  function getPrimary_object() {
    if ($entities = $this->entities) {
      return reset($entities);
    }
  }
}

