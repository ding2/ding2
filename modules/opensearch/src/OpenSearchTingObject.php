<?php
/**
 * @file
 * OpenSearchTingObject class.
 */

namespace OpenSearch;

use Drupal\ting\TingObjectInterface;
use TingClientObject;

/**
 * Class OpenSearchObject
 *
 * Represents a material from Open Search.
 *
 * @package OpenSearch
 */
class OpenSearchTingObject implements TingObjectInterface {

  /**
   * @var string[] list of property-names that can be found directly on $this
   *   and should not be delegated to $this->clientObject.
   */
  protected $localProperties = ['clientObject'];

  /**
   * @var TingClientObject an object from the Ting Client that represents a
   *   material search object.
   */
  protected $openSearchObject;

  /**
   * OpenSearchObject constructor.
   *
   * @param TingClientObject $open_search_object
   *   The Open Search result this object wraps.
   */
  public function __construct($open_search_object) {
    $this->openSearchObject = $open_search_object;
  }

  /**
   * Retrieves the title of a material.
   *
   * @return FALSE|string
   *   The title of the material, or FALSE if it could not be determined.
   */
  public function getTitle() {
    $title = FALSE;
    if (!empty($this->openSearchObject->record['dc:title'])) {
      // Use first title with dkdcplus:full if available.
      if (isset($this->openSearchObject->record['dc:title']['dkdcplus:full'])) {
        $title = $this->openSearchObject->record['dc:title']['dkdcplus:full'][0];
      }

      else {
        $title = $this->openSearchObject->record['dc:title'][''][0];
      }
    }
    return $title;
  }

  /**
   * Handle property mutation.
   */
  public function __set($name, $value) {
    // Handle local properties.
    if (in_array($name, $this->localProperties)) {
      $this->$name = $value;
    }
    else {
      // Everything else goes to the Open Search object.
      watchdog('opensearch', "Setting '$name'", WATCHDOG_DEBUG);
      $this->openSearchObject->$name = $value;
    }
  }

  /**
   * Handle property reads.
   *
   * Delegates all non-local property reads to the Open Search object.
   */
  public function __get($name) {
    // Handle local properties.
    if (in_array($name, $this->localProperties)) {
      return $this->$name;
    }

    // Everything else goes to the Open Search object.
    watchdog('opensearch', "Getting '$name'", WATCHDOG_DEBUG);
    if (isset($this->openSearchObject->$name)) {
      return $this->openSearchObject->$name;
    }

    return NULL;
  }

  /**
   * Test if a property is present.
   */
  public function __isset($name) {
    // Handle local properties.
    if (in_array($name, $this->localProperties)) {
      return isset($this->$name);
    }

    // Everything else goes to the Open Search object.
    watchdog('opensearch', "Is '$name' set?", WATCHDOG_DEBUG);
    return isset($this->openSearchObject->$name);
  }

  /**
   * Unsets a property.
   */
  public function __unset($name) {
    // Handle local properties.
    if (in_array($name, $this->localProperties)) {
      unset($this->$name);
    }
    else {
      // Everything else goes to the Open Search object.
      watchdog('opensearch', "Unsetting '$name'", WATCHDOG_DEBUG);
      unset($this->openSearchObject->$name);
    }
  }
}
