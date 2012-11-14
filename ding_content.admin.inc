<?php

/**
 * @file
 * Admin page callbacks for the ding_content module.
 */

/**
 * AJAX Callback function to return a list of media files
 *
 * More or less a copy of the media_browser_list callback.
 * @see media_browser_list()
 */
function ding_content_media_browser_list() {
  module_load_include('inc', 'media', 'includes/media.browser');
  global $user;
  $params = drupal_get_query_parameters();
  // How do we validate these?  I don't know.
  // I think PDO should protect them, but I'm not 100% certain.
  array_walk_recursive($params, '_media_recursive_check_plain');

  $types = isset($params['types']) ? $params['types'] : NULL;
  $url_include_patterns = isset($params['url_include_patterns']) ? $params['url_include_patterns'] : NULL;
  $url_exclude_patterns = isset($params['url_exclude_patterns']) ? $params['url_exclude_patterns'] : NULL;

  $start = isset($params['start']) ? $params['start'] : 0;
  $limit = isset($params['limit']) ? $params['limit'] : media_variable_get('browser_pager_limit');

  $query = db_select('file_managed', 'f');
  $query->fields('f', array('fid'));
  $query->range($start, $limit);
  $query->orderBy('f.fid', 'DESC');

  // Add conditions based on file type *or* allowed extensions.
  $condition = $query;
  if (!empty($types) && !empty($params['file_extensions'])) {
    $condition = db_or();
  }
  if (!empty($types)) {
    $condition->condition('f.type', $types, 'IN');
  }
  if (!empty($params['file_extensions'])) {
    $extensions = array_filter(explode(' ', $params['file_extensions']));
    foreach ($extensions as $extension) {
      $condition->condition('f.uri', '%' . db_like('.' . $extension), 'LIKE');
    }
  }
  if ($condition instanceof DatabaseCondition) {
    $query->condition($condition);
  }

  if ($url_include_patterns) {
    $query->condition('f.uri', '%' . db_like($v) . '%', 'LIKE');
    // Insert stream related restrictions here.
  }
  if ($url_exclude_patterns) {
    $query->condition('f.uri', '%' . db_like($v) . '%', 'NOT LIKE');
  }

  // @todo Implement granular editorial access: http://drupal.org/node/696970.
  //   In the meantime, protect information about private files from being
  //   discovered by unprivileged users. See also media_view_page().
  if (!user_access('administer media')) {
    $query->condition('f.uri', db_like('private://') . '%', 'NOT LIKE');
  }

  $query->condition('f.status', FILE_STATUS_PERMANENT);
  $query->condition('f.uid', $user->uid);

  foreach (array_keys(media_get_hidden_stream_wrappers()) as $name) {
    $query->condition('f.uri', db_like($name . '://') . '%', 'NOT LIKE');
  }

  $fids = $query->execute()->fetchCol();
  dd('test');
  dd($fids);
  $files = file_load_multiple($fids);
  foreach ($files as $file) {
    media_browser_build_media_item($file);
  }

  drupal_json_output(array('media' => array_values($files)));
  exit();
}