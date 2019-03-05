<?php
/**
 * @file
 * The OpenSearchTingCollection class.
 */

namespace OpenSearch;

use Ting\TingObjectCollectionInterface;
use TingClientObjectCollection;

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
  public function __construct(TingClientObjectCollection $collection) {
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
    // We work under the assumption that this collection would never be
    // instantiated if $this->tingObjects was empty so no null check here.
    return array_shift($objects);
  }
}
