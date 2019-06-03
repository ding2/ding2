<?php

$plugin = array(
  'title' => t('Ding Facetbrowser'),
  'description' => t('Ding facetbrowser description'),
  'single' => TRUE,
  'content_types' => array('ding_facetbrowser'),
  'render callback' => 'ding_facetbrowser_content_type_render',
  'category' => t('Ting'),
  'render last' => TRUE,
);

/**
 * Callback function for the ctools content_type.
 */
function ding_facetbrowser_content_type_render($subtype, $conf, $panel_args, $context) {
  $block_content = FALSE;
  $content_in_facet = FALSE;
  $executed_search_module = FALSE;
  $block = new stdClass();

  $block->module = 'ding_facetbrowser';
  $block->delta  = 'ding_facetbrowser';

  // Invoke ding_facetbrowser() from executed search module.
  $executed_search = menu_get_item();
  if (!empty($executed_search['page_arguments'])) {
    list($executed_search_module, ) = $executed_search['page_arguments'];
  }
  if (is_string($executed_search_module)) {
    $results = module_invoke($executed_search_module, 'ding_facetbrowser');
    if (is_object($results)) {
      foreach ($results->search_result->getFacets() as $facet) {
        if (count($facet->getTerms()) > 0) {
          $content_in_facet = TRUE;
          break;
        }
      }
      if ($content_in_facet === TRUE || $results->show_empty == TRUE) {
        $block_content = theme('facetbrowser', array(
          'search_result' => $results->search_result,
        ));
      }
    }
    $path = drupal_get_path('module', 'ding_facetbrowser');

    $block->title = t('Ding Facetbrowser');
    $block->content['#markup'] = '<div class="js-facet-browser-toggle">' . $block_content . '</div>';
    $block->content['#attached'] = array(
      'js' => array(
        array(
          'data' => $path . '/js/ding_facetbrowser.js',
        ),
        array(
          'data' => array(
            'ding_facetbrowser' => array(
              'selector' => '.js-facet-browser-toggle',
              'number_of_terms' => variable_get('ding_facetbrowser_number_of_terms', 5),
            ),
          ),
          'type' => 'setting',
        ),
      ),
      'libraries_load' => array(
        array('js.cookie'),
      ),
    );

    return $block;
  }
}

/**
 * Returns an edit form for settings.
 */
function ding_facetbrowser_ding_facetbrowser_content_type_edit_form($form, &$form_state) {
  return $form;
}
