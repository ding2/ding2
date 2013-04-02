<?php

/**
 * @file
 * Mock implementation of simpleSAML.
 */
class SimpleSAML_Auth_Simple {
  /**
   * Constructor, empty for now.
   */
  public function __construct($sp) {}

  public function isAuthenticated() {
    // gateway returns attributes if authentication goes well 
    // for now only wayf-id and mail
    if (isset($_GET['eduPersonTargetedID'])) {
      // set attributes
      $this->setAttribute('eduPersonTargetedID', $_GET['eduPersonTargetedID']);
      $this->setAttribute('mail', $_GET['mail']);
      return TRUE;
    }
    // user might already be logged in
    //check in $_SESSION
    else {
      $ID = $this->getAttribute('eduPersonTargetedID');
      if (isset($ID)) {
        return TRUE;
      }
    }
    // user failed authentication
    return FALSE;
  }

  public function getAttributes() {
    return isset($_SESSION['wayf_login']) ? $_SESSION['wayf_login'] : NULL;
  }

  private function setAttribute($name, $value) {
    $_SESSION['wayf_login'][$name][0] = $value;
  }

  private function getAttribute($name) {
    return isset($_SESSION['wayf_login'][$name][0]) ? $_SESSION['wayf_login'][$name][0] : NULL;
  }

  public function requireAuth($idp = NULL) {
    global $base_url;
    $home = $base_url . '/' . current_path();
    $config = variable_get('ding_wayf');
    $gateway = $config['gatewayf'];

    header('Location:' . $gateway . '?returnUrl=' . $home . '&idp=' . $idp);
    exit;
  }

  public function logout($url = NULL) {
    global $base_url;
    $config = variable_get('ding_wayf');
    $gateway = $config['gatewayf'];
  
   $url = $base_url.'/'.$config['redirect'];
   
    unset($_SESSION['wayf_login']);
    if (isset($url)) {
      header('Location:' . $gateway . '?returnUrl=' . $url . '&op=logout');
      exit;
    }
  }

}
