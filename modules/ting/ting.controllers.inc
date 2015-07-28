<?php

/**
 * @file
 * Entity controllers for TingEntity and TingCollection
 */

/**
 * Controller class for ting objects.
 */
class TingObjectController extends DrupalDefaultEntityController {
  public function load($ids = array(), $conditions = array()) {
    module_load_include('client.inc', 'ting');
    $queried_entities = array();
    // We really don't support loading of all objects. We're adding to
    // $ids depending on conditions.
    if ($ids === FALSE) {
      $ids = array();
    }

    // Ensure that the requested entities exists locally if getting by
    // ding_entity_id.
    $unknown = array();
    if (isset($conditions['ding_entity_id'])) {
      $query = db_select($this->entityInfo['base table'], 'base');
      $query->addField('base', 'ding_entity_id');
      $query->addField('base', 'tid');
      $query->condition('ding_entity_id', $conditions['ding_entity_id']);
      $known = $query->execute()->fetchAllKeyed();
      foreach ($conditions['ding_entity_id'] as $ding_entity_id) {
        if (!isset($known[$ding_entity_id])) {
          // Collect all unknown.
          $unknown[$ding_entity_id] = $ding_entity_id;
        }
        elseif (!in_array($ding_entity_id, $ids)) {
          // Add the local id to the ids loaded.
          $ids[] = $known[$ding_entity_id];
        }
      }
    }

    // This is the same as parent::load(), with the exception that we fetch
    // into objects.
    $entities = array();

    // Revisions are not statically cached, and require a different query to
    // other conditions, so separate the revision id into its own variable.
    if ($this->revisionKey && isset($conditions[$this->revisionKey])) {
      $revision_id = $conditions[$this->revisionKey];
      unset($conditions[$this->revisionKey]);
    }
    else {
      $revision_id = FALSE;
    }

    // Create a new variable which is either a prepared version of the $ids
    // array for later comparison with the entity cache, or FALSE if no $ids
    // were passed. The $ids array is reduced as items are loaded from cache,
    // and we need to know if it's empty for this reason to avoid querying the
    // database when all requested entities are loaded from cache.
    $passed_ids = !empty($ids) ? array_flip($ids) : FALSE;
    // Try to load entities from the static cache, if the entity type supports
    // static caching.
    if ($this->cache && !$revision_id) {
      $entities += $this->cacheGet($ids, $conditions);
      // If any entities were loaded, remove them from the ids still to load.
      if ($passed_ids) {
        $ids = array_keys(array_diff_key($passed_ids, $entities));
      }
    }

    $cached_entity_ids = array();
    foreach ($entities as $entity) {
      $cached_entity_ids[] = $entity->ding_entity_id;
    }

    // Load any remaining entities from the database. This is the case if $ids
    // is set to FALSE (so we load all entities), if there are any ids left to
    // load, if loading a revision, or if $conditions was passed without $ids.
    if ($ids === FALSE || $ids || $revision_id || ($conditions && !$passed_ids)) {
      // Build the query.
      $query = $this->buildQuery($ids, $conditions, $revision_id);
      $result = $query->execute();
      // Normally we'd use fetchAllAssoc($this->idKey, 'TingEntity'),
      // but DatabaseStatementPrefetch is buggy.
      $result->setFetchMode(PDO::FETCH_CLASS, 'TingEntity');
      $queried_entities = $result->fetchAllAssoc($this->idKey);
    }

    $objects = array();
    // Now load all objects in one go.
    $get_ids = !empty($conditions['ding_entity_id']) ? $conditions['ding_entity_id'] : array();
    foreach ($queried_entities as $qe) {
      $get_ids[] = $qe->ding_entity_id;
    }
    if ($get_ids && $load_ids = array_diff($get_ids, $cached_entity_ids)) {
      $objects = ting_get_objects(array_unique($load_ids));
    }

    // Not known locally. Create a proxy if it exists in the well.
    if (count($unknown)) {
      $new_ids = array();
      foreach ($unknown as $ding_entity_id) {
        if (isset($objects[$ding_entity_id])) {
          // Insert a new local proxy row.
          $ting_object = array(
            'ding_entity_id' => $ding_entity_id,
          );
          drupal_write_record('ting_object', $ting_object);
          drupal_write_record('ting_object_revision', $ting_object);
          db_update('ting_object')
            ->fields(array('vid' => $ting_object['vid']))
            ->condition('tid', $ting_object['tid'])
            ->execute();
          // Add new id to the loaded set.
          $new_ids[] = $ting_object['tid'];
        }
      }
      if ($new_ids) {
        // Build the query.
        $query = $this->buildQuery($new_ids, array());
        $result = $query->execute();
        // Normally we'd use fetchAllAssoc($this->idKey, 'TingEntity'),
        // but DatabaseStatementPrefetch is buggy.
        $result->setFetchMode(PDO::FETCH_CLASS, 'TingEntity');
        $queried_entities += $result->fetchAllAssoc($this->idKey);
      }
    }

    foreach ($queried_entities as &$qe) {
      $qe->reply = $objects[$qe->ding_entity_id];
    }
    // Pass all entities loaded from the database through $this->attachLoad(),
    // which attaches fields (if supported by the entity type) and calls the
    // entity type specific load callback, for example hook_node_load().
    if (!empty($queried_entities)) {
      $this->attachLoad($queried_entities, $revision_id);
      $entities += $queried_entities;
    }

    // If entity supports cache.
    if ($this->cache) {
      // Add entities to the cache if we are not loading a revision.
      if (!empty($queried_entities) && !$revision_id) {
        $this->cacheSet($queried_entities);
      }
    }

    // Ensure that the returned array is ordered the same as the original
    // $ids array if this was passed in and remove any invalid ids.
    if ($passed_ids) {
      // Remove any invalid ids from the array.
      $passed_ids = array_intersect_key($passed_ids, $entities);
      foreach ($entities as $entity) {
        $passed_ids[$entity->{$this->idKey}] = $entity;
      }
      $entities = $passed_ids;
    }
    return $entities;
  }

