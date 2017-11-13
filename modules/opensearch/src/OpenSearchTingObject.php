<?php
/**
 * @file
 * OpenSearchTingObject class.
 */

namespace OpenSearch;

use Ting\TingObjectInterface;
use TingClientObject;
use TingRelation;

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
   * @var string Id of the owner of the object, eg. the Agency.
   */
  protected $ownerId;

  /**
   * @var TingRelation[] list of materials related to this material.
   */
  protected $relations;

  /**
   * {@inheritdoc}
   */
  public function getId() {
    return $this->openSearchObject->id;
  }

  public function getRelations(){
    return [];
  }

  public function isLocal() {
    return variable_get('ting_agency', -1) != $this->getOwnerId();
  }

  /**
   * Get provider-specific local ID.
   *
   * @return string
   *   The local ID.
   */
  public function getSourceId() {
    return $this->openSearchObject->localId;
  }

  /**
   * Sets the Ding id.
   *
   * @param string $id
   *   The Ding specific ID for the object. Usually the entity id.
   */
  public function setId($id) {
    $this->id = $id;
  }

  /**
   * {@inheritdoc}
   */
  public function getOwnerId() {
    return $this->ownerId;
  }

  /**
   * Sets the Owner ID.
   */
  public function setOwnerId($owner_id) {
    $this->ownerId = $owner_id;
  }


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
   * {@inheritdoc}
   */
  public function getTitle() {
    $long_title = $this->firstEntry($this->getRecordEntry('dc:title', 'dkdcplus:full'));
    return $long_title ?: $this->getShortTitle();
  }

  /**
   * {@inheritdoc}
   */
  public function getShortTitle() {
    return $this->firstEntry($this->getRecordEntry('dc:title'));
  }

  /**
   * {@inheritdoc}
   */
  public function getType() {
    return $this->firstEntry($this->getRecordEntry('dc:type', 'dkdcplus:BibDK-Type'));
  }

  /**
   * {@inheritdoc}
   */
  public function getFormat() {
    return $this->getRecordEntry('dc:format');
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
    $description = $this->getRecordEntry('dc:description', 'dkdcplus:series');
    return $this->processSeriesDescription($description;

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
   * {@inheritdoc}
   */
  public function getYear() {
    return $this->firstEntry($this->getRecordEntry('dc:date'));
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
   * @return string|array|FALSE
   *   The value from the open search object or FALSE if not found
   */
  protected function getRecordEntry($l1_key, $l2_key = '') {
    // Not a nested value, just fetch by l1_key.
    return isset($this->openSearchObject->record[$l1_key][$l2_key]) ? $this->openSearchObject->record[$l1_key][$l2_key] : FALSE;
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
    watchdog('opensearch', "Getting '$name'", [], WATCHDOG_DEBUG);
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
      watchdog('opensearch', "Setting '$name'", [], WATCHDOG_DEBUG);
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
    watchdog('opensearch', "Is '$name' set?", [], WATCHDOG_DEBUG);
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
      watchdog('opensearch', "Unsetting '$name'", [], WATCHDOG_DEBUG);
      unset($this->openSearchObject->$name);
    }
  }

  /**
   * Get the first entry from a Record Entry.
   *
   * Record Entries assumes that an entry can have multiple values for the same
   * key (eg. a material may have Subtitles in several languages), thus we
   * generally return entries as arrays.
   *
   * Use this function if you want to assume that there is only one entry for
   * the entry and you want to skip the array.
   *
   * TODO BBS-SAL: This distinction between "details" properties (which we
   * return as arrays) and the rest (eg. getYear) where we return the first
   * entry in the array because the caller seems to require it is confusing.
   * Should we just decide the cardinallity of the fields up front, or should we
   * stick to the "old" conversion and always return a [$value]?
   *
   * @param mixed $entry
   *   An entry
   *
   * @return mixed
   *   The first entry in the array or the entry itself if it is not an array.
   */
  protected function firstEntry($entry) {
    if (is_array($entry) && count($entry) > 0) {
      $array_values = array_values($entry);
      return array_shift($array_values);
    }

    // Return the entry back if it is not an array.
    return $entry;
  }

  /**
   * Process series information.
   *
   * This could be handled more elegantly if we had better structured data.
   * For now we have to work with what we got to convert titles to links
   * Series information appear in the following formats:
   * - Samhørende: [title 1] ; [title 2] ; [title 3]
   * - [volumne number]. del af: [title]
   *
   * @param string[] $series
   *   List of series descriptions.
   */
  private function processSeriesDescription($series) {
    $result = '';
    $parts = explode(':', $series);

    if (is_array($parts) && count($parts) >= 2) {
      $prefix = $parts[0] . ': ';

      if (stripos($prefix, 'del af:') !== FALSE) {
        $title = trim($parts[1]);
        $path = str_replace('@serietitle', drupal_strtolower($title), variable_get('ting_search_register_serie_title', 'phrase.titleSeries="@serietitle"'));
        $link = l($title, 'search/ting/' . $path, array('attributes' => array('class' => array('series'))));
        $result = $prefix . $link;
      }
      elseif (stripos($prefix, 'Samhørende:') !== FALSE) {
        $titles = $parts[1];
        // Multiple titles are separated by ' ; '. Explode to iterate over them.
        $titles = explode(' ; ', $titles);
        foreach ($titles as &$title) {
          $title = trim($title);
          // Some title elements are actually volumne numbers.
          // Do not convert these to links.
          if (!preg_match('/(nr.)? \d+/i', $title)) {
            $title = l($title, 'search/ting/"' . $title . '"');
          }
        }
        // Reassemple titles.
        $titles = implode(', ', $titles);
        $result = $prefix . ' ' . $titles;
      }
      else {
        return $series;
      }
    }

    return $result;
  }

}
