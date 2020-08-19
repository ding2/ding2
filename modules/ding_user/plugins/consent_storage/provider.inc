<?php

/**
 * @file
 * Provider consent storage.
 */

$plugin = [
  'title' => t('Provider consent storage'),
  'description' => t('ECC consent storage plugin that makes it possible to upgrade anonymous consent for provider users.'),
  'consent_storage_callback' => 'ding_user_store_provider_user_consent',
];

/**
 * Store record of consent in the database.
 *
 * This is an extention of ECC's basic consent storage plugin, that also saves
 * a cookie for anynomous users referencing the stored consent in DB. If a
 * provider user subsequently logs in from the same device, we can then upgrade
 * it and link it to them.
 *
 * @param string $type
 *   The consent type (for example banner or form ID).
 *
 * @return bool
 *   Returns TRUE on storage success.
 *
 * @throws \Exception
 */
function ding_user_store_provider_user_consent($type) {
  global $user;

  // Unfortunately we can not call the code from the basic plugin directly,
  // since it doesn't give us $cid, so we have to copy some code from ECC.
  $revision_id = _eu_cookie_compliance_get_current_policy_node_revision();
  $timestamp = time();
  $ip_address = ip_address();
  $uid = $user->uid;

  $cid = db_insert('eu_cookie_compliance_basic_consent')
    ->fields(array(
      'uid' => $uid,
      'ip_address' => $ip_address,
      'timestamp' => $timestamp,
      'revision_id' => $revision_id ? $revision_id : 0,
      'consent_type' => $type,
    ))
    ->execute();

  if (!user_is_logged_in()) {
    // This is an anonymous consent. Store a cookie referencing the consent.
    $cookie_name = eu_cookie_compliance_get_settings()['cookie_name'];
    $lifetime = variable_get('eu_cookie_compliance_cookie_lifetime', 100);
    // Use the current cookie name for ECC agreed cookied (with "-cid" appended)
    // and also the same lifetime. This way we tie it to the current policy.
    // Using REQUEST_TIME to get as close to the lifetime for ECC cookie.
    setcookie($cookie_name . '-cid', $cid, REQUEST_TIME + $lifetime * 3600 * 24, '/');
  }

  return TRUE;
}
