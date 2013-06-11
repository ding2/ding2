<?php
/**
 * @file
 * ding_content.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ding_content_user_default_permissions() {
  $permissions = array();

  // Exported permission: access comments.
  $permissions['access comments'] = array(
    'name' => 'access comments',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'comment',
  );

  // Exported permission: access content.
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: access content overview.
  $permissions['access content overview'] = array(
    'name' => 'access content overview',
    'roles' => array(
      'administrator' => 'administrator',
      'lokalredaktør' => 'lokalredaktør',
      'redaktør' => 'redaktør',
    ),
    'module' => 'node',
  );

  // Exported permission: access workbench.
  $permissions['access workbench'] = array(
    'name' => 'access workbench',
    'roles' => array(
      'administrator' => 'administrator',
      'formidler' => 'formidler',
      'gæsteblogger' => 'gæsteblogger',
      'lokalredaktør' => 'lokalredaktør',
      'redaktør' => 'redaktør',
    ),
    'module' => 'workbench',
  );

  // Exported permission: administer comments.
  $permissions['administer comments'] = array(
    'name' => 'administer comments',
    'roles' => array(
      'administrator' => 'administrator',
      'lokalredaktør' => 'lokalredaktør',
      'redaktør' => 'redaktør',
    ),
    'module' => 'comment',
  );

  // Exported permission: administer custom content.
  $permissions['administer custom content'] = array(
    'name' => 'administer custom content',
    'roles' => array(
      'administrator' => 'administrator',
      'redaktør' => 'redaktør',
    ),
    'module' => 'ctools_custom_content',
  );

  // Exported permission: administer menu.
  $permissions['administer menu'] = array(
    'name' => 'administer menu',
    'roles' => array(
      'administrator' => 'administrator',
      'redaktør' => 'redaktør',
    ),
    'module' => 'menu',
  );

  // Exported permission: administer opening hours configuration.
  $permissions['administer opening hours configuration'] = array(
    'name' => 'administer opening hours configuration',
    'roles' => array(
      'administrator' => 'administrator',
      'lokalredaktør' => 'lokalredaktør',
      'redaktør' => 'redaktør',
    ),
    'module' => 'opening_hours',
  );

  // Exported permission: administer panel-nodes.
  $permissions['administer panel-nodes'] = array(
    'name' => 'administer panel-nodes',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'panels_node',
  );

  // Exported permission: administer taxonomy.
  $permissions['administer taxonomy'] = array(
    'name' => 'administer taxonomy',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: create files.
  $permissions['create files'] = array(
    'name' => 'create files',
    'roles' => array(
      'formidler' => 'formidler',
      'lokalredaktør' => 'lokalredaktør',
      'redaktør' => 'redaktør',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: create panel content.
  $permissions['create panel content'] = array(
    'name' => 'create panel content',
    'roles' => array(
      'administrator' => 'administrator',
      'redaktør' => 'redaktør',
    ),
    'module' => 'node',
  );

  // Exported permission: create panel-nodes.
  $permissions['create panel-nodes'] = array(
    'name' => 'create panel-nodes',
    'roles' => array(
      'administrator' => 'administrator',
      'redaktør' => 'redaktør',
    ),
    'module' => 'panels_node',
  );

  // Exported permission: delete any files.
  $permissions['delete any files'] = array(
    'name' => 'delete any files',
    'roles' => array(
      'redaktør' => 'redaktør',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: delete any panel content.
  $permissions['delete any panel content'] = array(
    'name' => 'delete any panel content',
    'roles' => array(
      'administrator' => 'administrator',
      'redaktør' => 'redaktør',
    ),
    'module' => 'node',
  );

  // Exported permission: delete any panel-nodes.
  $permissions['delete any panel-nodes'] = array(
    'name' => 'delete any panel-nodes',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'panels_node',
  );

  // Exported permission: delete own files.
  $permissions['delete own files'] = array(
    'name' => 'delete own files',
    'roles' => array(
      'formidler' => 'formidler',
      'lokalredaktør' => 'lokalredaktør',
      'redaktør' => 'redaktør',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: delete own panel content.
  $permissions['delete own panel content'] = array(
    'name' => 'delete own panel content',
    'roles' => array(
      'administrator' => 'administrator',
      'redaktør' => 'redaktør',
    ),
    'module' => 'node',
  );

  // Exported permission: delete own panel-nodes.
  $permissions['delete own panel-nodes'] = array(
    'name' => 'delete own panel-nodes',
    'roles' => array(
      'administrator' => 'administrator',
      'redaktør' => 'redaktør',
    ),
    'module' => 'panels_node',
  );

  // Exported permission: delete revisions.
  $permissions['delete revisions'] = array(
    'name' => 'delete revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'lokalredaktør' => 'lokalredaktør',
      'redaktør' => 'redaktør',
    ),
    'module' => 'node',
  );

  // Exported permission: delete terms in 1.
  $permissions['delete terms in 1'] = array(
    'name' => 'delete terms in 1',
    'roles' => array(
      'administrator' => 'administrator',
      'redaktør' => 'redaktør',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: delete terms in 2.
  $permissions['delete terms in 2'] = array(
    'name' => 'delete terms in 2',
    'roles' => array(
      'administrator' => 'administrator',
      'redaktør' => 'redaktør',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: edit any files.
  $permissions['edit any files'] = array(
    'name' => 'edit any files',
    'roles' => array(
      'administrator' => 'administrator',
      'redaktør' => 'redaktør',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: edit any panel content.
  $permissions['edit any panel content'] = array(
    'name' => 'edit any panel content',
    'roles' => array(
      'administrator' => 'administrator',
      'redaktør' => 'redaktør',
    ),
    'module' => 'node',
  );

  // Exported permission: edit any panel-nodes.
  $permissions['edit any panel-nodes'] = array(
    'name' => 'edit any panel-nodes',
    'roles' => array(
      'administrator' => 'administrator',
      'redaktør' => 'redaktør',
    ),
    'module' => 'panels_node',
  );

  // Exported permission: edit opening hours for content.
  $permissions['edit opening hours for content'] = array(
    'name' => 'edit opening hours for content',
    'roles' => array(
      'administrator' => 'administrator',
      'lokalredaktør' => 'lokalredaktør',
      'redaktør' => 'redaktør',
    ),
    'module' => 'opening_hours',
  );

  // Exported permission: edit own comments.
  $permissions['edit own comments'] = array(
    'name' => 'edit own comments',
    'roles' => array(
      'administrator' => 'administrator',
      'formidler' => 'formidler',
      'gæsteblogger' => 'gæsteblogger',
      'lokalredaktør' => 'lokalredaktør',
      'redaktør' => 'redaktør',
    ),
    'module' => 'comment',
  );

  // Exported permission: edit own files.
  $permissions['edit own files'] = array(
    'name' => 'edit own files',
    'roles' => array(
      'formidler' => 'formidler',
      'lokalredaktør' => 'lokalredaktør',
      'redaktør' => 'redaktør',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: edit own panel content.
  $permissions['edit own panel content'] = array(
    'name' => 'edit own panel content',
    'roles' => array(
      'administrator' => 'administrator',
      'redaktør' => 'redaktør',
    ),
    'module' => 'node',
  );

  // Exported permission: edit own panel-nodes.
  $permissions['edit own panel-nodes'] = array(
    'name' => 'edit own panel-nodes',
    'roles' => array(
      'administrator' => 'administrator',
      'redaktør' => 'redaktør',
    ),
    'module' => 'panels_node',
  );

  // Exported permission: edit terms in 1.
  $permissions['edit terms in 1'] = array(
    'name' => 'edit terms in 1',
    'roles' => array(
      'administrator' => 'administrator',
      'redaktør' => 'redaktør',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: edit terms in 2.
  $permissions['edit terms in 2'] = array(
    'name' => 'edit terms in 2',
    'roles' => array(
      'administrator' => 'administrator',
      'redaktør' => 'redaktør',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: import media.
  $permissions['import media'] = array(
    'name' => 'import media',
    'roles' => array(
      'administrator' => 'administrator',
      'lokalredaktør' => 'lokalredaktør',
      'redaktør' => 'redaktør',
    ),
    'module' => 'media',
  );

  // Exported permission: manipulate all queues.
  $permissions['manipulate all queues'] = array(
    'name' => 'manipulate all queues',
    'roles' => array(
      'administrator' => 'administrator',
      'lokalredaktør' => 'lokalredaktør',
      'redaktør' => 'redaktør',
    ),
    'module' => 'nodequeue',
  );

  // Exported permission: manipulate queues.
  $permissions['manipulate queues'] = array(
    'name' => 'manipulate queues',
    'roles' => array(
      'administrator' => 'administrator',
      'lokalredaktør' => 'lokalredaktør',
      'redaktør' => 'redaktør',
    ),
    'module' => 'nodequeue',
  );

  // Exported permission: post comments.
  $permissions['post comments'] = array(
    'name' => 'post comments',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'comment',
  );

  // Exported permission: revert revisions.
  $permissions['revert revisions'] = array(
    'name' => 'revert revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'lokalredaktør' => 'lokalredaktør',
      'redaktør' => 'redaktør',
    ),
    'module' => 'node',
  );

  // Exported permission: skip comment approval.
  $permissions['skip comment approval'] = array(
    'name' => 'skip comment approval',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'comment',
  );

  // Exported permission: translate content.
  $permissions['translate content'] = array(
    'name' => 'translate content',
    'roles' => array(
      'administrator' => 'administrator',
      'redaktør' => 'redaktør',
    ),
    'module' => 'translation',
  );

  // Exported permission: use panels dashboard.
  $permissions['use panels dashboard'] = array(
    'name' => 'use panels dashboard',
    'roles' => array(
      'administrator' => 'administrator',
      'redaktør' => 'redaktør',
    ),
    'module' => 'panels',
  );

  // Exported permission: view files.
  $permissions['view files'] = array(
    'name' => 'view files',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: view own files.
  $permissions['view own files'] = array(
    'name' => 'view own files',
    'roles' => array(),
    'module' => 'file_entity',
  );

  // Exported permission: view own private files.
  $permissions['view own private files'] = array(
    'name' => 'view own private files',
    'roles' => array(),
    'module' => 'file_entity',
  );

  // Exported permission: view own unpublished content.
  $permissions['view own unpublished content'] = array(
    'name' => 'view own unpublished content',
    'roles' => array(
      'administrator' => 'administrator',
      'formidler' => 'formidler',
      'lokalredaktør' => 'lokalredaktør',
      'redaktør' => 'redaktør',
    ),
    'module' => 'node',
  );

  // Exported permission: view revisions.
  $permissions['view revisions'] = array(
    'name' => 'view revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'lokalredaktør' => 'lokalredaktør',
      'redaktør' => 'redaktør',
    ),
    'module' => 'node',
  );

  return $permissions;
}
