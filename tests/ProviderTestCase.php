<?php

/**
 * @file
 * Base class for provider tests. Fakes some environment.
 */

use Phly\Http\Response;
use Phly\Http\Stream;
use Prophecy\Argument;
use Prophecy\Promise\ReturnPromise;

require_once 'includes/classes/FBS.php';
require_once 'includes/classes/FBSAuthenticationHandler.php';
require_once 'includes/classes/FBSGuzzleHttpClient.php';
require_once 'includes/classes/FBSCacheInterface.php';
require_once 'includes/classes/FBSCacheMemory.php';
require_once 'includes/classes/FBSLogInterface.php';
require_once 'includes/classes/FBSLogStdout.php';

/**
 * Fake it.
 */
function drupal_get_path($type, $name) {
  return '.';
}

/**
 * Base class for provider tests.
 */
abstract class ProviderTestCase extends PHPUnit_Framework_TestCase {
  protected $fbs = NULL;
  protected $provider = NULL;

  protected $useService = FALSE;

  protected $serviceUsername = NULL;

  protected $servicePassword = NULL;

  protected $serviceAgency = NULL;

  protected $serviceEndpoint = NULL;

  protected $prophecy = NULL;

  protected $total_calls = 0;
  /**
   * Set up the test.
   */
  public function setUp() {
    require_once "fbs.module";
    $service_def = getenv('FBS_SERVICE');
    if ($service_def) {
      list($this->serviceUsername, $this->servicePassword, $this->serviceAgency, $this->serviceEndpoint) = explode('|', $service_def);
      if (!empty($this->serviceUsername) &&
          !empty($this->servicePassword) &&
          !empty($this->serviceAgency) &&
          !empty($this->serviceEndpoint)) {
        $this->useService = TRUE;
      }
    }
  }

  /**
   * Invoke a provider method.
   */
  protected function providerInvoke($hook) {
    if (!$this->fbs) {
      $this->initService();
    }

    if (empty($this->provider)) {
      $this->fail('Provider not set for test.');
    }

    $args = func_get_args();
    array_shift($args);

    $function = $this->providerFunction($hook);
    if (is_callable($function)) {
      return call_user_func_array($function, $args);
    }

    $this->fail("Provider does not implement " . $this->provider . '_' . $hook . '.');
  }

  /**
   * Initialize FBS service.
   */
  protected function initService() {
    $httpclient = $this->getHttpClient();

    if ($this->useService) {
      $client = new FBSGuzzleHttpClient();
      $client = new FBSAuthenticationHandler($this->serviceUsername, $this->servicePassword, $client, new FBSCacheMemory(), new FBSLogStdout());
      $this->fbs = fbs_service($this->serviceAgency, $this->serviceEndpoint, $client, NULL, TRUE);
    }
    else {
      $this->fbs = fbs_service('1234', '', $httpclient, NULL, TRUE);
    }
  }

  /**
   * Get the provider function.
   */
  protected function providerFunction($hook) {
    $provider = fbs_ding_provider();

    if (!isset($provider['provides'][$this->provider])) {
      return NULL;
    }
    $provider = $provider['provides'][$this->provider];
    $function = 'fbs' . '_' . (isset($provider['prefix']) ? $provider['prefix'] . '_' : '') . $hook;

    if (isset($provider['file'])) {
      require_once $provider['file'];
    }

    if (function_exists($function)) {
      return $function;
    }

    return NULL;
  }

  /**
   * Get HTTP Client, possibly preloaded with responses.
   */
  protected function getHttpClient($replies = array()) {
    if (!$this->prophecy) {
      $this->prophecy = $this->prophesize('Reload\Prancer\HttpClient');
    }
    if ($replies) {
      $this->replies($replies);
    }
    return $this->prophecy->reveal();
  }

  /**
   * Set expected responses.
   */
  protected function replies($replies) {
    if ($this->useService) {
      return;
    }

    if (!$this->prophecy) {
      $this->getHttpClient();
    }

    $responses = array();
    foreach ($replies as $reply) {
      if (!($reply instanceof Reply)) {
        $reply = new Reply($reply);
      }
      $responses[] = $reply->getResponse();
    }

    $this->prophecy->request(Argument::any())
      ->will(new ReturnPromise($responses));

    $this->total_calls += count($responses);
    $this->prophecy->request(Argument::any())->shouldBeCalledTimes($this->total_calls);
  }

  /**
   * Load ding includes.
   */
  protected function requireDing($module, $file) {
    $modules_dir = getenv('DING_MODULES');
    if (!$modules_dir) {
      $this->fail("You need to provide the path to ding modules in the DING_MODULES env variable.");
    }
    $file = rtrim($modules_dir, '/') . '/' . $module . '/' . $file;
    if (!file_exists($file)) {
      $this->fail("Could not load " . $file);
    }

    require_once $file;
  }
}

/**
 * Helper class for constructing fake replies from the server.
 */
class Reply {
  protected $data;
  protected $code = 200;
  protected $message = '';

  /**
   * Create reply.
   *
   * @param array $data
   *   Data to return as body.
   */
  public function __construct(array $data = NULL) {
    $this->data = $data;
  }

  /**
   * Set the HTTP status code of the reply.
   */
  public function code($code) {
    $this->code = $code;
    return $this;
  }

  /**
   * Set the HTTP message of the reply.
   */
  public function message($message) {
    $this->message = $message;
    return $this;
  }

  /**
   * Return the respone.
   */
  public function getResponse() {
    $response = (new Response(new Stream('php://memory', 'w')))->withStatus($this->code, $this->message);
    if (!is_null($this->data)) {
      $response->getBody()->write(json_encode($this->data));
    }
    return $response;
  }
}
