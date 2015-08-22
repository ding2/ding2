<?php

/**
 * @file
 *
 * Contains admin page callback for ting search context module.
 */

/**
 * Page callback (admin/content/ting-search-context)
 *
 * Renders the rate nodes VBO view.
 */
function ting_search_context_rate_nodes() {
	$output = t('The rate nodes view wasn\'t found');
	if ($view = views_get_view('ting_search_context_rate_nodes')) {
		$output = $view->preview('block_1');
	}
	return $output;
}

/**
 * Form builder (admin/config/ding/searchcontext)
 * Implements hook_form().
 * Admin form to configure position of related content on search page
 */
function ting_search_context_admin_settings_form($form, &$form_state) {
  $form = array();

  $form['ting_search_context_admin_settings_form'] = array(
    '#type' => 'fieldset',
    '#title' => t('Position related content on search page'),
  );

  $form['ting_search_context_admin_settings_form']['ting_search_context_position'] = array(
    '#type' => 'radios',
    '#title' => t('Position'),
    '#description' => t('Select the position of related content on the search page. On small screens related content is always displayed at the bottom of the page.'),
    '#options' => ting_search_context_get_positions(),
    '#default_value' => variable_get('ting_search_context_position', 'js-below-search-result'),
  );

  // Add administration feel and look.
  $form = system_settings_form($form);

  return $form;
}
