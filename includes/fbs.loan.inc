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

/**
 * Implements provider loan, renew.
 */
function fbs_loan_renew($account, $loans) {
  $result = array();

  $res = fbs_service()->MaterialLoans->renewLoans(fbs_service()->agencyId, fbs_patron_id($account), $loans);

  foreach ($res as $loan) {
    // Using an array for renewalStatus is an odd choice, but we'll only
    // consider the loan renewed if 'renewed' is the only status.
    if ($loan->renewalStatus == array('renewed')) {
      $result[$loan->loanDetails->loanId] = DingProviderLoan::STATUS_RENEWED;
    }
    else {
      $result[$loan->loanDetails->loanId] = DingProviderLoan::STATUS_NOT_RENEWED;
    }
  }

  return $result;
}
