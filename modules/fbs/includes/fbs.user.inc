<?php

/**
 * @file
 * Handles user authentication and update.
 */

/**
 * Implements provider user, authenticate.
 *
 * @param string $name
 *   User name.
 * @param string $pincode
 *   Supplied pincode.
 *
 * @return array
 *   Authentication result.
 */
function fbs_user_authenticate($name, $pincode) {
  $pass = _fbs_wayf_login($name);
  if ($pass) {
    // Wayf login.
    if ($pass !== $pincode) {
      // Die if we didn't get the same pincode as we generated in
      // wayf_login_credentials.
      return array(
        'success' => FALSE,
      );
    }

    $res = fbs_service()->Patron->getPreAuthenticatedPatron(fbs_service()->agencyId, $name);
  }
  else {
    // Normal login.
    $auth = new FBS\Model\AuthenticationRequest();
    $auth->libraryCardNumber = $name;
    $auth->pincode = $pincode;

    $res = fbs_service()->Patron->authenticate(fbs_service()->agencyId, $auth);
  }

  $result = array(
    'success' => $res->authenticated,
  );
  if ($res->authenticated) {
    // Save patron info in creds.
    $result['creds'] = _fbs_patron_info($res->patron);

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
      $denied = FALSE;
      $result['user']['blocks'] = array();
      foreach ($res->patron->blockStatus as $block) {
        $result['user']['blocked'] = TRUE;
        $result['user']['blocks'][] = $block->message;
        // Don't allow users blocked by "O" (library card stolen) or "S"
        // (blocked by self service automation) statusses log in.
        if (in_array($block->blockedReason, array('O', 'S'))) {
          $denied = TRUE;
        }
      }
      if ($denied) {
        $result['messages'] = $result['user']['blocks'];
        $result['success'] = FALSE;
      }
    }
  }

  return $result;
}

/**
 * Implements provider user, update_pincode.
 *
 * @param string $name
 *   User name.
 * @param string $new_pincode
 *   New pincode.
 *
 * @return array
 *   Update result.
 */
function fbs_user_update_pincode($account, $new_pincode) {
  $patron_info = fbs_get_patron_info($account);

  $update = new FBS\Model\UpdatePatronRequest();
  $pincode_change = new FBS\Model\PincodeChange();
  $pincode_change->pincode = $new_pincode;
  $pincode_change->libraryCardNumber = $patron_info['library_card_number'];
  $update->pincodeChange = $pincode_change;

  $res = fbs_service()->Patron->update(fbs_service()->agencyId, fbs_patron_id($account), $update);
  // FBS doesn't give any other indication of success than returning rather
  // than throwing an error.
  $result = array('creds' => _fbs_patron_info($res->patron));
  $result['creds']['library_card_number'] = $patron_info['library_card_number'];
  return $result;
}
