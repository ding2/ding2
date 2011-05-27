<?php

/**
 * @file
 * Ding reservation related classes.
 */

/**
 * Class representing a reservation.
 */
class DingProviderReservation {
  /**
   * Value of DingProviderReservation::status if the reservation is active.
   */
  const STATUS_ACTIVE = 1;

  /**
   * Value of DingProviderReservation::status if the reservation is ready for
   * pickup.
   */
  const STATUS_FECTHABLE = 2;

  /**
   * Id of the reservation. Used as identifier. No assumptions are made about
   * it, however it should be a sting value suitable for values in forms and
   * the like.
   */
  protected $id;

  /**
   * Materials number, optional. Is shown to the user.
   */
  protected $materials_number = '';

  /**
   * Id of the ding_entity.
   */
  protected $ding_entity_id;

  /**
   * The ding_entity.
   */
  protected $entity;

  /**
   * Fallback display if the reservation is an obscure material that is not
   * known by the datawell.
   */
  protected $display_name;

  /**
   * Status of the reservation, either DingProviderReservation::STATUS_ACTIVE
   * or DingProviderReservation::STATUS_FECTHABLE.
   */
  protected $status;

  /**
   * Id of pickup place.
   */
  protected $pickup_branch_id;

  /**
   * Creation date of reservation. Format: YYYY-MM-DD.
   */
  protected $created;

  /**
   * Reservation valid to. Format: YYYY-MM-DD.
   *
   * For DingProviderReservation::STATUS_ACTIVE this is when the reservation
   * expires, for DingProviderReservation::STATUS_FECTHABLE it is the last
   * pickup date.
   */
  protected $expiry;

  /**
   * Queue number. optional. Only valid for
   * DingProviderReservation::STATUS_ACTIVE reservations.
   */
  protected $queue_number;


  /**
   * Pickup number. Only valid for DingProviderReservation::STATUS_FECTHABLE
   * reservations.
   */
  protected $pickup_number;

  /**
   * Notes - some additional information.
   */
  protected $notes = '';

  /*
   titel
   type
   forfatter
   sprog
   materiale nr
   */

  public function __construct($id, $data = array()) {
    $this->id = $id;
    // Default display name.
    $this->display_name = t('Title not available');
    $properties = array(
      'materials_number',
      'ding_entity_id',
      'entity',
      'display_name',
      'status',
      'pickup_branch',
      'pickup_branch_id',
      'created',
      'expiry',
      'queue_number',
      'pickup_number',
      'notes',
    );
    foreach ($properties as $prop) {
      if (isset($data[$prop])) {
        $this->$prop = $data[$prop];
      }
    }
  }

  public function __get($prop) {
    // Use property_exists() to support NULL values.
    if (property_exists($this, $prop)) {
      return $this->$prop;
    }
    elseif (($method = 'get' . strtoupper($prop[0]) . substr($prop, 1)) &&
      method_exists($this, $method)) {
      return call_user_func(array($this, $method));
    }

    throw new Exception('Undefined property via __get(): ' . $prop);
  }

  public function __isset($prop) {
    return property_exists($this, $prop);
  }

  function getPickup_branch() {
    return ding_provider_invoke('reservation', 'branch_name', $this->pickup_branch);
  }

  function getEntity() {
    if (!isset($this->entity) && !empty($this->ding_entity_id)) {
      $this->entity = ding_entity_load($this->ding_entity_id);
    }
    return $this->entity;
  }

  /*
   titel
   type
   forfatter
   sprog
   materiale nr
   */

  function getTitle() {
    $this->getEntity();
    return $this->title = $this->entity->title;
  }

  function getCreator() {
    $this->getEntity();
    return $this->creator = $this->entity->creator;
  }

  function getType() {
    $this->getEntity();
    return $this->type = $this->entity->type;
  }

  function getLanguage() {
    $this->getEntity();
    return $this->language = $this->entity->language;
  }
}

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
