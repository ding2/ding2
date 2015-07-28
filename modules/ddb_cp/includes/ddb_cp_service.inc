<?php
/**
 * @file
 * The ddbService class has the sole responsibility for communicating
 * with the DDB webservice.
 */

 /**
  * A custom exception for the DdbService class.
  */
class DdbWsException extends Exception {

  /**
   * Default constructor.
   */
  public function __construct($message, $code, Exception $previous = NULL) {
    parent::__construct($message, $code, $previous);
  }

  /**
   * Implements __toString magic function.
   *
   * @return string
   *   A formatted string for display.
   */
  public function __toString() {
    return t('Error calling DDB service:') . ' ' . $this->code . ' ' . $this->message . "\n";
  }
}

/**
 * DDB service call to handle communication with the web-service.
 */
class DdbService {

  // Private properties.
  private $uri = NULL;

  // Public properties.
  public $names = NULL;
  public $type = NULL;

  /**
   * The constructor.
   *
   * @param string $uri
   *   The optional URI of the host running the webservice. If not
   *   specified, will try to read the URI as a Drupal variable. This
   *   value can be set through the control panel.
   *
   * @throws Exception
   *   Throws a general exception if an improper URI is specified.
   */
  public function __construct($uri = NULL) {
    if ($uri) {
      if (!parse_url($uri, PHP_URL_HOST)) {
        // @todo: Should this be a DdbWsException, it's related to the web-service ?
        throw new Exception(t('You must provide a valid URI when creating a new instance of DdbService:') . ' ' . $uri);
      }
      $host = parse_url($uri, PHP_URL_HOST);
      $scheme = parse_url($uri, PHP_URL_SCHEME);

      $this->uri = isset($scheme) ? $scheme . '://' . $host : 'http://' . $host;
    }
    else {
      $this->uri = variable_get('ddb_cp_service_uri');
    }

    $this->names = $this->getHostnames();

    $this->type = 'unknown';
    if ($this->getHostname() == $this->names['prod']) {
      $this->type = 'prod';
    }
    if ($this->getHostname() == $this->names['dev']) {
      $this->type = 'dev';
    }
    if ($this->getHostname() == $this->names['stg']) {
      $this->type = 'stg';
    }
  }

  /**
   * This function returns the primary hostname of the site.
   *
   * It depends on the current standard for a Drupal multi site setup
   * in which the hostname is included in the configuration path.
   *
   * @return string
   *   A string containing the primary hostname.
   */
  private function getHostname() {
    $result = &drupal_static(__FUNCTION__);

    if (!isset($result)) {
      $parts = explode('/', conf_path());
      $result = $parts[1];
    }

    return $result;
  }

  /**
   * This function retrieves a list of hostnames from the webservice.
   *
   * In this way, naming conventions may be changed without changing
   * the code of the control panel.
   *
   * @return string
   *   An array of strings naming the 'prod', 'dev', and 'stg' sites.
   */
  private function getHostnames() {
    $result = &drupal_static(__FUNCTION__);

    if (!isset($result)) {
      if ($cache = cache_get('ddb_cp_hostnames')) {
        $result = $cache->data;
      }
      else {
        try {
          $data = $this->makeRequest('/json/hostnames?site=' . $this->getHostname(), PHP_URL_HOST);
          $data = json_decode($data);
        }
        catch (DdbWsException $e) {
          $result = NULL;
        }

        // @todo: If the exception above is triggered the $data variable will not exists?
        if (isset($data->{'result'})) {
          $result['dev'] = $data->{'result'}[0]->{'dev'};
          $result['prod'] = $data->{'result'}[0]->{'prod'};
          $result['stg'] = $data->{'result'}[0]->{'stg'};

          cache_set('ddb_cp_hostnames', $result);
        }
        else {
          $result = NULL;
        }
      }
    }

    return $result;
  }

  /**
   * This is the function that actually calls the webservice.
   *
   * @param string $query
   *   The webservice query string.
   *
   * // @todo: missing return type?
   * @return
   *   The raw result of the call.
   *
   * @throws DdbWsException
   *   Returns HTTP error code/message if unsuccessful.
   */
  private function makeRequest($query) {
    $result = drupal_http_request($this->uri . $query);
    if ($result->code != 200) {
      throw new DdbWsException($result->error, $result->code);
    }
    return $result->data;
  }

