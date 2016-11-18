<?php
/**
 * @file
 * ding_serendipity.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function ding_serendipity_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ding_serendipity_callbacks';
  $strongarm->value = array(
    'ding_entity_rating_materials_by_rating' => 'ding_entity_rating_materials_by_rating',
    'ding_interests_materials' => 'ding_interests_materials',
    'ding_interests_nodes_by_bundle' => 'ding_interests_nodes_by_bundle',
    'ding_serendipity_fallback_ting_object' => 'ding_serendipity_fallback_ting_object',
    'ding_serendipity_lists_ting_objects_adhr' => 'ding_serendipity_lists_ting_objects_adhr',
    'ding_serendipity_lists_ting_objects_adhl' => 'ding_serendipity_lists_ting_objects_adhl',
    'ding_serendipity_lists_frontpage_search' => 'ding_serendipity_lists_frontpage_search',
    'ding_serendipity_lists_loan_adhl' => 'ding_serendipity_lists_loan_adhl',
    'ding_serendipity_lists_author_from_lists' => 'ding_serendipity_lists_author_from_lists',
    'ding_serendipity_site_field_related_material' => 'ding_serendipity_site_field_related_material',
    'ding_serendipity_site_field_related_content' => 'ding_serendipity_site_field_related_content',
    'ding_serendipity_taxonomy_term_recent' => 'ding_serendipity_taxonomy_term_recent',
    'ding_serendipity_taxonomy_term_related_by_term' => 'ding_serendipity_taxonomy_term_related_by_term',
    'ding_serendipity_taxonomy_term_recommended_objects' => 'ding_serendipity_taxonomy_term_recommended_objects',
    'ding_serendipity_taxonomy_term_popular_objects' => 'ding_serendipity_taxonomy_term_popular_objects',
    'ding_serendipity_ting_entity_ting_object_author' => 'ding_serendipity_ting_entity_ting_object_author',
    'ding_serendipity_ting_entity_ting_object_subject' => 'ding_serendipity_ting_entity_ting_object_subject',
    'ding_serendipity_ting_entity_ting_object_type' => 'ding_serendipity_ting_entity_ting_object_type',
    'ding_serendipity_ting_entity_ting_object_adhl' => 'ding_serendipity_ting_entity_ting_object_adhl',
    'ding_serendipity_ting_entity_ting_object_adhr' => 'ding_serendipity_ting_entity_ting_object_adhr',
    'ding_serendipity_ting_entity_ting_object_openlist_adhl' => 'ding_serendipity_ting_entity_ting_object_openlist_adhl',
    'ding_entity_rating' => 0,
    'ding_interests' => 0,
    'ding_serendipity_fallback' => 0,
    'ding_serendipity_lists' => 0,
    'ding_serendipity_lists_followed_terms_nodes' => 0,
    'ding_serendipity_lists_followed_terms_ting_objects' => 0,
    'ding_serendipity_site' => 0,
    'ding_serendipity_taxonomy_term' => 0,
    'ding_serendipity_ting_entity' => 0,
  );
  $export['ding_serendipity_callbacks'] = $strongarm;

  return $export;
}
