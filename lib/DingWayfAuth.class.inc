<?php
/**
 * @file
 * Wrapper class for communication with either SimpleSAMLphp or a WAYF gateway.
 *
 * For information about the gateway contact DBC.
 */


class DingWayfAuth {

  protected $serviceProvider = NULL;
  protected $saml = FALSE;

  /**
   * Default constructor.
   */
  public function __construct($service_provider) {
    $type = variable_get('ding_wayf_type', FALSE);
    if (!$type) {
      drupal_set_message(t('The WAYF login module is not configured yet, plase contact the site administrator.'), 'error', FALSE);
    }

    // If type is local we need to connect to the local SimpleSAMLphp
    // installation.
    switch ($type) {
      case 'local':
        $auto_loader = ding_wayf_check_simplesamlphp();
        if ($auto_loader) {
          // Load local SimpleSAMLphp.
          require_once $auto_loader;
          $this->saml = new SimpleSAML_Auth_Simple($service_provider);
        }
        break;

      case 'gateway':
        $this->saml = new DingWayfAuthGateway();
        break;

      default:
        watchdog('ding_wayf', 'Unknown connection type found in DingWayfAuth constructor.', array(), WATCHDOG_ERROR);
        break;
    }

    // Save the service provider id for later.
    $this->serviceProvider = $service_provider;
  }

  /**
   * Check if the current user is authenticated.
   *
   * @return bool
   *   TRUE is the user is authenticated else FALSE.
   */
  public function isAuthenticated() {
    // User logged into Drupal.
    if ($this->saml && $this->saml->isAuthenticated()) {
      // User is logged into WAYF.
      return TRUE;
    }

    return FALSE;
  }

  /**
   * Get attributes from the authentication provider.
   *
   * @return null|array
   *   If attributes have been set an array is returned else NULL.
   */
  public function getAttributes() {
    return $this->saml->getAttributes();
  }

  /**
   * Get named attribute from the authentication provider.
   *
   * @param string $name
   *   Name of the attribute to get.
   *
   * @return null|array
   *   If the attribute have been set it is returned else NULL.
   */
  public function getAttribute($name) {
    return $this->saml->getAttribute($name);
  }

  /**
   * Redirects the user to the authentication providers login page.
   *
   * Note: that the TRUE return value used not be used as a redirect will happen
   * if the saml connection exists.
   *
   * @param string $idp
   *   If using a gateway the identity provider string can be sent with the
   *   redirect.
   *
   * @return bool
   *   If the connection to saml have not been created FALSE is returned else
   *   TRUE.
   */
  public function requireAuth($idp = NULL) {
    if ($this->saml) {
      if ($this->saml instanceof DingWayfAuthGateway) {
        $gateway = variable_get('ding_wayf_gateway', array('address' => 'https://dringo-ssl.dbc.dk/gatewayf'));
        $this->saml->requireAuth($idp, $gateway['address']);
      }
      else {
        $this->saml->requireAuth();
      }
    }
    else {
      watchdog('ding_wayf', 'SAML connection not found in DingWayfAuth requireAuth function.', array(), WATCHDOG_ERROR);
      return FALSE;
    }

    return TRUE;
  }

  /**
   * Logout the user and redirect.
   *
   * @param string $url
   *   If given the user will be redirect to this URL after logout.
   */
  public function logout($url = NULL) {
    if ($this->saml) {
      if ($this->saml instanceof DingWayfAuthGateway) {
        // Get configuration.
        $gateway = variable_get('ding_wayf_gateway', array('address' => 'https://dringo-ssl.dbc.dk/gatewayf'));
        $this->saml->logout($url, $gateway['address']);
      }
      else {
        $this->saml->logout($url);
      }
    }
  }
}

/**
 * Class DingWayfAuthGateway.
 *
 * Wrapper class for communication with the SimpleSAMLphp DBC gateway.
 */
class DingWayfAuthGateway {
  /**
   * Check is the current user is authenticated at the gateway.
   *
   * @return bool
   *   TRUE if user is authenticated else FALSE.
   */
  public function isAuthenticated() {
    $error = isset($_GET['error']) ? $_GET['error'] : FALSE;
    if ($error) {
      watchdog('ding_wayf', 'The gateway returned an error: %error', array('%error' => $error), WATCHDOG_ERROR);
    }

    // The gateway returns attributes in the $_POST array, if authentication
    // have gone well.
    if (!empty($_POST['eduPersonTargetedID'])) {
      $this->setAttributes($_POST);
      return TRUE;
    }
    else {
      $wayf_id = $this->getAttribute('eduPersonTargetedID');
      if (isset($wayf_id)) {
        return TRUE;
      }
    }

    // User is not authenticated.
    return FALSE;
  }

  /**
   * Get all attributes stored in the session.
   *
   * @return null|array
   *   If attributes have been set an array is returned else NULL.
   */
  public function getAttributes() {
    return isset($_SESSION['wayf_login']) ? $_SESSION['wayf_login'] : NULL;
  }

  /**
   * Stores attributes in the users current session.
   *
   * @todo do we really need to store the information.
   *
   * @param array $attributes
   *   Attributes from the gateway responce.
   */
  protected function setAttributes($attributes) {
    // Enrich attributes with login_type.
    $login_type = isset($_GET['logintype']) ? $_GET['logintype'] : NULL;

    if ($login_type == 'wayf') {
      $login_type = 'wayf_id';
    }

    if ($login_type == 'nemlogin') {
      $login_type = 'nem_id';
    }
    else {
      $login_type = 'wayf_id';
    }

    $attributes['login_type'] = $login_type;

    // @todo filter the data before storing in the session.
    $_SESSION['wayf_login'] = $attributes;
  }

  /**
   * Get named attribute from the current users session.
   *
   * @param string $name
   *   Name of the attribute to get from the session.
   *
   * @return null|string
   *   If attribute is found it is returned else NULL.
   */
  public function getAttribute($name) {
    return isset($_SESSION['wayf_login'][$name][0]) ? $_SESSION['wayf_login'][$name][0] : NULL;
  }

  /**
   * Redirect the user to WAYF gateway for authentication.
   *
   * @param string $idp
   *   The identity provider string to use.
   * @param string $gateway
   *   The address of the gateway.
   */
  public function requireAuth($idp = NULL, $gateway = NULL) {
    global $base_url;
    $home = $base_url . '/' . current_path();

    // Redirect the user by setting the location header.
    header('Location:' . $gateway . '?returnUrl=' . $home . '&idp=' . $idp);
    exit;
  }

  /**
   * Logout the user from the gateway.
   *
   * If the user is logged into drupal the URL given is "/user/logout". So this
   * function do not need to think about drupal logout.
   *
   * @param string $url
   *   URL to redirect to after WAYF logout.
   * @param string $gateway
   *   The address of the gateway.
   */
  public function logout($url = NULL, $gateway = NULL) {
    // Unset session variables.
    if (isset($_SESSION['wayf_login'])) {
      unset($_SESSION['wayf_login']);
    }

    // If the $url is empty get the base url a use that in the redirect.
    if (is_null($url)) {
      global $base_url;
      $url = $base_url;
    }

    // Redirect to the gateway.
    header('Location:' . $gateway . '?returnUrl=' . $url . '&op=logout');
    exit;
  }
}
