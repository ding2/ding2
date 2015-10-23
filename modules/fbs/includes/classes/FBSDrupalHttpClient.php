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
class FBSDrupalHttpClient implements HttpClient {
  /**
   * {@inheritdoc}
   */
  public function request(RequestInterface $request) {
    $url = (string) $request->getUri();
    $body = $request->getBody();
    $body->seek(0);
    $headers = $request->getHeaders();

    foreach ($headers as $name => $value) {
      $headers[$name] = implode(', ', $value);
    }

    $headers['Accept'] = 'application/json';
    $headers['Content-Type'] = 'application/json';

    $options = array(
      'method' => $request->getMethod(),
      'headers' => $headers,
      'data' => $body->getContents(),
    );
    $res = drupal_http_request($url, $options);

    $response = (new Response(new Stream('php://memory', 'w')))
              ->withStatus($res->code, $res->status_message);
    $response->getBody()->write($res->data);
    return $response;
  }
}