  /**
   * Executes a job on the Jenkins server.
   *
   * @param string $job
   *   A string with the name of the job to execute.
   * @param array $parms
   *   Optional parameters to pass to the job.
   *
   * @return bool
   *   Returns TRUE on success, FALSE otherwise.
   */
  public function execute($job, $parms = NULL) {
    $query = '/json/execute?job=' . urlencode($job);

    foreach ($parms as $key => $value) {
      $query .= '&' . urlencode($key) . '=' . urlencode($value);
    }

    try {
      $this->makeRequest($query);
    }
    catch (DdbWsException $e) {
      return FALSE;
    }

    return TRUE;
  }

  /**
   * Retrieves the subscription model.
   *
   * @return mixed
   *   A string containing the subscription model. FALSE if call fails.
   */
  public function model() {
    $result = &drupal_static(__FUNCTION__);

    if (!isset($result)) {
      $site = $this->names['prod'];

      try {
        $data = json_decode($this->makeRequest('/json/model?site=' . $site));
      }
      catch (DdbWsException $e) {
        drupal_set_message(t(DDB_CP_MSG_ERROR_NO_WEB_SERVICE), 'error');
        return FALSE;
      }

      if (isset($data->{'result'})) {
        $result = $data->{'result'};
      }
    }

    return $result;
  }

  /**
   * Retrieves the status record for the current site(s).
   *
   * @return mixed
   *   An array of arrays representing the JSON response from the
   *   webservice. FALSE if call fails.
   */
  public function status() {
    $result = &drupal_static(__FUNCTION__);

    if (!isset($result)) {
      $site = $this->names['prod'];

      try {
        $data = json_decode($this->makeRequest('/json/status?site=' . $site));
      }
      catch (DdbWsException $e) {
        drupal_set_message(t(DDB_CP_MSG_ERROR_NO_WEB_SERVICE), 'error');
        return FALSE;
      }

      if (isset($data->{'result'})) {
        $result = _ddb_cp_object_to_array($data->{'result'});
      }
      else {
        return FALSE;
      }
    }

    return $result;
  }

  /**
   * Retrieves a list of templates available for creating a new developer site.
   *
   * @param string $site
   *   The full DNS name of the current site.
   *
   * @return mixed
   *   Returns an array of strings with template names. FALSE if
   *   call fails.
   */
  public function templates($site) {
    try {
      $data = json_decode($this->makeRequest('/json/templates?site=' . $site));
    }
    catch (DdbWsException $e) {
      drupal_set_message(t(DDB_CP_MSG_ERROR_NO_WEB_SERVICE), 'error');
      return FALSE;
    }

    if (isset($data->{'result'})) {
      return $data->{'result'};
    }
    else {
      return array();
    }
  }

  /**
   * Retrieves the full test report from the Jenkins server.
   *
   * @param string $site
   *   The full DNS name of the site.
   * @param string $number
   *   The optional build number. Defaults to latest.
   *
   * @return mixed
   *   The XML test report. FALSE if call fails.
   */
  public function testReport($site, $number = NULL) {
    $query = '/xml/test_report?site=' . $site;
    if (isset($number)) {
      $query .= '&number=' . $number;
    }
    try {
      return $this->makeRequest($query);
    }
    catch (DdbWsException $e) {
      return FALSE;
    }
  }

  /**
   * Retrieves a brief test report from the Jenkins server.
   *
   * @param string $site
   *   The full DNS name of the site.
   * @param string $number
   *   The optional build number. Defaults to latest.
   *
   * @return mixed
   *   The XML test report. FALSE if call fails.
   */
  public function testResult($site, $number = NULL) {
    $query = '/xml/test_result?site=' . $site;
    if (isset($number)) {
      $query .= '&number=' . $number;
    }
    try {
      return $this->makeRequest($query);
    }
    catch (DdbWsException $e) {
      return FALSE;
    }
  }
}

/**
 * Convert the object format returned by json_decode() to an array of arrays.
 *
 * @todo: This parameter is strange as the function calls it self in line, so it may be a object or an array?
 * @param mixed $obj
 *   An object created by json_decode().
 *
 * @return mixed
 *   The json_decode() object converted to an array of arrays.
 */
function _ddb_cp_object_to_array($obj) {
  $arr = [];
  $_arr = is_object($obj) ? get_object_vars($obj) : $obj;
  foreach ($_arr as $key => $val) {
    $val = (is_array($val) || is_object($val)) ? _ddb_cp_object_to_array($val) : $val;
    $arr[$key] = $val;
  }
  return $arr;
}
