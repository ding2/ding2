<?php

/**
 * @file
 * Contains admin page callback for ting search context module.
 */

/**
 * Page callback (admin/content/ting-search-context).
 *
 * Renders the rate nodes VBO view.
 */
function ting_search_context_admin_rate_nodes() {
  $output = t("The rate nodes view wasn't found");
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
  if (!$context) {
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

  // Form actions.
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#disabled' => $context && $context->type == 'system',
  );
  // Delete button.
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
    // Bypass form-validation since this is a cancel-button.
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
    // Format and validate the subjects.
    $subjects = $form_state['values']['subjects'];

    $trimmed_subjects = array();
    $invalid_subjects = array();
    $duplicate_subjects = array();
    foreach (explode(',', $subjects) as $key => $subject) {
      // Prepare the subject string for validation.
      $subject = mb_strtolower(trim($subject));
      // Ensure only 1 whitespace.
      $subject = preg_replace('/[\s]+/', ' ', $subject);

      // Check for duplicate subjects.
      if (in_array($subject, $trimmed_subjects)) {
        // A subject may be duplicated more than once.
        if (!in_array($subject, $duplicate_subjects)) {
          $duplicate_subjects[] = $subject;
        }
      }

      // Validation (skip empty).
      if (!empty($subject)) {
        $trimmed_subjects[] = $subject;

        if (_ting_search_context_validate_subject($subject)) {
          $invalid_subjects[] = $subject;
        }
      }
    }

    // We want to show all subject related errors at once. Unfortunately, this
    // is not possible by calling form_set_error separately for all errors. So
    // we collect the error messages in an array and use an "implode hack" to
    // show them at once.
    $error_messages = array();
    // Inform the user of invalid subjects, if any.
    if (!empty($invalid_subjects)) {
      $invalid_subjects = implode(', ', $invalid_subjects);
      $error_messages[] = t('Subjects should only contain alpanumeric characters, whitespaces and dashes. (%subjects)', array(
        '%subjects' => check_plain($invalid_subjects),
      ));
    }
    // Inform the user of duplicate subjects, if any.
    if (!empty($duplicate_subjects)) {
      $duplicate_subjects = implode(', ', $duplicate_subjects);
      $error_messages[] = t("There's duplicate subjects (%subjects)", array(
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
      form_set_error('subjects', implode('</li><li>', $error_messages));
    }

    // Recreate the input string with the trimmed subjects.
    $subjects = implode(', ', $trimmed_subjects);
    $form_state['values']['subjects'] = $subjects;
    // This will present the corrected string to the user.
    $form_state['complete form']['add_context']['subjects']['#value'] = $subjects;
  }
}

/**
 * Helper function to validate a subject string.
 *
 * @see ting_search_context_admin_context_form_validate()
 */
function _ting_search_context_validate_subject($subject) {
  // \p{L} matches a single code point in the category "letter".
  // \p{N} matches any kind of numeric character in any script.
  // The \u modifier enabled UTF-8.
  // Allow for whitespaces and dashes.
  // http://stackoverflow.com/questions/7271607/remove-non-alphanumeric-characters-including-%C3%9F-%C3%8A-etc-from-a-string
  return preg_match('/[^\p{L}\p{N}\s-]/u', $subject);
}

/**
 * Submit callback for the context form.
 *
 * @see ting_search_context_admin_context_form()
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
  }

  // Save, set message and go back,.
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
 * Submit handler for the delete button on the context form.
 */
function ting_search_context_admin_context_form_delete($form, &$form_state) {
  // Pass along any destination parameter set from previous pages.
  $destination = array();
  if (isset($_GET['destination'])) {
    $destination = drupal_get_destination();
    unset($_GET['destination']);
  }
  // Should allways be set since this is only available on the edit form.
  $context_id = $form_state['ting_search_context']->context_id;
  $path = 'admin/config/ting/ting-search-context/contexts/' . $context_id . '/delete';
  $form_state['redirect'] = array($path, array('query' => $destination));
}

/**
 * Submit calback for the cancel callback on the context form.
 *
 * @see ting_search_context_admin_context_form()
 */
function ting_search_context_admin_context_form_cancel($form, &$form_state) {
  // Go back to contexts settings (or destination if parameter is set).
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
 * Submit handler for the context delete confirm form.
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
 * Form builder (admin/config/ding/searchcontext).
 *
 * Admin form to configure position of related content on search page.
 */
function ting_search_context_admin_settings_form($form, &$form_state) {
  $form['ting_search_context_admin_settings_form'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings for the Ting Search Context Module'),
  );

  $form['ting_search_context_admin_settings_form']['ting_search_context_position'] = array(
    '#type' => 'radios',
    '#title' => t('Position'),
    '#description' => t('Select the position of related content on the search page. On small screens related content is always displayed at the bottom of the page.'),
    '#options' => ting_search_context_get_positions(),
    '#default_value' => variable_get('ting_search_context_position', 'js-below-search-result'),
  );

  $form['ting_search_context_admin_settings_form']['ting_search_context_pass_ratio'] = array(
    '#type' => 'textfield',
    '#title' => t('Pass ratio'),
    '#description' => t('The ratio of search results needed to qualify as a context. If no context qualifies the search is put in the neutral context. Minimum 0.5. Maximum 1.0.'),
    '#default_value' => variable_get('ting_search_context_pass_ratio', 0.60),
  );

  $form['ting_search_context_admin_settings_form']['ting_search_context_audio_types'] = array(
    '#type' => 'textfield',
    '#title' => t('Audio types'),
    '#description' => t('Definition of audio types. Seperated by comma'),
    '#default_value' => variable_get('ting_search_context_audio_types', 'lydbog (net),lydbog (cd-mp3),lydbog (cd)'),
  );
  $form['ting_search_context_admin_settings_form']['ting_search_context_film_types'] = array(
    '#type' => 'textfield',
    '#title' => t('Film types'),
    '#description' => t('Definition of film types. Seperated by comma'),
    '#default_value' => variable_get('ting_search_context_film_types', 'film (net),dvd,blue-ray'),
  );
  $form['ting_search_context_admin_settings_form']['ting_search_context_music_types'] = array(
    '#type' => 'textfield',
    '#title' => t('Music types'),
    '#description' => t('Definition of music types. Seperated by comma'),
    '#default_value' => variable_get('ting_search_context_music_types', 'cd (musik),grammofonplade,node'),
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
 * Submit function to clear cache on form submit.
 *
 * Deletes all cid's starting with /search/ting.
 */
function ding_search_context_admin_settings_submit($form, &$form_state) {
  $url = url('search/ting/', array('absolute' => TRUE));
  cache_clear_all($url, 'cache_page', TRUE);
}

/**
 * Form builder for image settings.
 */
function ting_search_context_admin_fallback_images($form, &$form_state) {
  $form['ting_search_context_fallback_images'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
    '#title' => t('Fallback images'),
    '#description' => t('Used when displaying rated nodes without an image.'),
    '#attributes' => array(
      'class' => array('ting-search-context-fallaback-images'),
    ),
  );
  $form['ting_search_context_fallback_images']['image_new'] = array(
    '#type' => 'fieldset',
    '#title' => t('Upload new image'),
  );
  $form['ting_search_context_fallback_images']['image_new']['fid'] = array(
    '#type' => 'managed_file',
    '#default_value' => '',
    '#process' => array('file_managed_file_process', 'ting_search_context_file_process'),
    '#upload_location' => 'public://ting_search_context/',
    '#upload_validators' => array(
      'file_validate_extensions' => array('gif png jpg jpeg'),
      // 2MB.
      'file_validate_size' => array(2 * 1024 * 1024),
    ),
  );

  $form['ting_search_context_fallback_images']['existing_title'] = array(
    '#type' => 'item',
    '#title' => t('Existing images'),
  );

  $count = 1;

  foreach (variable_get('ting_search_context_fallback_images', array()) as $fid) {
    $form['ting_search_context_fallback_images']['image_' . $fid] = array(
      '#type' => 'fieldset',
      '#title' => t('Image !count', array('!count' => $count)),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    // Use a modified managed file element to clean up permanent files.
    // See: ting_search_context_file_process()
    $form['ting_search_context_fallback_images']['image_' . $fid]['fid'] = array(
      '#type' => 'managed_file',
      '#default_value' => $fid,
      '#process' => array('file_managed_file_process', 'ting_search_context_file_process'),
      '#upload_location' => 'public://ting_search_context/',
      '#upload_validators' => array(
        'file_validate_extensions' => array('gif png jpg jpeg'),
        // 2MB.
        'file_validate_size' => array(2 * 1024 * 1024),
      ),
    );
    $count++;
  }

  $path = drupal_get_path('module', 'ting_search_context');
  $form['#attached']['css'][] = $path . '/css/ting_search_context.admin.css';

  return $form;
}

/**
 * Submit callback for fallback images form.
 */
function ting_search_context_admin_fallback_images_submit($form, &$form_state) {
  $fallback_images = array();

  foreach ($form_state['values']['ting_search_context_fallback_images'] as $value) {
    if ($value['fid'] != 0) {
      $image = file_load($value['fid']);

      // New upload; upgrade to permanent and add file usage.
      if ($image->status == 0) {
        $image->status = FILE_STATUS_PERMANENT;
        file_save($image);
        file_usage_add($image, 'ting_search_context', 'fallback_image', 1);

        drupal_set_message(t('Fallback image @image was uploaded and saved.', array(
          '@image' => $image->filename,
        )));
      }

      $fallback_images[] = $image->fid;
    }
  }

  // Save references.
  variable_set('ting_search_context_fallback_images', $fallback_images);
}

/**
 * Process function for fallback image managed file element.
 *
 * @see file_managed_file_process()
 */
function ting_search_context_file_process($element, &$form_state, $form) {
  $image = $element['#file'] ? $element['#file'] : FALSE;

  if ($image) {
    // Clean up file usage when removing permanent files. Also disable AJAX
    // funtionality to give better feedback in the UI.
    // When the user is removing a new upload without "saving", the file will
    // be temporaty and we let the faster default AJAX handling take care of
    // deleting the file.
    if ($image->status == FILE_STATUS_PERMANENT) {
      $element['remove_button']['#submit'] = array(
        'ting_search_context_file_remove_submit',
      );
      unset($element['remove_button']['#ajax']);
      $element['remove_button']['#prefix'] = '<br>';
    }
    else {
      $element['remove_button']['#value'] = t('Cancel');
      $element['save_button'] = array(
        '#prefix' => '<br>',
        '#type' => 'submit',
        '#value' => t('Save'),
        '#weight' => -6,
      );
    }

    // Show a preview of the image. It's done here to ensure that it's shown
    // right after AJAX upload.
    $element['preview'] = array(
      '#type' => 'markup',
      '#markup' => theme('image_style', array(
        'path' => $image->uri,
        'style_name' => 'ting_search_context_thumbnail',
        'attributes' => array(
          'class' => 'preview',
        ),
      )),
      '#weight' => -40,
      '#suffix' => '<br>',
    );
  }
  else {
    $element['upload_button']['#prefix'] = '<br>';
  }

  return $element;
}

/**
 * Submit callback for remove button on permanent files.
 */
function ting_search_context_file_remove_submit($form, &$form_state) {
  // A fancy way to get the triggering remove button element.
  // see: file_managed_file_submit()
  $parents = $form_state['triggering_element']['#array_parents'];
  array_pop($parents);
  $element = drupal_array_get_nested_value($form, $parents);

  $image = $element['#file'];
  file_usage_delete($image, 'ting_search_context', 'fallback_image', 1);
  file_delete($image);
  drupal_set_message(t('Fallback image @image was deleted.', array(
    '@image' => $image->filename,
  )));

  // Remove our reference to the file.
  $fallback_images = variable_get('ting_search_context_fallback_images', array());
  if (($key = array_search($image->fid, $fallback_images)) !== FALSE) {
    unset($fallback_images[$key]);
  }
  variable_set('ting_search_context_fallback_images', $fallback_images);
}
