<?php

/**
 * @file
 * The TingOpenlistRequestException class.
 */

/**
 * TingOpenlistRequestException exception.
 */
class TingOpenlistRequestException extends Exception {

  /**
   * The object returned by drupal_http_request().
   * @var object
   */
  public $response;

  /**
   * The URL called.
   * @var string
   */
  public $request_url;

  /**
   * Construct exception.
   *
   * @param object $response
   *   The object returned by drupal_http_request().
   * @param string $request_url
   *   The URL called.
   */
  public function __construct($response, $request_url) {
    parent::__construct(t('Ting openlist error.'));
    $this->response = $response;
    $this->request_url = $request_url;
  }

}
