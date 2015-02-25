<?php

use Reload\Prancer;
use Reload\Prancer\HttpClient;
use \JsonMapper;
use Reload\Prancer\Serializer;
use Reload\Prancer\Serializer\JsonMapperSerializer;

require_once 'vendor/autoload.php';

use Psr\Http\Message\RequestInterface;
// use Psr\Http\Message\ResponseInterface;
use Phly\Http\Response;
class DrupalHttpClient implements HttpClient {
    public function request(RequestInterface $request) {
        return new Response(
        );
    }

}

/**
 * Master service class.
 */
class FBS {
  public $agencyId;
  /**
   * Authentication API.
   *
   * @var \FBS\ExternalAuthenticationApi;
   */
  public $Authentication;

  /**
   * Catalog API.
   *
   * @var \FBS\ExternalCatalogApi;
   */
  public $Catalog;

  /**
   * Loans API.
   *
   * @var \FBS\ExternalMaterialLoansApi;
   */
  public $MaterialLoans;

  /**
   * Patron API.
   *
   * @var \FBS\ExternalPatronApi;
   */
  public $Patron;

  /**
   * Payments API.
   *
   * @var \FBS\ExternalPaymentApi;
   */
  public $Payment;

  /**
   * Locations API.
   *
   * @var \FBS\ExternalPlacementApi;
   */
  public $Placement;

  /**
   * Reservation API.
   *
   * @var \FBS\ExternalReservationsApi;
   */
  public $Reservations;


  protected static $instances = array();

  /**
   * The base URL of the service.
   */
  protected $endpoint;

  /**
   * HTTP client used.
   */
  protected $httpClient;

  /**
   * Serializer used.
   */
  protected $serializer;

  /**
   * Get service.
   *
   * Yeah, basically a singleton.
   */
  public static function get($agency_id, $endpoint, HttpClient $client = NULL, Serializer $serializer = NULL) {
    $key = $agency_id . ';' . $endpoint;
    if (!isset(self::$instances[$key])) {
      self::$instances[$key] = new self($agency_id, $endpoint, $client, $serializer);
    }

    return self::$instances[$key];
  }

  /**
   * Constructor.
   */
  protected function __construct($agency_id, $endpoint, HttpClient $client = NULL, Serializer $serializer = NULL) {
    $this->agencyId = $agency_id;
    $this->endpoint = $endpoint;
    if (empty($client)) {
      $client = new DrupalHttpClient();
    }
    $this->httpClient = $client;

    if (empty($serializer)) {
      $serializer = new JsonMapperSerializer(new JsonMapper());
    }
    $this->serializer = $serializer;

    // Instantiate API classes.
    $apis = array(
      'Authentication',
      'Catalog',
      'MaterialLoans',
      'Patron',
      'Payment',
      'Placement',
      'Reservations',
    );

    foreach ($apis as $api) {
      $class = '\FBS\External' . $api . 'Api';
      $this->{$api} = new $class($endpoint, $this->httpClient, $this->serializer);
    }

  }
}
