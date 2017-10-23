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
  $chunk = _ting_search_carousel_get_frontpage_covers($index, $offset, TING_SEARCH_CAROUSEL_CHUNK_SIZE);
  foreach ($chunk['collections'] as $collection) {
    $build[] = array(
      '#type' => 'ding_carousel_item',
      '#content' => array(
        '#type' => 'ting_search_carousel_cover',
        '#cover' => $collection,
      ),
    );
  }

  // If there's more covers, add a placeholder at the end to signal the user
  // that it's loading.
  if ($chunk['next_offset'] > -1) {
    $build[] = array(
      '#type' => 'ding_carousel_item',
      '#placeholder' => TRUE,
      '#content' => array(
        '#type' => 'ting_search_carousel_cover',
        '#cover' => ting_search_carousel_collection_placeholder(),
      ),
    );
  }

  // Return JSON output.
  drupal_json_output(array(
    'content' => drupal_render($build),
    'offset' => $chunk['next_offset'],
  ));
}
