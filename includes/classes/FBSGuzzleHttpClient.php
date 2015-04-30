<?php

/**
 * @file
 * Guzzle HttpClient adaptor for FBS service.
 */

use GuzzleHttp\Exception\RequestException;
use GuzzleHttp\Stream\Stream as GStream;
use Reload\Prancer\HttpClient;
use Psr\Http\Message\RequestInterface;
use Phly\Http\Response;
use Phly\Http\Stream;

/**
 * Drupal implementation of HttpClient.
 *
 * This is primarily to be able to run tests outside of a bootstrapped Drupal.
 */
class FBSGuzzleHttpClient implements HttpClient {

  /**
   * Constructor.
   */
  public function __construct() {
    $this->guzzle = new GuzzleHttp\Client();
  }

  /**
   * {@inheritdoc}
   */
  public function request(RequestInterface $request) {
    $url = (string) $request->getUri();
    $body = $request->getBody();
    $body->seek(0);
    $headers = $request->getHeaders();
    $headers['Accept'] = 'application/json';
    $headers['Content-Type'] = 'application/json';

    $req = $this->guzzle->createRequest($request->getMethod(), $url);
    $req->setHeaders($headers);
    $req->setBody(GStream::factory($body->getContents()));

    try {
      $res = $this->guzzle->send($req);
    }
    catch (RequestException $e) {
      // Guzzle will throw exceptions for 4xx and 5xx responses, so we catch
      // them here and quietly get the response object.
      $res = $e->getResponse();
      if (!$res) {
        throw $e;
      }
    }

    $response = (new Response(new Stream('php://memory', 'w')))
              ->withStatus($res->getStatusCode(), $res->getReasonPhrase());
    $response->getBody()->write((string) $res->getBody());
    return $response;
  }
}
