<?php
/**
 * @file
 * The ConnieTingObject class.
 */

namespace Connie\Search;

use Ting\TingObject;

/**
 * TingObjectInterface implementation for testing.
 */
class ConnieTingObject extends TingObject {

  /**
   * ConnieTingObject constructor.
   *
   * @param string $id
   *   The id of the object.
   */
  public function __construct($id) {
    $this->setId($id);
    $this->setSourceId('unique-connie-id');
    $this->setTitle('Connie and the Sorcerer\'s Stone');
    $this->setShortTitle('Connie');
    $this->setOwnerId('connie-agency');
  }

}
