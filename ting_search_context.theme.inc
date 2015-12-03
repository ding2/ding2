<?php

/**
 * @file
 * Theme functions used with the ting search context.
 */

/**
 * Implements default preprocess function for the search context.
 */
function template_preprocess_ting_search_context(&$vars, $hook) {
  // Add Javascript settings
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

  //Image
  $field_name = ting_search_context_get_image_field_name($node);
  $image = field_view_field('node', $node, $field_name, array(
    'label' => 'hidden',
    'settings' => array(
      'image_style' => 'ting_search_context',
    ),
    ));
  $vars['image'] = drupal_render($image);

  //URL
  $webtrends_paramater = 'WT.mc_id=searchcontext';
  if ($node->type == 'ding_search_context_link') {
    $wrapper = entity_metadata_wrapper('node', $node);
    $link = $wrapper->field_search_context_link->url->value();

    // One of the main usecases for ding_search_context_links is to link to search queries. Search queries are tricky because they
    // are a mix of escaped and not escaped characters. This code handles it in a primitive fashion by only escaping the quotes.
    $url = str_replace('"', '%22', $link ); // Quotes inside search queries need to be escaped

    if (strpos($url, '?') == false) {
      $url .= '?WT.mc_id=searchcontext';
    } else {
      $url .= '&WT.mc_id=searchcontext';
    }
  } else {
    $url = url('node/' . $node->nid, array('absolute' => TRUE, 'query' => array ('WT.mc_id' => 'searchcontext')));
  }

  $vars['url'] = $url;

  // Title
  $title = check_plain($node->title);
  if (strlen($title) > 20) {
    $title = substr($title, 0, 18) . '..';
  }
  $vars['title'] = $title;
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
    $items[] = format_string('!icon @facet !message', array(
      '!icon' => $icon,
      '@facet' => $facet,
      '!message' => $message,
    ));
  }

  $output = theme('item_list', array('items' => $items));

  if (!empty($missing)) {
    $output .= '<strong>' . l(t('Configure facets'), 'admin/config/ting/facets') . '</strong>';
  }

  return $output;
}
