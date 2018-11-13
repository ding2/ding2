<?php
/**
 * @file
 * Classes autoloader.
 */

/**
 * Register an autoloader for the custom classes.
 */
spl_autoload_register(function ($class) {
  $file_path = dirname(__FILE__) . '/' . $class . '.class.inc';
  $file_path = str_replace('\\', DIRECTORY_SEPARATOR, $file_path);

  if (file_exists($file_path)) {
    require_once $file_path;
  }
});
