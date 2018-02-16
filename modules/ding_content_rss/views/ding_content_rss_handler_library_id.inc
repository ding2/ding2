<?php

/**
 * @file
 * Node's "Library ID" custom field handler.
 */

/**
 * Class ding_content_rss_handler_library_id.
 */
// @codingStandardsIgnoreStart
class ding_content_rss_handler_library_id extends views_handler_field {

  /**
   * {@inheritdoc}
   */
  function option_definition() {
    $options = parent::option_definition();
    return $options;
  }

  /**
   * {@inheritdoc}
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
  }

  /**
   * {@inheritdoc}
   */
  function query() {}

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
// @codingStandardsIgnoreEnd
