<?php
/**
 * @file
 * The ConnieTingObject class.
 */

namespace Connie\Search;

use Ting\TingObject;
use Ting\TingObjectInterface;

/**
 * TingObjectInterface implementation for testing.
 *
 * @package Connie\Search
 */
class ConnieTingObject extends TingObject {

  /**
   * ConnieTingObject constructor.
   */
  public function __construct() {
    $this->setSourceId('unique-connie-id');
    $this->setTitle('Connie and the Sorcerer\'s Stone');
    $this->setShortTitle('Connie');
    $this->setId('connie-123');
    $this->setOwnerId('connie-agency');
  }
}
