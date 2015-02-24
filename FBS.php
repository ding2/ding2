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

class FBS
{
    /**
     * @var \FBS\ExternalAuthenticationApi;
     */
    public $Authentication;

    /**
     * @var \FBS\ExternalCatalogApi;
     */
    public $Catalog;

    /**
     * @var \FBS\ExternalMaterialLoansApi;
     */
    public $MaterialLoans;

    /**
     * @var \FBS\ExternalPatronApi;
     */
    public $Patron;

    /**
     * @var \FBS\ExternalPaymentApi;
     */
    public $Payment;

    /**
     * @var \FBS\ExternalPlacementApi;
     */
    public $Placement;

    /**
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
    public static function get($endpoint, HttpClient $client = null, Serializer $serializer = null)
    {
        if (!isset(self::$instances[$endpoint])) {
            self::$instances[$endpoint] = new self($endpoint, $client, $serializer);
        }

        return self::$instances[$endpoint];
    }

    /**
     * Constructor.
     */
    protected function __construct($endpoint, HttpClient $client = null, Serializer $serializer = null)
    {
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
            $this->{$api} = new  $class($endpoint, $this->httpClient, $this->serializer);
        }

    }
}
