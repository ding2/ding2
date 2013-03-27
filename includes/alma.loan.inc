<?php
/**
 * @file
 * Implements provider hooks that is associated with loans in alma.
 */

/**
 * Implements hook_loan_list().
 *
 * This functions finds all loans for a given user account and returns the loans
 * as DingProviderLoan objects.
 *
 */
function alma_loan_list($account) {
  $creds = ding_user_get_creds($account);
  $results = array();

  try {
    // Get all loans form alma for the user account given.
    $loans =  alma_client_invoke('get_loans', $creds['name'], $creds['pass']);
  }
  catch (Exception $e) {
    throw new DingProviderLoanUserError($e->getMessage());
  }

  foreach ($loans as $loan) {
    $results[$loan['id']] = new DingProviderLoan($loan['id'], array(
      'ding_entity_id' => variable_get('ting_agency', '') . ':' . $loan['record_id'],
      'loan_date' => $loan['loan_date'],
      'expiry' => $loan['due_date'],
      'renewable' => $loan['is_renewable'],
      'materials_number' => $loan['id'],
      'notes' => isset($loan['notes']) ? $loan['notes'] : DingEntityBase::NULL,
    ));
  }

  return $results;
}

/**
 * Implements hook_loan_renew().
 *
 * Tries to renew the loans with the id's passed as parameter.
 */
function alma_loan_renew($account, $ids) {
  $creds = ding_user_get_creds($account);
  $result = array();
  $res = alma_client_invoke('renew_loan', $creds['name'], $creds['pass'], $ids);

  foreach ($ids as $id) {
    if (isset($res[$id]) && $res[$id] === TRUE) {
      $result[$id] = DingProviderLoan::STATUS_RENEWED;
    }
    else {
      /**
       * @todo there are message saying why, the renew failed.
       */
      $result[$id] = DingProviderLoan::STATUS_NOT_RENEWED;
    }
  }
  return $result;
}
