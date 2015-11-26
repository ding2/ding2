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

/**
 * Callback for the context overview administratition page.
 */
function ting_search_context_admin_contexts() {
	$output = array();
  if ($view = views_get_view('ting_search_context_contexts')) {
    $output = $view->preview('block_1');
  }
	return $output;
}

/**
 * Form-builder for the context form. Used when adding and editing contexts.
 *
 * @see ting_search_context_forms()
 * @see ting_search_context_admin_context_form_validate()
 * @see ting_search_context_admin_context_form_submit()
 * @see ting_search_context_admin_context_form_cancel()
 */
function ting_search_context_admin_context_form($form, &$form_state, $context = FALSE) {
	$form = array();

  if ($context) {
    // Save the context object in form_state for later use.
    $form_state['ting_search_context'] = $context;
  }

	$form['add_context'] = array(
		'#type' => 'fieldset',
		'#title' => t('Add context'),
	);
  $types = ting_search_context_get_types();
  // We don't allow creation or editing of system context types.
  if ($context && $context->type != 'system') {
    unset($types['system']);
  }
	$form['add_context']['type'] = array(
		'#type' => 'select',
		'#title' => t('Context type'),
		'#description' => t('Select the type of context to create'),
		'#options' => $types,
		'#default_value' => $context ? $context->type : 'search',
    '#disabled' => $context && $context->type == 'system',
	);
	$form['add_context']['name'] = array(
		'#type' => 'textfield',
		'#title' => t('Name'),
		'#description' => t('Enter the name of the context'),
		'#maxlength' => 255,
		'#required' => TRUE,
    '#default_value' => $context ? $context->name : '',
    '#disabled' => $context && $context->type == 'system',
	);
	$form['add_context']['search'] = array(
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
    '#default_value' => $context && $context->type == 'search' ? $context->search : '',
	);
	$form['add_context']['context'] = array(
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
    '#default_value' => $context && $context->type == 'subject' ? $context->context : '',
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
    '#default_value' => $context && $context->type == 'subject' ? $context->subjects : '',
	);

	// Form actions
	$form['actions'] = array('#type' => 'actions');
	$form['actions']['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save'),
    '#disabled' => $context && $context->type == 'system',
	);
  // Delete button
  if ($context && $context->type != 'system') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#submit' => array('ting_search_context_admin_context_form_delete'),
    );
  }
  $form['actions']['cancel'] = array(
    '#type' => 'submit',
    '#value' => t('Back'),
    '#submit' => array('ting_search_context_admin_context_form_cancel'),
    // Bypass form-validation since this is a cancel-button
    '#limit_validation_errors' => array(),
    '#weight' => 40,
  );
	return $form;
}

/**
 * Validation callback for the context form.
 *
 * @see ting_search_context_admin_context_form()
 */
function ting_search_context_admin_context_form_validate($form, &$form_state) {
	$type = $form_state['values']['type'];
  $context = isset($form_state['ting_search_context']) ? $form_state['ting_search_context'] : FALSE;
  $changed = FALSE;
  $is_new = !$context;

	if ($type == 'search') {
    // Don't let the user create identical search string contexts.
    $search_string = $form_state['values']['search'];

    if ($context) {
      $changed = mb_strtolower($search_string, 'UTF-8') !== mb_strtolower($context->search, 'UTF-8');
    }

    if ($is_new || $changed) {
      if ($identical = ting_search_context_search_string_context_exists($search_string)) {
        form_set_error('search_string', t('An identical seach string context already exists: %context', array(
              '%context' => check_plain($identical->name),
        )));
      }
    }
	}
	else {
		// Subject should be a comma separated list of single words containing
		// alpanumeric characters (case-insensitive).
		$subjects = $form_state['values']['subjects'];

    $trimmed_subjects = array();
		$invalid_subjects = array();
    $duplicate_subjects = array();
		foreach (explode(',', $subjects) as $key => $subject) {
			// The only modification we make:
      $subject = mb_strtolower(trim($subject));

      // Check for duplicate subjects.
      if (in_array($subject, $trimmed_subjects)) {
        // A subject may be duplicated more than once
        if (!in_array($subject, $duplicate_subjects)) {
          $duplicate_subjects[] = $subject;
        }
      }

      // We skip any empty subjects.
      if (!empty($subject)) {
        $trimmed_subjects[] = $subject;

        // UTF-8 compatible check for non-alpahnumeric characters:
        // http://stackoverflow.com/questions/7271607/remove-non-alphanumeric-characters-including-%C3%9F-%C3%8A-etc-from-a-string
        if (preg_match('/[^\p{L}\p{N}]/u', $subject) || preg_match('/\s/', $subject)) {
          $invalid_subjects[] = $subject;
        }
      }
		}

    $error_messages = array();
    // Inform the user of invalid subjects, if any.
    if (!empty($invalid_subjects)) {
      $invalid_subjects = implode(', ', $invalid_subjects);
      $error_messages[] = t('Subjects should be a single word containing alpanumeric characters (%subjects)', array(
        '%subjects' => check_plain($invalid_subjects),
      ));
    }
    // Inform the user of duplicate subjects, if any.
    if (!empty($duplicate_subjects)) {
      $duplicate_subjects = implode(', ', $duplicate_subjects);
      $error_messages[] = t('There\'s duplicate subjects (%subjects)', array(
        '%subjects' => check_plain($duplicate_subjects),
      ));
    }

    if ($context) {
      $changed = $subjects !== $context->subjects;
    }
    // Don't let the user create identical subject contexts.
    if ($is_new || $changed) {
      if ($identical = ting_search_context_subject_context_exists($trimmed_subjects)) {
        $error_messages[] = t('An identical subject context already exists: %identical', array(
          '%identical' => check_plain($identical->name),
        ));
      }
    }

    if (!empty($error_messages)) {
      form_set_error('subjects', theme('item_list', array('items' => $error_messages)));
    }

		// Recreate the input string with the trimmed subjects.
		$subjects = implode(', ', $trimmed_subjects);
    $form_state['values']['subjects'] = $subjects;
    // This will present the corrected string to the user.
		$form_state['complete form']['add_context']['subjects']['#value'] = $subjects;
	}
}

