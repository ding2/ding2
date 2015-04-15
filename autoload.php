<?php
/**
 * @file
 * Basic autoloader implementation.
 */

spl_autoload_register(function ($class_name) {
  $file = __DIR__ . '/lib/' . $class_name . '.class.inc';
  if (file_exists($file)) {
    include_once $file;
  }
});
