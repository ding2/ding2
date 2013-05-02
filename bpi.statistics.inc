<?php
/**
 * @file
 * BPI statistics related logic here.
 */

function bpi_statistics($type) {
  $ajax = ($type == 'ajax') ? TRUE : FALSE;

  if ($ajax) {
    $commands = array();

    $commands[] = ajax_command_alert('Stub guys!');

    return array('#type' => 'ajax', '#commands' => $commands);
  }
  else {
    return '<h2>STUB GUYS!</h2>';
  }
}
