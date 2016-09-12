<?php

/**
 * Function for adding classes to body element
 */
function ddbasic_body_class($class = array()) {
  $classes = &drupal_static(__FUNCTION__, array());
  if(!empty($class)) {
    if(!is_array($class)) {
      $class = array($class); 
    }
    $classes = array_merge($classes, $class);
  } 
  return $classes;
}
