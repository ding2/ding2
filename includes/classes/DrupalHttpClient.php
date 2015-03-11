<?php

/**
 * @file
 * Drupal HttpClient for FBS service.
 */

use Reload\Prancer\HttpClient;
use Psr\Http\Message\RequestInterface;
use Phly\Http\Response;
use Phly\Http\Stream;

/**
 * Drupal implementation of HttpClient.
 */
class DrupalHttpClient implements HttpClient {
  const SESSION_KEY = 'drupal_http_client_session_id';

  protected $sessionId = NULL;

  /**
   * {@inheritdoc}
   */
  public function request(RequestInterface $request) {
    // If the path matches this, it's an authentication request, so we wont
    // add session id.
    $auth_request = preg_match('{/external/v1/[-A-Za-z0-9]+/authentication/login$}', $request->getUri()->getPath());

    $url = (string) $request->getUri();
    $body = $request->getBody();
    $body->seek(0);
    $headers = $request->getHeaders();
    $headers['Accept'] = 'application/json';
    $headers['Content-Type'] = 'application/json';
    if (!$auth_request) {
      $headers['X-Session'] = $this->getSessionId();
    }
    $options = array(
      'method' => $request->getMethod(),
      'headers' => $headers,
      'data' => $body->getContents(),
    );
    drupal_debug(array($url, $options), 'request');
    $res = drupal_http_request($url, $options);

    // The server wants us to authenticate. Do it and retry the request.
    if (!$auth_request && $res->code == 401) {
      $this->authenticate();
      $res = drupal_http_request($url, $options);
    }

    drupal_debug($res, 'reponse');
    $response = (new Response(new Stream('php://memory', 'w')))
              ->withStatus($res->code, $res->status_message);
    $response->getBody()->write($res->data);
    return $response;
  }

  /**
   * Get session id.
   */
  protected function getSessionId() {
    if (!$this->sessionId) {
      if ($cache = cache_get(self::SESSION_KEY)) {
        $this->sessionId = $cache->data;
      }

      if (!$this->sessionId) {
        $this->authenticate();
      }
    }

    return $this->sessionId;
  }

  /**
   * Authenticate with FBS and get a session id.
   */
  protected function authenticate() {
    cache_clear_all(self::SESSION_KEY, 'cache');
    $this->sessionId = NULL;
    $login = new FBS\Model\Login();
    $login->username = variable_get('fbs_username', '');
    $login->password = variable_get('fbs_password', '');
    $res = fbs_service()->Authentication->login(fbs_service()->agencyId, $login);
    if (isset($res->sessionKey)) {
      $this->sessionId = $res->sessionKey;
      cache_set(self::SESSION_KEY, $this->sessionId, 'cache', CACHE_TEMPORARY);
    }
    else {
      watchdog('fbs', 'Error athentication with FBS. Check endpoint, agency id, username and password.', array(), WATCHDOG_CRITICAL);
    }
  }
}