/**
 * Submit callback for the context form.
 *
 * @see ting_search_context_admin_context_form().
 */
function ting_search_context_admin_context_form_submit($form, &$form_state) {
  $context = new stdClass();

  // Prepare the context object for ting_search_context_save().
  $context->type = $form_state['values']['type'];
  $context->name = $form_state['values']['name'];

  switch ($context->type) {
    case 'search':
      $context->search = $form_state['values']['search'];
      break;
    case 'subject':
      $context->context = $form_state['values']['context'];
      $context->subjects = $form_state['values']['subjects'];
  }

  if (isset($form_state['ting_search_context'])) {
    $context->context_id = $form_state['ting_search_context']->context_id;
    $context->is_new = FALSE;
  }
  else {
    $context->is_new = TRUE;
  }

  // Save, set message and go back,
  if (ting_search_context_save($context)) {
    drupal_set_message(t('Context saved'));
  }
  else {
    drupal_set_message(t('Something went wrong !op %context.', array(
      '!op' => empty($context->context_id) ? 'saving' : 'updating',
      '%context' => $context->name ? $context->name : 'Unknown',
    )), 'error');
  }
	$form_state['redirect'] = 'admin/config/ting/ting-search-context/contexts';
}

/**
 * Submit handler for the delete button on the context form
 */
function ting_search_context_admin_context_form_delete($form, &$form_state) {
  // Pass along any destination parameter set from previous pages
  $destination = array();
  if (isset($_GET['destination'])) {
    $destination = drupal_get_destination();
    unset($_GET['destination']);
  }
  // Should allways be set since this is only available on the edit form.
  $context_id = $form_state['ting_search_context']->context_id;
  $path = 'admin/config/ting/ting-search-context/contexts/' . $context_id .'/delete';
  $form_state['redirect'] = array($path, array('query' => $destination));
}

/**
 * Submit calback for the cancel callback on the context form.
 *
 * @see ting_search_context_admin_context_form()
 */
function ting_search_context_admin_context_form_cancel($form, &$form_state) {
	// Go back to contexts settings (or destination if parameter is set)
	$form_state['redirect'] = 'admin/config/ting/ting-search-context/contexts';
}

/**
 * Form builder for the context delete confirm form.
 */
function ting_search_context_admin_context_delete_confirm_form($form, &$form_state, $context) {
  $ratings = ting_search_context_ratings_load($context->context_id);

  // Save the context and it's associated ratings for later processing.
  $form['ting_search_context']['context'] = array('#type' => 'value', '#value' => $context);
  $form['ting_search_context']['ratings'] = array('#type' => 'value', '#value' => $ratings);

  $message = format_plural(count($ratings),
    'This action cannot be undone and will delete 1 associated rating.',
    'This action cannot be undone and will delete @count associated ratings.'
  );

  return confirm_form($form,
    t('Are you sure you want to delete %context?', array('%context' => $context->name)),
    'admin/config/ting/ting-search-context/contexts/' . $context->context_id . '/edit',
    $message,
    t('delete'),
    t('cancel')
  );
}

/**
 * Submit hanlder for the context delete confirm form.
 */
function ting_search_context_admin_context_delete_confirm_form_submit($form, &$form_state) {
  $context = $form_state['values']['context'];
  $ratings = $form_state['values']['ratings'];

  if (ting_search_context_delete($context->context_id)) {
    $message = t('Context %context and !ratings deleted', array(
      '%context' => $context->name,
      '!ratings' => format_plural(count($ratings), '1 associated rating', '@count associated ratings'),
    ));

    drupal_set_message($message);
  }
  else {
    $params = array('%context' => $context->name);
    drupal_set_message(t('Something went wrong deleting %context. See log for further details'), $params);
  }

  $form_state['redirect'] = 'admin/config/ting/ting-search-context/contexts';
}

/**
 * Form builder (admin/config/ding/searchcontext)
 * Admin form to configure position of related content on search page
 */
function ting_search_context_admin_settings_form($form, &$form_state) {
  $form = array();

  $missing = ting_search_context_get_missing_facets();
  if (!empty($missing)) {
    // Prepare a status array.
    $status = array(
      'missing' => $missing,
      'required' => ting_search_context_get_required_facets(),
    );

    $form['ting_search_context_status'] = array(
      '#type' => 'item',
      '#title' => t('Status'),
      '#markup' => theme('ting_search_context_status', array('status' => $status))
    );
  }

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

  // Add custom submit handler to clear cache. This will ensure that the changes
  // are reflected at once and for all users (this will also clear varnish
  // cache).
  $form['#submit'][] = 'ding_search_context_admin_settings_submit';

  return $form;
}

/**
 * Submit function to clear cache on form submit. Deletes all cid's starting with /search/ting.
 */
function ding_search_context_admin_settings_submit($form, &$form_state) {
  $url = url('search/ting/',  array('absolute' => TRUE));
  cache_clear_all($url, 'cache_page', TRUE);
}
