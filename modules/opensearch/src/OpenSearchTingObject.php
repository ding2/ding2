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
   * Local property for holding the relations array.
   *
   * The property needs to be local as the __get() magic functions won't be
   * able to properly handle arrays as they need to be passed by reference.
   *
   * @var TingRelation[] list of materials related to this material.
   */
  protected $relations = [];

  /**
   * OpenSearchObject constructor.
   *
   * @param TingClientObject $open_search_object
   *   The Open Search result this object wraps.
   */
  public function __construct(TingClientObject $open_search_object) {
    $this->openSearchObject = $open_search_object;
  }

  /**
   * {@inheritdoc}
   */
  public function getId() {
    return $this->openSearchObject->id;
  }

  /**
   * {@inheritdoc}
   */
  public function getRelations() {
    // If relations are not set; do another request to get relations.
    // relationData holds the raw relation data from the query. If it is not
    // available, attempt to load it by re-loading the entire object with
    // with_relations = TRUE.
    if (NULL === $this->getRelationsData()) {
      module_load_include('inc', 'opensearch', 'opensearch.client');
      $loaded = opensearch_get_object($this->getId(), FALSE, TRUE);
      $this->openSearchObject = $loaded;
    }

    // If we have not converted relationsData to TingRelations yet, get started.
    if (NULL !== $this->getRelationsData() && empty($this->relations)) {
      $relation_objects = [];
      $entity_ids = [];
      foreach ($this->getRelationsData() as $record) {
        if (isset($record->relationUri, $record->relationObject)) {
          $entity_ids[] = $record->relationUri;
        }
      }

      // We found relations, now load them as full entities.
      if (count($entity_ids) > 0) {
        $objects = entity_load('ting_object', array(), array('ding_entity_id' => $entity_ids));
        // Produce an array of loaded objects keyed by search-provider ids.
        $relation_objects = array_reduce($objects, function ($carry, $object) {
          $carry[$object->id] = $object;
          return $carry;
        }, []);
      }

      // Wrap each loaded relation object in a TingRelation that will be able
      // to store the relation uri and type we may need later.
      $this->relations = array_map(function ($record) use ($relation_objects) {
        return new TingRelation($record->relationType, $record->relationUri, isset($relation_objects[$record->relationUri]) ? $relation_objects[$record->relationUri] : NULL);
      }, $this->getRelationsData());

    }
    return $this->relations;
  }

  /**
   * Determines whether this material is local to the library-system provider.
   *
   * @return bool
   *   Whether the material is local.
   */
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
    return $this->openSearchObject->ownerId;
  }

  /**
   * {@inheritdoc}
   */
  public function getClassification() {
    // Get the first classification.
    $classification = $this->firstEntry($this->getRecordEntry('dc:subject', 'dkdcplus:DK5'));

    if (empty($classification)) {
      return FALSE;
    }

    // Ignore the shorthand for "Skønlitteratur".
    return $classification === 'sk' ? '' : $classification;
  }

  /**
   * {@inheritdoc}
   */
  public function getClassificationText() {
    $dk5_text = $this->firstEntry($this->getRecordEntry('dc:subject', 'dkdcplus:DK5-Text'));

    if (empty($dk5_text)) {
      return FALSE;
    }

    return $dk5_text;
  }

  /**
   * {@inheritdoc}
   */
  public function getCreators($format = TingObjectInterface::NAME_FORMAT_DEFAULT) {
    // Get all authors, filter away instances of the field that is only used for
    // search internals (eg, a sort-field).
    if ($format == TingObjectInterface::NAME_FORMAT_SURNAME_FIRST) {
      $creators = $this->getRecordEntry('dc:creator', 'oss:sort');
    }
    else {
      // Filter away fields that should only be used for internals.
      $search_only_fields = ['oss:sort'];
      $creators = $this->filterRecordsExclude($this->getRecordLevel('dc:creator'), $search_only_fields);
      // Each record entry is a single-element array - map it to a array of
      // strings by picking the first element from each.
      $creators = $this->recordsFlatten($creators);
    }

    return empty($creators) ? [] : $creators;
  }

  /**
   * {@inheritdoc}
   */
  public function getSubjects() {
    // Filter away fields that should only be used for internals.
    $search_only_fields = [
      'dkdcplus:genre',
      'dkdcplus:DK5',
      'dkdcplus:DK5-Text',
      'dkdcplus:DBCO',
      'dkdcplus:DBCN',
    ];
    $subjects = $this->filterRecordsExclude($this->getRecordLevel('dc:subject'), $search_only_fields);
    return $this->recordsFlatten($subjects);
  }

  /**
   * {@inheritdoc}
   */
  public function getLanguage() {
    if (!isset($this->reply->record['dc:language'])) {
      return FALSE;
    }
    $languages = $this->reply->record['dc:language'];
    $languages_string = '';
    foreach (reset($languages) as $key => $lang) {
      if ($lang == 'mul') {
        continue;
      }
      $languages_string .= ', ' . $languages[''][$key];
    }
    $languages_string = (!empty($languages_string)) ? ltrim($languages_string, ', ') : FALSE;
    return $languages_string;
  }

  /**
   * {@inheritdoc}
   */
  public function isOnline() {
    // Check if the material has its own URI - if so we assume it is online.
    return !empty($this->getRecordEntry('dc:identifier', 'dcterms:URI'));
  }

  /**
   * {@inheritdoc}
   */
  public function getOnlineUrl() {
    $url = '';
    // Try to find the online url from relation data, which requires us to get
    // relations. First check if relations are set; if not do another request
    // to get relations.
    $relations = $this->getRelations();

    foreach ($relations as $relation) {
      if ($relation->getType() === 'dbcaddi:hasOnlineAccess') {
        $url = preg_replace('/^\[URL\]/', '', $relation->getURI());
        // Check for correct url or leading token - some uri is only an id.
        if (stripos($url, 'http') === 0 || strpos($url, '[') === 0) {
          // Give other modules a chance to rewrite the url.
          drupal_alter('ting_online_url', $url, $this);
        }
      }
    }

    // No hasOnlineAccess found so fallback to dc:identifier.
    if (empty($url) && !empty($this->getRecordEntry('dc:identifier', 'dcterms:URI'))) {
      $url = $this->firstEntry($this->getRecordEntry('dc:identifier', 'dcterms:URI'));
      // Give ting_proxy a change to rewrite the url.
      drupal_alter('ting_online_url', $url, $this);
    }

    return $url;
  }

  /**
   * {@inheritdoc}
   */
  public function getMaterialSource() {
    return $this->firstEntry($this->getRecordEntry('ac:source'));
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
    $search_only_fields = ['oss:sort'];
    $ispartof = $this->filterRecordsExclude($this->getRecordLevel('dcterms:isPartOf'), $search_only_fields);
    return $this->recordsFlatten($ispartof);
  }

  /**
   * {@inheritdoc}
   */
  public function getContributors() {
    $search_only_fields = ['oss:sort'];
    $contributors = $this->filterRecordsExclude($this->getRecordLevel('dc:contributor'), $search_only_fields);
    // We may have multiple field containing contributors, flatten that multi-
    // dimensional array of records down to their values.
    $contributors = $this->recordsFlatten($contributors);

    // Default to returning an empty list.
    return empty($contributors) ? [] : $contributors;
  }

  /**
   * {@inheritdoc}
   */
  public function getAbstract() {
    return $this->firstEntry($this->getRecordEntry('dcterms:abstract'));
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
  public function getGenre() {
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
    $description = $this->firstEntry($this->getRecordEntry('dc:description', 'dkdcplus:series'));
    return $this->processSeriesDescription($description);

  }

  /**
   * {@inheritdoc}
   */
  public function getSeriesTitles() {
    $series = $this->getRecordEntry('dc:title', 'dkdcplus:series');
    // No match, return early.
    if (empty($series)) {
      return [];
    }

    $series_titles = array();
    foreach ($series as $serie) {
      // Each title might contain both title and series number separated by ;.
      // Split them into parts. If there is no series number for a title then
      // the title should only contain a single element.
      $series_titles[] = explode(';', $serie, 2);
    }

    return empty($series_titles) ? [] : $series_titles;
  }

  /**
   * {@inheritdoc}
   */
  public function getDescription() {
    $description = $this->firstEntry($this->getRecordEntry('dc:description'));

    if (empty($description)) {
      return FALSE;
    }

    if (drupal_strlen($description) > TING_OBJ_DESCRIPTION_LENGTH) {
      $description = truncate_utf8($description, TING_OBJ_DESCRIPTION_LENGTH, TRUE, TRUE);
    }
    else {
      $description .= t('...');
    }

    return $description;
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
    $isbn = array();

    // Nothing to do.
    if (empty($this->openSearchObject->record['dc:identifier']['dkdcplus:ISBN'])) {
      return $isbn;
    }

    // Get ISBN numbers.
    $isbn = $this->openSearchObject->record['dc:identifier']['dkdcplus:ISBN'];
    foreach ($isbn as $k => $number) {
      $isbn[$k] = str_replace(array(' ', '-'), '', $number);
    }
    rsort($isbn);
    return $isbn;
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
   * Data-formats in which the object is available.
   */
  public function getFormatsAvailable() {
    return $this->openSearchObject->formatsAvailable;
  }

  /**
   * Fetch a record from the Open Search object.
   *
   * @param string $l1_key
   *   Key for the first level of value to fetch.
   * @param string $l2_key
   *   Key for the second level of value to fetch. If not specified it is
   *   assumed that the value can be fetched via $array[$l1_key]['']
   *
   * @return string|array|false
   *   The value from the open search object or FALSE if not found
   */
  protected function getRecordEntry($l1_key, $l2_key = '') {
    // Not a nested value, just fetch by l1_key.
    return isset($this->openSearchObject->record[$l1_key][$l2_key]) ? $this->openSearchObject->record[$l1_key][$l2_key] : FALSE;
  }

  /**
   * Fetch a record from the Open Search object.
   *
   * @param string $l1_key
   *   Key for the first level of value to fetch.
   *
   * @return array
   *   The level, empty array if no entry could be found
   */
  protected function getRecordLevel($l1_key) {
    // Not a nested value, just fetch by l1_key.
    return empty($this->openSearchObject->record[$l1_key]) ? [] : $this->openSearchObject->record[$l1_key];
  }

  /**
   * Filters away records with blacklisted keys.
   *
   * @param array $records
   *   Associative list of records.
   *
   * @param array $blacklist
   *   List of keys that should be removed from the list of records.
   *
   * @return array
   *   The filtered list of records.
   */
  protected function filterRecordsExclude($records, $blacklist = []) {
    return array_filter($records, function ($key) use ($blacklist) {
      return !in_array($key, $blacklist);
    }, ARRAY_FILTER_USE_KEY);
  }

  /**
   * Flattens a 2-level array into a 1-level array.
   *
   * Eg [ key1 => [ key2 => val2, key3 => val3]] is reduced to [val2, val3].
   *
   * @param array $records
   *   A list of records each itself an array.
   *
   * @return array
   *   List of all unique values of the nested arrays.
   */
  protected function recordsFlatten($records) {
    if (!is_array($records)) {
      return $records;
    }

    $records = array_reduce($records, function ($carry, $entry) {
      // Reduce each associative array into its value and add them to the carry.
      return empty($entry) ? $carry : array_merge($carry, array_values($entry));
    }, []);

    return array_unique($records);
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
      // Everything else goes to the Open Search object.
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
    // Everything else goes to the Open Search object.
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
   * @param mixed $entry
   *   An entry.
   *
   * @return mixed
   *   The first entry in the array or the entry itself if it is not an array.
   */
  protected function firstEntry($entry) {
    if (is_array($entry) && count($entry) > 0) {
      $array_values = array_values($entry);
      return reset($array_values);
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
   * @param string $series
   *   Series description.
   *
   * @return string
   *    A cleaned up version of the series description contain only the title.
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
          // Some title elements are actually volume numbers.
          // Do not convert these to links.
          if (!preg_match('/(nr.)? \d+/i', $title)) {
            $title = l($title, 'search/ting/"' . $title . '"');
          }
        }
        // Reassemble titles.
        $titles = implode(', ', $titles);
        $result = $prefix . ' ' . $titles;
      }
      else {
        return $series;
      }
    }

    return $result;
  }

  /**
   * Gets the raw relations data from the embedded opensearch object.
   *
   * If empty relations can be loaded by issuing a new search with relation-
   * loading enabled
   *
   * @return object[]|NULL
   *   List of raw data-objects with relationType, relationUri and a nested
   *   relationObject if the relation is an indexed material. NULL if no
   *   relations has been loaded.
   */
  protected function getRelationsData() {
    return isset($this->openSearchObject->relationsData) ? $this->openSearchObject->relationsData : NULL;
  }

}
