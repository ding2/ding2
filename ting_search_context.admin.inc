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
	// Get needed information
	$selected_contexts = array();
	if (isset($_SESSION['ting_search_context_selected_contexts'])) {
		$selected_contexts = $_SESSION['ting_search_context_selected_contexts'];
	}
  $context_info = ting_search_context_get_context_info();
  // Build the form
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
	$rows = array();
	foreach ($context_info as $name => $context) {
		$rows[$name] = array(
			'machine_name' => $name,
			'readable_label' => $context['label'],
			'rating_count' => $context['total_count'],
		);
		// Add the selected class if this row is selected.
		if (in_array($name, $selected_contexts)) {
			$rows[$name]['#attributes'] = array('class' => array('selected'));
		}
	}	
	// Make sure the selected contexts is checked in the overview table.
	$default_values = array();
	foreach ($selected_contexts as $context_name) {
		$default_values[$context_name] = 1;
	}
	$form['overview'] = array(
		'#prefix' => '<br/>',	
		'#type' => 'tableselect',
		'#header' => $header,
		'#options' => $rows,
		'#default_value' => $default_values,
		'#advanced_select' => FALSE,
		'#empty' => t('No ratings found in the system'),
	);
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Update'),
		'#description' => t('Updates the detail table'),
		'#validate' => array('ting_search_context_overview_form_validate'),
		'#submit' =>  array('ting_search_context_overview_form_submit'),
	);

	// If any contexts is selected in the overview table, we show the detail
	// table with all the nodes rated in the selected contexts.
	if (!empty($selected_contexts)) {
		$header = array(
			'title' => array('data' => t('Title'), 'field' => 'n.title'),
			'type' => array('data' => t('Type'), 'field' => 'n.type'),
			'status' => array('data' => t('Status'), 'field' => 'n.status'),
			'name' => array('data' => t('Context'), 'field' => 'name'),
			'rating' => array('data' => t('Rating'), 'field' => 'rating'),
		);
		$query = db_select('node', 'n')->extend('TableSort');
		$query->join('field_data_field_ting_search_context', 'fd', 
			'n.nid = fd.entity_id');
		$query->fields('n', array('nid', 'title', 'type', 'status'));
		$query->addField('fd', 'field_ting_search_context_name', 'name');
		$query->addField('fd', 'field_ting_search_context_rating', 'rating');
		$or_condition = db_or();
		foreach ($selected_contexts as $context_name) {
			$or_condition->condition('field_ting_search_context_name', $context_name);
		}
		$query->condition($or_condition);
		$result = $query->orderByHeader($header)->execute();
		$languages = language_list();
		$rows = array();
		foreach ($result as $row) {
			$row = (array) $row;
			$node = node_load($row['nid']);
			$langcode = entity_language('node', $node);
			$l_options = $langcode != LANGUAGE_NONE && isset($languages[$langcode]) ? 
				array('language' => $languages[$langcode]) : array();
			$rows[] = array(
				'title' => array(
					'data' => array(
						// Use #type link. See https://drupal.org/node/745272
						'#type' => 'link',
						'#title' => $row['title'],
						// We currently only support nodes so we can safely link to 'node/'
						'#href' => 'node/' . $row['nid'] . '/edit',
						'#options' => $l_options,
					),
				),
				'type' => check_plain(node_type_get_name($row['type'])),
				'status' => $row['status'] ? t('published') : t('not published'),
				'name' => $context_info[$row['name']]['label'],
				'rating' => $row['rating'],
			);
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