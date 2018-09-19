<?php

/**
 * @file
 * Entity classes for ting objects and collections.
 */

define('TING_OBJ_DESCRIPTION_LENGTH', 180);

use Ting\TingObjectInterface;
use Ting\TingObjectCollectionInterface;

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

  /**
   * Ting Entity if the relation is a relation to a material.
   *
   * @return \TingEntity|NULL
   *   The entity.
   */
  public function getObject() {
    return $this->properties['object'] !== DingEntityBase::NULL ? $this->properties['object'] : NULL;
  }

  /**
   * Returns the URI for the relation.
   *
   * @return string|NULL
   *   The uri.
   */
  public function getURI() {
    return $this->properties['uri'] !== DingEntityBase::NULL ? $this->properties['uri'] : NULL;
  }

  /**
   * Returns the type of related relation.
   *
   * @return string|NULL
   *   The type.
   */
  public function getType() {
    return $this->properties['type'] !== DingEntityBase::NULL ? $this->properties['type'] : NULL;
  }

}

/**
 * Ting object entity.
 */
class TingEntity extends DingEntity {

  // The following properties are never accessed as actual properties. Instead
  // DingEntityBase (base parent) reads in their default values and removes
  // them. They are from then on accessed via a dynamic getter in
  // DingEntityBase.
  // A future refactor of this class would be to do away with this pattern all
  // together and go back to ordinary getters. This would make the
  // DingEntityBase subclasses much more transparent and make it clear where
  // they are called from.
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

  /**
   * The embedded search-provider specific object.
   *
   * @var Ting\TingObjectInterface
   */
  public $reply;

  /**
   * The Ting object that the entity uses to access data from a search provider.
   *
   * @return \Ting\TingObjectInterface
   *   The object.
   */
  public function getTingObject() {
    return $this->reply;
  }

  /**
   * Set the Ting object the entity should use to access search provider data.
   *
   * @param \Ting\TingObjectInterface $reply
   *   The object.
   */
  public function setTingObject(TingObjectInterface $reply) {
    $this->reply = $reply;
  }

  /**
   * The size or duration of the resource.
   *
   * Eg. "245 sider".
   * Eg. "12 t., 34 min."
   *
   * @return string
   *   The extent.
   */
  public function getExtent() {
    return empty($this->reply) ? FALSE : $this->reply->getExtent();
  }

  /**
   * Returns the material classification.
   *
   * @return string|FALSE
   *   The classification.
   */
  public function getClassification() {
    return empty($this->reply) ? FALSE : $this->reply->getClassification();
  }

  /**
   * Get relations for the material.
   *
   * Eg. "Berlingske tidende, 2005-08-20" (for a newspaper article).
   *
   * @return string[]
   *   Relations.
   */
  public function getIsPartOf() {
    if (empty($this->reply)) {
      return [];
    }

    return $this->reply->isPartOf();
  }

  /**
   * List of contributors to the material.
   *
   * Eg, name of the translator of the material.
   *
   * @return string[]
   *   List of contributors, empty if none could be found.
   */
  public function getContributors() {
    if (empty($this->reply)) {
      return [];
    }
    return $this->reply->getContributors();
  }

  /**
   * Get provider-specific local ID.
   *
   * @return string
   *   The local ID.
   */
  public function getLocalId() {
    return !empty($this->reply) ? $this->reply->getSourceId() : FALSE;
  }

  /**
   * Gets the owner of the object, eg. the agency.
   *
   * @return string
   *   The ID.
   */
  public function getOwnerId() {
    return empty($this->reply) ? FALSE : $this->reply->getOwnerId();
  }

  /**
   * Gets the material type.
   *
   * Eg. "Bog"
   * Eg. "Lydbog (cd)"
   *
   * @return string
   *   The type.
   */
  public function getType() {
    return empty($this->reply) ? FALSE : $this->reply->getType();
  }

  /**
   * Retrieves the title of a material.
   *
   * If a longer version of the title exists it will be preferred.
   *
   * @return FALSE|string
   *   The title of the material, or FALSE if it could not be determined.
   */
  public function getTitle() {
    return empty($this->reply) ? FALSE : $this->reply->getTitle();
  }

  /**
   * List of titles of the series the material is a part of.
   *
   * @return string[]
   *   List of titles, empty if none could be found.
   */
  public function getSeriesTitles() {
    return empty($this->reply) ? [] : $this->reply->getSeriesTitles();
  }

  /**
   * Lists the description of the series the material is a part of.
   *
   * @return mixed
   *   The materials.
   */
  public function getSerieDescription() {
    return empty($this->reply) ? FALSE : $this->reply->getSeriesDescription();
  }

  /**
   * Returns a short abstract for the material.
   *
   * @return string|FALSE
   *   The abstract.
   */
  public function getAbstract() {
    return empty($this->reply) ? FALSE : $this->reply->getAbstract();
  }

  /**
   * Retrives materials related to the material represented by this entity.
   *
   * @return TingRelation[]
   *   Array of TingRelation instances.
   */
  public function getRelations() {
    return empty($this->reply) ? [] : $this->reply->getRelations();
  }

  /**
   * Returns the creators of the material.
   *
   * For a book the creator would typically be the author.
   *
   * @return string[].
   *   The list of formatted author-names, empty if none was found.
   */
  public function getCreators() {
    return empty($this->reply) ? [] : $this->reply->getCreators();
  }

  /**
   * Get the creators field with inverted fields.
   *
   * @return array
   *   List of item creators with inverted fields.
   */
  public function getInvertedCreators() {
    return empty($this->reply) ? [] : $this->reply->getCreators(TingObjectInterface::NAME_FORMAT_SURNAME_FIRST);
  }

