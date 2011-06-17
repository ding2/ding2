<?php

/**
 * Get list of user loans.
 */
function openruth_loan_list($account) {
  $creds = ding_user_get_creds($account);
  $result = array();
  $status = _openruth_user_status($creds);

  if (isset($status->loans)) {
    foreach ($status->loans->loan as $loan) {
      $result[$loan->copyId] = new DingProviderLoan($loan->copyId, array(
                       'ding_entity_id' => variable_get('ting_agency', '') . ':' . $loan->itemId,
                       'display_name' => $loan->itemDisplayTitle,
                       'loan_date' => $loan->loanDate,
                       'expiry' => $loan->loanReturnDate,
                       'renewable' => $loan->loanRenewable == 'renewable',
                     ));

    }
  }

  return $result;
}