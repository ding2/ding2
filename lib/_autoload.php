<?php
/**
 * @file
 * Mock implementation of simpleSAML.
 */


class SimpleSAML_Auth_Simple {
  /**
   * Constructor, empty for now.
   */
  public function __construct($sp) {

  }

  public function isAuthenticated() {
    // @TODO handle errors.
    $error = isset($_GET['error']) ? $_GET['error'] : FALSE;
    if ($error) {
      // Handle this.
    }

    // Gateway returns attributes in $_POST if authentication goes well.
    if (!empty($_POST['eduPersonTargetedID'])) {
      $this->setAttributes($_POST);
      return TRUE;
    }

    // @TODO is this ok - maybe use $_GET instead
    /* if (isset($_GET['eduPersonTargetedID'])) {
      // set attributes
      $this->setAttribute('eduPersonTargetedID', $_GET['eduPersonTargetedID']);
      $this->setAttribute('mail', $_GET['mail']);
      return TRUE;
      } */

    // user might already be logged in
    //check in $_SESSION
    else {
      $wayf_id = $this->getAttribute('eduPersonTargetedID');
      if (isset($wayf_id)) {
        return TRUE;
      }
    }
    // user is not authenticated
    return FALSE;
  }

  public function getAttributes() {


    // @TODO .. if user is

    return isset($_SESSION['wayf_login']) ? $_SESSION['wayf_login'] : NULL;
  }

  private function setAttributes($attributes) {
    //enrich attriubutes with login_type
    $loginType = isset($_GET['logintype']) ? $_GET['logintype'] : NULL;
    if ($loginType == 'wayf') {
      $loginType = 'wayf_id';
    }
    elseif ($loginType == 'nemlogin') {
      $loginType = 'nem_id';
    }
    else {
      // default
      $loginType = 'wayf_id';
    }

    $attributes['login_type'] = $loginType;
    $_SESSION['wayf_login'] = $attributes;
  }

  public function getAttribute($name) {
    return isset($_SESSION['wayf_login'][$name][0]) ? $_SESSION['wayf_login'][$name][0] : NULL;
  }

  /* \brief redirect to gatewayf for authentication via wayf
   *
   */

  public function requireAuth($idp = NULL) {
    global $base_url;
    $home = $base_url . '/' . current_path();
    $config = variable_get('ding_wayf');
    $gateway = $config['gatewayf'];

    header('Location:' . $gateway . '?returnUrl=' . $home . '&idp=' . $idp);
    exit;
  }

  /**
   * NOTICE; this logout does a redirect to log out of wayf, and thus
   * must fake a drupal-user logout to log drupal user out in a proper way
   */
  public function logout($url = NULL) {

    // unset session variables
    if (isset($_SESSION['wayf_login'])) {
      unset($_SESSION['wayf_login']);
    }

    global $base_url;
    $config = variable_get('ding_wayf');
    $gateway = $config['gatewayf'];

    // and now we fake a drupal logout before
    // the redirect takes place
    // log out drupal user
    // @see user/user.pages.inc::user_logout()
    global $user;
    if (isset($user->mail))
      watchdog('wayf', 'Session closed for %name.', array('%name' => $user->mail));
    module_invoke_all('user_logout', $user);
    // Destroy the current session, and reset $user to the anonymous user.
    session_destroy();
    // redirect to gatewayf; pass returnUrl for simplesaml to redirect
    header('Location:' . $gateway . '?returnUrl=' . $base_url . '&op=logout');
    exit;
  }

}
