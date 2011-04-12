<?php

/**
 * @file
 * Ding reservation exception classes.
 */
/**
 * Parent class for reservation errors.
 */
class DingReservationUserError extends DingProviderUserException {}

/**
 * Exception thrown when the item is already reserved.
 */
class DingReservationUserErrorReservationExists extends DingReservationUserError{
  public function __construct(string $message = "", int $code = 0) {
    if (empty($message)) {
      $message = t('"You have already reserved "@title".');
    }
    parent::__construct($message);
  }
}

/**
 * The item is not available for reservation.
 */
class DingReservationUserErrorNotAvailable extends DingReservationUserError {
  public function __construct(string $message = "", int $code = 0) {
    if (empty($message)) {
      $message = t('"@title" is not available for reservation.');
    }
    parent::__construct($message);
  }
}

/**
 * Reservation is not allowed.
 */
class DingReservationUserErrorNotAllowed extends DingReservationUserError{
  public function __construct(string $message = "", int $code = 0) {
    if (empty($message)) {
      $message = t("You're not allowed to reserve \"@title\".");
    }
    parent::__construct($message);
  }
}

/**
 * Custom error from the provider. Should not be used for internal errors.
 */
class DingReservationUserErrorCustom extends DingReservationUserError {
  public function __construct($message) {
    parent::__construct($message);
  }
}
