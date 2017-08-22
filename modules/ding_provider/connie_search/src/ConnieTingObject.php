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
    $this->setLocalId('unique-connie-id');
    $this->setTitle('Connie and the Sorcerer\'s Stone');
    $this->setShortTitle('Connie');
    $this->setDingId('connie-123');
    $this->setOwnerId('connie-agency');
  }
}
