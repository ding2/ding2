<?php
/**
 * @file
 * The ddbService class has the sole responsibility for communicating
 * with the DDB webservice.
 */

/**
 * DDB service call to handle communication with the web-service.
 */
class ddbService {

  // Private properties
  private $uri = NULL;

  // Public properties
  public $names = NULL;
  public $type = NULL;


  // Private methods
  private function get_hostname() {
    $result = &drupal_static(__FUNCTION__);

    if (!isset($result)) {
      $parts = explode('/', conf_path());
      $result = $parts[1];
    }

    return $result;
  }

  private function get_hostnames() {
    $result = &drupal_static(__FUNCTION__);

    if (!isset($result)) {
      if ($cache = cache_get('ddb_hostnames')) {
        $result = $cache->data;
      }
      else {
        try {
          $data = json_decode($this->make_request('/json/hostnames?site=' . $this->get_hostname(), PHP_URL_HOST));
        } catch (Exception $e) {
        }

        if (isset($data->{'result'})) {
          $result['dev'] = $data->{'result'}[0]->{'dev'};
          $result['prod'] = $data->{'result'}[0]->{'prod'};
          $result['stg'] = $data->{'result'}[0]->{'stg'};

          cache_set('ddb_hostnames', $result, 'cache', time() + 3600);
        }
        else {
          $result = NULL;
        }
      }
    }

    return $result;
  }

  private function make_request($query) {
    $result = drupal_http_request($this->uri . $query);
    if ($result->code == 200) {
      return $result->data;
    }
    else {
      throw new Exception(t('Error calling DDB service:') . ' ' . $result->code . ' ' . $result->error);
    }
  }

  // Public methods
  public function __construct($uri = NULL) {
    if ($uri) {
      if (!parse_url($uri, PHP_URL_HOST)) {
        throw new Exception(t('You must provide a valid URI when creating a new instance of ddbService:') . ' ' . $url);
      }
      $host = parse_url($uri, PHP_URL_HOST);
      $scheme = parse_url($uri, PHP_URL_SCHEME);
      $uri = isset($scheme) ? $scheme . '://' . $host : 'http://' . $host;
    }
    else {
      $this->uri = variable_get('ddb_service_url');
    }

    $parts = explode('.', $this->get_hostname());
    $this->type = 'prod';
    if (preg_match('/-dev$/', $parts[0])) {
      $this->type = 'dev';
    }
    if (preg_match('/-stg$/', $parts[0])) {
      $this->type = 'stg';
    }

    $this->names = $this->get_hostnames();
  }

  public function execute($job, $parms = NULL) {
    $query = '/json/execute?job=' . urlencode($job);

    foreach ($parms as $key => $value) {
      $query .= '&' . urlencode($key) . '=' . urlencode($value);
    }

    try {
      $this->make_request($query);
    } catch (Exception $e) {
      return FALSE;
    }

    return TRUE;
  }

  public function model() {
    $result = &drupal_static(__FUNCTION__);

    if (!isset($result)) {
      $site = $this->names['prod'];

      try {
        $data = json_decode($this->make_request('/json/model?site=' . $site));
      } catch (Exception $e) {
        drupal_set_message(t(DDB_CP_MSG_ERROR_NO_WEB_SERVICE), 'error');
        return FALSE;
      }

      if (isset($data->{'result'})) {
        $result = $data->{'result'};
      }
    }

    return $result;
  }

  public function status() {
    $result = &drupal_static(__FUNCTION__);

    if (!isset($result)) {
      $site = $this->names['prod'];

      try {
        $data = json_decode($this->make_request('/json/status?site=' . $site));
      } catch (Exception $e) {
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

  public function templates($site) {
    try {
      $data = json_decode($this->make_request('/json/templates?site=' . $site));
    } catch (Exception $e) {
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

  public function test_report($site, $number = NULL) {
    $query = '/xml/test_report?site=' . $site;
    if (isset($number)) {
      $query .= '&number=' . $number;
    }

    try {
      return $this->make_request($query);
    } catch (Exception $e) {
      return FALSE;
    }
  }

  public function test_result($site, $number = NULL) {
    $query = '/xml/test_result?site=' . $site;
    if (isset($number)) {
      $query .= '&number=' . $number;
    }

    try {
      return $this->make_request($query);
    } catch (Exception $e) {
      return FALSE;
    }
  }
}
