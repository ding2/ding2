<?php
/**
 * @file
 * Provides portable access to a "Ting" object retrieved from a search provider.
 */

namespace Ting;

interface TingObjectInterface {

  const NAME_FORMAT_SURNAME_FIRST = __CLASS__ . 'first';

  const NAME_FORMAT_DEFAULT = __CLASS__ . 'default';

  /**
   * Returns materials related to this material.
   *
   * @return \TingRelation[]
   *   An array of relations.
   */
  public function getRelations();

  /**
   * Determines whether the material is local.
   *
   * A local material is a material that is available from the library that is
   * primary for the current Ding installation.
   *
   * @return bool
   *   Whether the material is local.
   */
  public function isLocal();

  /**
   * Gets the owner of the object, eg. the agency.
   *
   * @return string|FALSE
   *   The ID, or FALSE if it could not be determined.
   */
  public function getOwnerId();

  /**
   * Gets the search-provider specific id for the material.
   *
   * This ID can be assumed unique across all objects returned from the search-
   * provider.
   *
   * @return string
   *   The ID.
   */
  public function getId();

  /**
   * The unique id for the material in the source system.
   *
   * The TingObject is a representation of an object in a source-system indexed
   * by the search provider. The source id is the id that can be used to
   * uniquely identify this object in the source system.
   *
   * The ID can not be assumed to be unique among other TingObjects as the
   * search-provider may search across objects originating from several source-
   * systems.
   *
   * @return string|FALSE
   *   The source ID, or FALSE if it could not be determined.
   */
  public function getSourceId();

  /**
   * Retrieves the title of a material.
   *
   * If a longer version of the title exists it will be preferred.
   *
   * @return string|FALSE
   *   The title of the material, or FALSE if it could not be determined.
   */
  public function getTitle();

  /**
   * Retrieves the title of a material.
   *
   * If a short version of the title exists it will be preferred.
   *
   * @return FALSE|string
   *   The title of the material, or FALSE if it could not be determined.
   */
  public function getShortTitle();

  // Material Details getters.

  /**
   * Age for the target audience for the material.
   *
   * Eg. "fra 11 år
   *
   * @return string|FALSE
   *   The age, or FALSE if it could not be determined.
   */
  public function getAge();

  /**
   * Target audience for the material.
   *
   * Eg. "børnematerialer"
   *
   * @return string|FALSE
   *   The target group, or FALSE if it could not be determined.
   */
  public function getAudience();

  /**
   * Get an description of the material.
   *
   * @return string|FALSE
   *   The description, or FALSE if it could not be determined.
   */
  public function getDescription();

  /**
   * The size or duration of the resource.
   *
   * Eg. "245 sider".
   * Eg. "12 t., 34 min."
   *
   * @return string|FALSE
   *   The extent, or FALSE if it could not be determined.
   */
  public function getExtent();

  /**
   * The file format, physical medium, or dimensions of the resource.
   *
   * Eg. "1 cd, MP3"
   * Eg. "illustreret i farver"
   *
   * @return string|FALSE
   *   The format, or FALSE if it could not be determined.
   */
  public function getFormat();

  /**
   * The genre of the material.
   *
   * Eg. "fantasy"
   *
   * @return string|FALSE
   *   The genre, or FALSE if it could not be determined.
   */
  public function getGenre();

  /**
   * The ISBN of the material.
   *
   * Eg. "9780615384238"
   *
   * @return string[]
   *   Zero or more ISBNs.
   */
  public function getIsbn();

  /**
   * Get list of musicians listed as contributors.
   *
   * @return string[]
   *   The musicians.
   */
  public function getMusician();

  /**
   * Get the Pan European Game Information (PEGI) rating for the material.
   *
   * Eg. "PEGI-mærkning: 18"
   *
   * @return string|FALSE
   *   The rating, or FALSE if it could not be determined.
   */
  public function getPegi();

  /**
   * The name of the publisher of the material.
   *
   * @return string|FALSE
   *   The name, or FALSE if it could not be determined.
   */
  public function getPublisher();

  /**
   * Get materials that references this material.
   *
   * @return string[]
   *   IDs of the materials.
   */
  public function getReferenced();

  /**
   * Get newer materials that replaces this material.
   *
   * @return mixed
   *   The materials, or FALSE if it could not be determined.
   */
  public function getReplacedBy();

