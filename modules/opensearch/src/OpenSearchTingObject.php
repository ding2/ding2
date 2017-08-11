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
  protected $localProperties = ['openSearchObject'];

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
   * {@inheritdoc}
   */
  public function getFormat() {
    return $this->getRecordEntry('dc:format');
  }

  /**
   * Fetch a record from the Open Search object.
   *
   * @param string $l1_key
   *   Key for the first level of value to fetch
   *
   * @param string $l2_key
   *   Key for the second level of value to fetch. If not specified it is
   *   assumed that the value can be fetched via $array[$l1_key]['']
   *
   * @return mixed
   *   The value from the open search object or FALSE if not found
   */
  protected function getRecordEntry($l1_key, $l2_key = '') {
    // Not a nested value, just fetch by l1_key.
    return isset($this->openSearchObject->record[$l1_key][$l2_key]) ? $this->openSearchObject->record[$l1_key][$l2_key] : FALSE;
  }

  /**
   * {@inheritdoc}
   */
  public function isPartOf() {
    return $this->getRecordEntry('dcterms:isPartOf');
  }

  /**
   * {@inheritdoc}
   */
  public function getSpoken() {
    return $this->getRecordEntry('dc:language', 'dkdcplus:spoken');
  }

  /**
   * {@inheritdoc}
   */
  public function getSubTitles() {
    return $this->getRecordEntry('dc:language', 'dkdcplus:subtitles');
  }

  /**
   * {@inheritdoc}
   */
  public function getGenere() {
    return $this->getRecordEntry('dc:subject', 'dkdcplus:genre');
  }

  /**
   * {@inheritdoc}
   */
  public function getSpatial() {
    return $this->getRecordEntry('dcterms:spatial');
  }

  /**
   * {@inheritdoc}
   */
  public function getMusician() {
    return $this->getRecordEntry('dc:contributor', 'dkdcplus:mus');
  }

  /**
   * {@inheritdoc}
   */
  public function getTracks() {
    return $this->getRecordEntry('dcterms:hasPart', 'dkdcplus:track');
  }

  /**
   * {@inheritdoc}
   */
  public function getReferenced() {
    return $this->getRecordEntry('dcterms:isReferencedBy');
  }

  /**
   * {@inheritdoc}
   */
  public function getSeriesDescription() {
    return $this->getRecordEntry('dc:description', 'dkdcplus:series');
  }

  /**
   * {@inheritdoc}
   */
  public function getDescription() {
    return $this->getRecordEntry('dc:description');
  }

  /**
   * {@inheritdoc}
   */
  public function getSource() {
    return $this->getRecordEntry('dc:source');
  }

  /**
   * {@inheritdoc}
   */
  public function getReplaces() {
    return $this->getRecordEntry('dcterms:replaces');
  }

  /**
   * {@inheritdoc}
   */
  public function getReplacedBy() {
    return $this->getRecordEntry('dcterms:replacedBy');
  }

  /**
   * {@inheritdoc}
   */
  public function getIsbn() {
    return $this->getRecordEntry('dc:identifier', 'dkdcplus:ISBN');
  }

  /**
   * {@inheritdoc}
   */
  public function getURI() {
    $value = $this->getRecordEntry('dc:identifier', 'dcterms:URI');
    foreach ($value as $val) {
      $ret[] = l($val, $val);
    }
  }

  /**
   * {@inheritdoc}
   */
  public function getVersion() {
    return $this->getRecordEntry('dkdcplus:version');
  }

  /**
   * {@inheritdoc}
   */
  public function getExtent() {
    return $this->getRecordEntry('dcterms:extent');
  }

  /**
   * {@inheritdoc}
   */
  public function getPublisher() {
    return $this->getRecordEntry('dc:publisher');
  }

  /**
   * {@inheritdoc}
   */
  public function getRights() {
    return $this->getRecordEntry('dc:rights');
  }

  /**
   * {@inheritdoc}
   */
  public function getAge() {
    return $this->getRecordEntry('dcterms:audience', 'dkdcplus:age');
  }

  /**
   * {@inheritdoc}
   */
  public function getAudience() {
    return $this->getRecordEntry('dcterms:audience');
  }

  /**
   * {@inheritdoc}
   */
  public function getPegi() {
    return $this->getRecordEntry('dcterms:audience', 'dkdcplus:pegi');
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

    // TODO BBS-SAL: Remove logging when SAL is implemented.
    // Everything else goes to the Open Search object.
    watchdog('opensearch', "Getting '$name'", WATCHDOG_DEBUG);
    if (isset($this->openSearchObject->$name)) {
      return $this->openSearchObject->$name;
    }

    return NULL;
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
      // TODO BBS-SAL: Remove logging when SAL is implemented.
      // Everything else goes to the Open Search object.
      watchdog('opensearch', "Setting '$name'", WATCHDOG_DEBUG);
      $this->openSearchObject->$name = $value;
    }
  }

  /**
   * Test if a property is present.
   */
  public function __isset($name) {
    // Handle local properties.
    if (in_array($name, $this->localProperties)) {
      return isset($this->$name);
    }
    // TODO BBS-SAL: Remove logging when SAL is implemented.
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
      // TODO BBS-SAL: Remove logging when SAL is implemented.
      // Everything else goes to the Open Search object.
      watchdog('opensearch', "Unsetting '$name'", WATCHDOG_DEBUG);
      unset($this->openSearchObject->$name);
    }
  }
}
