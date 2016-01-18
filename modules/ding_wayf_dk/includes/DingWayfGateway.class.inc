<?php
/**
 * @file
 * Simple class for communication with the SimpleSAMLphp DBC gateway.
 */

namespace WAYF;
use WAYF\SPortoException;

/**
 * DingWayfGateway class
 */
class DingWayfGateway implements WayfServiceInterface {
  protected $config = array();

  /**
   * Default construct for the class.
   *
   * @param array $config
   *   WAYF configuration. This is not used by the object but it's the default
   *   parameter when the class is created in the wayf_dk module. It's used by
   *   other service classes. So here it's simply overridden with gateway WAYF
   *   settings.
   */
  public function __construct(array $config) {
    $this->config = $config;

    // Note: This is a config override hack.
    $this->config['gateway'] = variable_get('ding_wayf_dk_gateway_endpoint', '');
    $this->config['return'] = array(
      'login' => variable_get('ding_wayf_dk_gateway_consumer', ''),
      'logout' => variable_get('ding_wayf_dk_gateway_logout_endpoint', ''),
    );
  }

  /**
   * Authentication with the Single SignOn Service.
   *
   * @param array $providerids
   *   Provider ids are used for scoping in the wayf_dk_login service class, but
   *   it's not used by this service class.
   *
   * @return array
   *   The response from the gateway.
   *
   * @throws \WAYF\SPortoException
   *   Is thrown on gateway error.
   */
  public function authenticate($providerids = array()) {
    // Check error callback.
    $error = isset($_GET['error']) ? $_GET['error'] : FALSE;
    if ($error) {
      watchdog('ding_wayf', 'The gateway returned an error: %error', array('%error' => $error), WATCHDOG_ERROR);
      throw new SPortoException('The gateway returned an error: ' . $error);
    }

    // The gateway returns attributes in the $_POST array, if authentication
    // have gone well.
    if (empty($_POST['eduPersonTargetedID'])) {

      // Redirect the user by setting the location header.
      header('Location:' . $this->config['gateway'] . '?returnUrl=' . $this->config['return']['login'] . '&idp=wayf');
      exit;
    }
    else {
      if (!empty($_POST['eduPersonTargetedID'])) {
        // @TODO: WHAT should be store ind the session.
        $_SESSION['wayf_dk_login'] = array(
          'nameID' => '',
          'sessionIndex' => '',
        );

        // We don't have a XML message in this service class, so we simply
        // return an empty message. It makes debugging harder, but it should be
        // okay.
        return array(
          'attributes' => $_POST,
          'response' => '',
        );
      }
    }
  }

  /**
   * Logout using the current session information.
   */
  public function logout() {
    // Remove session information to end redirect loop in logout endpoint. This
    // assumes that we get logged out at WAYF. This is not optimal, but the best
    // we have.
    unset($_SESSION['wayf_dk_login']);

    // Redirect to the gateway.
    header('Location:' . $this->config['gateway'] . '?returnUrl=' . $this->config['return']['logout'] . '&op=logout');
    exit;
  }

  /**
   * Check if the user is logged in.
   *
   * As we don't know if the user is logged in we simply check if session WAYF
   * variable exists for the user. This don't grantee that the user is logged
   * into WAYF, but it's the best we have.
   */
  public function isLoggedIn() {
    return isset($_SESSION['wayf_dk_login']);
  }

  /**
   * Generate sp metadata based on configuration.
   *
   * @return string
   *   Message that no metadata is provided by this service class.
   */
  public function getMetadata() {
    return 'No metadata available for the current service class.';
  }
}
