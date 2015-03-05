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

  // Our danny patron.
  private $danny = array(
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

  /**
   * Implements the interface.
   */
  public function request(RequestInterface $request) {
    $path = $request->getUri()->getPath();

    if (preg_match('{/external/v1/(?P<agency_id>.*)/patrons/authenticate$}', $path, $matches)) {
      return $this->authenticate($request, $matches);
    }
    if (preg_match('{/external/v1/(?P<agency_id>.*)/patrons/(?P<patron_id>\d+)$}', $path, $matches)) {
      return $this->update($request, $matches);
    }
    elseif (preg_match('{/external/v1/(?P<agency_id>.*)/patron/(?P<patron_id>\d+)/fees$}', $path, $matches)) {
      return $this->getFees($request, $matches);
    }
    elseif (preg_match('{/external/v1/(?P<agency_id>.*)/patrons/(?P<patron_id>\d+)/loans$}', $path, $matches)) {
      return $this->getLoans($request, $matches);
    }
    elseif (preg_match('{/external/v1/(?P<agency_id>.*)/patrons/(?P<patron_id>\d+)/reservations}', $path, $matches)) {
      return $this->getReservations($request, $matches);
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
  private function authenticate($request, $vars) {
    $creds = $this->getPayload($request);
    $response = new Response(new Stream('php://memory', 'w'));
    $auth_patron = array(
      'authenticated' => FALSE,
      'patron' => NULL,
    );
    if ($creds->libraryCardNumber === 'danny' && $creds->pincode === '1111') {
      $auth_patron['authenticated'] = TRUE;
      $auth_patron['patron'] = $this->danny;
    }

    $response->getBody()->write(json_encode($auth_patron));
    return $response;
  }

  /**
   * Fake an update request.
   *
   * We update some of the keys of danny and return the new patron.
   */
  private function update($request, $vars) {
    $update_request = $this->getPayload($request);
    $response = new Response(new Stream('php://memory', 'w'));

    $patron = $this->danny;
    if ($update_request->patron->phoneNumber) {
      $patron['phoneNumber'] = $update_request->patron->phoneNumber;
    }

    $auth_patron = array(
      'authenticated' => TRUE,
      'patron' => $patron,
    );

    $response->getBody()->write(json_encode($auth_patron));
    return $response;
  }

  /**
   * Fake fee listing.
   */
  private function getFees($request, $vars) {
    // No fees.
    $response = new Response(new Stream('php://memory', 'w'));
    $response->getBody()->write(json_encode(array()));
    return $response;
  }

  /**
   * Fake loan listing.
   */
  private function getLoans($request, $vars) {
    // No loans.
    $response = new Response(new Stream('php://memory', 'w'));
    $response->getBody()->write(json_encode(array()));
    return $response;
  }

  /**
   * Fake reservations listing.
   */
  private function getReservations($request, $vars) {
    // No reservatons.
    $response = new Response(new Stream('php://memory', 'w'));
    $response->getBody()->write(json_encode(array()));
    return $response;
  }
}
