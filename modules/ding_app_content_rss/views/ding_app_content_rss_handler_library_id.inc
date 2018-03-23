<?php

/**
 * @file
 * Node's "Library ID" custom field handler.
 */

/**
 * Class ding_app_content_rss_handler_library_id.
 */
class ding_app_content_rss_handler_library_id extends views_handler_field {

  /**
   * Query definition. MUST be here as it is required by views field handler.
   */
  function query() {
    // Do nothing -- to override the parent query.
  }

  /**
   * Find out the information to render.
   */
  function render($data) {
    $node = $data->_field_data['nid']['entity'];
    $library_target = field_get_items('node', $node, 'og_group_ref');
    $id = $library_target[0]['target_id'];
    return $id;
  }

}
