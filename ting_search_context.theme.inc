<?php

/**
 * @file
 * Theme functions used with the ting search context.
 */

/**
 * Implements default preprocess function for the search context.
 */
function template_preprocess_ting_search_context(&$vars, $hook) {
  // Add Javascript settings.
  drupal_add_js(array('ting_search_context_id' => $vars['context_id']), 'setting');
  drupal_add_js(array('ting_search_context_position' => $vars['position']), 'setting');

  // Add JavaScript and CSS using wrapper functions.
  _ting_search_context_add_javascript();
  _ting_search_context_add_css();
}

/**
 * Implements default preprocess function for the search context content.
 */
function template_preprocess_ting_search_context_content(&$vars, $hook) {
  $node = $vars['node'];
  $wrapper = entity_metadata_wrapper('node', $node);

  // Attempt to find an image for the rated node.
  // First priority is to use an image from a field on the node.
  $image_uri = FALSE;
  if ($field_name = ting_search_context_get_image_field_name($node)) {
    if ($image = $wrapper->$field_name->value()) {
      $image_uri = $image['uri'];
    }
  }
  // If we didn't have a field name for the node type or if there was no image
  // set on the field, use a random fallback image if any.
  if (!$image) {
    $fallback_images = variable_get('ting_search_context_fallback_images', array());
    if (!empty($fallback_images)) {
      $key = array_rand($fallback_images);
      if ($image = file_load($fallback_images[$key])) {
        $image_uri = $image->uri;
      }
    }
  }

  if ($image_uri) {
    $vars['image'] = array(
      '#theme' => 'image_style',
      '#path' => $image_uri,
      '#style_name' => 'ting_search_context',
    );
  }

  // URL.
  $webtrends_paramater = 'WT.mc_id=searchcontext';
  if ($node->type == 'ding_search_context_link') {
    $link = $wrapper->field_search_context_link->url->value();

    // One of the main usecases for ding_search_context_links is to link to
    // search queries. Search queries are tricky because they are a mix of
    // escaped and not escaped characters. This code handles it in a primitive
    // fashion by only escaping the quotes.
    //
    // Quotes inside search queries need to be escaped.
    $url = str_replace('"', '%22', $link);

    if (strpos($url, '?') == FALSE) {
      $url .= '?WT.mc_id=searchcontext';
    }
    else {
      $url .= '&WT.mc_id=searchcontext';
    }
  }
  else {
    $url = url('node/' . $node->nid, array('absolute' => TRUE, 'query' => array('WT.mc_id' => 'searchcontext')));
  }

  $vars['url'] = $url;

  // Title.
  $vars['title'] = $wrapper->title->value(array('sanitize' => TRUE));
}

/**
 * Theme function for facets status message.
 */
function theme_ting_search_context_status(&$vars) {
  $missing = $vars['status']['missing'];
  $required = $vars['status']['required'];

  $items = array();
  foreach ($required as $facet) {
    if (in_array($facet, $missing)) {
      $icon = theme('image', array('path' => 'misc/watchdog-error.png'));
      $message = t('is missing');
    }
    else {
      $icon = theme('image', array('path' => 'misc/watchdog-ok.png'));
      $message = t('is installed correctly');
    }
    $items[] = t('!icon @facet !message', array(
      '!icon' => $icon,
      '@facet' => $facet,
      '!message' => $message,
    ));
  }

  return theme('item_list', array('items' => $items));
}
