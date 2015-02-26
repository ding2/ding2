<?php

/**
 * @file
 * Handles user loans.
 */

/**
 * Implements provider loan, list.
 */
function fbs_loan_list($account) {
  $result = array();

  $res = fbs_service()->MaterialLoans->getLoans(fbs_service()->agencyId, fbs_patron_id($account));

  foreach ($res as $loan) {
    $id = $loan->loanDetails->loanId;
    $result[$id] = new DingProviderLoan($id, array(
      'ding_entity_id' => $loan->loanDetails->recordId,
      'loan_date' => $loan->loanDetails->loanDate,
      'expiry' => $loan->loanDetails->dueDate,
      'renewable' => $loan->isRenewable,
      'materials_number' => $loan->loanDetails->materialItemNumber,
    ));
  }

  return $result;
}
