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
	$form['title_overview'] = array(
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
		$rows[$name] = array(
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
		'#value' => t('Update'),
		'#description' => t('Updates the detail table'),
		'#validate' => array('ting_search_context_overview_form_validate'),
		'#submit' =>  array('ting_search_context_overview_form_submit'),
	);

	// If the context was selected we set up the detail table with rated nodes.
	if (!empty($_SESSION['ting_search_context_selected_contexts'])) {
		$selected_contexts = $_SESSION['ting_search_context_selected_contexts'];
		// Check the selected values in the table.
		$default_value = array();
		foreach ($selected_contexts as $context_name) {
			$default_value[$context_name] = 1;
		}
		$form['overview']['#default_value'] = $default_value;
		// Set up the table
		$header = array(
			array('data' => t('Title'), 'field' => 'n.title'),
			array('data' => t('Type'), 'field' => 'n.type'),
			array('data' => t('Status'), 'field' => 'n.status'),
			array('data' => t('Context'), 'field' => 'name'),
			array('data' => t('Rating'), 'field' => 'rating'),
		);
		$query = db_select('node', 'n')->extend('TableSort');
		$query->join('field_data_field_ting_search_context', 'fd', 'n.nid = fd.entity_id');
		$query->fields('n', array('title', 'type', 'status'));
		$query->addField('fd', 'field_ting_search_context_name', 'name');
		$query->addField('fd', 'field_ting_search_context_rating', 'rating');
		$result = $query->orderByHeader($header)->execute();
		$rows = array();
		foreach ($result as $row) {
			$rows[] = array('data' => (array) $row);
		}
		$form['title_detail'] = array(
			'#type' => 'html_tag',
			'#suffix' => '<hr/>',
			'#tag' => 'h2',
			'#value' => t('Search context details'),
		);		
		$form['detail'] = array(
			'#prefix' => '<br/>',
			'#theme' => 'table',
			'#header' => $header,
			'#rows' => $rows,
			'#empty' => t('There was no nodes rated in the selected contexts'),
		);
		// file_put_contents("/home/drupalpro/debug/debug.txt", print_r($selected_contexts , TRUE), FILE_APPEND);
	}

	return $form;
}

/**
 * Submit callback for the ting_search_context_overview_form.
 *
 * @see ting_search_context_overview_form()
 */
function ting_search_context_overview_form_submit($form, &$form_state) {
	// Filter out unchecked contexts.
	$selected_contexts = array_filter($form_state['values']['overview']);
	if (!empty($selected_contexts)) {
		$_SESSION['ting_search_context_selected_contexts'] = $selected_contexts;
	}
	else {
		$_SESSION['ting_search_context_selected_contexts'] = array();
	}
}

/**
 * Validate callback for the ting_search_context_overview_form.
 *
 * @see ting_search_context_overview_form() 
 */
function ting_search_context_overview_form_validate($form, &$form_state) {
	// Nothing to do yet.
}