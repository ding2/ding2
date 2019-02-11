<?php

/**
 * @file
 * Response object for orders.
 */

use GuzzleHttp\Exception\RequestException;
use GuzzleHttp\Psr7\Response;

/**
 * Class for Ding Ill order responses.
 */
class DingIllResponse {
  private $statusCode;
  private $orderId;
  private $error;

  /**
   * Constructor.
   *
   * @param string $statusCode
   *   The HTTP status code.
   * @param string $orderId
   *   The order ID from a successful request.
   * @param string $error
   *   Error if exception was thrown.
   */
  public function __construct($statusCode, $orderId, $error) {
    $this->statusCode = $statusCode;
    $this->orderId = $orderId;
    $this->error = $error;
  }

  /**
   * Create DingIllResponse object from GuzzleHttp response.
   *
   * @param GuzzleHttp\Psr7\Response $response
   *   The GuzzleHttp response object.
   *
   * @return DingIllResponse
   *   The DingIllResponse object.
   */
  public static function createFromResponse(Response $response) {
    $response_body = $response->getBody();
    $content = json_decode($response_body->getContents());
    return new self($content->statusCode, $content->data->orsId, $content->error);
  }

  /**
   * Create DingIllResponse object from a GuzzleHttp exception.
   *
   * @param GuzzleHttp\Exception\RequestException $e
   *   The GuzzleHttp request exception.
   *
   * @return DingIllResponse
   *   The DingIllResponse object with the error message.
   */
  public static function createFromRequestException(RequestException $e) {
    return new self($e->getCode(), NULL, $e->getMessage());
  }

  /**
   * Get the status code from the API.
   *
   * @return string
   *   The HTTP status code.
   */
  public function getStatusCode() {
    return $this->statusCode;
  }

  /**
   * Get the order ID from the API.
   *
   * @return string
   *   The order ID from the API.
   */
  public function getOrderId() {
    return $this->orderId;
  }

  /**
   * Get the error message from the API.
   *
   * @return string
   *   The error message from the API.
   */
  public function getError() {
    return $this->error;
  }

}
