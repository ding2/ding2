<?php
/**
 * @file
 * Drush integration for the bpi module.
 */

/**
 * Implements hook_drush_command().
 */
function bpi_drush_command() {
  $items = array();

  $items['bpi-user-show-bpi-user-id'] = array(
    'description' => 'Show BPI user id for all or a single user.',
    'arguments' => array(
      'username' => 'The username.',
    ),
  );

  $items['bpi-user-set-bpi-user-id'] = array(
    'description' => 'Set BPI user id for a user.',
    'arguments' => array(
      'username' => 'The username.',
      'bpi-user-id' => 'The BPI user id.',
    ),
    // Argument "username" is required.
    'required-arguments' => 1,
  );

  return $items;
}

/**
 * Command callback. Show BPI user ids for users.
 *
 * @param string $username
 *   The username.
 *
 * @return bool
 *   Success.
 */
function drush_bpi_user_show_bpi_user_id($username = NULL) {
  $users = array();
  if ($username) {
    $user = user_load_by_name($username);
    if (!$user) {
      return drush_log(dt('No such user: !username', array('!username' => $username)), 'error');
    }
    $users[] = $user;
  }
  else {
    $users = entity_load('user');
  }

  foreach ($users as $user) {
    echo str_pad($user->name, 32) . (isset($user->data['bpi_user_id']) ? $user->data['bpi_user_id'] : ''), PHP_EOL;
  }

  return TRUE;
}

/**
 * Command callback. Set the BPI user id for a user.
 *
 * @param string $username
 *   The username.
 * @param string $bpi_user_id
 *   The BPI user id.
 *
 * @return bool
 *   Success.
 */
function drush_bpi_user_set_bpi_user_id($username, $bpi_user_id = NULL) {
  $account = user_load_by_name($username);
  if (!$account) {
    return drush_log(dt('No such user: !username', array('!username' => $username)), 'error');
  }
  user_save($account, array('data' => array('bpi_user_id' => $bpi_user_id)));

  return TRUE;
}
