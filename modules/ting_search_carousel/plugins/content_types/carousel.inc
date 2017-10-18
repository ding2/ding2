<?php

/**
 * @file
 * Provides search results as a Panels content type.
 */

$plugin = array(
  'title' => t('Ting search carousel'),
  'single' => TRUE,
  'description' => t('A carousel displaying search results against the data well'),
  'category' => t('Ting'),
);

/**
 * Return the pane contents.
 */
function ting_search_carousel_carousel_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  if ($searches = variable_get('ting_carousel_search_queries', array())) {
    $carousels = array();
    foreach ($searches as $index => $search) {
      $chunk = _ting_search_carousel_get_frontpage_entities($index, 0, TING_SEARCH_CAROUSEL_CHUNK_SIZE, TRUE);

      $items = array();
      foreach ($chunk['entities'] as $entity) {
        $items[] = ting_object_view($entity, 'teaser');
      }

      $carousels[] = array(
        '#type' => 'ding_carousel',
        '#title' => $search['title'],
        '#path' => 'ting_search_carousel/results/ajax/' . $index,
        '#items' => $items,
        '#offset' => $chunk['next_offset'],
        // Add a single placeholder to fetch more content later if there is more
        // content.
        '#placeholders' => $chunk['next_offset'] > -1 ? TING_SEARCH_CAROUSEL_CHUNK_SIZE + 1 : 0,
      );
    }

    $block->content = array(
      '#type' => 'ding_tabbed_carousel',
      '#tabs' => $carousels,
      '#transition' => variable_get('ting_search_carousel_transition', 'fade'),
    );
  }

  return $block;
}

/**
 * Return the pane titles.
 */
function ting_search_carousel_carousel_content_type_admin_title($subtype, $conf, $context) {
  return t('Ting search carousel');
}

/**
 * Returns an edit form for the content type.
 */
function ting_search_carousel_carousel_content_type_edit_form($form, &$form_state) {
  return $form;
}