  /**
   * List of materials this material replaces.
   *
   * @return mixed
   *   The materials, or FALSE if it could not be determined.
   */
  public function getReplaces();

  /**
   * Information about rights held in and over the resource.
   *
   * @return mixed
   *   The rights, or FALSE if it could not be determined.
   */
  public function getRights();

  /**
   * Description of the series which the material is a part of.
   *
   * @return string|FALSE
   *   The series description, or FALSE if it could not be determined.
   */
  public function getSeriesDescription();

  /**
   * Title of the material from which this material stems.
   *
   * Eg. "Harry Potter and the philosopher's stone" is the source for
   *  "Harry Potter und der Stein der Weisen"
   *
   * @return string|FALSE
   *   The title of the source, or FALSE if it could not be determined.
   */
  public function getSource();

  /**
   * Spatial characteristics of the resource.
   *
   * Eg. "USA"
   * Eg. "Italien"
   *
   * @return string|FALSE
   *   Spatial description of the material, or FALSE if it could not be
   *   determined.
   */
  public function getSpatial();

  /**
   * Material spoken language.
   *
   * @return string|FALSE
   *   The language, or FALSE if it could not be determined.
   */
  public function getSpoken();

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
  public function getSubTitles();

  /**
   * Titles of tracks in this material.
   *
   * @return string[]
   *   Track titles.
   */
  public function getTracks();

  /**
   * Host publication URI.
   *
   * @return string|FALSE
   *   The uri formatted as a link, or FALSE if it could not be determined.
   */
  public function getURI();

  /**
   * The revision of the material.
   *
   * Eg. "1. udgave, 1. oplag (2016)".
   *
   * @return string|FALSE
   *   The version, or FALSE if it could not be determined.
   */
  public function getVersion();

  /**
   * Get relations for the material.
   *
   * Eg. "Berlingske tidende, 2005-08-20" (for a newspaper article).
   *
   * @return string[]
   *   Relations.
   */
  public function isPartOf();

  /**
   * Gets the material type.
   *
   * Eg. "Bog"
   * Eg. "Lydbog (cd)"
   *
   * @return string|FALSE
   *   The type, or FALSE if it could not be determined.
   */
  public function getType();

  /**
   * Get the year the material was produced.
   *
   * Format YYYY.
   *
   * @return string|FALSE
   *   The year, or FALSE if it could not be determined.
   */
  public function getYear();

  /**
   * Returns the material classification.
   *
   * @return string|FALSE
   *   The classification, or FALSE if it could not be determined.
   */
  public function getClassification();

  /**
   * Returns a short abstract for the material.
   *
   * @return string|FALSE
   *   The abstract, or FALSE if it could not be determined.
   */
  public function getAbstract();

  /**
   * Returns the creators of the material.
   *
   * For a book the creator would typically be the author.
   *
   * @param string $format
   *   TingObjectInterface::NAME_FORMAT_* formats to specify how the authors
   *   names should be formatted.
   *
   * @return string[].
   *   The list of formatted author-names, empty if none was found.
   */
  public function getCreators($format = self::NAME_FORMAT_DEFAULT);

  /**
   * Returns list of subjects/keywords for the material.
   *
   * @return string[]
   *   List of subjects, empty if none could be found.
   */
  public function getSubjects();

  /**
   * The language of the material.
   *
   * @return string|FALSE
   *   The language, FALSE if it could not be found.
   */
  public function getLanguage();

  /**
   * URL where the material can be found online.
   *
   * @return string|FALSE
   *   The URL, FALSE if it could not be found.
   */
  public function getOnlineUrl();

  /**
   * Whether the material is a purely online material.
   *
   * @return bool
   *   TRUE if the material can only be found online.
   */
  public function isOnline();

  /**
   * Returns the original source of the material.
   *
   * Eg. Bibliotekskatalog, Anmeldelser.
   *
   * @return string|FALSE
   *   The source of the material, or FALSE if it could not be determined.
   */
  public function getMaterialSource();

  /**
   * List of contributors to the material.
   *
   * Eg, name of the translator of the material.
   *
   * @return string[]
   *   List of contributors, empty if none could be found.
   */
  public function getContributors();

  /**
   * List of titles of the series the material is a part of.
   *
   * Each title is an array of one or two elements:
   * - The first element represents the series title and is required.
   * - The second element represents the series number and is optional.
   *
   * @return string[][]
   *   List of titles, empty if none could be found.
   */
  public function getSeriesTitles();

}
