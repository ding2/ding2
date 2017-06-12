<?php
/**
 * @file
 * Provides a client for the Axiell Aleph library information webservice.
 */

require __DIR__ . '../../../vendor/autoload.php';

use GuzzleHttp\Client;

class AlephClient {
  /**
   * @var $base_url
   * The base server URL to run the requests against.
   */
  private $base_url;

  /**
   * @var $client
   * The GuzzleHttp Client.
   */
  private $client;

  /**
   * @var $library_id
   * The Aleph library ID.
   */
  private $library_id = 'ICE53';

  /**
   * Constructor, checking if we have a sensible value for $base_url.
   *
   * @param string $base_url
   *   The base url for the Aleph end-point.
   *
   * @throws \Exception
   */
  public function __construct($base_url) {
    if (stripos($base_url, 'http') === 0 && filter_var($base_url, FILTER_VALIDATE_URL, FILTER_FLAG_SCHEME_REQUIRED)) {
      $this->base_url = $base_url;
      $this->client = new GuzzleHttp\Client();
    }
    else {
      // TODO: Use a specialised exception for this.
      throw new Exception('Invalid base URL: ' . $base_url);
    }
  }

  /**
   * Perform request to the Aleph server.
   *
   * @param string $method
   *    The query method (GET, POST, etc.).
   * @param array $params
   *    Query string parameters in the form of key => value.
   * @param bool $check_status
   *    Check the status element, and throw an exception if it is not ok.
   *
   * @return DOMDocument
   *    A DOMDocument object with the response.
   */
  private function request($method, $operation, $params, $check_status = TRUE) {
    $query = array(
      'op' => $operation,
      'library' => $this->library_id
    );

    $options = array(
      'query' => array_merge($query, $params),
      'allow_redirects' => FALSE
    );

    // Send the request.
    $response = $this->client->request($method, $this->base_url, $options);

    // Status from Aleph is OK.
    if ($response->getStatusCode() == 200) {
      $dom = new DOMDocument();
      $dom->loadXML($response->getBody());

      // Check for errors from Aleph and throw error exception.
      $error_nodes = $dom->getElementsByTagName('error');

      if (!empty($error_nodes[0])) {
        $error_message = $error_nodes[0]->nodeValue;
      }

      if (!$check_status || !empty($error_message)) {
        throw new AlephClientCommunicationError('Status is not okay: ' . $error_message);
      }

      // If there's no errors, return the dom.
      else {
        return $dom;
      }
    }

    // Throw exception if the status from Aleph is not OK.
    else {
      throw new AlmaClientHTTPError('Request error: ' . $request->code . $request->error);
    }
  }

  /**
   * Authenticate against Aleph.
   *
   * @param string $bor_id
   *    The user ID (z303-id).
   *
   * @param string $verification
   *    The password.
   *
   * @return array $return
   *    Array with user information and 'success'-key with true or false.
   */
  public function authenticate($bor_id, $verification) {
    $return = array(
      'success' => FALSE,
    );

    try {
      $res = $this->request('GET', 'bor-auth', array(
        'bor_id' => $bor_id,
        'verification' => $verification
      ));

      if ($res) {
        $return['success'] = TRUE;
      }

      // Set creds.
      $return['creds'] = array(
        'name' => $bor_id,
        'pass' => $verification,
      );
    }
    catch (Exception $e) {
      watchdog('aleph', 'Authentication error for user @user: “@message”', array(
        '@user' => $bor_id, '@message' => $e->getMessage()
      ), WATCHDOG_ERROR);
    }

    return $return;
  }
}

/**
 * Define exceptions for different error conditions inside the Aleph client.
 */
class AlephClientInvalidURLError extends Exception { }

class AlephClientHTTPError extends Exception { }

class AlephClientCommunicationError extends Exception { }

class AlephClientInvalidPatronError extends Exception { }

class AlephClientUserAlreadyExistsError extends Exception { }

class AlephClientBorrCardNotFound extends Exception { }

class AlephClientReservationNotFound extends Exception { }
