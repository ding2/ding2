<?php
/**
 * @file
 * Ding loan related classes.
 */

/**
 * Class representing a debt.
 */
class DingProviderDebt extends DingEntityBase {
  /**
   * Id of the debt. Used as identifier. No assumptions are made about
   * it, however it should be a sting value suitable for values in forms and
   * the like.
   */
  protected $id = DingEntityBase::NULL;

  /**
   * Creation date of debt. Format: YYYY-MM-DD.
   */
  protected $date = DingEntityBase::NULL;

  /**
   * Debt type.
   *
   * This is a provider-specific value, and is not required.
   */
  protected $type = DingEntityBase::NULL;


  protected $display_name = DingEntityBase::NULL;

  /**
   * The amount owed, floating point.
   */
  protected $amount = DingEntityBase::NULL;


  public function __construct($id, $data = array()) {
    parent::__construct();
    $this->properties['id'] = $id;
    // Default display name.
    $this->properties['display_name'] = t('Title not available');
    $properties = array(
      'display_name',
      'pickup_branch_id',
      'date',
      'amount',
      'type',
    );
    $this->_populate($properties, $data);
  }
}
