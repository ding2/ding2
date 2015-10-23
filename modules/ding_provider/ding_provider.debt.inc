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

  /**
   * Display name.
   *
   * Used to display material title when one could not be fetched from the
   * datawell, so used to store a fallback title e.g. the library system.
   */
  protected $display_name = DingEntityBase::NULL;

  /**
   * Note from the provider about the debt.
   */
  protected $note = DingEntityBase::NULL;

  /**
   * The amount owed, floating point.
   */
  protected $amount = DingEntityBase::NULL;

  /**
   * Material number for which the debt is about also known as faust number.
   */
  protected $material_number = DingEntityBase::NULL;

  /**
   * Default constructor for this class.
   *
   * @param string $id
   *   Debt id from the provider.
   * @param array $data
   *   Information about the debt from the provider.
   */
  public function __construct($id, $data = array()) {
    parent::__construct();
    $this->properties['id'] = $id;
    // Default display name.
    $this->properties['display_name'] = t('Title not available');
    $this->properties['amount_paid'] = 0;
    $this->properties['invoice_number'] = FALSE;
    $properties = array(
      'material_number',
      'display_name',
      'pickup_branch_id',
      'date',
      'amount',
      'amount_paid',
      'invoice_number',
      'type',
      'note',
    );
    $this->_populate($properties, $data);
  }
}
