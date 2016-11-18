<?php

/**
 * @file
 * Ding user related classes.
 */

 /**
  * Exception for trying to create existing user.
  *
  * Basename should be DingProviderUser, but that confuses things with
  * DingProviderUserException, so we use DingProviderAuth.
  */
class DingProviderAuthUserExistsError extends DingProviderUserException {
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
