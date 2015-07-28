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
class FBSFakeHttpClient implements HttpClient {

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
    'receiveEmail' => TRUE,
    'blockStatus' => NULL,
    'receiveSms' => FALSE,
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

    $pathes = array(
      '(?P<agency_id>.*)/patrons/authenticate$' => 'authenticate',
      '(?P<agency_id>.*)/patrons/(?P<patron_id>\d+)$' => 'update',
      '(?P<agency_id>.*)/patron/(?P<patron_id>\d+)/fees$' => 'getFees',
      '(?P<agency_id>.*)/patrons/(?P<patron_id>\d+)/loans$' => 'getLoans',
      '(?P<agency_id>.*)/patrons/(?P<patron_id>\d+)/reservations$' => 'getReservations',
      '(?P<agency_id>.*)/catalog/availability$' => 'getAvailability',
      '(?P<agency_id>.*)/catalog/holdings$' => 'getHoldings',
      '(?P<agency_id>.*)/branches$' => 'getBranches',
    );

    foreach ($pathes as $request_path => $method) {
      if (preg_match('{/external/v1/' . $request_path . '$}', $path, $matches)) {
        return $this->{$method}($request, $matches);
      }
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
   * Get parsed query string.
   */
  private function getQuery($request) {
    $query = $request->getUri()->getQuery();

    $result = array();
    // Naive implementation, but I think it'll do.
    foreach (explode('&', $query) as $part) {
      list($name, $val) = explode('=', $part);
      if (isset($result[$name])) {
        if (is_array($result[$name])) {
          $result[$name][] = $val;
        }
        else {
          $result[$name] = array($result[$name], $val);
        }
      }
      else {
        $result[$name] = $val;
      }
    }

    return $result;
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

    if ($update_request->patron->emailAddress) {
      $patron['emailAddress'] = $update_request->patron->emailAddress;
    }

    if ($update_request->patron->preferredPickupBranch) {
      $patron['preferredPickupBranch'] = $update_request->patron->preferredPickupBranch;
    }

    if ($update_request->patron->onHold) {
      $patron['onHold'] = $update_request->patron->onHold;
    }

    $patron['receiveSms'] = (bool) $update_request->patron->receiveSms;
    $patron['receiveEmail'] = (bool) $update_request->patron->receiveEmail;


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

  /**
   * Fake availability.
   */
  private function getAvailability($request, $vars) {
    $response = new Response(new Stream('php://memory', 'w'));

    $availability = array();

    foreach ((array) $this->getQuery($request)['recordid'] as $record_id) {
      $availability[] = array(
        'recordId' => $record_id,
        'available' => TRUE,
        'reservable' => TRUE,
      );
    }

    $response->getBody()->write(json_encode($availability));
    return $response;
  }

  /**
   * Fake holdings.
   */
  private function getHoldings($request, $vars) {
    $response = new Response(new Stream('php://memory', 'w'));

    $holdings = array();

    foreach ((array) $this->getQuery($request)['recordid'] as $record_id) {
      $holdings[] = array(
        'recordId' => $record_id,
        'reservable' => TRUE,
        'holdings' => array(
          array(
            // Holding.
            'materials' => array(
              array(
                // Material.
                'itemNumber' => '123456',
                'available' => TRUE,
              ),
            ),
            'branch' => array(
              // AgencyBranch.
              'branchId' => '113',
              'title' => 'Andeby Bibliotek',
            ),
            'department' => array(
              // AgencyDepartment.
              'departmentId' => 'DEP1',
              'title' => 'Voksne',
            ),
            'location' => array(
              // AgencyLocation.
              'locationId' => 'LOC1',
              'title' => 'Reol 3',
            ),
            'sublocation' => array(
              // AgencySublocation.
              'sublocationId' => 'SUB1',
              'title' => 'Hylde 2',
            ),
          )
        ),
      );
    }

    $response->getBody()->write(json_encode($holdings));
    return $response;
  }

  /**
   * Fake holdings.
   */
  private function getBranches($request, $vars) {
    $response = new Response(new Stream('php://memory', 'w'));

    $branches = array(
      // Messed up ordering, so we'll see if they're properly sorted.
      array(
        'branchId' => 114,
        'title' => 'Gåserød Bibliotek',
      ),
      array(
        'branchId' => 113,
        'title' => 'Andeby Bibliotek',
      ),
      array(
        'branchId' => 115,
        'title' => 'Andelev Bibliotek',
      ),
      array(
        'branchId' => 99999999,
        'title' => 'Langbortistan Bibliotek',
      ),
      array(
        'branchId' => 123,
        'title' => 'Usleravnekrog Bibliotek',
      ),
    );

    $response->getBody()->write(json_encode($branches));
    return $response;
  }
}
