<?php

/**
 * @file
 * Fake HttpClient that returns generated responses, in order to be able to
 * test the module without a real service available.
 */

use Reload\Prancer\HttpClient;
use Psr\Http\Message\RequestInterface;
use Phly\Http\Response;
use Phly\Http\Stream;

/**
 * Fake HTTP client that implements the Reload\Prancer\HttpClient interface.
 */
class FakeHttpClient implements HttpClient {
  /**
   * Implements the interface.
   */
  public function request(RequestInterface $request) {
    $key = $request->getMethod() . ':' . $request->getUri()->getPath();
    $path = $request->getUri()->getPath();

    if (preg_match('{/external/v1/(.*)/patrons}', $path, $matches)) {
      return $this->authenticate($request, $matches[1]);
    }

    return (new Response(new Stream('php://memory', 'w')))->withStatus(501, 'not implemented');
  }

  /**
   * Get the payload (body) of request.
   *
   * Decodes the JSON.
   */
  private function getPayload($request) {
    $stream = $request->getBody();
    $stream->seek(0);
    return json_decode($stream->getContents());
  }

  /**
   * Fake an authentication request.
   */
  private function authenticate($request, $agency_id) {
    $creds = $this->getPayload($request);
    $response = new Response(new Stream('php://memory', 'w'));
    $auth_patron = array(
      'authenticated' => FALSE,
      'patron' => NULL,
    );
    if ($creds->libraryCardNumber === 'danny' && $creds->pincode === '1111') {
      $auth_patron['authenticated'] = TRUE;
      $auth_patron['patron'] = array(
        // Patron.
        'birthday' => '1946-10-15',
        'coAddress' => NULL,
        'address' => array(
          // Address
          'country' => 'Danmark',
          'city' => 'København',
          'street' => 'Alhambravej 1',
          'postalCode' => '1826',
        ),
        // ISIL of Vesterbro bibliotek
        'preferredPickupBranch' => '113',
        'onHold' => NULL,
        'patronId' => 234143,
        'recieveEmail' => TRUE,
        'blockStatus' => NULL,
        'recieveSms' => FALSE,
        'emailAddress' => 'onkel@danny.dk',
        'phoneNumber' => '80345210',
        'name' => 'Dan Turrell',
        'receivePostalMail' => FALSE,
        'defaultInterestPeriod' => 30,
        'resident' => TRUE,
      );
    }

    $response->getBody()->write(json_encode($auth_patron));
    return $response;
  }
}
