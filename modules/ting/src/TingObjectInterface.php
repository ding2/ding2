<?php
/**
 * @file
 * Provides portable access to a "Ting" object retrieved from a search provider.
 */

namespace Drupal\ting;

interface TingObjectInterface {

  /**
   * Retrieves the title of a material.
   *
   * @return FALSE|string
   *   The title of the material, or FALSE if it could not be determined.
   */
  public function getTitle();

  // Material Details getters.

  /**
   * TODO.
   *
   * @return mixed
   *   TODO.
   */
  public function getAge();

  /**
   * TODO.
   *
   * @return mixed
   *   TODO.
   */
  public function getAudience();

  /**
   * TODO.
   *
   * @return mixed
   *   TODO.
   */
  public function getDescription();

  /**
   * TODO.
   *
   * @return mixed
   *   TODO.
   */
  public function getExtent();

  /**
   * TODO.
   *
   * @return mixed
   *   TODO.
   */
  public function getFormat();

  /**
   * TODO.
   *
   * @return mixed
   *   TODO.
   */
  public function getGenere();

  /**
   * TODO.
   *
   * @return mixed
   *   TODO.
   */
  public function getIsbn();

  /**
   * TODO.
   *
   * @return mixed
   *   TODO.
   */
  public function getMusician();

  /**
   * TODO.
   *
   * @return mixed
   *   TODO.
   */
  public function getPegi();

  /**
   * TODO.
   *
   * @return mixed
   *   TODO.
   */
  public function getPublisher();

  /**
   * TODO.
   *
   * @return mixed
   *   TODO.
   */
  public function getReferenced();

  /**
   * TODO.
   *
   * @return mixed
   *   TODO.
   */
  public function getReplacedBy();

  /**
   * TODO.
   *
   * @return mixed
   *   TODO.
   */
  public function getReplaces();

  /**
   * TODO.
   *
   * @return mixed
   *   TODO.
   */
  public function getRights();

  /**
   * TODO.
   *
   * @return mixed
   *   TODO.
   */
  public function getSeriesDescription();

  /**
   * TODO.
   *
   * @return mixed
   *   TODO.
   */
  public function getSource();

  /**
   * TODO.
   *
   * @return mixed
   *   TODO.
   */
  public function getSpatial();

  /**
   * TODO.
   *
   * @return mixed
   *   TODO.
   */
  public function getSpoken();

  /**
   * TODO.
   *
   * @return mixed
   *   TODO.
   */
  public function getSubTitles();

  /**
   * TODO.
   *
   * @return mixed
   *   TODO.
   */
  public function getTracks();

  /**
   * TODO.
   *
   * @return mixed
   *   TODO.
   */
  public function getURI();

  /**
   * TODO.
   *
   * @return mixed
   *   TODO.
   */
  public function getVersion();

  /**
   * TODO.
   *
   * @return mixed
   *   TODO.
   */
  public function isPartOf();
}
