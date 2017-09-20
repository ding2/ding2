<?php
/**
 * @file
 * The TingPseudoObject class.
 */

namespace Ting;

/**
 * Value Object implementation of a TingObjectInterface.
 *
 * Can be used to manually construct a TingObjectInterface compatible object.
 *
 * @package Ting
 */
class TingObject implements TingObjectInterface {

  // TODO BBS-SAL: We run with public access for now as some legacy-code still
  // needs directly access, but should be changed to protected when SAL is done.
  public $id;
  public $ownerId;
  public $sourceId;
  public $title;
  public $shortTitle;
  public $age;
  public $audience;
  public $description;
  public $extent;
  public $format;
  public $genere;
  public $isbn;
  public $musician;
  public $pegi;
  public $publisher;
  public $referenced;
  public $replacedBy;
  public $replaces;
  public $rights;
  public $seriesDescription;
  public $source;
  public $spatial;
  public $spoken;
  public $subTitles;
  public $tracks;
  public $uRI;
  public $version;
  public $type;
  public $year;
  public $isPartOf;
  public $isLocal;
  public $relations = [];

  /**
   * {@inheritdoc}
   */
  public function isLocal() {
    return $this->isLocal;
  }

  /**
   * {@inheritdoc}
   */
  public function getRelations() {
    return $this->relations;
  }

  // TODO BBS-SAL: Temporary fix to allow the pseudo object to be accessed via
  // properties, must be removed together with the dynamic property functions
  // at the bottom of this class when the SAL port is complete.
  protected $localProperties = [];

  /**
   * {@inheritdoc}
   */
  public function getOwnerId() {
    return $this->ownerId;
  }

  /**
   * Sets the owner id.
   */
  public function setOwnerId($owner_id) {
    $this->ownerId = $owner_id;
  }

  /**
   * {@inheritdoc}
   */
  public function getId() {
    return $this->id;
  }

  /**
   * Sets the id.
   */
  public function setId($id) {
    $this->id = $id;
  }

  /**
   * {@inheritdoc}
   */
  public function getSourceId() {
    return $this->sourceId;
  }

  /**
   * Set local id.
   */
  public function setSourceId($source_id) {
    $this->sourceId = $source_id;
  }

  /**
   * Set title.
   */
  public function setTitle($title) {
    $this->title = $title;
  }

  /**
   * Set Short title.
   */
  public function setShortTitle($short_title) {
    $this->shortTitle = $short_title;
  }

  /**
   * Set age.
   */
  public function setAge($age) {
    $this->age = $age;
  }

  /**
   * Set audience.
   */
  public function setAudience($audience) {
    $this->audience = $audience;
  }

  /**
   * Set description.
   */
  public function setDescription($description) {
    $this->description = $description;
  }

  /**
   * Set extent.
   */
  public function setExtent($extent) {
    $this->extent = $extent;
  }

  /**
   * Set format.
   */
  public function setFormat($format) {
    $this->format = $format;
  }

  /**
   * Set genere.
   */
  public function setGenere($genere) {
    $this->genere = $genere;
  }

  /**
   * Set ISBN.
   */
  public function setIsbn($isbn) {
    $this->isbn = $isbn;
  }

  /**
   * Set musican.
   */
  public function setMusician($musician) {
    $this->musician = $musician;
  }

  /**
   * Set PEGI.
   */
  public function setPegi($pegi) {
    $this->pegi = $pegi;
  }

  /**
   * Set publisher.
   */
  public function setPublisher($publisher) {
    $this->publisher = $publisher;
  }

  /**
   * Set referenced.
   */
  public function setReferenced($referenced) {
    $this->referenced = $referenced;
  }

  /**
   * Set replaced by.
   */
  public function setReplacedBy($replaced_by) {
    $this->replacedBy = $replaced_by;
  }

  /**
   * Set replaces.
   */
  public function setReplaces($replaces) {
    $this->replaces = $replaces;
  }

