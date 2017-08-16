<?php
/**
 * @file
 * The OpenSearchTingCollection class.
 */

namespace OpenSearch;

use Ting\TingObjectCollectionInterface;

/**
 * Class OpenSearchTingObjectCollection
 *
 * Wraps a TingClientObjectCollection to provide integration to Ding.
 * @package OpenSearch
 */
class OpenSearchTingObjectCollection implements TingObjectCollectionInterface {

  /**
   * @var \OpenSearch\OpenSearchTingObject[]
   */
  protected $tingObjects = [];

  /**
   * OpenSearchTingCollection constructor.
   *
   * @param \TingClientObjectCollection $collection
   *   Collection from the ting client.
   */
  public function __construct($collection) {
    if (!empty($collection->objects)) {
      $this->tingObjects = array_map(function ($object) {
        return new OpenSearchTingObject($object);
      }, $collection->objects);
    }
  }

  /**
   * {@inheritdoc}
   */
  public function getObjects() {
    return $this->tingObjects;
  }

  /**
   * {@inheritdoc}
   */
  public function getPrimaryObject() {
    // Get the first array-entry (without modifying the array).
    $objects = array_values($this->tingObjects);
    return empty($this->tingObjects) ? NULL : array_shift($objects);
  }
}
