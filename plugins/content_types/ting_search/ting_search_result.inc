<?php

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Ting search results'),
  'description' => t('Ting search results description'),
  'single' => TRUE,
  'content_types' => array('ting_search_result'),
  'render callback' => 'ting_search_result_content_type_render',
  'defaults' => array(),
  'icon' => 'icon_example.png',
  'category' => t('Ting'),
);

/**
 * Returns the administrative title for a type.
 */
function ctools_ting_search_result_content_type_admin_title($subtype, $conf, $context) {
  $type = module_invoke($conf['type'], 'ting_search', 'name', TRUE);
  return t('@type search result', array('@type' => $type));
}

/**
 * Render the custom content type.
 */
function ting_search_result_content_type_render($subtype, $conf, $panel_args, $context) {
  // Display nothing at all if no keywords were entered.
  $keys = array_pop($panel_args);

  // Build the content type block.
  $block = new stdClass();
  $block->module  = 'ting_search';
  $block->delta   = 'result';

  $results = '';

  // Need settings for:
  // $no result override

  if (!empty($conf['log'])) {
    // Log the search keys:
    watchdog('ting_search', '%keys (@type).', array('%keys' => $keys, '@type' => module_invoke($conf['type'], 'ting_search', 'name')), WATCHDOG_NOTICE, l(t('results'), $_GET['q']));
  }

  // Collect the search results:
  $results = ting_search_data($keys);

  if ($results) {
    $block->title = t('Ting Search results');
    $block->content = $results;
  }
  else {
    if (empty($conf['override_empty'])) {
      $block->title = t('Your search yielded no results');
      $block->content = search_help('search#noresults', drupal_help_arg());
    }
    else {
      $block->title = $conf['empty_title'];
      $block->content = check_markup($conf['empty'], $conf['empty_format'], FALSE);
    }
  }

  return $block;
}

/**
 * Returns an edit form for custom type settings.
 */
function ting_search_ting_search_result_content_type_edit_form($form, &$form_state) {
  return $form;
}

