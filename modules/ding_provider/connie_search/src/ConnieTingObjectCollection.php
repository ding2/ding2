<?php
/**
 * @file
 * The ConnieTingObjectCollection class.
 */

namespace Connie\Search;

use Ting\TingObjectCollectionInterface;

/**
 * Dummy object collection implementation.
 *
 * Implemented for testing purposes.
 */
class ConnieTingObjectCollection implements TingObjectCollectionInterface {

  /**
   * @var \Ting\TingObjectInterface[]
   */
  protected $objects;

  /**
   * ConnieObjectCollection constructor.
   *
   * @param \Ting\TingObjectInterface[] $objects
   *   The objects in the collection.
   */
  public function __construct(array $objects) {
    $this->objects = $objects;
  }

  /**
   * {@inheritdoc}
   */
  public function getObjects() {
    return $this->objects;
  }

  /**
   * {@inheritdoc}
   */
  public function getPrimaryObject() {
    // Get the first array-entry (without modifying the array).
    $objects = array_values($this->objects);
    return empty($this->tingObjects) ? NULL : array_shift($objects);
  }

  /**
   * Simple factory for returning a collection with a single object.
   *
   * @return \Connie\Search\ConnieTingObjectCollection
   *   The collection.
   */
  public static function getSingleCollection() {
    return new self([new ConnieTingObject()]);
  }

}
