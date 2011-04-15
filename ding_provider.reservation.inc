<?php

/**
 * @file
 * Ding reservation exception classes.
 */
/**
 * Parent class for reservation errors.
 */
class DingProviderReservationUserError extends DingProviderUserException {}

/**
 * Exception thrown when the item is already reserved.
 */
class DingProviderReservationExists extends DingProviderReservationUserError{
  public function __construct($message = "", $code = 0) {
    if (empty($message)) {
      $message = t('"You have already reserved "@title".');
    }
    parent::__construct($message);
  }
}

/**
 * The item is not available for reservation.
 */
class DingProviderReservationNotAvailable extends DingProviderReservationUserError {
  public function __construct($message = "", $code = 0) {
    if (empty($message)) {
      $message = t('"@title" is not available for reservation.');
    }
    parent::__construct($message);
  }
}

/**
 * Reservation is not allowed.
 */
class DingProviderReservationNotAllowed extends DingProviderReservationUserError{
  public function __construct($message = "", $code = 0) {
    if (empty($message)) {
      $message = t("You're not allowed to reserve \"@title\".");
    }
    parent::__construct($message);
  }
}
