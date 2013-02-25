<?php

function wyrna_wayf_authenticate($name, $wayfid) { 
  $return = array('success'=>FALSE);
  
  if( DingWayfUser::instance()->loginWayf($name, $wayfid) ){
  $return['creds'] = array(
      'name' => $name,
      'pass' => $wayfid,
    );

    $return['user'] = array(
      'data' => array('display_name' => $name),
      'mail' => $name,
    );
    $return['success'] = TRUE;
    $return['messages'] = array('HEJ', 'notice');
  }
  return $return;
}

function wyrna_wayf_bind($name, $wayfid) {
  return DingWayfUser::instance()->bindWayf($name, $wayfid);
}

function wyrna_wayf_delete($name) {
  return DingWayfUser::instance()->deleteWayf($name);
}

class DingWayfUser {
  private static $instance;
  protected $validUsers = array();

  private function __construct() {
    
    variable_set('wyrna_users',
        array('eduPersonTargetedID' => 'WAYF-1234567890', 'mail' => 'dummy@dbc.dk',));
    
    $this->validUsers = variable_get('wyrna_users', array());
  }

  public static function instance() {
    if (!isset(self::$instance)) {
      self::$instance = new DingWayfUser();
    }

    return self::$instance;
  }

  public function deleteWayf($name) {
    unset($this->validUsers[$name]);
    variable_set('wyrna_users', $this->validUsers);
  }

  public function loginWayf($name, $wayfid) {
    return isset($this->validUsers[$name]) && $this->validUsers[$name] == $wayfid;
  }

  public function bindWayf($name, $wayfid) {
    $this->validUsers[$name] = $wayfid;
    variable_set('wyrna_users', $this->validUsers);
    return TRUE;
  }
}
