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
   * The OpenPlatform API token URL.
   *
   * @var string
   *   The URL used for token generation for authentication against the OpenPlatform API.
   */
  private $tokenUrl;

  /**
   * The generated token from OpenPlatform.
   *
   * @var string
   *   Generated token from OpenPlatform.
   */
  private $token;

  private $clientId;

  private $clientSecret;
  private $patronId;
  private $agency;

  /**
   * Constructor.
   *
   * Constructs the OpenPlatform API client.
   */
  public function __construct($hostname, $tokenUrl, $clientId, $clientSecret, $patronId, $agency) {
    // Initialize properties.
    $this->hostname = $hostname;
    $this->tokenUrl = $tokenUrl;
    $this->clientId = $clientId;
    $this->clientSecret = $clientSecret;
    $this->agency = $agency;
    $this->patronId = $patronId;

    // Initialize the instantiated GuzzleHttp Client.
    $this->client = new Client();
  }

  /**
   * Request a token for OpenPlatform with authenticated user.
   *
   * @param string $patron_pin
   *   The patron's pin code.
   *
   * @return string
   *   The OpenPlatform access token for an authenticated user.
   */
  protected function requestToken($patron_pin) {
    $response = $this->client->request('POST', $this->tokenUrl, [
      'auth' => [$this->clientId, $this->clientSecret],
      'form_params' => [
        'grant_type' => 'password',
        'username' => $this->patronId . '@DK-' . $this->agency,
        'password' => $patron_pin,
      ],
    ])->getBody();
    $data = json_decode($response);
    return $data->access_token;
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
    $this->token = $this->requestToken($request->getPin());

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
