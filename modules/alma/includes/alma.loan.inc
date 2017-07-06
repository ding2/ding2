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
 */
function alma_loan_list($account, $reset = FALSE) {
  // Get creds is outside cache function as it may throw exception if the user
  // is not longer logged in.
  $creds = ding_user_get_creds($account);

  $results = &drupal_static(__FUNCTION__, FALSE);
  if (!$results || $reset) {
    // Check if ding_session_cache is available.
    if (module_exists('ding_session_cache') && !$reset) {
      $results = ding_session_cache_get('alma', 'loans');
    }

    // If both static cache and session cache failed, try reloading information
    // from alma.
    if (empty($results) || $reset) {
      try {
        // Get all loans form alma for the user account given.
        $loans = alma_client_invoke('get_loans', $creds['name'], $creds['pass']);
      }
      catch (Exception $e) {
        throw new DingProviderLoanUserError($e->getMessage());
      }

      $results = array();
      foreach ($loans as $loan) {
        $results[$loan['id']] = new DingProviderLoan($loan['id'], array(
          'ding_entity_id' => ding_provider_build_entity_id($loan['record_id']),
          'loan_date' => $loan['loan_date'],
          'expiry' => $loan['due_date'],
          'renewable' => $loan['is_renewable'],
          'materials_number' => $loan['id'],
          'notes' => isset($loan['notes']) ? $loan['notes'] : DingEntityBase::NULL,
        ));
      }

      // Store the reservations into ding session cache.
      if (module_exists('ding_session_cache')) {
        ding_session_cache_set('alma', 'loans', $results);
      }
    }
  }

  return $results;
}

/**
 * Implements hook_loan_renew().
 *
 * Tries to renew the loans with the id's passed as parameter.
 */
function alma_loan_renew($account, $ids) {
  $error_mapping = array(
    'requested' => DingProviderLoan::STATUS_RENEWAL_REQUESTED,
    'maxnum' => DingProviderLoan::STATUS_RENEWAL_NUM_EXCEEDED,
    'reserved' => DingProviderLoan::STATUS_RENEWAL_RESERVED,
  );

  $creds = ding_user_get_creds($account);
  $result = array();
  $res = alma_client_invoke('renew_loan', $creds['name'], $creds['pass'], $ids);

  foreach ($ids as $id) {
    if (isset($res[$id]) && $res[$id] === TRUE) {
      $result[$id] = DingProviderLoan::STATUS_RENEWED;

      // Clear ding session cache.
      if (module_exists('ding_session_cache')) {
        ding_session_cache_clear('alma', 'loans');
      }
    }
    elseif (isset($error_mapping[$res[$id]])) {
      $result[$id] = $error_mapping[$res[$id]];
    }
    else {
      $result[$id] = DingProviderLoan::STATUS_NOT_RENEWED;
    }
  }

  return $result;
}

/**
 * Replace entity for the reservation.
 *
 * Should be used in the case object in not in Ting anymore or the reservation
 * is an remote reservation.
 *
 * @param object $ting_entity
 *   Provider reservation object.
 *
 * @return object
 *   Ting entity object, filled with data from provider service.
 */
function alma_loan_populate_pseudo_entity($ting_entity) {
  $alma_object = alma_client_invoke('catalogue_record_detail', $ting_entity->localId);

  if ($alma_object['request_status'] == 'ok' && isset($alma_object['records'][$ting_entity->localId])) {
    $source = $alma_object['records'][$ting_entity->localId];

    $ting_entity->reply->record['dc:title']['dkdcplus:full'] = array($source['titles'][0]);
    $ting_entity->reply->record['dc:type']['dkdcplus:BibDK-Type'] = array($source['media_class']);
    $ting_entity->reply->record['dc:date'][''] = array($source['publication_year']);

    // If it a ill Alma record authors are not always available.
    if (isset($source['authors'])) {
      $ting_entity->reply->record['dc:creator']['dkdcplus:aut'] = $source['authors'];
    }

    // If it is an inter library loan (ill) Alma record isbn are not always
    // available.
    if (isset($source['isbns'][0])) {
      $ting_entity->reply->record['dc:identifier']['dkdcplus:ISBN'][0] = str_replace(array('-', ' ', 'ISBN'), '', $source['isbns'][0]);
    }

    $ting_entity->ting_title = array(LANGUAGE_NONE => array(array('id' => $ting_entity->ding_entity_id)));
    $ting_entity->ting_type = array(LANGUAGE_NONE => array(array('id' => $ting_entity->ding_entity_id)));
    $ting_entity->ting_author = array(LANGUAGE_NONE => array(array('id' => $ting_entity->ding_entity_id)));
    $ting_entity->ting_cover = array(LANGUAGE_NONE => array(array('local_id' => $ting_entity->provider_id)));
  }

  return $ting_entity;
}
