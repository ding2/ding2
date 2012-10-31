<?php

/**
 * @file
 * Mock implementation of simpleSAML.
 */

class SimpleSAML_Auth_Simple {
  private static $attributes = array();

  /**
   * Constructor for mock object.
   */
  public function __construct($sp) {
    $attributes = variable_get('simplesaml_mock');

    if (!$attributes) {
      self::$attributes = $attributes;
    }
  }

  public function isAuthenticated() {
    $this->updateAttributes();
    return !empty(self::$attributes);
  }

  public function getAttributes() {
    $this->updateAttributes();
    return self::$attributes;
  }

  public function requireAuth() {
    $this->updateAttributes();

    if (empty(self::$attributes)) {
      drupal_set_message(t('Not WAYF authenticated.'));
      drupal_goto('<front>');
    }
  }

  public function logout() {
    variable_del('simplesaml_mock');
    self::$attributes = array();
  }

  private function updateAttributes() {
    if (empty(self::$attributes)) {
      self::$attributes = variable_get('simplesaml_mock', array());
    }
  }

  /**
   * Helper method for testing.
   */
  public static function setAttributes($attribute_list) {
    self::$attributes = $attribute_list;
    variable_set('simplesaml_mock', $attribute_list);
  }

}
