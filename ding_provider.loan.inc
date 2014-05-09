<?php

/**
 * @file
 * Ding loan related classes.
 */

/**
 * Class representing a loan.
 */
class DingProviderLoan extends DingEntityBase {
  /**
   * Renewal succeeded.
   */
  const STATUS_RENEWED = 1;

  /**
   * Renewal failed.
   */
  const STATUS_NOT_RENEWED = 2;

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
   * The ding_entity.
   */
  protected $entity = DingEntityBase::NULL;

  /**
   * Fallback display if the loan is an obscure material that is not
   * known by the datawell.
   */
  protected $display_name = DingEntityBase::NULL;

  /**
   * Creation date of reservation. Format: YYYY-MM-DD.
   */
  protected $loan_date = DingEntityBase::NULL;

  /**
   * Loan due date. Format: YYYY-MM-DD.
   */
  protected $expiry = DingEntityBase::NULL;

  /**
   * Whether the loan can be renewed.
   */
  protected $renewable = DingEntityBase::NULL;

  /**
   * True for inter library loans.
   */
  protected $remote_loan = DingEntityBase::NULL;

  /**
   * Notes - some additional information.
   */
  protected $notes  = DingEntityBase::NULL;

  /**
   * Message - A message with a reason for why a loan is not renewable
   */
  protected $message  = DingEntityBase::NULL;

  public function __construct($id, $data = array()) {
    parent::__construct();
    $this->properties['id'] = $id;
    // Default display name.
    $this->properties['display_name'] = t('Title not available');
    $this->properties['materials_number'] = NULL;
    $properties = array(
      'materials_number',
      'ding_entity_id',
      'entity',
      'display_name',
      'loan_date',
      'expiry',
      'renewable',
      'remote_loan',
      'notes',
      'author',
      'title',
      'publication_year',
      'message',
    );
    $this->_populate($properties, $data);
  }

  public function __wakeup() {
    foreach (get_object_vars($this) as $prop => $val) {
      if (isset($this->properties[$prop]) && $this->properties[$prop] === self::NULL) {
        $this->properties[$prop] = $val;
      }
      elseif (isset($this->properties[$prop])) {
        $this->$prop = $this->properties[$prop];
      }
    }
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
 * Parent class for loan errors.
 */
class DingProviderLoanUserError extends DingProviderUserException {}

