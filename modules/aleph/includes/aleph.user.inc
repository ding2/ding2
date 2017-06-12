<?php
/**
 * @file
 * Handles user authentication with the aleph provider.
 */

 /**
  * Implements hook_user_authenticate().
  */
 function aleph_user_authenticate($uid, $pass) {
   $client = aleph_client();
   return $client->authenticate($uid, $pass);
 }

 /**
  * Check if the user creds is set correctly.
  *
  * @param array $creds
  *   Array with the user credentials.
  *
  * @return bool
  *   TRUE if user is authenticated else FALSE
  */
 function aleph_user_is_authenticated($creds) {
   return (isset($creds['name']) && isset($creds['pass']));
 }
