<?php

/**
 * @file
 * Handles user authentication and update.
 */

/**
 * Implements provider user, authenticate.
 */
function fbs_user_authenticate($name, $pincode) {
  $auth = new FBS\Model\AuthenticationRequest();
  $auth->libraryCardNumber = $name;
  $auth->pincode = $pincode;

  $res = fbs_service()->Patron->authenticate(fbs_service()->agencyId, $auth);
  $result = array(
    'success' => $res->authenticated,
  );
  if ($res->authenticated) {
    // We'll call the patronId for "creds", as it makes it easy to dig it out
    // later.
    $result['creds'] = _fbs_creds($res->patron);

    // We have to save the library card number/CPR number, as the pincode
    // change call uses it.
    $result['creds']['library_card_number'] = $name;

    $result['user'] = array(
      'mail' => $res->patron->emailAddress,
      'data' => array(
        'display_name' => $res->patron->name,
      ),
      'private' => array(
        'branch' => $res->patron->preferredPickupBranch,
      ),
      'blocked' => !empty($res->patron->blockStatus),
    );

    if ($res->patron->blockStatus) {
      $result['user']['blocks'] = array();
      foreach ($res->patron->blockStatus as $block) {
        $result['user']['blocks'][] = $block->message;
      }
    }
  }

  return $result;
}

/**
 * Implements provider user, update_pincode.
 */
function fbs_user_update_pincode($account, $new_pincode) {
  $creds = fbs_get_creds($account);

  $update = new FBS\Model\UpdatePatronRequest();
  $pincode_change = FBS\Model\PincodeChange();
  $pincode_change->pincode = $new_pincode;
  $pincode_change->libraryCardNumber = $creds['library_card_number'];
  $update->pincodeChange = $pincode_change;

  $res = fbs_service()->Patron->update(fbs_service()->agencyId, fbs_patron_id($account), $update);
  // FBS doesn't give any other indication of success than returning rather
  // than throwing an error.
  return array('creds' => _fbs_creds($res->patron));
}
