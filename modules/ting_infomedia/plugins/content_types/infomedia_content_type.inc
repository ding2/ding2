<?php

/**
 * @file
 * Infomedia ctools content type that takes an argument.
 */

/**
 * Plugin description array.
 */
$plugin = array(
  'title' => t('infomedia article'),
  'content_types' => 'infomedia_content_type',
  'single' => TRUE,
  'render callback' => 'infomedia_content_type_render',
  'description' => t('infomedia content type - works with a infomedia context.'),
  'required context' => new ctools_context_required(t('infomedia'), 'infomedia'),
  'admin title' => 'ctools_plugin_example_infomedia_content_type_admin_title',
  'admin info' => 'ctools_plugin_example_infomedia_content_type_admin_info',
  'category' => array(t('Ting'), -9),
);

/**
 * Plugin title callback.
 */
function ting_infomedia_infomedia_content_type_admin_title($subtype, $conf, $context = NULL) {
  $output = t('Infomedia article');

  if (isset($conf['override_title']) && !empty($conf['override_title_text'])) {
    $output = filter_xss_admin($conf['override_title_text']);
  }

  return $output;
}

/**
 * Plugin admin_info callback.
 */
function ting_infomedia_infomedia_content_type_admin_info($subtype, $conf, $context = NULL) {
  $block = new stdClass();
  $block->title = "Infomedia article content type";

  return $block;
}

/**
 * Plugin render callback.
 */
function infomedia_content_type_render($subtype, $conf, $args, $context) {
  $block = new stdClass();
  $id = (isset($args[0])) ? (int) $args[0] : $context->original_argument;
  $block->content = drupal_render(ting_infomedia_view($id));

  return $block;
}
