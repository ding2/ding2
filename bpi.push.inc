<?php
/**
 * @file
 * Syndication logic here.
 */

/**
 * Start a content push session.
 *
 * @see bpi_menu()
 *
 * @param string $type
 *   Request type, simple http or ajax.
 * @param int $nid
 *   Node id, whose content is to be pushed.
 * @return Array/string
 *   Ajax command set in case of ajax request, push content page
 *   markup otherwise.
 */
function bpi_push_action($type, $nid) {
  $is_ajax = ($type == 'ajax') ? TRUE : FALSE;

  if (empty($nid)) {
    drupal_goto('admin/content');
  }

  if ($is_ajax) {
    $commands = array();

    $commands[] = ajax_command_alert('Stub fellas!');

    return array('#type' => 'ajax', '#commands' => $commands);
  }
  else {
    return '<h2>Stub fellas!</h2>';
  }
}