  /**
   * Set rights.
   */
  public function setRights($rights) {
    $this->rights = $rights;
  }

  /**
   * Set series description.
   */
  public function setSeriesDescription($series_description) {
    $this->seriesDescription = $series_description;
  }

  /**
   * Set source.
   */
  public function setSource($source) {
    $this->source = $source;
  }

  /**
   * Set spatial.
   */
  public function setSpatial($spatial) {
    $this->spatial = $spatial;
  }

  /**
   * Set spoken.
   */
  public function setSpoken($spoken) {
    $this->spoken = $spoken;
  }

  /**
   * Set subtitles.
   */
  public function setSubTitles($subtitles) {
    $this->subTitles = $subtitles;
  }

  /**
   * Set tracks.
   */
  public function setTracks($tracks) {
    $this->tracks = $tracks;
  }

  /**
   * Set URI.
   */
  public function setURI($uri) {
    $this->uRI = $uri;
  }

  /**
   * Set version.
   */
  public function setVersion($version) {
    $this->version = $version;
  }

  /**
   * Set type.
   */
  public function setType($type) {
    $this->type = $type;
  }

  /**
   * Set year.
   */
  public function setYear($year) {
    $this->year = $year;
  }

  /**
   * Set is part of.
   */
  public function setIsPartOf($is_part_of) {
    $this->isPartOf = $is_part_of;
  }

  /**
   * Retrieves the title of a material.
   *
   * If a longer version of the title exists it will be preferred.
   *
   * @return FALSE|string
   *   The title of the material, or FALSE if it could not be determined.
   */
  public function getTitle() {
    return $this->title;
  }

  /**
   * Retrieves the title of a material.
   *
   * If a short version of the title exists it will be preferred.
   *
   * @return FALSE|string
   *   The title of the material, or FALSE if it could not be determined.
   */
  public function getShortTitle() {
    return $this->shortTitle;
  }

  /**
   * Age for the target audience for the material.
   *
   * Eg. "fra 11 år
   *
   * @return string
   *   The age.
   */
  public function getAge() {
    return $this->age;
  }

  /**
   * Target audience for the material.
   *
   * Eg. "børnematerialer"
   *
   * @return string
   *   The target group.
   */
  public function getAudience() {
    return $this->audience;
  }

  /**
   * Get an description of the material.
   *
   * @return string
   *   The description.
   */
  public function getDescription() {
    return $this->description;
  }

  /**
   * The size or duration of the resource.
   *
   * Eg. "245 sider".
   * Eg. "12 t., 34 min."
   *
   * @return string
   *   The extent.
   */
  public function getExtent() {
    return $this->extent;
  }

  /**
   * The file format, physical medium, or dimensions of the resource.
   *
   * Eg. "1 cd, MP3"
   * Eg. "illustreret i farver"
   *
   * @return string
   *   The format.
   */
  public function getFormat() {
    return $this->format;
  }

  /**
   * The genere of the material.
   *
   * Eg. "fantasy"
   *
   * @return string
   *   The genere.
   */
  public function getGenere() {
    return $this->genere;
  }

  /**
   * The ISBN of the material.
   *
   * Eg. "9780615384238"
   *
   * @return string
   *   The ISBN.
   */
  public function getIsbn() {
    return $this->isbn;
  }

  /**
   * Get list of musicians listed as contributors.
   *
   * @return string[]
   *   The musicians.
   */
  public function getMusician() {
    return $this->musician;
  }

  /**
   * Get the Pan European Game Information (PEGI) rating for the material.
   *
   * Eg. "PEGI-mærkning: 18"
   *
   * @return string
   *   The rating.
   */
  public function getPegi() {
    return $this->pegi;
  }

  /**
   * The name of the publisher of the material.
   *
   * @return string
   *   The name.
   */
  public function getPublisher() {
    return $this->publisher;
  }

  /**
   * Get materials that references this material.
   *
   * @return string[]
   *   IDs of the materials.
   */
  public function getReferenced() {
    return $this->referenced;
  }

