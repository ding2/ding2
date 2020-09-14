<?php
/**
 * @file
 * AdditionalInformationService class.
 */

class AdditionalInformationService {
  protected $wsdlUrl;
  protected $username;
  protected $group;
  protected $password;
  protected $forceUrl;

  /**
   * Instantiate the addi client.
   */
  public function __construct($wsdl_url, $username, $group, $password, $forceUrl = FALSE) {
    $this->wsdlUrl = $wsdl_url;
    $this->username = $username;
    $this->group = $group;
    $this->password = $password;
    $this->forceUrl = $forceUrl;
  }

  /**
   * Get information by ISBN.
   *
   * @param mixed $isbn
   *   Expects either a single ISBN, or an array of them, for looking up
   *   multiple materials at a time.
   *
   * @return array
   *   Array of the images that were found.
   */
  public function getByIsbn($isbn) {
    $isbn = str_replace('-', '', $isbn);

    $identifiers = $this->collectIdentifiers('isbn', $isbn);
    $response = $this->sendRequest($identifiers);
    return $this->extractAdditionalInformation('isbn', $response);
  }

  /**
   * Get information by FAUST number.
   *
   * @param mixed $faust_number
   *   Expects either a single FAUST number, or an array of them, for looking
   *   up multiple materials at a time.
   *
   * @return array
   *   Array of the images that were found.
   */
  public function getByFaustNumber($faust_number) {
    $identifiers = $this->collectIdentifiers('faust', $faust_number);
    $response = $this->sendRequest($identifiers);
    return $this->extractAdditionalInformation('faust', $response);
  }

  /**
   * Get information by local ID and library code.
   *
   * @param mixed $local_id
   *   Expects either a single object with localIdentifier and libraryCode
   *   attributes, or an array of such objects.
   *
   * @return array
   *   Array of the images that were found.
   */
  public function getByLocalIdentifier($local_id) {
    $identifiers = $this->collectIdentifiers('localIdentifier', $local_id);
    $response = $this->sendRequest($identifiers);
    return $this->extractAdditionalInformation('localIdentifier', $response);
  }

  /**
   * Get information by PID (supported in moreinfo version 2.7 and up).
   *
   * @param mixed $pid
   *   Expects either a single FAUST number, or an array of them, for looking
   *   up multiple materials at a time.
   *
   * @return array
   *   Array of the images that were found.
   */
  public function getByPid($pid) {
    $identifiers = $this->collectIdentifiers('pid', $pid);
    $response = $this->sendRequest($identifiers);
    return $this->extractAdditionalInformation('pid', $response);
  }

  /**
   * Expand the provided IDs into the array structure used in sendRequest.
   */
  protected function collectIdentifiers($id_type, $ids) {
    if (!is_array($ids)) {
      $ids = array($ids);
    }

    $identifiers = array();
    foreach ($ids as $id) {
      // If we're passed objects from getByLocalIdentifier, convert them
      // to arrays.
      if (is_object($id)) {
        $identifiers[] = (array) $id;
      }
      // Otherwise, just map the ID type to the ID number.
      else {
        $identifiers[] = array($id_type => $id);
      }
    }

    return $identifiers;
  }

  /**
   * Send request to the addi server, returning the data response.
   */
  protected function sendRequest($identifiers) {
    $auth_info = array(
      'authenticationUser' => $this->username,
      'authenticationGroup' => $this->group,
      'authenticationPassword' => $this->password,
    );

    // New moreinfo service.
    $client = new SoapClient($this->wsdlUrl . '/?wsdl');

    // The soap client uses the URL from the namespace in the WSDL, which during
    // test and in other situations not always is the behaviour one whats. This
    // allows you to force the end-point URL.
    If ($this->forceUrl) {
      $client->__setLocation($this->wsdlUrl . '/');
    }

    // Record the start time, so we can calculate the difference, once
    // the addi service responds.
    $start_time = explode(' ', microtime());

    // Start on the responds object.
    $response = new stdClass();
    $response->identifierInformation = array();

    // Try to get covers 40 at the time as the service has a limit.
    try {
      $offset = 0;
      $ids = array_slice($identifiers, $offset, 40);
      while (!empty($ids)) {
        $data = $client->moreInfo(array(
          'authentication' => $auth_info,
          'identifier' => $ids,
        ));

        // Check if the request went through.
        if ($data->requestStatus->statusEnum != 'ok') {
          throw new AdditionalInformationServiceException($data->requestStatus->statusEnum . ': ' . $data->requestStatus->errorText);
        }

        // Move result into the responce object.
        $response->requestStatus = $data->requestStatus;
        if (is_array($data->identifierInformation)) {
          // If more than one element have been found an array is returned.
          $response->identifierInformation = array_merge($response->identifierInformation, $data->identifierInformation);
        }
        else {
          // If only one "cover" have been request, we need to wrap the data in
          // an array.
          $response->identifierInformation = array_merge($response->identifierInformation, array($data->identifierInformation));
        }

        // Single image... not array but object.
        $offset += 40;
        $ids = array_splice($identifiers, $offset, 40);
      }
    }
    catch (Exception $e) {
      // Re-throw Addi specific exception.
      throw new AdditionalInformationServiceException($e->getMessage());
    }

    $stop_time = explode(' ', microtime());
    $time = floatval(($stop_time[1] + $stop_time[0]) - ($start_time[1] + $start_time[0]));

    // Drupal specific code - consider moving this elsewhere.
    if (variable_get('addi_enable_logging', FALSE)) {
      watchdog('addi', 'Completed request (' . round($time, 3) . 's): Ids: %ids', array('%ids' => implode(', ', $ids)), WATCHDOG_DEBUG, 'http://' . $_SERVER["HTTP_HOST"] . $_SERVER["REQUEST_URI"]);
    }

    if (!is_array($response->identifierInformation)) {
      $response->identifierInformation = array($response->identifierInformation);
    }

    return $response;
  }

  /**
   * Extract the data we need from the server response.
   */
  protected function extractAdditionalInformation($id_name, $response) {
    $additional_informations = array();

    foreach ($response->identifierInformation as $info) {
      // To avoid unnecessary downloads we also check that the identifier from
      // the result is of the expected type (e.g. $id_name = 'pid').
      if (empty($info->identifierKnown) && !isset($info->identifier->$id_name)) {
        continue;
      }

      // First check for an internal moreinfo cover image.
      $thumbnail_url = $detail_url = NULL;
      $cover_image = isset($info->coverImage) ? $info->coverImage : FALSE;
      if ($cover_image) {
        if (!is_array($cover_image)) {
          $cover_image = array($cover_image);
        }

        foreach ($cover_image as $image) {
          switch ($image->imageSize) {
            case 'thumbnail':
              $thumbnail_url = $image->_;
              break;

            case 'detail':
              $detail_url = $image->_;
              break;

            default:
              // Do nothing other image sizes may appear but ignore them for
              // now.
          }
        }
      }

      // In some cases moreinfo will return external URLs to a covers supplied
      // by the owner of the record.
      $extern_url = NULL;
      if (isset($info->externUrl)) {
        // Sometimes moreinfo will provide several links. Since it's external we
        // have no general way of detecting the quality/size of each image link
        // and therefore we will just have to pick the first one.
        if (is_array($info->externUrl)) {
          $extern_url = $info->externUrl[0]->_;
        }
        else {
          $extern_url = $info->externUrl->_;
        }
      }

      $additional_info = new AdditionalInformation(
        $thumbnail_url,
        $detail_url,
        $extern_url
      );
      $additional_informations[$info->identifier->$id_name] = $additional_info;
    }

    return $additional_informations;
  }
}
