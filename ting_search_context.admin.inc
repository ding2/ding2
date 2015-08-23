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
function ting_search_context_admin_rate_nodes() {
	$output = t('The rate nodes view wasn\'t found');
	if ($view = views_get_view('ting_search_context_rate_nodes')) {
		$output = $view->preview('block_1');
	}
	return $output;
}


function ting_search_context_admin_contexts() {
	$output = array();
	return $output;
}

function ting_search_context_admin_context_form($form, &$form_state, $context_id = NULL) {
	$form = array();

	$form['add_context'] = array(
		'#type' => 'fieldset',
		'#title' => t('Add context'),
	);
	$form['add_context']['type'] = array(
		'#type' => 'select',
		'#title' => t('Context type'),
		'#description' => t('Select the type of context to create'),
		'#options' => array(
			'search' => t('Search string context'),
			'subject' => t('Subject context'),
		),
		'#default_value' => 'search',
	);
	$form['add_context']['name'] = array(
		'#type' => 'textfield',
		'#title' => t('Name'),
		'#description' => t('Enter the name of the context'),
		'#maxlength' => 255,
		'#required' => TRUE,
	);
	$form['add_context']['search_string'] = array(
		'#type' => 'textfield',
		'#title' => t('Search string'),
		'#description' => t('Enter the search string'),
		'#maxlength' => 255,
		'#states' => array(
			'visible' => array(
				':input[name="type"]' => array('value' => 'search'),
			),
			'required' => array(
				':input[name="type"]' => array('value' => 'search'),
			),
		),
	);
	$form['add_context']['parent_context'] = array(
		'#type' => 'select',
		'#title' => t('Parent context'),
		'#description' => t('Select the parent context'),
		'#options' => array(
			'voksen_fag' => t('Voksen faglitteratur'),
			'voksen_skøn' => t('Voksen skønlitteratur'),
			'børne_fag' => t('Børne faglitteratur'),
			'børne_skøn' => t('Børne skønlitteratur'),
		),
		'#states' => array(
			'visible' => array(
				':input[name="type"]' => array('value' => 'subject'),
			),
		),
	);
	$form['add_context']['subjects'] = array(
		'#type' => 'textfield',
		'#title' => t('Subjects'),
		'#description' => t('Enter the subjects seperated by commas'),
		'#maxlength' => 255,
		'#states' => array(
			'visible' => array(
				':input[name="type"]' => array('value' => 'subject'),
			),
			'required' => array(
				':input[name="type"]' => array('value' => 'subject'),
			),
		),
	);

	// Form actions
	$form['actions'] = array('#type' => 'actions');
	$form['actions']['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save'),
	);
  $form['actions']['cancel'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel'),
    '#submit' => array('ting_search_context_admin_context_form_cancel'),
    // Bypass form-validation since this is a cancel-button
    '#limit_validation_errors' => array(),
    '#weight' => 40,
  );
	return $form;
}

function ting_search_context_admin_context_form_validate($form, &$form_state) {
	$type = $form_state['values']['type'];

	if ($type == 'search') {

	}
	else {
		// Subject should be a comma separated list of single words containing
		// alpanumeric characters (case-insensitive).
		// We perform some basic trimming and validation here, so that user doesn't
		// end up creating an unusable subject context.
		// TODO: alphanumeric or alphabetic?
		$subjects = $form_state['values']['subjects'];

		$trimmed_subjects = array();
		$invalid_subjects = array();
		// PHP provides a utility function to parse comma-separed list into array:
		foreach (str_getcsv($subjects) as $subject) {
			// The only modification we make:
			$subject = trim($subject);
			$trimmed_subjects[] = $subject;

			// TODO: Use regexp instead to allow utf8
			if (!ctype_alnum($subject)) {
				$invalid_subjects[] = $subject;
			}
			// Check for whitespaces
			else if (preg_match('/\s/', $subject)) {
				$invalid_subjects[] = $subject;
			}
		}

		// Recreate the input string with the trimmed subjects.
		$subjects = array_shift($trimmed_subjects) . '';
		foreach ($trimmed_subjects as $subject) {
			$subjects .= ', ' . $subject;
		}
		$form_state['complete form']['add_context']['subjects']['#value'] = $subjects;

		if (!empty($invalid_subjects)) {
			$subjects = array_shift($invalid_subjects) . '';
			foreach ($invalid_subjects as $subject) {
				$subjects .= ', ' . $subject;
			}
			form_set_error('subjects', t('Subjects should be a single word containing alpanumeric characters (@subjects)', array(
				'@subjects' => $subjects
			)));
		}
	}
}

function ting_search_context_admin_context_form_submit($form, &$form_state) {
	$type = $form_state['values']['type'];
	$name = $form_state['values']['name'];

	// TODO: Error handling
	switch ($type) {
		case 'search':
			$search_string = $form_state['values']['search_string'];
			ting_search_context_save_context($type, $name, $search_string);
			break;
		case 'subject':
			$context = $form_state['values']['parent_context'];
			$subjects = $form_state['values']['subjects'];
			ting_search_context_save_context($type, $name, $context, $subjects);
			break;
	}

	// Set message and go back,
	drupal_set_message(t('Context saved'));
	$form_state['redirect'] = 'admin/config/ting/ting-search-context/contexts';
}

function ting_search_context_admin_context_form_cancel($form, &$form_state) {
	// Go back to contexts settings (or destination if parameter is set)
	$form_state['redirect'] = 'admin/config/ting/ting-search-context/contexts';
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