  /**
   * Get newer materials that replaces this material.
   *
   * @return mixed
   *   The materials.
   */
  public function getReplacedBy() {
    return $this->replacedBy;
  }

  /**
   * List of materials this material replaces.
   *
   * @return mixed
   *   The materials.
   */
  public function getReplaces() {
    return $this->replaces;
  }

  /**
   * Information about rights held in and over the resource.
   *
   * @return mixed
   *   The rights.
   */
  public function getRights() {
    return $this->rights;
  }

  /**
   * List of materials in the same series as the this material.
   *
   * @return mixed
   *   The materials.
   */
  public function getSeriesDescription() {
    return $this->seriesDescription;
  }

  /**
   * Title of the material from which this material stems.
   *
   * Eg. "Harry Potter and the philosopher's stone" is the source for
   *  "Harry Potter und der Stein der Weisen"
   *
   * @return string
   *   The title of the source.
   */
  public function getSource() {
    return $this->source;
  }

  /**
   * Spatial characteristics of the resource.
   *
   * Eg. "USA"
   * Eg. "Italien"
   *
   * @return string
   *   Spatial description of the material.
   */
  public function getSpatial() {
    return $this->spatial;
  }

  /**
   * Material spoken language.
   *
   * @return string
   *   The language.
   */
  public function getSpoken() {
    return $this->spoken;
  }

  /**
   * Material subtitles.
   *
   * List of languages the material has subtitles in.
   *
   * Eg. ['Dansk', 'Tysk']
   *
   * @return string[]
   *   List of languages.
   */
  public function getSubTitles() {
    return $this->subTitles;
  }

  /**
   * Titles of tracks in this material.
   *
   * @return string[]
   *   Track titles.
   */
  public function getTracks() {
    return $this->tracks;
  }

  /**
   * Host publication URI.
   *
   * @return string
   *   The uri formatted as a link.
   */
  public function getURI() {
    return $this->uRI;
  }

  /**
   * The revision of the material.
   *
   * Eg. "1. udgave, 1. oplag (2016)".
   *
   * @return string
   *   The version.
   */
  public function getVersion() {
    return $this->version;
  }

  /**
   * Get relations for the material.
   *
   * Eg. "Berlingske tidende, 2005-08-20" (for a newspaper article).
   *
   * @return string[]
   *   Relations.
   */
  public function isPartOf() {
    return $this->isPartOf;
  }

  /**
   * Gets the material type.
   *
   * Eg. "Bog"
   * Eg. "Lydbog (cd)"
   *
   * @return string
   *   The type.
   */
  public function getType() {
    return $this->type;
  }

  /**
   * Get the year the material was produced.
   *
   * Format YYYY.
   *
   * @return string
   *   The year
   */
  public function getYear() {
    return $this->year;
  }

  /**
   * Handle property reads.
   *
   * Delegates all non-local property reads to the Open Search object.
   */
  public function __get($name) {
    // TODO BBS-SAL: Remove logging when SAL is implemented.
    watchdog('TingPseudoObject', "Getting '$name'", WATCHDOG_DEBUG);

    // Handle local properties.
    if (in_array($name, $this->localProperties)) {
      return $this->$name;
    }

    return NULL;
  }

  /**
   * Handle property mutation.
   */
  public function __set($name, $value) {
    // TODO BBS-SAL: Remove logging when SAL is implemented.
    watchdog('TingPseudoObject', "Setting '$name'", WATCHDOG_DEBUG);

    if (in_array($name, $this->localProperties)) {
      $this->$name = $value;
    }
  }

  /**
   * Test if a property is present.
   */
  public function __isset($name) {
    // TODO BBS-SAL: Remove logging when SAL is implemented.
    watchdog('TingPseudoObject', "Is '$name' set?", WATCHDOG_DEBUG);
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

    // TODO BBS-SAL: Remove logging when SAL is implemented.
    watchdog('TingPseudoObject', "Unsetting '$name'", WATCHDOG_DEBUG);
  }
}
