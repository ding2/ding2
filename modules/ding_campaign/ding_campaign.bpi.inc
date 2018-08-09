<?php

/**
 * @file
 * Implementation of BPI hooks.
 */

/**
 * Implements hook_bpi_syndicate_get_bpi_types().
 */
function ding_campaign_bpi_syndicate_get_bpi_types() {
  return array('campaign');
}

/**
 * Implements bpi_syndicate_action_url().
 */
function ding_campaign_bpi_syndicate_action_url($bpi_type, $bpi_id, array $mapping) {
  if (in_array($bpi_type, ding_campaign_bpi_syndicate_get_bpi_types())) {
    return url(str_replace('_', '-', 'node/add/' . $mapping['content_type']), array('query' => array('bpi_type' => $bpi_type, 'bpi_id' => $bpi_id)));
  }

  return NULL;
}

/**
 * Implements hook_bpi_get_field_mapping().
 */
function ding_campaign_bpi_get_field_mapping_form($bpi_type, $content_type, array $field_mapping) {
  if (in_array($bpi_type, ding_campaign_bpi_syndicate_get_bpi_types())) {
    $field_options = array('' => '') + bpi_get_field_instances($content_type);

    return array(
      'title' => array(
        '#type' => 'select',
        '#title' => t('BPI title'),
        '#description' => t('Titles are automatically assigned.'),
        '#options' => array('title' => t('Title')),
        '#value' => 'title',
        '#disabled' => TRUE,
      ),

      'body' => array(
        '#type' => 'select',
        '#title' => t('BPI body'),
        '#description' => t('Field to extract the main content from (body field).'),
        '#options' => $field_options,
        '#default_value' => isset($field_mapping['body']) ? $field_mapping['body'] : NULL,
      ),

      'url' => array(
        '#type' => 'select',
        '#title' => t('BPI url'),
        '#description' => t('Field to extract the url from.'),
        '#options' => $field_options,
        '#default_value' => isset($field_mapping['url']) ? $field_mapping['url'] : NULL,
      ),
    );
  }

  return NULL;
}

/**
 * Implements hook_bpi_convert_to_bpi_alter().
 */
function ding_campaign_bpi_convert_to_bpi_alter(&$bpi_content, $node, $mapping) {
  if (in_array($mapping['bpi_node_type'], ding_campaign_bpi_syndicate_get_bpi_types())) {
    $url_field = isset($mapping['field_mapping']['url']) ? field_view_field('node', $node, $mapping['field_mapping']['url']) : NULL;
    $url = bpi_get_field_value($url_field);
    $bpi_content['url'] = $url;

    $campaign_type = bpi_get_field_value(field_view_field('node', $node, 'field_camp_settings'));
    $bpi_content['data'] = array(
      'type' => $campaign_type,
    );
  }
}

/**
 * Implements hook_bpi_syndicate_form().
 */
function ding_campaign_bpi_syndicate_form_alter(&$form, $bpi_content, $syndicated_images) {
  $current_language = $form['language']['#value'];
  $data = json_decode($bpi_content['data'], TRUE);
  $type = isset($data['type']) ? $data['type'] : 'plain';

  if (!in_array($type, array('full', 'image', 'plain'))) {
    $type = 'plain';
  }

  $form['field_camp_settings'][$current_language]['#default_value'] = $type;
  $form['field_camp_link'][$current_language][0]['value']['#default_value'] = isset($bpi_content['url']) ? $bpi_content['url'] : NULL;
}

/**
 * Implements hook_bpi_get_image_type().
 */
function ding_campaign_bpi_get_image_type($image_field_name, $node) {
  if ($node->type === 'ding_campaign') {
    $pattern = '/field_camp_(?<image_type>.+)/';
    if (preg_match($pattern, $image_field_name, $matches)) {
      return $matches['image_type'];
    }
  }

  return NULL;
}
