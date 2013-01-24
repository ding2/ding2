<?php

/**
 * @file
 * Documentation of Ding! WAYF API.
 */

/**
 * Specifies which attributes are needed to login using WAYF.
 *
 * @return
 *   array of strings naming attributes.
 */
function hook_ding_wayf_attributes() {
  return array(
    'schacPersonalUniqueID' => array(
      'field' => 'CPR',
      'authname' => TRUE,
      ),
    );
}
?>
