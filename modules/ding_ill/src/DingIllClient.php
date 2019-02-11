<?php

/**
 * @file
 * Client for OpenPlatform.
 */

use GuzzleHttp\Client;
use GuzzleHttp\Exception\RequestException;

/**
 * Client for interlibrary loans.
 */
class DingIllClient {

  /**
   * The OpenPlatform API URL.
   *
   * @var string
   *   URL for the OpenPlatform API.
   */
  private $hostname;

  /**
   * The GuzzleHTTP client used to make requests against the API.
   *
   * @var GuzzleHttp\Client
   *   GuzzleHTTP client to make requests against the API.
   */
  private $client;

  /**
   * The OpenPlatform API token.
   *
   * @var string
   *   The token used for authentication against the OpenPlatform API.
   */
  private $token;

  /**
   * Constructor.
   *
   * Constructs the OpenPlatform API client.
   */
  public function __construct($hostname, $token) {
    // Initialize properties.
    $this->hostname = $hostname;
    $this->token = $token;

    // Initialize the instantiated GuzzleHttp Client.
    $this->client = new Client(array('base_uri' => $hostname));
  }

  /**
   * Make a request to the OpenPlatform API with the token.
   *
   * @param string $method
   *   The HTTP request method. For example, 'GET'.
   * @param string $type
   *   The type of the request. For example, 'order'.
   * @param DingIllRequest $request
   *   The Ding ILL request object.
   *
   * @return Psr\Http\Message\ResponseInterface|RequestException
   *   The GuzzleHttp response or an exception.
   */
  public function request($method, $type, DingIllRequest $request) {
    try {
      $response = $this->client->request($method, '/' . $type, array(
        'access_token' => $this->token,
        'body' => (array) $request,
      ));

      return $response->getBody();
    }
    catch (RequestException $e) {
      watchdog_exception('ding_ill', $e);
      return $e->getMessage();
    }
  }

}
