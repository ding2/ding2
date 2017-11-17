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
 *   If TRUE cache is reset (default: FALSE)
 *
 * @return array
 *   Loan information.
 */
function fbs_loan_list($account, $reset = FALSE) {
  $results = &drupal_static(__FUNCTION__, array());

  if (empty($results) || $reset) {
    // Check if ding_session_cache is available.
    if (module_exists('ding_session_cache') && !$reset) {
      $results = ding_session_cache_get('fbs', 'loans', array());
    }

    // If both static cache and session cache failed, try reloading information
    // from FBS.
    if (empty($results) || $reset) {
      $res = array();
      try {
        $res = fbs_service()->MaterialLoans->getLoans(fbs_service()->agencyId, fbs_patron_id($account));
      } catch (Exception $e) {
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
          'ding_entity_id' => $ids[$loan->loanDetails->recordId],
          'loan_date' => $loan->loanDetails->loanDate,
          'expiry' => $loan->loanDetails->dueDate,
          'renewable' => $loan->isRenewable,
          'materials_number' => $loan->loanDetails->materialItemNumber,
        );

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
              '@year' => $periodical->volumeYear
            ));
          }
          else {
            $loan_data['notes'] = t('Issue @vol', array('@vol' => $vol));
          }
        }

        // Handle inter library loans.
        if (!empty($loan->loanDetails->ilBibliographicRecord)) {
          $loan_data['display_name'] = $loan->loanDetails->ilBibliographicRecord->title;
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
 * @param array $loan
 *   Loan ids to renew.
 *
 * @return array
 *   Result of revewals.
 */
function fbs_loan_renew($account, $loans) {
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
      $result[$loan->loanDetails->loanId] = DingProviderLoan::STATUS_NOT_RENEWED;
      if (in_array('deniedMaxRenewalsReached', $loan->renewalStatus)) {
        $result[$loan->loanDetails->loanId] = DingProviderLoan::STATUS_RENEWAL_NUM_EXCEEDED;
      }
      if (in_array('deniedReserved', $loan->renewalStatus)) {
        $result[$loan->loanDetails->loanId] = DingProviderLoan::STATUS_RENEWAL_RESERVED;
      }
    }
  }

  // Clear ding session cache.
  if (module_exists('ding_session_cache')) {
    ding_session_cache_clear('fbs', 'loans');
  }

  return $result;
}
