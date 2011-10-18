<?php

/**
 * @file
 * class ding_library_nid_to_gid_argument
 * Handler that allows to use group fields with a nid as argument.
 */

class ding_library_nid_to_gid_argument extends views_handler_argument_numeric {
  function query($group_by = FALSE) {
    // Try to load the node from the argument and get the gid from it.
    $group = node_load($this->argument);
    if (empty($group)) {
      $this->argument = 0;
    }
    else {
      $node_wrapper = entity_metadata_wrapper('node', $group);
      // We use try/catch since we get an exception if the node isn't a group.
      try {
        $this->argument = $node_wrapper->group->gid->value();
      } catch (EntityMetadataWrapperException $e) {
        $this->argument = 0;
      } 
    }
    parent::query($group_by);
  }
}
