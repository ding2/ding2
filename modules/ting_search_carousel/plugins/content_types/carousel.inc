<?php
/**
 * @file
 * Provides search results as a Panels content type.
 */

$plugin = array(
  'title' => t('Ting search carousel'),
  'single' => TRUE,
  'description' => t('A carousel displaying search results against the Ting system'),
  'category' => t('Ting'),
  'content_types' => 'ting_search_carousel',
  'render callback' => 'ting_search_carousel_content_type_render',
  'edit form' => 'ting_search_carousel_settings_form',
);
