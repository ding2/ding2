<?php
/**
 * @file
 * Provides portable access to a "Ting" object retrieved from a search provider.
 */

namespace Ting;

interface TingObjectInterface {

  /**
   * Gets the owner of the object, eg. the agency.
   *
   * @return string
   *   The ID.
   */
  public function getOwnerId();

  /**
   * Gets the ding-specific id for this object. (Usually the entity id).
   *
   * @return string
   *   The ID.
   */
  public function getDingId();

  /**
   * Get provider-specific local ID.
   *
   * @return string
   *   The local ID.
   */
  public function getLocalId();

  /**
   * Retrieves the title of a material.
   *
   * If a longer version of the title exists it will be preferred.
   *
   * @return FALSE|string
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
   * @return string
   *   The age.
   */
  public function getAge();

  /**
   * Target audience for the material.
   *
   * Eg. "børnematerialer"
   *
   * @return string
   *   The target group.
   */
  public function getAudience();

  /**
   * Get an description of the material.
   *
   * @return string
   *   The description.
   */
  public function getDescription();

  /**
   * The size or duration of the resource.
   *
   * Eg. "245 sider".
   * Eg. "12 t., 34 min."
   *
   * @return string
   *   The extent.
   */
  public function getExtent();

  /**
   * The file format, physical medium, or dimensions of the resource.
   *
   * Eg. "1 cd, MP3"
   * Eg. "illustreret i farver"
   *
   * @return string
   *   The format.
   */
  public function getFormat();

  /**
   * The genere of the material.
   *
   * Eg. "fantasy"
   *
   * @return string
   *   The genere.
   */
  public function getGenere();

  /**
   * The ISBN of the material.
   *
   * Eg. "9780615384238"
   *
   * @return string
   *   The ISBN.
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
   * @return string
   *   The rating.
   */
  public function getPegi();

  /**
   * The name of the publisher of the material.
   *
   * @return string
   *   The name.
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
   *   The materials.
   */
  public function getReplacedBy();

  /**
   * List of materials this material replaces.
   *
   * @return mixed
   *   The materials.
   */
  public function getReplaces();

  /**
   * Information about rights held in and over the resource.
   *
   * @return mixed
   *   The rights.
   */
  public function getRights();

  /**
   * List of materials in the same series as the this material.
   *
   * @return mixed
   *   The materials.
   */
  public function getSeriesDescription();

  /**
   * Title of the material from which this material stems.
   *
   * Eg. "Harry Potter and the philosopher's stone" is the source for
   *  "Harry Potter und der Stein der Weisen"
   *
   * @return string
   *   The title of the source.
   */
  public function getSource();

  /**
   * Spatial characteristics of the resource.
   *
   * Eg. "USA"
   * Eg. "Italien"
   *
   * @return string
   *   Spatial description of the material.
   */
  public function getSpatial();

  /**
   * Material spoken language.
   *
   * @return string
   *   The language.
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
   * @return string
   *   The uri formatted as a link.
   */
  public function getURI();

  /**
   * The revision of the material.
   *
   * Eg. "1. udgave, 1. oplag (2016)".
   *
   * @return string
   *   The version.
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
   * @return string
   *   The type.
   */
  public function getType();

  /**
   * Get the year the material was produced.
   *
   * Format YYYY.
   *
   * @return string
   *   The year
   */
  public function getYear();
}
