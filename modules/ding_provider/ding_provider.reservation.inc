<?php

/**
 * @file
 * Ding reservation related classes.
 */

/**
 * Class representing a reservation.
 */
class DingProviderReservation extends DingEntityBase {
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
  protected $id = DingEntityBase::NULL;

  /**
   * Materials number, optional. Is shown to the user.
   */
  protected $materials_number = DingEntityBase::NULL;

  /**
   * Id of the ding_entity.
   */
  protected $ding_entity_id = DingEntityBase::NULL;

  /**
   * Boolean for if reservation is ready for pickup.
   */
  protected $ready_for_pickup = DingEntityBase::NULL;

  /**
   * Pickup date
   */
  protected $pickup_date = DingEntityBase::NULL;

  /**
   * Order Id
   */
  protected $order_id = DingEntityBase::NULL;

  /**
   * Organisation Id
   */
  protected $organisation_Id = DingEntityBase::NULL;

  /**
   * The ding_entity.
   */
  protected $entity = DingEntityBase::NULL;

  /**
   * Fallback display if the reservation is an obscure material that is not
   * known by the datawell.
   */
  protected $display_name = DingEntityBase::NULL;

  /**
   * Status of the reservation, either DingProviderReservation::STATUS_ACTIVE
   * or DingProviderReservation::STATUS_FECTHABLE.
   */
  protected $status = DingEntityBase::NULL;

  /**
   * Delete status of the reservation, either yes or no
   */
  protected $can_delete = DingEntityBase::NULL;

  /**
   * Id of pickup place.
   */
  protected $pickup_branch_id = DingEntityBase::NULL;

  /**
   * Id of pickup place.
   */
  protected $pickup_order_id = DingEntityBase::NULL;

  /**
   * orderArrived. Boolean.
   */
  protected $order_arrived = DingEntityBase::NULL;

  /**
   * Creation date of reservation. Format: YYYY-MM-DD.
   */
  protected $created = DingEntityBase::NULL;

  /**
   * Reservation valid to. Format: YYYY-MM-DD.
   *
   * For DingProviderReservation::STATUS_ACTIVE this is when the reservation
   * expires, for DingProviderReservation::STATUS_FECTHABLE it is the last
   * pickup date.
   */
  protected $expiry = DingEntityBase::NULL;

  /**
   * Queue number. optional. Only valid for
   * DingProviderReservation::STATUS_ACTIVE reservations.
   */
  protected $queue_number = DingEntityBase::NULL;


  /**
   * Pickup number. Only valid for DingProviderReservation::STATUS_FECTHABLE
   * reservations.
   */
  protected $pickup_number = DingEntityBase::NULL;

  /**
   * Notes - some additional information.
   */
  protected $notes = DingEntityBase::NULL;

  /**
   * Reservation_type - the type of reservation.
   *   - DING_RESERVATION_READY
   *   - DING_RESERVATION_NOT_READY
   *   - DING_RESERVATION_INTERLIBRARY_LOANS
   */
  protected $reservation_type = DingEntityBase::NULL;

  /**
   * Status - status for interlibrary loans
   */
  protected $ill_status = DingEntityBase::NULL;

  /*
   titel
   type
   forfatter
   sprog
   materiale nr
   */

  public function __construct($id, $data = array()) {
    parent::__construct();
    $this->properties['id'] = $id;
    // Default display name.
    $this->properties['display_name'] = t('Title not available');
    $this->properties['ready_for_pickup'] = FALSE;
    $properties = array(
      'order_id',
      'organisation_Id',
      'materials_number',
      'ding_entity_id',
      'entity',
      'display_name',
      'status',
      'can_delete',
      'pickup_branch',
      'pickup_order_id',
      'pickup_branch_id',
      'created',
      'expiry',
      'queue_number',
      'pickup_number',
      'pickup_date',
      'notes',
      'order_arrived',
      'ready_for_pickup',
      'reservation_type',
      'author',
      'title',
      'publication_year',
      'ill_status',
    );
    $this->_populate($properties, $data);
  }

  public function __wakeup() {
    foreach (get_object_vars($this) as $prop => $val) {
      if (isset($this->properties[$prop]) && $this->properties[$prop] === self::NULL) {
        $this->properties[$prop] = $val;
      }
      else if (isset($this->properties[$prop])) {
        $this->$prop = $this->properties[$prop];
      }
    }
  }

  function getPickup_branch() {
    return ding_provider_invoke('reservation', 'branch_name', $this->pickup_branch);
  }

  function getEntity() {
    if (!isset($this->entity) || $this->entity === self::NULL) {
      if (!empty($this->ding_entity_id)) {
        $this->entity = ding_entity_load($this->ding_entity_id);
      }
      else {
        $this->entity = NULL;
      }
    }
    return $this->entity;
  }

  function getTitle() {
    $this->getEntity();
    if ($this->entity) {
      return $this->title = $this->entity->title;
    }
  }

  function getCreator() {
    $this->getEntity();
    if ($this->entity) {
      return $this->creator = $this->entity->creator;
    }
  }

  function getType() {
    $this->getEntity();
    if ($this->entity) {
      return $this->type = $this->entity->type;
    }
  }

  function getLanguage() {
    $this->getEntity();
    if ($this->entity) {
      return $this->language = $this->entity->language;
    }
  }
}

/**
 * Parent class for reservation errors.
 */
class DingProviderReservationUserError extends DingProviderUserException { }

/**
 * Exception thrown when the item is already reserved.
 */
class DingProviderReservationExists extends DingProviderReservationUserError {
  public function __construct($message = "", $code = 0) {
    if (empty($message)) {
      $message = t('"You have already reserved "@title".');

      if ($code) {
        $message .= t('Error message "@code."', array('@code' => $code));
      }
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

      if ($code) {
        $message .= t('Error message "@code."', array('@code' => $code));
      }
    }
    parent::__construct($message);
  }
}

/**
 * Reservation is not allowed.
 */
class DingProviderReservationNotAllowed extends DingProviderReservationUserError {
  public function __construct($message = "", $code = 0) {
    if (empty($message)) {
      $message = t("You're not allowed to reserve \"@title\".");

      if ($code) {
        $message .= t('Error message "@code."', array('@code' => $code));
      }
    }
    parent::__construct($message);
  }
}
