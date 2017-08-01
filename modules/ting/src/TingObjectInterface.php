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
}
