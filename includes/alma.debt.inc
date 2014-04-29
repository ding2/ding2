<?php
/**
 * @file
 * Alma debt provider for Ding.
 */

/**
 * Provide list of DingProviderDebt objects for a user.
 *
 * @param stdClass $account
 *   User object to provide debts for.
 * @param bool $reset
 *   Reset static cache if TRUE else get debts from cache.
 *
 * @return array
 *   DingProviderDebt objects in array, keyed by debt ID.
 */
function alma_debt_list($account, $reset = FALSE) {
  $creds = ding_user_get_creds($account);

  // Use static cache to speed up communication with Alma.
  $results = &drupal_static(__FUNCTION__, FALSE);
  if (!$results || $reset) {
    // Get debts from Alma.
    $debts = alma_client_invoke('get_debts', $creds['name'], $creds['pass']);

    // Create DingProviderDebt instances from Alma's list.
    $results = array();
    foreach ($debts['debts'] as $debt) {
      // Get the material number from the display name and remove it form it.
      preg_match('/^(\w+)\s+(.+)/', $debt['display_name'], $matchs);
      if (count($matchs) == 3) {
        $debt['display_name'] = $matchs[2];
        $debt['material_number'] = $matchs[1];
      }

      // Translate the fee type code into an text string.
      $debt['type'] = alma_debt_translate_debt_type($debt['type']);

      $debt_object = new DingProviderDebt($debt['id'], $debt);
      $results[$debt['id']] = $debt_object;
    }
  }

  return $results;
}

/**
 * Mark debts as paid.
 *
 * @param float $amount
 *   The total amount paid.
 * @param array $debt_ids
 *   IDs of the paid debts.
 * @param mixed $order_id
 *   Order ID of the payment transaction, to be recorded in the backend system.
 *
 * @return array
 *   Array from ALMA with the results.
 */
function alma_debt_payment_received($amount, $debt_ids = array(), $order_id = NULL) {
  // Return result from Alma.
  return alma_client_invoke('add_payment', implode(',', $debt_ids), $order_id);
}

/**
 * Translate alma debt types into an human readable string in english.
 *
 * @param string $debt_type
 *   The ALMA debt type.
 *
 * @return string
 *   English translation of the debt type. It has been
 */
function alma_debt_translate_debt_type($debt_type) {
  // If translation is not found, return the type. So set it as default.
  $str = t($debt_type);

  switch ($debt_type) {
    case 'overdueFeeInvoiceDebt':
      $str = t('Overdue fee invoice');
      break;

    case 'overdueFeeDebt':
      $str = t('Overdue fee');
      break;

    case 'loanFeeDebt':
      $str = t('Loan fee');
      break;

    case 'reservationPickupFeeDebt':
      $str = t('Reservation pick-up fee');
      break;

    case 'reservationFeeDebt':
      $str = t('Reservation fee');
      break;

    case 'deleteReservationFeeDebt':
      $str = t('Delete reservation fee');
      break;

    case 'illFeeDebt':
      $str = t('Interlibrary fee');
      break;

    case 'smsReservationFeeDebt':
      $str = t('SMS reservation fee');
      break;

    case 'smsReminderFeeDebt':
      $str = t('SMS reminder fee');
      break;

    case 'smsRecall1FeeDebt':
      $str = t('SMS first recall fee');
      break;

    case 'smsRecall2FeeDebt':
      $str = t('SMS second recall fee');
      break;

    case 'smsRecall3FeeDebt':
      $str = t('SMS third recall fee');
      break;

    case 'smsRecall4FeeDebt':
      $str = t('SMS fourth recall fee');
      break;

    case 'smsRecall5FeeDebt':
      $str = t('SMS fifth recall fee');
      break;

    case 'emailReminderFeeDebt':
      $str = t('E-mail reminder fee');
      break;

    case 'otherFeeDebt':
      $str = t('Unknown or other fee');
      break;
  };

  return $str;
}
