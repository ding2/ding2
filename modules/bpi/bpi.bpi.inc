<?php

/**
 * @file
 * Implementation of BPI hooks.
 */

/**
 * Implements hook_bpi_syndicate_get_bpi_types().
 */
function bpi_bpi_syndicate_get_bpi_types() {
  return array('article');
}

/**
 * Implements hook_bpi_get_field_mapping().
 */
function bpi_bpi_get_field_mapping_form($bpi_type, $content_type, array $field_mapping) {
  if (in_array($bpi_type, bpi_bpi_syndicate_get_bpi_types())) {
    $field_options = array('' => '') + bpi_get_field_instances($content_type);

    return array(
      'bpi_field_title' => array(
        '#type' => 'select',
        '#title' => t('BPI title'),
        '#description' => t('Titles are automatically assigned.'),
        '#options' => array('title' => t('Title')),
        '#value' => 'title',
        '#disabled' => TRUE,
      ),

      'bpi_field_teaser' => array(
        '#type' => 'select',
        '#title' => t('BPI teaser'),
        '#description' => t('The field to extract the teaser from. If the content type have a body summary, assign it to the body field.'),
        '#options' => $field_options,
        '#default_value' => isset($field_mapping['bpi_field_teaser']) ? $field_mapping['bpi_field_teaser'] : NULL,
      ),

      'bpi_field_body' => array(
        '#type' => 'select',
        '#title' => t('BPI body'),
        '#description' => t('Field to extract the main content from (body field).'),
        '#options' => $field_options,
        '#default_value' => isset($field_mapping['bpi_field_body']) ? $field_mapping['bpi_field_body'] : NULL,
      ),

      'bpi_field_tags' => array(
        '#type' => 'select',
        '#title' => t('BPI tags'),
        '#options' => $field_options,
        '#default_value' => isset($field_mapping['bpi_field_tags']) ? $field_mapping['bpi_field_tags'] : NULL,
      ),

      'bpi_field_materials' => array(
        '#type' => 'select',
        '#title' => t('BPI materials'),
        '#description' => t('Field used to get reference to the T!NG data well.'),
        '#options' => $field_options,
        '#default_value' => isset($field_mapping['bpi_field_materials']) ? $field_mapping['bpi_field_materials'] : NULL,
      ),
    );
  }

  return NULL;
}

/**
 * Implements bpi_syndicate_action_url().
 */
function bpi_bpi_syndicate_action_url($bpi_type, $bpi_id, array $mapping) {
  if (in_array($bpi_type, bpi_bpi_syndicate_get_bpi_types())) {
    return url(str_replace('_', '-', 'node/add/' . $mapping['bpi_content_type']), array('query' => array('bpi_type' => $bpi_type, 'bpi_id' => $bpi_id)));
  }

  return NULL;
}
