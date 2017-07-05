<?php

/**
 * @file
 * Ding user related classes.
 */

/**
 * Exception thrown for authentication error.
 */
class DingProviderUserAuthFailure extends Exception {}

 /**
  * Exception for trying to create existing user.
  */
class DingProviderUserExistsError extends DingProviderEnduserException {

  /**
   * Construct new exception.
   */
  public function __construct($message = "", $code = 0) {
    if (empty($message)) {
      $message = t('You already have an account.');
    }
    parent::__construct($message);
  }

}
