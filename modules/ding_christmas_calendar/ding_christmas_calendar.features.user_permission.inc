<?php
/**
 * @file
 * ding_christmas_calendar.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ding_christmas_calendar_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access quiz'.
  $permissions['access quiz'] = array(
    'name' => 'access quiz',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'quiz',
  );

  // Exported permission: 'administer quiz configuration'.
  $permissions['administer quiz configuration'] = array(
    'name' => 'administer quiz configuration',
    'roles' => array(
      'administrators' => 'administrators',
      'editor' => 'editor',
      'local administrator' => 'local administrator',
    ),
    'module' => 'quiz',
  );

  // Exported permission: 'administer xmas calendar'.
  $permissions['administer xmas calendar'] = array(
    'name' => 'administer xmas calendar',
    'roles' => array(
      'editor' => 'editor',
      'local administrator' => 'local administrator',
    ),
    'module' => 'ding_christmas_calendar',
  );

  // Exported permission: 'create multichoice content'.
  $permissions['create multichoice content'] = array(
    'name' => 'create multichoice content',
    'roles' => array(
      'administrators' => 'administrators',
      'editor' => 'editor',
      'local administrator' => 'local administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create quiz content'.
  $permissions['create quiz content'] = array(
    'name' => 'create quiz content',
    'roles' => array(
      'administrators' => 'administrators',
      'editor' => 'editor',
      'local administrator' => 'local administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create quiz_page content'.
  $permissions['create quiz_page content'] = array(
    'name' => 'create quiz_page content',
    'roles' => array(
      'administrators' => 'administrators',
      'editor' => 'editor',
      'local administrator' => 'local administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any multichoice content'.
  $permissions['delete any multichoice content'] = array(
    'name' => 'delete any multichoice content',
    'roles' => array(
      'administrators' => 'administrators',
      'editor' => 'editor',
      'local administrator' => 'local administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any quiz content'.
  $permissions['delete any quiz content'] = array(
    'name' => 'delete any quiz content',
    'roles' => array(
      'administrators' => 'administrators',
      'editor' => 'editor',
      'local administrator' => 'local administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any quiz results'.
  $permissions['delete any quiz results'] = array(
    'name' => 'delete any quiz results',
    'roles' => array(
      'administrators' => 'administrators',
      'editor' => 'editor',
      'local administrator' => 'local administrator',
    ),
    'module' => 'quiz',
  );

  // Exported permission: 'delete any quiz_page content'.
  $permissions['delete any quiz_page content'] = array(
    'name' => 'delete any quiz_page content',
    'roles' => array(
      'administrators' => 'administrators',
      'editor' => 'editor',
      'local administrator' => 'local administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own multichoice content'.
  $permissions['delete own multichoice content'] = array(
    'name' => 'delete own multichoice content',
    'roles' => array(
      'administrators' => 'administrators',
      'editor' => 'editor',
      'local administrator' => 'local administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own quiz content'.
  $permissions['delete own quiz content'] = array(
    'name' => 'delete own quiz content',
    'roles' => array(
      'administrators' => 'administrators',
      'editor' => 'editor',
      'local administrator' => 'local administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own quiz_page content'.
  $permissions['delete own quiz_page content'] = array(
    'name' => 'delete own quiz_page content',
    'roles' => array(
      'administrators' => 'administrators',
      'editor' => 'editor',
      'local administrator' => 'local administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete results for own quiz'.
  $permissions['delete results for own quiz'] = array(
    'name' => 'delete results for own quiz',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'quiz',
  );

  // Exported permission: 'edit any multichoice content'.
  $permissions['edit any multichoice content'] = array(
    'name' => 'edit any multichoice content',
    'roles' => array(
      'administrators' => 'administrators',
      'editor' => 'editor',
      'local administrator' => 'local administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any quiz content'.
  $permissions['edit any quiz content'] = array(
    'name' => 'edit any quiz content',
    'roles' => array(
      'administrators' => 'administrators',
      'editor' => 'editor',
      'local administrator' => 'local administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any quiz_page content'.
  $permissions['edit any quiz_page content'] = array(
    'name' => 'edit any quiz_page content',
    'roles' => array(
      'administrators' => 'administrators',
      'editor' => 'editor',
      'local administrator' => 'local administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own multichoice content'.
  $permissions['edit own multichoice content'] = array(
    'name' => 'edit own multichoice content',
    'roles' => array(
      'administrators' => 'administrators',
      'editor' => 'editor',
      'local administrator' => 'local administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own quiz content'.
  $permissions['edit own quiz content'] = array(
    'name' => 'edit own quiz content',
    'roles' => array(
      'administrators' => 'administrators',
      'editor' => 'editor',
      'local administrator' => 'local administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own quiz_page content'.
  $permissions['edit own quiz_page content'] = array(
    'name' => 'edit own quiz_page content',
    'roles' => array(
      'administrators' => 'administrators',
      'editor' => 'editor',
      'local administrator' => 'local administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit question titles'.
  $permissions['edit question titles'] = array(
    'name' => 'edit question titles',
    'roles' => array(
      'administrators' => 'administrators',
      'editor' => 'editor',
      'local administrator' => 'local administrator',
    ),
    'module' => 'quiz',
  );

  // Exported permission: 'manual quiz revisioning'.
  $permissions['manual quiz revisioning'] = array(
    'name' => 'manual quiz revisioning',
    'roles' => array(
      'administrators' => 'administrators',
      'editor' => 'editor',
      'local administrator' => 'local administrator',
    ),
    'module' => 'quiz',
  );

  // Exported permission: 'score any quiz'.
  $permissions['score any quiz'] = array(
    'name' => 'score any quiz',
    'roles' => array(
      'administrators' => 'administrators',
      'editor' => 'editor',
      'local administrator' => 'local administrator',
    ),
    'module' => 'quiz',
  );

  // Exported permission: 'score own quiz'.
  $permissions['score own quiz'] = array(
    'name' => 'score own quiz',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'quiz',
  );

  // Exported permission: 'score taken quiz answer'.
  $permissions['score taken quiz answer'] = array(
    'name' => 'score taken quiz answer',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'quiz',
  );

  // Exported permission: 'view any quiz question correct response'.
  $permissions['view any quiz question correct response'] = array(
    'name' => 'view any quiz question correct response',
    'roles' => array(
      'administrators' => 'administrators',
      'editor' => 'editor',
      'local administrator' => 'local administrator',
    ),
    'module' => 'quiz',
  );

  // Exported permission: 'view any quiz results'.
  $permissions['view any quiz results'] = array(
    'name' => 'view any quiz results',
    'roles' => array(
      'administrators' => 'administrators',
      'editor' => 'editor',
      'local administrator' => 'local administrator',
    ),
    'module' => 'quiz',
  );

  // Exported permission: 'view any unpublished quiz content'.
  $permissions['view any unpublished quiz content'] = array(
    'name' => 'view any unpublished quiz content',
    'roles' => array(),
    'module' => 'view_unpublished',
  );

  // Exported permission: 'view any unpublished quiz_page content'.
  $permissions['view any unpublished quiz_page content'] = array(
    'name' => 'view any unpublished quiz_page content',
    'roles' => array(),
    'module' => 'view_unpublished',
  );

  // Exported permission: 'view own quiz results'.
  $permissions['view own quiz results'] = array(
    'name' => 'view own quiz results',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'quiz',
  );

  // Exported permission: 'view quiz question outside of a quiz'.
  $permissions['view quiz question outside of a quiz'] = array(
    'name' => 'view quiz question outside of a quiz',
    'roles' => array(
      'administrators' => 'administrators',
      'editor' => 'editor',
      'local administrator' => 'local administrator',
    ),
    'module' => 'quiz',
  );

  // Exported permission: 'view results for own quiz'.
  $permissions['view results for own quiz'] = array(
    'name' => 'view results for own quiz',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'quiz',
  );

  return $permissions;
}
