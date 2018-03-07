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

  public $abstract;
  public $age;
  public $audience;
  public $classifications;
  public $contributors;
  public $creatorsFormatSurnameFirst;
  public $creatorsFormatDefault;
  public $description;
  public $extent;
  public $format;
  public $genere;
  public $id;
  public $isbn;
  public $isLocal;
  public $isPartOf;
  public $language;
  public $materialSource;
  public $musician;
  public $online;
  public $onlineUrl;
  public $ownerId;
  public $pegi;
  public $publisher;
  public $referenced;
  public $relations = [];
  public $replacedBy;
  public $replaces;
  public $rights;
  public $seriesDescription;
  public $seriesTitles;
  public $shortTitle;
  public $source;
  public $sourceId;
  public $spatial;
  public $spoken;
  public $subjects;
  public $subTitles;
  public $title;
  public $tracks;
  public $type;
  public $uRI;
  public $version;
  public $year;

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
   * Returns the material classification.
   *
   * @return string|FALSE
   *   The classification.
   */
  public function getClassification() {
    return $this->classifications;
  }

  /**
   * Returns a short description of the contents of the material.
   *
   * @return string|FALSE
   *   The abstract.
   */
  public function getAbstract() {
    return $this->abstract;
  }

  /**
   * Sets a short description of the contents of the material.
   *
   * @param string $abstract
   *   A short description of the contents of the material
   */
  public function setAbstract($abstract) {
    $this->abstract = $abstract;
  }

  /**
   * Sets the material classification.
   *
   * @param string $classifications
   *   The material classification.
   */
  public function setClassifications($classifications) {
    $this->classifications = $classifications;
  }

  /**
   * Set the contributors to the material.
   *
   * @param string[] $contributors
   *   List of contributors, empty if none could be found.
   */
   public function setContributors($contributors) {
    $this->contributors = $contributors;
  }

  /**
   * Set names of the creators of the material with surname first.
   *
   * @param string[] $creators
   *   Creator names, surname first.
   */
  public function setCreatorsFormatSurnameFirst($creators) {
    $this->creatorsFormatSurnameFirst = $creators;
  }

  /**
   * Set names of the creators of the material in default format.
   *
   * @param string[] $creators
   *   Creator names, default format.
   */
  public function setCreatorsFormatDefault($creators) {
    $this->creatorsFormatDefault = $creators;
  }

  /**
   * Set whether the material is local.
   *
   * @param $isLocal bool
   *   Whether the material is local.
   */
  public function setIsLocal($isLocal) {
    $this->isLocal = $isLocal;
  }

  /**
   * Set the language of the material.
   *
   * @param string $language
   *   The language.
   */
  public function setLanguage($language) {
    $this->language = $language;
  }

  /**
   * Returns the original source of the material.
   *
   * @param string $materialSource
   *   The source of the material.
   */
  public function setMaterialSource($materialSource) {
    $this->materialSource = $materialSource;
  }

  /**
   * Set whether the material is a purely online material.
   *
   * @param bool $online
   *   TRUE if the material can only be found online.
   */
  public function setOnline($online) {
    $this->online = $online;
  }

  /**
   * Set URL where the material can be found online.
   *
   * @param string $onlineUrl
   *   The URL.
   */
  public function setOnlineUrl($onlineUrl) {
    $this->onlineUrl = $onlineUrl;
  }

  /**
   * Set materials related to this material.
   *
   * @param \TingRelation[] $relations
   *   An array of relations.
   */
  public function setRelations(array $relations) {
    $this->relations = $relations;
  }

  /**
   * Set list of titles of the series the material is a part of.
   *
   * @param string[] $seriesTitles
   *   List of titles, empty if none could be found.
   */
  public function setSeriesTitles($seriesTitles) {
    $this->seriesTitles = $seriesTitles;
  }

  /**
   * Set list of subjects/keywords for the material.
   *
   * @param string[] $subjects
   *   List of subjects, empty if none could be found.
   */
  public function setSubjects($subjects) {
    $this->subjects = $subjects;
  }

  /**
   * Sets which properties should be delegates to a Open Search object
   *
   * @param string[] $localProperties
   *   Property names which not be delegated.
   */
  public function setLocalProperties(array $localProperties) {
    $this->localProperties = $localProperties;
  }

  /**
   * Returns the creators of the material.
   *
   * For a book the creator would typically be the author.
   *
   * @param string $format
   *   TingObjectInterface::NAME_FORMAT_* formats to specify how the authors
   *   names should be formatted.
   *
   * @return string[]
   *   The list of formatted author-names, empty if none was found.
   */
  public function getCreators($format = self::NAME_FORMAT_DEFAULT) {
    return $format == self::NAME_FORMAT_SURNAME_FIRST ? $this->creatorsFormatSurnameFirst : $this->creatorsFormatDefault;
  }

  /**
   * Returns list of subjects/keywords for the material.
   *
   * @return string[]
   *   List of subjects, empty if none could be found.
   */
  public function getSubjects() {
    return $this->subjects;
  }

  /**
   * The language of the material.
   *
   * @return string|FALSE
   *   The language, FALSE if it could not be found.
   */
  public function getLanguage() {
    return $this->language;
  }

  /**
   * URL where the material can be found online.
   *
   * @return string|FALSE
   *   The URL, FALSE if it could not be found.
   */
  public function getOnlineUrl() {
    return $this->onlineUrl;
  }

  /**
   * Whether the material is a purely online material.
   *
   * @return bool
   *   TRUE if the material can only be found online.
   */
  public function isOnline() {
    return $this->isOnline;
  }

  /**
   * Returns the original source of the material.
   *
   * Eg. Bibliotekskatalog, Anmeldelser.
   *
   * @return string|FALSE
   *   The source of the material.
   */
  public function getMaterialSource() {
    return $this->materialSource;
  }

  /**
   * List of contributors to the material.
   *
   * Eg, name of the translator of the material.
   *
   * @return string[]
   *   List of contributors, empty if none could be found.
   */
  public function getContributors() {
    return $this->contributors;
  }

  /**
   * List of titles of the series the material is a part of.
   *
   * @return string[]
   *   List of titles, empty if none could be found.
   */
  public function getSeriesTitles() {
    return $this->seriesTitles;
  }

}
