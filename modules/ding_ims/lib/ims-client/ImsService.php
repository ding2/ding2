<?php
/**
 * @file
 * ImsService class.
 */

class ImsService {
  protected $wsdlUrl;
  protected $username;
  protected $password;

  /**
   * Instantiate the ims client.
   */
  public function __construct($wsdl_url, $username, $password) {
    $this->wsdlUrl = $wsdl_url;
    $this->username = $username;
    $this->password = $password;
  }

  /**
   * Get information by FAUST number.
   *
   * @param mixed $faust_numbers
   *   Expects either a single FAUST number, or an array of them, for looking
   *   up multiple titles at a time.
   *
   * @return array
   *   Array of placements.
   */
  public function getByFaustNumber($faust_numbers) {
    // Cast to array to ensure the variable is an array and not a string
    $faust_numbers = (array) $faust_numbers;

    // Loop the faust numbers since the ims service only accepts one faust 
    // pr. request 
    $placements = array();
    foreach($faust_numbers as $faust_number) {
      $response = $this->sendRequest($faust_number);
      $placements[] = $this->extractPlacements($response);
    }

    return $placements;
  }

  /**
   * Send request to the ims server, returning the data response.
   */
  protected function sendRequest($faust_number) {
    $auth_info = array(
      'Username' => $this->username,
      'Password' => $this->password,
    );

    // New ims service.
    $client = new SoapClient($this->wsdlUrl);

    // Record the start time, so we can calculate the difference, once
    // the ims service responds.
    $start_time = explode(' ', microtime());

    // Start on the responds object.
    $response = new stdClass();
    $response->identifierInformation = array();

    // Try to get covers 40 at the time as the service has a limit.
    try {    
      $data = $client->Ping(array(
        'Credentials' => $auth_info,
        'BibliographicRecordId' => $faust_number,
      ));

      // Check if the request went through.
      if ($data->requestStatus->statusEnum != 'ok') {
        throw new ImsServiceException($data->requestStatus->statusEnum . ': ' . $data->requestStatus->errorText);
      }
    }
    catch (Exception $e) {
      // Re-throw Ims specific exception.
      throw new ImsServiceException($e->getMessage());
    }

    $stop_time = explode(' ', microtime());
    $time = floatval(($stop_time[1] + $stop_time[0]) - ($start_time[1] + $start_time[0]));

    // Drupal specific code - consider moving this elsewhere.
    if (variable_get('ims_enable_logging', FALSE)) {
      watchdog('ims', 'Completed request', WATCHDOG_DEBUG, '(' . round($time, 3) . 's): Ids: %ids', array('%ids' => implode(', ', $ids)) . ' http://' . $_SERVER["HTTP_HOST"] . $_SERVER["REQUEST_URI"]);
    }

    if (!is_array($response->identifierInformation)) {
      $response->identifierInformation = array($response->identifierInformation);
    }

    return $response;
  }
}