  /**
   * Gets entities from the static cache.
   *
   * Superclass method doesn't deal with arrays in conditions.
   */
  protected function cacheGet($ids, $conditions = array()) {
    $entities = array();
    // Load any available entities from the internal cache.
    if (!empty($this->entityCache)) {
      if ($ids) {
        $entities += array_intersect_key($this->entityCache, array_flip($ids));
      }
      // If loading entities only by conditions, fetch all available entities
      // from the cache. Entities which don't match are removed later.
      elseif ($conditions) {
        $entities = $this->entityCache;
      }
    }

    // Exclude any entities loaded from cache if they don't match $conditions.
    // This ensures the same behavior whether loading from memory or database.
    if ($conditions) {
      // Check that conditions has ding_entity_id key.
      if (!empty($conditions['ding_entity_id'])) {
        foreach ($entities as $entity) {
          if (!in_array($entity->ding_entity_id, $conditions['ding_entity_id'])) {
            unset($entities[$entity->{$this->idKey}]);
          }
        }
      }
    }

    return $entities;
  }
}

/**
 * Controller class for ting collections.
 */
class TingCollectionController implements DrupalEntityControllerInterface {

  /**
   * Static cache of entities.
   *
   * @var array
   */
  protected $entityCache;

  /**
   * Constructor: sets basic variables.
   */
  public function __construct($entityType) {
    $this->entityCache = array();
  }

  protected function cacheSet($entities) {
    $this->entityCache += $entities;
  }

  /**
   * Implements DrupalEntityControllerInterface::resetCache().
   */
  public function resetCache(array $ids = NULL) {
    if (isset($ids)) {
      foreach ($ids as $id) {
        unset($this->entityCache[$id]);
      }
    }
    else {
      $this->entityCache = array();
    }
  }

  /**
   * Implements DrupalEntityControllerInterface::load().
   */
  public function load($ids = array(), $conditions = array()) {
    module_load_include('client.inc', 'ting');
    $entities = array();
    $queried_entities = array();
    if (isset($conditions['ding_entity_id'])) {
      foreach ($conditions['ding_entity_id'] as $ding_entity_id) {
        if (isset($this->entityCache[$ding_entity_id])) {
          $entities[$ding_entity_id] = $this->entityCache[$ding_entity_id];
        }
        else {
          $reply = ting_get_object($ding_entity_id, TRUE);
          $object = NULL;
          if ($reply) {
            $object = new TingCollection($ding_entity_id);
            $object->reply = $reply;
            $queried_entities[$ding_entity_id] = $object;
          }

          if (isset($object)) {
            $entities[$ding_entity_id] = $object;
            // $this->entityCache[$ding_entity_id] = $object;
          }
        }
      }
    }

    if (!empty($queried_entities)) {
      $this->attachLoad($queried_entities);
      $entities += $queried_entities;
    }

    if (!empty($queried_entities)) {
      $this->cacheSet($queried_entities);
    }

    return $entities;
  }

  /**
   * Implements DrupalEntityControllerInterface::attachLoad().
   */
  protected function attachLoad(&$queried_entities) {
    // Attach fields.
    field_attach_load('ting_collection', $queried_entities);

    // Call hook_entity_load().
    foreach (module_implements('entity_load') as $module) {
      $function = $module . '_entity_load';
      $function($queried_entities, 'ting_collection');
    }
    $args = array(array($queried_entities));
    foreach (module_implements('ting_collection_load') as $module) {
      call_user_func_array($module . '_ting_collection_load', $args);
    }
  }
}
