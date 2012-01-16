<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function ding_tabroll_user_default_permissions() {
  $permissions = array();

  // Exported permission: create rolltab content
  $permissions['create rolltab content'] = array(
    'name' => 'create rolltab content',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: delete any rolltab content
  $permissions['delete any rolltab content'] = array(
    'name' => 'delete any rolltab content',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: delete own rolltab content
  $permissions['delete own rolltab content'] = array(
    'name' => 'delete own rolltab content',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: edit any rolltab content
  $permissions['edit any rolltab content'] = array(
    'name' => 'edit any rolltab content',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: edit own rolltab content
  $permissions['edit own rolltab content'] = array(
    'name' => 'edit own rolltab content',
    'roles' => array(
      '0' => 'administrator',
    ),
  );

  // Exported permission: manipulate all queues
  $permissions['manipulate all queues'] = array(
    'name' => 'manipulate all queues',
    'roles' => array(
      '0' => 'editor',
      '1' => 'administrator',
    ),
  );

  // Exported permission: manipulate queues
  $permissions['manipulate queues'] = array(
    'name' => 'manipulate queues',
    'roles' => array(
      '0' => 'editor',
      '1' => 'administrator',
    ),
  );

  // Exported permission: view imagecache 460_240_crop
  $permissions['view imagecache 460_240_crop'] = array(
    'name' => 'view imagecache 460_240_crop',
    'roles' => array(
      '0' => 'anonymous user',
      '1' => 'authenticated user',
      '2' => 'administrator',
    ),
  );

  return $permissions;
}
