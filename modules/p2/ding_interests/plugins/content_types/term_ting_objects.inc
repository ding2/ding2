<?php

/**
 * @file
 * To-do: doc here.
 */

$plugin = array(
  'title' => t('Ding interests: Term Ting Objects'),
  'description' => '',
  'single' => TRUE,
  'content_types' => array('taxonomy_term'),
  'required context' => new ctools_context_required(t('Term'), 'taxonomy_term'),
  'category' => t('Ding!'),
  'render callback' => 'ding_interests_term_ting_objects_content_type_render',
);

/**
 * To-do: doc here.
 */
function ding_interests_term_ting_objects_content_type_render($subtype, $conf, $panel_args, $context) {
  $term = $context->data;

  $block = new stdClass();

  // TODO This code is duplicated throughout the codebase. Please refactor. @MSD
  $search_string = ding_interest_get_term_cql($term);

  $options = array(
    'limit' => 10,
  );

  $results = ding_serendipity_do_search($search_string, $options);

  if (empty($results)) {
    return $block;
  }

  $ids = array();
  foreach ($results as $item) {
    $ids[] = $item['id'];
  }
  $objects = entity_load('ting_object', FALSE, array('ding_entityid' => $ids));

  $buffer = array();
  foreach ($objects as $key => $object) {
    $content = ting_object_view($object, 'compact');
    $content['#weight'] = $key;
    $buffer[] = $content;
  }

  $block->content = theme('ting_carousel', array(
      'objects' => $buffer,
      'extra' => l(t('More'), 'search/ting/' . $search_string),
    ));

  return $block;
}
