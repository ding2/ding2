<?php

/**
 * @file
 * Ding loan provider example.
 */

use Ting\TingObject;

/**
 * Implements loan, list provider hook.
 */
function connie_loan_list($account) {
  // Throw exception if we're not logged in.
  ding_user_get_creds();

  $result = array();
  $i = 7;
  // We fake a loan list from the reserved items as there's no way to
  // 'loan' from the frontend.
  if (isset($_SESSION['connie_reservations'])) {
    foreach ($_SESSION['connie_reservations'] as $id => $res) {
      $result[$id] = new DingProviderLoan($id, array(
        'ding_entity_id' => ding_provider_build_entity_id($res[0]),
        'display_name' => $res[1],
        'loan_date' => strftime('%Y-%m-%d', strtotime('now -' . $i . ' day')),
        'expiry' => strftime('%Y-%m-%d', strtotime('now ' . (14 -$i++) . ' day')),
        'renewable' => TRUE,
        'materials_number' => $id,
      ));
    }
  }
  return $result;
}

/**
 * Implements loan, renew provider hook.
 */
function connie_loan_renew($account, $ids) {
  ding_user_get_creds();

  $result = array();
  foreach ($ids as $id) {
    // 50/50 chance of renewal.
    $result[$id] = rand(0, 1) ? DingProviderLoan::STATUS_RENEWED : DingProviderLoan::STATUS_NOT_RENEWED;
  }

  return $result;
}

/**
 * Enrich pseudo entities.
 *
 * @param object $ting_entity
 *   Provider reservation object.
 * @param \Ting\TingObject $ting_object
 *   Mutable ting object that represents the raw search result from the search
 *   provider.
 *
 * @return object
 *   Ting entity object, filled with data from provider service.
 */
function connie_loan_populate_pseudo_entity($ting_entity, TingObject $ting_object) {
  $ting_object->setTitle(trim($ting_object->getTitle() . " Connie edition"));

  return $ting_entity;
}
