<?php
/**
 * @file
 * Panels argument plugin that loads the library node base on slug name.
 */

$plugin = array(
  'title' => t('Node: Ding library slug'),
  'keyword' => 'node',
  'description' => t('Creates a libray context from the libray slug.'),
  'context' => 'ding_library_slug_context',
);

/**
 * Loads context (library node) base on slug name.
 */
function ding_library_slug_context($arg = NULL, $conf = NULL, $empty = FALSE) {
  // If $empty == TRUE it wants a generic, unfilled context.
  if ($empty) {
    return ctools_context_create_empty('node');
  }

  // We can accept either a node object or a pure nid.
  if (is_object($arg)) {
    return ctools_context_create('node', $arg);
  }

  // Default value.
  $node = FALSE;

  // Add static cache.
  $cache = &drupal_static(__FUNCTION__, array());
  if (isset($cache['arg'])) {
    $node = $cache['arg'];
  }

  if (!$node) {
    $nid = FALSE;
    // Cast argument to an integer to see if it looks like a node ID.
    $num = intval($arg);
    if (is_numeric($num) && $num > 0) {
      $nid = $num;
    }
    elseif (strlen($arg) > 1) {
      // Try looking up the argument as a slug.
      $query = new EntityFieldQuery();
      $query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'ding_library')
        ->propertyCondition('status', 1)
        ->fieldCondition('field_ding_library_slug', 'value', $arg);

      $result = $query->execute();

      if (isset($result['node'])) {
        $nid = array_keys($result['node']);
        $nid = reset($nid);
      }
    }
    else {
      return FALSE;
    }

    // Check that it is a number that we found.
    if (!$nid || !is_numeric($nid)) {
      return FALSE;
    }

    // Load the related node.
    $node = node_load($nid);
    if (!$node) {
      return FALSE;
    }

    // Save the node in cache.
    $cache['arg'] = $node;
  }

  // Create the context.
  return ctools_context_create('node', $node);
}
