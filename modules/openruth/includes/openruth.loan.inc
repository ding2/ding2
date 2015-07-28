<?php
/**
 * @file
 * Implements handling of loans through OpenRuth.
 */

/**
 * Get list of user loans.
 */
function openruth_loan_list($account) {
  $result = array();

  // Get credentials and user status.
  $creds = ding_user_get_creds($account);
  $status = _openruth_user_status($creds);

  if (isset($status->loans->loan)) {
    foreach ($status->loans->loan as $loan) {

      // Try to parse display title to get periodical information.
      $notes = DingEntityBase::NULL;
      preg_match('/(\d+\.\d+)+\s(.*).+\s(\d{4}),\s(\d+)/', $loan->itemDisplayTitle, $matches);
      if ($matches) {
        $notes = $matches[3] . ', ' . $matches[4];
      }

      // Try to parse display title to get year of year book.
      preg_match('/(\d+\.\d+)(.+)(\d{4})$/', $loan->itemDisplayTitle, $matches);
      if ($matches) {
        $notes = $matches[3];
      }

      // Create DingProviderLoad object with the information.
      $result[$loan->copyId] = new DingProviderLoan($loan->copyId, array(
        'ding_entity_id' => ding_provider_build_entity_id($loan->itemId),
        'display_name' => isset($loan->itemTitle) ? $loan->itemTitle : DingEntityBase::NULL,
        'loan_date' => isset($loan->loanDate) ? $loan->loanDate : DingEntityBase::NULL,
        'expiry' => isset($loan->loanReturnDate) ? $loan->loanReturnDate : DingEntityBase::NULL,
        'renewable' => isset($loan->loanRenewable) ? $loan->loanRenewable == 'renewable' : DingEntityBase::NULL,
        'materials_number' => isset($loan->copyId) ? $loan->copyId : DingEntityBase::NULL,
        'author' => isset($loan->itemAuthor) ? $loan->itemAuthor : DingEntityBase::NULL,
        'publication_year' => isset($loan->itemPublicationYear) ? $loan->itemPublicationYear : DingEntityBase::NULL,
        'notes' => $notes,
      ));

      // Reset matches.
      $matches = NULL;
    }
  }

  return $result;
}

/**
 * Renew of loans.
 *
 * @param StdClass $account
 *   The user account the should have renewed loans.
 * @param array $ids
 *   The ids of the loans to renew.
 *
 * @return string
 *   DingProviderLoan::STATUS_RENEWED or DingProviderLoan::STATUS_NOT_RENEWED.
 */
function openruth_loan_renew($account, $ids) {
  $creds = ding_user_get_creds($account);

  $result = array();
  $res = openruth_client_invoke('renew_loan', $creds['name'], $ids);

  if ($res == TRUE) {
    _openruth_user_status($creds, TRUE);
  }
  foreach ($ids as $id) {
    if ($res[$id] === TRUE) {
      $result[$id] = DingProviderLoan::STATUS_RENEWED;
    }
    else {
      $result[$id] = DingProviderLoan::STATUS_NOT_RENEWED;
    }
  }

  return $result;
}

/**
 * Replace entity for the reservation in the case object in not in Ting anymore
 * or the reservation is an remote reservation.
 *
 * @param DingEntity $ting_entity
 *   Provider reservation object.
 *
 * @return DingEntity
 *   Ting entity object, filled with data from provider service.
 */
function openruth_loan_populate_pseudo_entity($ting_entity) {
  $openruth_object = openruth_seek_reserved_item($ting_entity->localId);

  if (is_object($openruth_object)) {
    $ting_entity->reply->record['dc:title']['dkdcplus:full'] = array($openruth_object->title);;
    $ting_entity->reply->record['dc:date'][''] = array($openruth_object['publication_year']);
    $ting_entity->reply->record['dc:creator']['dkdcplus:aut'] = array($openruth_object->author);
    $ting_entity->reply->record['dc:date'][''] = array($openruth_object->publication_year);

    $ting_entity->ting_title = array(LANGUAGE_NONE => array(array('id' => $ting_entity->ding_entity_id)));
    $ting_entity->ting_type = array(LANGUAGE_NONE => array(array('id' => $ting_entity->ding_entity_id)));
    $ting_entity->ting_author = array(LANGUAGE_NONE => array(array('id' => $ting_entity->ding_entity_id)));
    $ting_entity->ting_cover = array(LANGUAGE_NONE => array(array('local_id' => $ting_entity->provider_id)));
  }

  return $ting_entity;
}
