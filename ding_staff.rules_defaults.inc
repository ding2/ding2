<?php
/**
 * @file
 * ding_staff.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function ding_staff_default_rules_configuration() {
  $items = array();

  $items['rules_role_staff_assign'] = entity_import('rules_config', '{ "rules_role_staff_assign" : {
      "LABEL" : "assign staff role",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "ding_staff" ],
      "REQUIRES" : [ "rules", "ding_staff", "profile2" ],
      "ON" : [ "profile2_insert" ],
      "IF" : [
        { "data_is" : { "data" : [ "profile2:type:type" ], "value" : "ding_staff_profile" } }
      ],
      "DO" : [ { "ding_staff_add_role_staff" : { "profile_user" : [ "profile2:user" ] } } ]
    }
  }');

  return $items;
}


/**
* Implements of hook_rules_action_info().
*/
function ding_staff_rules_action_info() {
  return array(
    'ding_staff_add_role_staff' => array(
      'label' => t('Add staff role to user'),
      'group' => 'user',
      'parameter' => array(
        'profile_user' => array(
          'type' => 'user',
          'label' => t('User to add staff role to'),
        ),
      ),
    ),
  );
}
/*
 * Action to add the staff role to a user. 
 *
 * Since we cannot know which role ID the staff role has been assigned,
 * this function is used instead of the "add user role" action
 */
function ding_staff_add_role_staff($profile_user) {
  // get the uid from the object
  if (isset($profile_user->uid)) {
    $uid = $profile_user->uid;
  }
  else {
    return;
  }

  //make sure we have a user record
  if ($uid){
    // Define "staff" as the role to add.
    $role_name = "staff";
    $user = user_load($uid);
    
    // If the user doesn't already have the role, add the role to that user.
    $key = array_search($role_name, $user->roles);
    if ($key == FALSE) {

      // Get the rid from the roles table.
      $roles = user_roles(TRUE);
      $rid = array_search($role_name, $roles);
      if ($rid != FALSE) {
        $new_role[$rid] = $role_name;
        $all_roles = $user->roles + $new_role; // Add new role to existing roles.
        user_save($user, array('roles' => $all_roles));
        drupal_set_message(t('@username has been assigned the staff role.', array('@username' => $profile_user->name)), 'status');
      }
    }
  }
}