  /**
   * Returns list of subjects/keywords for the material.
   *
   * @return string[]
   *   List of subjects, empty if none could be found.
   */
  public function getSubjects() {
    return empty($this->reply) ? [] : $this->reply->getSubjects();
  }

  /**
   * The language of the material.
   *
   * @return string|FALSE
   *   The language, FALSE if it could not be found.
   */
  public function getLanguage() {
    return empty($this->reply) ? FALSE : $this->reply->getLanguage();
  }

  /**
   * Get the year the material was produced.
   *
   * Format YYYY.
   *
   * @return string
   *   The year
   */
  public function getDate() {
    return empty($this->reply) ? FALSE : $this->reply->getYear();
  }

  /**
   * Try to find the online url.
   *
   * @return mixed
   *   URL to the online resource or the empty string if not found.
   */
  public function getOnline_url() {
    return empty($this->reply) ? FALSE : $this->reply->getOnlineUrl();
  }

  /**
   * Whether the material is a purely online material.
   *
   * @return bool
   *   TRUE if the material can only be found online.
   */
  public function isOnline() {
    return empty($this->reply) ? FALSE : $this->reply->isOnline();
  }

  /**
   * Returns the original source of the material.
   *
   * Eg. Bibliotekskatalog, Anmeldelser.
   *
   * @return string|FALSE
   *   The source of the material.
   */
  public function getAc_source() {
    return empty($this->reply) ? FALSE : $this->reply->getMaterialSource();
  }

  /**
   * Get an description of the material.
   *
   * @return string
   *   The description.
   */
  public function getDescription() {
    return empty($this->reply) ? FALSE : $this->reply->getDescription();
  }

  /**
   * The ISBN of the material.
   *
   * Eg. "9780615384238"
   *
   * @return string[]
   *   Zero or more ISBNs.
   */
  public function getIsbn() {
    return empty($this->reply) ? FALSE : $this->reply->getIsbn();
  }
}

/**
 * Ting collection entity.
 */
class TingCollection extends DingEntityCollection {
  // Default properties we want handled via magic getters in DingEntityBase.
  public $title = DingEntityBase::NULL;
  public $types = DingEntityBase::NULL;
  public $types_count = DingEntityBase::NULL;
  public $primary_object = DingEntityBase::NULL;

  /**
   * The embedded search-provider specific object.
   *
   * @var Ting\TingObjectCollectionInterface
   */
  protected $tingObjectCollection;

  /**
   * Set the collection from the Ting search provider.
   *
   * @param \Ting\TingObjectCollectionInterface $tingObjectCollection
   *   The collection.
   */
  public function setTingObjectCollection(TingObjectCollectionInterface $tingObjectCollection) {
    $this->tingObjectCollection = $tingObjectCollection;
  }

  /**
   * Get the collection from the Ting search provider.
   *
   * @return \Ting\TingObjectCollectionInterface
   *   The collection.
   */
  public function getTingObjectCollection() {
    return $this->tingObjectCollection;
  }

  /**
   * TingCollection constructor.
   *
   * @param string $id
   *   Entity Id.
   * @param \Ting\TingObjectCollectionInterface $object_collection
   *   Search provider collection.
   */
  public function __construct($id, \Ting\TingObjectCollectionInterface $object_collection) {
    $this->ding_entity_id = $id;
    $this->tingObjectCollection = $object_collection;

    parent::__construct();
  }

  /**
   * The title of the collection.
   *
   * @return string|FALSE
   *   The title or FALSE if it could not be determined.
   */
  public function getTitle() {
    foreach ($this->tingObjectCollection->getObjects() as $object) {
      // Find the title of the object that was used to fetch this collection. We
      // don't look at dkdcplus:full as it might be too specific ("1Q84. Book 1"
      // for instance).
      if ($object->getId() === $this->getId() && !empty($object->getShortTitle())) {
        return $object->getShortTitle();
      }
    }

    // If we couldn't find the object, use the title of the first object.
    $primary_object = $this->tingObjectCollection->getPrimaryObject();
    return $primary_object === NULL ? FALSE : $primary_object->getShortTitle();
  }

  /**
   * Get list of entities in this collection.
   *
   * @return \Ting\TingObject[]
   *   List of TingObject instances.
   */
  public function getEntities() {
    // Override magic getter-property from DingEntityBase by setting a property.
    // This way this getter will only be invoked once as long as the caller
    // uses property access.
    $this->entities = array();
    $objects = $this->tingObjectCollection->getObjects();
    if (!empty($objects)) {
      $entity_ids = array();
      foreach ($objects as $record) {
        // Pull the entity with the same id at the top.
        if ($record->getId() == $this->getId()) {
          array_unshift($entity_ids, $record->getId());
        }
        else {
          $entity_ids[] = $record->getId();
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

  /**
   * List of material types.
   *
   * Eg. "Bog".
   *
   * @return string[]
   *   The list.
   */
  public function getTypes() {
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

  /**
   * Gets the number of different types of materials in the collection.
   *
   * @return array
   *   Count of the various types, keyed by type name.
   */
  public function getTypes_count() {
    $types = array();
    foreach ($this->entities as $object) {
      if (!isset($types[$object->type])) {
        $types[$object->type] = 1;
      }
      else {
        $types[$object->type]++;
      }
    }
    return $this->types_count = $types;
  }

  /**
   * Get the primary Object in this collection.
   *
   * @return \TingEntity|NULL
   *   The object.
   */
  public function getPrimary_object() {
    if ($entities = $this->entities) {
      return reset($entities);
    }
  }
}
