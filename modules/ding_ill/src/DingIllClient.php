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
   * Undocumented function.
   *
   * @param DingIllRequest $request
   * @return void
   */
  public function order(DingIllRequest $request) {
    try {
      return $this->client->request('POST', '/order', (array) $request);
    }
    catch (RequestException $e) {
      watchdog_exception('ding_ill', $e);
      return $e->getMessage();
    }
  }

}
