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

/**
 * Replace entity for the reservation in the case object in not in Ting anymore
 * or the reservation is an remote reservation.
 *
 * @param $ting_entity
 *   Provider reservation object.
 * @return
 *   Ting entity object, filled with data from provider service.
 */
function alma_loan_populate_pseudo_entity($ting_entity) {
  $alma_object = alma_client_invoke('catalogue_record_detail', $ting_entity->localId);

  if ($alma_object['request_status'] == 'ok' && isset($alma_object['records'][$ting_entity->localId])) {
    $source = $alma_object['records'][$ting_entity->localId];

    $ting_entity->reply->record['dc:title']['dkdcplus:full'] = array($source['titles'][0]);
    $ting_entity->reply->record['dc:type']['dkdcplus:BibDK-Type'] = array($source['media_class']);
    $ting_entity->reply->record['dc:date'][''] = array($source['publication_year']);
    $ting_entity->reply->record['dc:creator']['dkdcplus:aut'] = $source['authors'];
    $ting_entity->reply->record['dc:identifier']['dkdcplus:ISBN'][0] = str_replace(array('-', ' ', 'ISBN'), '', $source['isbns'][0]);

    $ting_entity->ting_title = array(LANGUAGE_NONE => array(array('id' => $ting_entity->ding_entity_id)));
    $ting_entity->ting_type = array(LANGUAGE_NONE => array(array('id' => $ting_entity->ding_entity_id)));
    $ting_entity->ting_author = array(LANGUAGE_NONE => array(array('id' => $ting_entity->ding_entity_id)));
    $ting_entity->ting_cover = array(LANGUAGE_NONE => array(array('local_id' => $ting_entity->provider_id)));
  }

  return $ting_entity;
}
