<?php

/**
 * @file
 * Handles user debts.
 */

/**
 * Implements provider debt, list.
 */
function fbs_debt_list($account) {
  $result = array();

  $res = fbs_service()->Payment->getFees(fbs_service()->agencyId, fbs_patron_id($account));

  foreach ($res as $fee) {
    $id = $fee->feeId;
    $result[$id] = new DingProviderDebt($id, array(
      'date' => $fee->creationDate,
      'display_name' => $fee->reasonMessage,
      'amount' => $fee->amount,
      'amount_paid' => $fee->paidDate ? $fee->amount : 0,
      'invoice_number' => NULL,
      'type' => $fee->type,
    ));
  }

  return $result;
}
