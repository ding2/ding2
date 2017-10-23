<?php

/**
 * @file
 * Handles search carousel pages data.
 */

/**
 * AJAX callback to retrieve carousel items.
 *
 * @param int $index
 *   Configuration index.
 * @param int $offset
 *   Offset into result to fetch from.
 */
function ting_search_carousel_result($index, $offset) {
  $build = array();
  $chunk = _ting_search_carousel_get_frontpage_entities($index, $offset, TING_SEARCH_CAROUSEL_CHUNK_SIZE);
  foreach ($chunk['entities'] as $entity) {
    $build[] = array(
      '#type' => 'ding_carousel_item',
      '#content' => ting_object_view($entity, 'teaser'),
    );
  }

  // If there's more covers, add a placeholder at the end to signal the user
  // that it's loading.
  if ($chunk['next_offset'] > -1) {
    $build[] = array(
      '#type' => 'ding_carousel_item',
      '#placeholder' => TRUE,
    );
  }

  // Return JSON output.
  drupal_json_output(array(
    'content' => drupal_render($build),
    'offset' => $chunk['next_offset'],
  ));
}
