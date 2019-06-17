<?php
/**
 * @file
 * Implements functions used to log users into the system through SSO services.
 */

/**
 * Implements hook_auth_single_sign_on().
 *
 * @oaram string $uuid
 *   Unique id for the person that's should be generated credentials for.
 *
 * @throws DingProviderUserAuthFailure
 *   If authentication fails.
 */
function fbs_auth_single_sign_on($uuid) {
  $res = new stdClass();
  try {
    $res = fbs_service()->Patron->getPreAuthenticatedPatron(fbs_service()->agencyId, $uuid);
  }
  catch (Exception $e) {
    watchdog_exception('fbs', $e);
  }

  if (empty($res->authenticated)) {
    throw new DingProviderUserAuthFailure();
  }

  // Parse/transform patron into user info array.
  $result = _fbs_patron_transform($uuid, $res->patron);
  $result['success'] = $res->authenticated;

  return $result;
}
