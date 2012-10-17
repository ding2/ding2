<?php

/**
 * @file
 * Mock implementation of simpleSAML.
 */

class SimpleSAML_Auth_Simple {
  private $attributes;

  /**
   * Constructor for mock object.
   */
  public function __construct($sp) {
  }

  public function isAuthenticated() {
    return isset($this->attributes);
  }

  public function getAttributes() {
    return $this->attributes;
  }

  public function requireAuth() {

  }

  public function logout() {
    unset($this->attributes);
  }

  /**
   * Helper method for testing.
   */
  public function setAttributes($attribute_list) {
    $this->attributes = $attribute_list;
  }

}
