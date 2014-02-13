<?php

/**
 * @file
 *
 * Contains admin page callback for ting search context module.
 */

/**
 * Form builder (admin/content/ting-search-context)
 */
function ting_search_context_admin_form($form, &$form_state) {
	$form['filter'] = array(
		'#type' => 'fieldset',
		'#title' => t('Show only items where'),
		'#tree' => FALSE,
	);
	
	return $form;
}