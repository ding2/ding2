<?php

/**
 * @file
 * The DingProviderConsentException class.
 */

/**
 * Default exception.
 */
class DingProviderConsentException extends Exception {

  /**
   * Construct exception.
   */
  public function __construct() {
    parent::__construct(t('Missing user consent'), 1);
  }

}
