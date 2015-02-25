<?php

/**
 * @file
 * Base class for provider tests. Fakes some environment.
 */

use Phly\Http\Response;
use Phly\Http\Stream;
use Prophecy\Argument;
use Prophecy\Promise\ReturnPromise;

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
  protected $provider = NULL;

  /**
   * Set up the test.
   */
  public function setUp() {
    require_once "fbs.module";
  }

  /**
   * Invoke a provider method.
   */
  protected function providerInvoke($hook) {
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
  protected function getHttpClient($json_responses) {
    $httpclient = $this->prophesize('Reload\Prancer\HttpClient');

    $responses = array();
    foreach ($json_responses as $json_data) {
      $response = new Response(new Stream('php://memory', 'w'), 200);
      $response->getBody()->write(json_encode($json_data));
      $responses[] = $response;
    }

    $httpclient->request(Argument::any())
            ->will(new ReturnPromise($responses));

    $httpclient->request(Argument::any())->shouldBeCalledTimes(count($responses));
    return $httpclient->reveal();
  }
}
