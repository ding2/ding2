<?php

function wyrna_wayf_authenticate($attribute_list) {
  $name = $attribute_list['mail'];
  $wayfid = $attribute_list['eduPersonTargetedID'];
  return array('success' => DingWayfUser::instance()->loginWayf($name, $wayfid));
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
  }
}
