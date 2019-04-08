<?php

/**
 * @file
 * Handles user loans.
 */

/**
 * Implements provider loan, list.
 *
 * @param object $account
 *   User to fetch list for.
 * @param bool $reset
 *   If TRUE cache is reset (default: FALSE).
 *
 * @return array
 *   Loan information.
 */
function fbs_loan_list($account, $reset = FALSE) {
  $results = &drupal_static(__FUNCTION__, NULL);

  if (is_null($results) || $reset) {
    // Check if ding_session_cache is available.
    if (module_exists('ding_session_cache') && !$reset) {
      $results = ding_session_cache_get('fbs', 'loans', NULL);
    }

    // If both static cache and session cache failed, try reloading information
    // from FBS.
    if (is_null($results) || $reset) {
      $results = array();

      $res = array();
      try {
        $res = fbs_service()->MaterialLoans->getLoans(fbs_service()->agencyId, fbs_patron_id($account));
      }
      catch (Exception $e) {
        watchdog_exception('fbs', $e);
      }

      $ids = array();
      foreach ($res as $loan) {
        $ids[$loan->loanDetails->recordId] = $loan->loanDetails->recordId;
      }
      $ids = ding_provider_build_entity_id($ids);

      foreach ($res as $loan) {
        $id = $loan->loanDetails->loanId;

        $loan_data = array(
          'loan_date' => $loan->loanDetails->loanDate,
          'expiry' => $loan->loanDetails->dueDate,
          'renewable' => $loan->isRenewable,
          'materials_number' => $loan->loanDetails->materialItemNumber,
        );

        // With the FBS provider we have to use FBS data for ILL, since we can't
        // rely on the record ID being unique in these cases.
        if (!empty($loan->loanDetails->ilBibliographicRecord)) {
          $loan_data['display_name'] = $loan->loanDetails->ilBibliographicRecord->title;
          $loan_data['author'] = $loan->loanDetails->ilBibliographicRecord->author;
        }
        elseif (isset($ids[$loan->loanDetails->recordId])) {
          $loan_data['ding_entity_id'] = $ids[$loan->loanDetails->recordId];
        }

        // Ding loan maintains a list of renewed loans in this session, and if
        // this loan is here we will use it for renewal feedback.
        $renewed_ids = array();
        if (module_exists('ding_session_cache')) {
          $renewed_ids = ding_session_cache_get('ding_loan', 'renewed_ids', array());
        }
        if (in_array($id, $renewed_ids)) {
          if ($loan->loanDetails->loanType === 'interLibraryLoan') {
            $loan_data['renewal_status'] = DingProviderLoan::STATUS_RENEWAL_REQUESTED;
          }
          else {
            $loan_data['renewal_status'] = DingProviderLoan::STATUS_RENEWED;
          }
        }
        elseif (empty($loan->isRenewable)) {
          // If loan is not renewable, see what FBS returned as renewalStatus
          // and try to provide some meaningful feedback based on that.
          $loan->renewalStatus = $loan->renewalStatusList;
          $loan_data['renewal_status'] = _fbs_loan_get_renewal_status($loan);
        }

        // If this is a periodical, add in issue data.
        if (isset($loan->loanDetails->periodical)) {
          $periodical = $loan->loanDetails->periodical;
          $vol = $periodical->volume;
          if (!empty($periodical->volumeNumber)) {
            $vol .= '.' . $periodical->volumeNumber;
          }
          if (!empty($periodical->volumeYear)) {
            $loan_data['notes'] = t('Issue @vol, @year', array(
              '@vol' => $vol,
              '@year' => $periodical->volumeYear,
            ));
          }
          else {
            $loan_data['notes'] = t('Issue @vol', array('@vol' => $vol));
          }
        }

        $results[$id] = new DingProviderLoan($id, $loan_data);
      }

      // Store the loans into ding session cache.
      if (module_exists('ding_session_cache')) {
        ding_session_cache_set('fbs', 'loans', $results);
      }
    }
  }

  return $results;
}

/**
 * Implements provider loan, renew.
 *
 * @param object $account
 *   User to renew loan for.
 * @param array $loans
 *   Loan ids to renew.
 *
 * @return array
 *   Result of revewals.
 */
function fbs_loan_renew($account, array $loans) {
  $res = array();
  try {
    $res = fbs_service()->MaterialLoans->renewLoans(fbs_service()->agencyId, fbs_patron_id($account), $loans);
  }
  catch (Exception $e) {
    watchdog_exception('fbs', $e);
  }

  $result = array();
  foreach ($res as $loan) {
    // Using an array for renewalStatus is an odd choice, but we'll only
    // consider the loan renewed if 'renewed' is the only status.
    if ($loan->renewalStatus == array('renewed')) {
      $result[$loan->loanDetails->loanId] =
        $loan->loanDetails->loanType == 'interLibraryLoan' ?
        DingProviderLoan::STATUS_RENEWAL_REQUESTED :
        DingProviderLoan::STATUS_RENEWED;
    }
    else {
      $result[$loan->loanDetails->loanId] = _fbs_loan_get_renewal_status($loan);
    }
  }

  // Clear ding session cache.
  if (module_exists('ding_session_cache')) {
    ding_session_cache_clear('fbs', 'loans');
  }

  return $result;
}

/**
 * Helper function to extract renewal status from the FBS loan.
 *
 * The renewal status is converted to Ding provider renewal status constants.
 *
 * @param object $loan
 *   The loan to extract renewal status from.
 *
 * @return int
 *   An integer representing a constant from DingProviderLoan.
 */
function _fbs_loan_get_renewal_status($loan) {
  if (in_array('deniedMaxRenewalsReached', $loan->renewalStatus)) {
    return DingProviderLoan::STATUS_RENEWAL_NUM_EXCEEDED;
  }
  if (in_array('deniedReserved', $loan->renewalStatus)) {
    return DingProviderLoan::STATUS_RENEWAL_RESERVED;
  }
  return DingProviderLoan::STATUS_NOT_RENEWED;
}
