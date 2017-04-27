<?php
/**
 * @file
 * Ding debt provider example.
 */

/**
 * Get list of unpayed fees.
 */
function connie_debt_list($account) {
  $result = array();

  return $result;
}

/**
 * Translate OpenRuth debt types into a human readable string in english.
 *
 * @param string $debt_type
 *   The OpenRuth debt type.
 *
 * @return string
 *   English translation of the debt type if found.
 */
function connie_debt_translate_debt_type($debt_type) {
  switch ($debt_type) {
    case 'compensation':
      $str = t('Compensation');
      break;

    case 'first recall':
      $str = t('First recall');
      break;

    case 'second recall':
      $str = t('Second recall');
      break;

    case 'third recall':
      $str = t('Third recall');
      break;

    case 'penalty':
      $str = t('Penalty');
      break;

    case 'reminder':
      $str = t('Reminder');
      break;

    case 'reservation':
      $str = t('Reservation');
      break;

    case 'other':
      $str = t('Other');
      break;

    default:
      $str = t('Unknown');
  };

  return $str;
}

/**
 * Callback function used to update OpenRuth after a payment have been received.
 *
 * @param string $amount
 *   The amount that have to be payed.
 * @param array $debt_ids
 *   The payment id's.
 * @param string $order_id
 *   The payments order id.
 *
 * @return bool
 *   If TRUE the payment was received or FALSE on failure.
 */
function connie_debt_payment_received($amount, $debt_ids = array(), $order_id = NULL) {
  // Send payment to backend.
  return TRUE;
}
