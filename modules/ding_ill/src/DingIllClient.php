<?php

/**
 * @file
 * Client for OpenPlatform.
 */

use DingIllRequest;
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
    $this->client = new Client();
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
   * @return DingIllResponse
   *   The ding ill response.
   */
  public function request($method, $type, DingIllRequest $request) {
    $response_object = new DingIllResponse();

    try {
      $response = $this->client->request($method, $this->hostname . '/' . $type,
        array(
          'form_params' => array(
            'access_token' => $this->token,
            'pids' => $request->getMaterials(),
            'pickUpBranch' => $request->getPickupBranch(),
          ),
        )
      );
      return $response_object::createFromResponse($response);
    }
    catch (RequestException $e) {
      watchdog_exception('ding_ill', $e);
      return $response_object::createFromRequestException($e);
    }
  }

}
