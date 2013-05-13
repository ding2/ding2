<?php

/**
 * Get list of user loans.
 */
function openruth_loan_list($account) {
  $creds = ding_user_get_creds($account);
  $result = array();
  $status = _openruth_user_status($creds);

  if (isset($status->loans->loan)) {
    foreach ($status->loans->loan as $loan) {
      $result[$loan->copyId] = new DingProviderLoan($loan->copyId, array(
        'ding_entity_id' => variable_get('ting_agency', '') . ':' . $loan->itemId,
        'display_name' => $loan->itemDisplayTitle,
        'loan_date' => $loan->loanDate,
        'expiry' => $loan->loanReturnDate,
        'renewable' => $loan->loanRenewable == 'renewable',
        'materials_number' => $loan->copyId,
        'author' => $loan->itemAuthor,
        'title' => $loan->itemTitle,
        'publication_year' => $loan->itemPublicationYear,
      ));
    }
  }

  return $result;
}

/**
 * Renew loans.
 */
function openruth_loan_renew($account, $ids) {
  $creds = ding_user_get_creds($account);

  $result = array();
  $res = openruth_client_invoke('renew_loan', $creds['name'], $ids);

  if ($res == TRUE) {
    $status = _openruth_user_status($creds, TRUE);
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
 * @param $ting_entity
 *   Provider reservation object.
 * @return
 *   Ting entity object, filled with data from provider service.
 */
function alma_loan_populate_pseudo_entity($ting_entity) {
  $openruth_object = openruth_seek_reserved_item($ting_entity->localId);

  if (is_object($openruth_object)) {

    // Unfortunately, openruth response doesnt contain anything about the loaned item type.

    $ting_entity->reply->record['dc:title']['dkdcplus:full'] = array($openruth_object->title);;

    $ting_entity->reply->record['dc:date'][''] = array($openruth_object['publication_year']);
    $ting_entity->reply->record['dc:creator']['dkdcplus:aut'] = array($openruth_object->author);
    $ting_entity->reply->record['dc:date'][''] = array($openruth_object->publication_year);

    /**
     * @TODO: Do openruth provide isbn's ?
     */
    //$ting_entity->reply->record['dc:identifier']['dkdcplus:ISBN'][0] = str_replace(array('-', ' ', 'ISBN'), '', $openruth_object['isbns'][0]);

    $ting_entity->ting_title = array(LANGUAGE_NONE => array(array('id' => $ting_entity->ding_entity_id)));
    $ting_entity->ting_type = array(LANGUAGE_NONE => array(array('id' => $ting_entity->ding_entity_id)));
    $ting_entity->ting_author = array(LANGUAGE_NONE => array(array('id' => $ting_entity->ding_entity_id)));
    $ting_entity->ting_cover = array(LANGUAGE_NONE => array(array('local_id' => $ting_entity->provider_id)));
  }

  return $ting_entity;
}