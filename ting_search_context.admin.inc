<?php

/**
 * @file
 *
 * Contains admin page callback for ting search context module.
 */

/**
 * Form builder (admin/content/ting-search-context)
 *
 * @see ting_search_context_overview_form_submit()
 * @see ting_search_context_overview_form_validate()
 */
function ting_search_context_overview_form($form, &$form_state) {
	// Title
	$form['title'] = array(
		'#type' => 'html_tag',
		'#suffix' => '<hr/>',
		'#tag' => 'h2',
		'#value' => t('Search context overview'),
	);
	// Table (Context overview)
	$header = array(
		'machine_name' => t('Machine name'),
		'readable_label' => t('Readable label'),
		'rating_count' => t('Rating count'),
	);
	$context_info = ting_search_context_get_context_info();
	$rows = array();
	foreach ($context_info as $name => $context) {
		$rows[] = array(
			'machine_name' => $name,
			'readable_label' => $context['label'],
			'rating_count' => $context['total_count'],
		);
	}
	$form['overview'] = array(
		'#prefix' => '<br/>',
		'#type' => 'tableselect',
		'#header' => $header,
		'#options' => $rows,
		'#empty' => t('No ratings found in the system'),
	);
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Show details'),
		'#description' => t('Shows detailed rating information about selected contexts.'),
		'#validate' => array('ting_search_context_overview_form_validate'),
		'#submit' =>  array('ting_search_context_overview_form_submit'),
	);
	return $form;
}

/**
 * Submit callback for the ting_search_context_overview_form.
 *
 * @see ting_search_context_overview_form()
 */
function ting_search_context_overview_form_submit($form, &$form_state) {

}

/**
 * Validate callback for the ting_search_context_overview_form.
 *
 * @see ting_search_context_overview_form() 
 */
function ting_search_context_overview_form_validate($form, &$form_state) {
	
}