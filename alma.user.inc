<?php

/**
 * 
 *
 * @param <type> $name
 * @param <type> $pass
 */
function alma_user_authenticate($uid, $pass) {
  $return = array(
    'success' => FALSE,
  );

  try {
    $res = alma_client_invoke('get_patron_info', $uid, $pass, TRUE);
  }
  catch (Exception $e) {
    /**
     *  @TODO re-throw better error message
     */
    throw $e;
  }

  $return['success'] = TRUE;
  $return['creds'] = array(
    'name' => $uid,
    'pass' => $pass,
  );

  return $return;
}

function alma_user_is_authenticated($creds) {
  return (isset($creds['name']) && isset($creds['pass']));
}