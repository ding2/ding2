<?php

/**
 * @file
 * Drupal HttpClient for FBS service.
 */

use FBS\Drupal\LoggingInterface;
use Reload\Prancer\HttpClient;
use Psr\Http\Message\RequestInterface;

/**
 * HttpClient that wraps another HttpClient and handles authentication.
 */
class FBSAuthenticationHandler implements HttpClient {
  const SESSION_KEY = 'fbs_drupal_http_client_session_id';

  protected $client = NULL;

  protected $cache = NULL;

  protected $log = NULL;

  protected $username = NULL;

  protected $password = NULL;

  protected $sessionId = NULL;

  /**
   * Constructor.
   *
   * @param string $username
   *   Username for login.
   * @param string $password
   *   Password for login.
   * @param HttpClient $real
   *   Real HttpClient to use for communicating with the service.
   * @param FBSCacheInterface $cache
   *   Cache backend to store the session token.
   * @param FBSLogInterface $log
   *   Where to log errors.
   */
  public function __construct($username, $password, HttpClient $real, FBSCacheInterface $cache, FBSLogInterface $log) {
    $this->username = $username;
    $this->password = $password;
    $this->client = $real;
    $this->cache = $cache;
    $this->log = $log;
  }

  /**
   * Passes the request on to the real HttpClient, catches authentication errors
   * and attempts to log in before retrying.
   *
   * One attempt at login is done per request.
   *
   * {@inheritdoc}
   */
  public function request(RequestInterface $request) {
    // If the path matches this, it's an authentication request, so we wont
    // add session id.
    $auth_request = preg_match('{/external/v1/[-A-Za-z0-9]+/authentication/login$}', $request->getUri()->getPath());

    $body = $request->getBody();
    $body->seek(0);
    if (!$auth_request) {
      $request = $request->withAddedHeader('X-Session', $this->getSessionId());
    }
    $response = $this->client->request($request);

    // The server wants us to authenticate. Do it and retry the request.
    if (!$auth_request && $response->getStatusCode() == 401) {
      if ($this->authenticate()) {
        $response = $this->client->request($request);
      }
    }

    return $response;
  }

  /**
   * Get session id.
   *
   * @return string|null
   *   The current session id or NULL.
   */
  protected function getSessionId() {
    if (!$this->sessionId) {
      $this->sessionId = $this->cache->get(self::SESSION_KEY);

      if (!$this->sessionId) {
        $this->authenticate();
      }
    }

    return $this->sessionId;
  }

  /**
   * Authenticate with FBS and get a session id.
   *
   * @return bool
   *   Whether the attempt was successful.
   */
  protected function authenticate() {
    $this->cache->delete(self::SESSION_KEY);
    $this->sessionId = NULL;
    $login = new FBS\Model\Login();
    $login->username = $this->username;
    $login->password = $this->password;
    $res = fbs_service()->Authentication->login(fbs_service()->agencyId, $login);
    if (isset($res->sessionKey)) {
      $this->sessionId = $res->sessionKey;
      $this->cache->set(self::SESSION_KEY, $this->sessionId);
      return TRUE;
    }
    else {
      $this->log->critical('Error athentication with FBS. Check endpoint, agency id, username and password.');
    }
    return FALSE;
  }
}
