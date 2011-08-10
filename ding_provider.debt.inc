<?php
/**
 * @file
 * Ding loan related classes.
 */

/**
 * Class representing a debt.
 */
class DingProviderDebt {
  /**
   * Id of the debt. Used as identifier. No assumptions are made about
   * it, however it should be a sting value suitable for values in forms and
   * the like.
   */
  var $id;

  /**
   * Creation date of debt. Format: YYYY-MM-DD.
   */
  var $date;

  /**
   * Debt type.
   *
   * This is a provider-specific value, and is not required.
   */
  var $type;


  /**
   * The amount owed, floating point.
   */
  var $amount;

  /**
   * Note – a description of what the debt was for.
   *
   * Not provided in all cases, and thus, not required.
   */
  var $note;

  public function __construct($id, $date, $amount, $note = '') {
    $this->id = $id;
    $this->amount = $amount;
    $this->date = $date;
    $this->note = $note;
  }
}
