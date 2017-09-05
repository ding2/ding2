<?php

/**
 * @file
 * The DingProviderConsentException class.
 */

/**
 * Default exception.
 */
class TingOpenlistRequestException extends Exception {

  /**
   * Construct exception.
   */
  public function __construct($response) {
    parent::__construct(t('Ting openlist error.'));
    $this->response = $response;
  }

}
