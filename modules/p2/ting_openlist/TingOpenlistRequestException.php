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
   *
   * @var object
   */
  protected $response;

  /**
   * The URL called.
   *
   * @var string
   */
  protected $request_url;

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

  /**
   * Returns the Drupal HTTP response object.
   *
   * @see drupal_http_request().
   *
   * @return object
   *   Drupal HTTP response object.
   */
  public function getResponse()
  {
    return $this->response;
  }

  /**
   * Return the requested URL.
   *
   * @return string
   *   Request URL.
   */
  public function getRequestUrl()
  {
    return $this->request_url;
  }

}
