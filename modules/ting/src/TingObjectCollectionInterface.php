<?php
/**
 * @file
 * Provides portable access to a "Ting" object retrieved from a search provider.
 */

namespace Ting;

/**
 * Interface TingObjectCollectionInterface
 *
 * Describes a collection of objects.
 *
 * Eg. The collection "Harry Potter and the Sorcerer's Stone" may contain
 * individual objects for versions of the movie, the book and the audiobook.
 *
 * @package Ting
 */
interface TingObjectCollectionInterface {

  /**
   * Returns the objects in the collection.
   *
   * @return \Ting\TingObjectInterface[]
   *   Returns the objects that makes up the collection.
   */
  public function getObjects();

  /**
   * Get the primary Object in this collection.
   *
   * @return \Ting\TingObjectInterface
   *   The object.
   */
  public function getPrimaryObject();
}
