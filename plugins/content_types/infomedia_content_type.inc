<?php

/**
 * @file
 * Infomedia ctools content type that takes an argument.
 *
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
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

function ctools_plugin_example_infomedia_content_type_admin_title($subtype, $conf, $context = NULL) {
  $output = t('Infomedia article');
  if (isset($conf['override_title']) && !empty($conf['override_title_text'])) {
    $output = filter_xss_admin($conf['override_title_text']);
  }
  return $output;
}

/**
 * Callback to provide administrative info (the preview in panels when building
 * a panel).
 *
 * In this case we'll render the content with a dummy argument and
 * a dummy context.
 */
function ctools_plugin_example_infomedia_content_type_admin_info($subtype, $conf, $context = NULL) {
  $block = new stdClass();
  $block->title = check_plain("Infomedia article content type");
  $block->content = t("<div>Aliquam quis erat purus. Ut urna erat, tincidunt at ultrices quis, dapibus et nulla. Praesent non justo diam, ac volutpat tortor. Donec id purus nulla. Nam dignissim, nibh ut hendrerit scelerisque, sem metus feugiat justo, ac molestie libero arcu eu leo.</div>");
  return $block;
}

/**
 * Run-time rendering of the body of the block (content type)
 *
 * @param $subtype
 * @param $conf
 *   Configuration as done at admin time
 * @param $args
 * @param $context
 *   Context - in this case we don't have any
 *
 * @return
 *   An object with at least title and content members
 */
function infomedia_content_type_render($subtype, $conf, $args, $context) {
  $block = new stdClass();
  $id = ( isset($args[0]) ) ? (int)$args[0] : $context->original_argument;
  // The title actually used in rendering.
  // $block->title = "Infomedia article";
  $block->content = drupal_render(ting_infomedia_view($id));

  return $block;
}
