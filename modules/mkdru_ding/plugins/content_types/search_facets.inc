<?php
/**
 * @file
 * Search facets pane plugin.
 */
$plugin = array(
  'single' => TRUE,
  'title' => t('Mkdru DING! search facets'),
  'description' => t('The results of a search using keywords.'),
  'required context' => new ctools_context_required(t('Keywords'), 'string'),
  'category' => t('MKDRU'),
  'render callback' => 'mkdru_ding_search_facets_render',
  'edit form' => 'mkdru_ding_search_facets_edit_form',
);

/**
 * Render callback.
 */
function mkdru_ding_search_facets_render($subtype, $conf, $args, $context) {
  $block = new stdClass();
  $block->title = t('Facets');

  $mkdru_config = variable_get('mkdru_defaults');
  $facets = empty($mkdru_config['facets']) ? array() : $mkdru_config['facets'];
  $block->content = '';
  foreach ($facets as $facet => $facet_options) {
    $block->content .= theme('mkdru_block_facet', array('class' => 'mkdru-facet-' . $facet, 'name' => $facet_options['displayName']));
  }

  return $block;
}

/**
 * Edit form callback.
 */
function mkdru_ding_search_facets_edit_form($form, &$form_state) {
  return $form;
}
