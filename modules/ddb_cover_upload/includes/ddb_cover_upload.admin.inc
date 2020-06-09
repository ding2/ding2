<?php

/**
 * @file
 * Admin interface for handling uploads to cover service.
 */

/**
 * Returns the list of steps and their associated forms.
 *
 * @return array
 *   List of steps and their forms.
 */
function _ddb_cover_upload_form_steps() {
  return array(
    DDB_COVER_UPLOAD_CONDITIONS => array(
      'form' => 'ddb_cover_upload_conditions',
      'step_title' => t('First time use'),
    ),
    DDB_COVER_UPLOAD_SEARCH => array(
      'form' => 'ddb_cover_upload_material',
      'step_title' => t('Select material'),
    ),
    DDB_COVER_UPLOAD_IMAGE_EDITOR => array(
      'form' => 'ddb_cover_upload_image_upload',
      'step_title' => t('Select image'),
    ),
    DDB_COVER_UPLOAD_METADATA => array(
      'form' => 'ddb_cover_upload_meta',
      'step_title' => t('Verify image'),
    ),
    DDB_COVER_UPLOAD_UPLOAD => array(
      'form' => 'ddb_cover_upload_client_upload',
      'step_title' => t('Upload image'),
    ),
  );
}

/**
 * The primary form builder for the multi-step form.
 *
 * This will include the rest of the form steps defined.
 *
 * This form has two defined submit handlers to process the different steps:
 *  - Previous: handles the way to get back one step in the wizard.
 *  - Next:     handles each step form submission,
 *
 * The third handler, the finish button handler, is the default form_submit
 * handler used to process the information.
 *
 * @param array $form
 *   The form element.
 * @param array $form_state
 *   The state of the form.
 *
 * @return array
 *   The full form including all steps.
 */
function ddb_cover_upload_form(array $form, array &$form_state) {
  // Initialize a description of the steps for the wizard.
  if (empty($form_state['step'])) {
    // This array contains the function to be called at each step to get the
    // relevant form elements. It will also store state information for each
    // step.
    $form_state['step_information'] = _ddb_cover_upload_form_steps();

    // Side effect here is that ´$form_state['step'] gets set.
    _ddb_cover_upload_determine_step(drupal_get_query_parameters(), $form_state);
  }

  // Get current step.
  $step = $form_state['step'];

  // Set title for step.
  drupal_set_title(_ddb_cover_upload_get_title($step, $form_state));

  // We use #limit_validation_errors to skip all complaints about validation
  // when using the back button. The values entered will be discarded, but they
  // will not be validated, which would be annoying in a "back" button.
  if ($step > DDB_COVER_UPLOAD_SEARCH && $step !== DDB_COVER_UPLOAD_UPLOAD) {
    $form['prev'] = array(
      '#type' => 'submit',
      '#value' => t('Previous'),
      '#name' => 'prev',
      '#weight' => 70,
      '#submit' => array('ddb_cover_upload_previous_submit'),
      '#limit_validation_errors' => array(),
    );
  }

  // Show the Next button only if there are more steps defined.
  if ($step < DDB_COVER_UPLOAD_UPLOAD) {
    $form['next'] = array(
      '#type' => 'submit',
      '#value' => t('Next'),
      '#name' => 'next',
      '#weight' => 80,
      '#submit' => array('ddb_cover_upload_next_submit'),
    );

    // Include each validation function defined for the different steps.
    $func = isset($form_state['step_information'][$step]['form']) ? $form_state['step_information'][$step]['form'] . '_validate' : NULL;
    if (!is_null($func) && function_exists($func)) {
      $form['next']['#validate'] = array($func);
    }
  }

  // Attach global assets to the form.
  $path = drupal_get_path('module', 'ddb_cover_upload');
  $form['#attached'] = array(
    'css' => array(
      $path . '/css/ddb_cover_upload.admin.css',
    ),
    'js' => array(),
    'library' => array(
      array('system', 'ui.dialog'),
    ),
  );

  // Call the function named in $form_state['step_information'] to get the
  // form elements to display for this step.
  $form = call_user_func($form_state['step_information'][$step]['form'], $form, $form_state);

  return $form;
}

/**
 * Accept terms of use of the form.
 *
 * @param array $form
 *   The form array.
 * @param array $form_state
 *   The state of the form.
 *
 * @return array
 *   The form for displaying and accepting terms of use.
 *
 * @throws \Exception
 *   Theme exception error.
 */
function ddb_cover_upload_conditions(array $form, array &$form_state) {
  $no_terms_set = t('[Contact DDB for copyright information and change module settings]');
  $terms = variable_get('ddb_cover_upload_terms_of_use', array('value' => 'Not configured yet!'))['value'];

  $form['ddb_cover_upload_conditions'] = array(
    '#theme' => 'ddb_cover_upload_conditions',
    '#copyright_text' => empty($terms) ? $no_terms_set : $terms,
  );

  $form['ddb_cover_upload_confirm'] = array(
    '#type' => 'checkbox',
    '#title' => t('I accept conditions'),
    '#required' => TRUE,
  );

  return $form;
}

/**
 * Select ting material step of the form.
 *
 * @param array $form
 *   The form array.
 * @param array $form_state
 *   The state of the form.
 *
 * @return array
 *   The form for referencing a material.
 *
 * @throws \Exception
 */
function ddb_cover_upload_material(array $form, array &$form_state) {
  $form['ddb_cover_upload'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'wrapper',
        'admin',
        'clearfix',
      ),
    ),
  );

  $form['ddb_cover_upload']['left'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'left',
      ),
    ),
  );

  $form['ddb_cover_upload']['left']['ddb_cover_upload_material'] = array(
    '#type' => 'textfield',
    '#title' => t('Material'),
    '#description' => t('Use the autocomplete to ensure that this value is always a data well PID.'),
    '#autocomplete_path' => 'admin/config/ting/ddb_cover_upload/autocomplete',
    '#required' => TRUE,
    '#default_value' => isset($form_state['values']['ddb_cover_upload_material']) ? $form_state['values']['ddb_cover_upload_material'] : '',
  );

  $form['ddb_cover_upload']['right'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'right',
      ),
    ),
  );

  $form['preview'] = array(
    '#type' => 'submit',
    '#value' => 'Preview',
    '#ajax' => array(
      'callback' => 'ddb_cover_upload_search_preview',
      'wrapper' => 'preview-wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  $content = FALSE;
  if (isset($form_state['values']['ddb_cover_upload_material'])) {
    $entity = ding_entity_load($form_state['values']['ddb_cover_upload_material'], 'ting_object');
    $content = ting_object_view($entity, 'teaser_full');
  }

  $form['ddb_cover_upload']['right']['results'] = array(
    '#theme' => 'ddb_cover_upload_search_preview',
    '#content' => $content,
  );

  return $form;
}

/**
 * Ajax form callback to render search preview.
 *
 * @param array $form
 *   The form array.
 * @param array $form_state
 *   The state of the form.
 *
 * @return string
 *   The rendered preview.
 *
 * @throws \Exception
 */
function ddb_cover_upload_search_preview(array $form, array $form_state) {
  $id = $form_state['values']['ddb_cover_upload_material'];

  $entity = ding_entity_load($id, 'ting_object');
  $content = FALSE;
  if ($entity) {
    $content = ting_object_view($entity, 'teaser_full');
  }

  $form['ddb_cover_upload']['right']['results'] = array(
    '#theme' => 'ddb_cover_upload_search_preview',
    '#content' => $content,
  );

  return $form['ddb_cover_upload']['right']['results'];
}

/**
 * Image upload step of the form.
 *
 * @param array $form
 *   The form array.
 * @param array $form_state
 *   The state of the form.
 *
 * @return array
 *   The form for image upload.
 *
 * @throws \Exception
 *   Theme exception error.
 */
function ddb_cover_upload_image_upload(array $form, array &$form_state) {
  $path = drupal_get_path('module', 'ddb_cover_upload');
  $form['#attached']['js'][] = array(
    'data' => array(
      'ddbCoverUpload' => array(
        'bashPath' => $path,
      ),
    ),
    'type' => 'setting',
  );

  // Load image editor and need support libraries.
  $form['#attached']['libraries_load'][] = array('fabric');
  $form['#attached']['libraries_load'][] = array('tui-color-picker');
  $form['#attached']['libraries_load'][] = array('tui-code-snippet');
  $form['#attached']['libraries_load'][] = array('tui-image-editor');

  // Custom JS to handle image upload and configuration of the image editor.
  $form['#attached']['js'][$path . '/js/ddb_cover_upload_ui.admin.js'] = array(
    'type' => 'file',
  );

  $form['image_editor'] = array(
    '#theme' => 'ddb_cover_upload_image_editor',
  );

  $form['is'] = array(
    '#type' => 'hidden',
    '#value' => $form_state['step_information'][DDB_COVER_UPLOAD_SEARCH]['stored_values']['ddb_cover_upload_material'],
  );

  // Build default image path that toast UI understands to load (hence the / first).
  $image = '/' . drupal_get_path('module', 'ddb_cover_upload') . '/images/default_cover.jpg';
  $step = $form_state['step_information'][DDB_COVER_UPLOAD_IMAGE_EDITOR];
  if (isset($step['stored_values']['image_file']) && $image !== $step['stored_values']['image_file']) {
    $image = file_create_url($form_state['step_information'][DDB_COVER_UPLOAD_IMAGE_EDITOR]['stored_values']['image_file']) . '?' . REQUEST_TIME;
  }
  else {
    // Disable next button, if no image have been uploaded yet.
    $form['next']['#attributes'] = array(
      'class' => array(
        'btn-form-submit',
        'disabled',
      ),
    );
  }
  $form['image_file'] = array(
    '#type' => 'hidden',
    // This needs to have an default value to allow JS to change the value.
    '#default_value' => $image,
  );

  // Add guidelines for best results.
  $form['best_result'] = array(
    '#theme' => 'ddb_cover_upload_best_result',
    '#weight' => 90,
  );

  return $form;
}

/**
 * Meta data step of the form.
 *
 * @param array $form
 *   The form array.
 * @param array $form_state
 *   The state of the form.
 *
 * @return array
 *   The form for image upload.
 *
 * @throws \Exception
 *   Theme exception error.
 */
function ddb_cover_upload_meta(array $form, array &$form_state) {
  // Add javascript to open dialog with information about usage of the service.
  $path = drupal_get_path('module', 'ddb_cover_upload');
  $form['#attached']['js'][$path . '/js/ddb_cover_upload_dialog.admin.js'] = array(
    'type' => 'file',
  );

  $form['ddb_cover_upload_meta'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'wrapper',
        'admin',
        'clearfix',
      ),
    ),
  );

  $form['ddb_cover_upload_meta']['right'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'right',
      ),
    ),
  );

  // Determine full path for image.
  $originalImagePath = $form_state['input']['image_file'];

  // Get metadata for original image.
  $originalImage = getimagesize($originalImagePath);
  $displayedImageUrl = file_create_url($originalImagePath) . '?' . REQUEST_TIME;

  $form_state['agency'] = variable_get('site_name', 'undefined');

  $form['ddb_cover_upload_meta']['left']['ddb_cover_upload_meta_data'] = array(
    '#markup' => '<div class="left form-wrapper"><img class="ddb-cover-upload__img--displayed" src="' . $displayedImageUrl . '"></div>',
  );

  // Get information about the entity and reuse view mode with minor changes.
  $material = FALSE;
  $entity = ding_entity_load($form_state['step_information'][1]['stored_values']['ddb_cover_upload_material']);
  if (FALSE !== $entity) {
    $material = ting_object_view($entity, 'teaser_full');
    $material['ting_author']['#label_display'] = 'inline';
    $keys = array('ting_cover', 'ting_title', 'ting_type', 'ting_abstract');
    foreach ($keys as $key) {
      unset($material[$key]);
    }
  }

  $form['ddb_cover_upload_meta']['right']['ddb_cover_upload_meta_data'] = array(
    '#theme' => 'ddb_cover_upload_meta_data',
    '#entity' => $entity,
    '#material' => $material,
    '#image_url' => $displayedImageUrl,
    '#meta_data' => array(
      'file_dimensions' => array('x' => $originalImage[0], 'y' => $originalImage[1]),
      'file_type' => $originalImage['mime'],
      'file_size' => filesize($originalImagePath),
      'agency' => $form_state['agency'],
    ),
  );

  $form['ddb_cover_upload_meta']['right']['ddb_cover_upload_meta_input'] = array(
    '#type' => 'textfield',
    '#title' => t('Image accreditation'),
    '#default_value' => isset($form_state['values']['ddb_cover_upload_meta_data']) ? $form_state['values']['ddb_cover_upload_meta_data'] : '',
    '#size' => 60,
    '#maxlength' => 128,
  );

  $no_terms_set = t('[Contact DDB for copyright information and change module settings]');
  $terms = variable_get('ddb_cover_upload_terms_of_use')['value'];
  $form['ddb_cover_upload_meta']['right']['ddb_cover_upload_meta_copyright'] = array(
    '#theme' => 'ddb_cover_upload_meta_copyright',
    '#copyright_text' => empty($terms) ? $no_terms_set : $terms,
  );

  return $form;
}

/**
 * Display cover submitted page.
 *
 * @param array $form
 *   The form array.
 * @param array $form_state
 *   The state of the form.
 *
 * @return array
 *   The form for image upload.
 *
 * @throws \Exception
 *   Theme exception error.
 */
function ddb_cover_upload_client_upload(array $form, array &$form_state) {
  $data = array();

  if (isset($form_state['step_information'])) {
    // Store data in session for using ajax to upload the information to the
    // upload service.
    $data = array(
      'pid' => $form_state['step_information'][DDB_COVER_UPLOAD_SEARCH]['stored_values']['ddb_cover_upload_material'],
      'image_uri' => $form_state['step_information'][DDB_COVER_UPLOAD_IMAGE_EDITOR]['stored_values']['image_file'],
      'accreditation' => $form_state['input']['ddb_cover_upload_meta_input'],
      'agency' => variable_get('ting_agency', ''),
    );
    $_SESSION['ddb_cover_upload_data'] = $data;
  }

  // Remove form step_information values to prevent re-submit of the data.
  unset($form_state['step_information']);
  unset($form_state['input']);

  $form['ddb_cover_upload_client_upload'] = [
    '#type' => 'container',
    '#attributes' => [
      'class' => [
        'wrapper',
        'admin',
        'clearfix',
      ],
    ],
  ];

  $image_url = '';
  if (isset($data['image_uri']) && file_exists(drupal_realpath($data['image_uri']))) {
    $image_url = file_create_url($data['image_uri']);
  }

  $form['ddb_cover_upload_client_upload']['#attached'] = array(
    'css' => array(
      drupal_get_path('module', 'ddb_cover_upload') . '/css/ddb_cover_upload.admin.css',
    ),
    'js' => array(
      drupal_get_path('module', 'ddb_cover_upload') . '/js/ddb_cover_upload_check_submission.admin.js',
    ),
  );

  $form['ddb_cover_upload_client_upload']['content'] = array(
    '#theme' => 'ddb_cover_upload_submitted',
    '#data' => $data,
    '#image' => $image_url,
  );

  return $form;
}

/**
 * Submit handler for the "previous" button.
 *
 * This function:
 * - Stores away $form_state['values']
 * - Decrements the step counter
 * - Replaces $form_state['values'] with the values from the previous state.
 * - Forces form rebuild.
 *
 * @param array $form
 *   The form element.
 * @param array $form_state
 *   The state of the form.
 */
function ddb_cover_upload_previous_submit(array $form, array &$form_state) {
  $current_step = &$form_state['step'];
  $form_state['step_information'][$current_step]['stored_values'] = $form_state['input'];
  if ($current_step > DDB_COVER_UPLOAD_SEARCH) {
    $current_step--;
    if (isset($form_state['step_information'][$current_step]['stored_values'])) {
      $form_state['values'] = $form_state['step_information'][$current_step]['stored_values'];
    }
  }
  $form_state['rebuild'] = TRUE;
}

/**
 * Submit handler for the 'next' button.
 *
 * This function:
 * - Saves away $form_state['values']
 * - Increments the step count.
 * - Replace $form_state['values'] from the last time we were at this page
 *   or with array() if we haven't been here before.
 * - Force form rebuild.
 *
 * @param array $form
 *   The form element.
 * @param array $form_state
 *   The state of the form.
 */
function ddb_cover_upload_next_submit(array $form, array &$form_state) {
  $current_step = &$form_state['step'];
  $form_state['step_information'][$current_step]['stored_values'] = $form_state['values'];

  if ($current_step === DDB_COVER_UPLOAD_CONDITIONS) {
    _ddb_cover_upload_save_conditions_acceptance();
  }

  if ($current_step < count($form_state['step_information'])) {
    $current_step++;
    if (!empty($form_state['step_information'][$current_step]['stored_values'])) {
      $form_state['values'] = $form_state['step_information'][$current_step]['stored_values'];
    }
    else {
      $form_state['values'] = array();
    }

    // Force rebuild with next step.
    $form_state['rebuild'] = TRUE;
  }
}

/**
 * Determine starting step when opening form.
 *
 * @param array $query
 *   The query parameters.
 * @param array $form_state
 *   The state of the form.
 */
function _ddb_cover_upload_determine_step(array $query, array &$form_state) {
  $form_state['step'] = DDB_COVER_UPLOAD_CONDITIONS;

  if (_ddb_cover_upload_is_conditions_accepted()) {
    $form_state['step'] = DDB_COVER_UPLOAD_SEARCH;

    // Also bypass material selection if pid is included as query parameter.
    if (isset($query['pid'])) {
      $form_state['step_information'][DDB_COVER_UPLOAD_SEARCH]['stored_values']['ddb_cover_upload_material'] = $query['pid'];
      $form_state['step'] = DDB_COVER_UPLOAD_IMAGE_EDITOR;
    }
  }
}

/**
 * Check if the state of conditions of usages acceptance.
 *
 * @return bool
 *   TRUE if they have been accepted else FALSE.
 */
function _ddb_cover_upload_is_conditions_accepted() {
  global $user;

  return isset($user->data['ddb_cover_upload_conditions_accepted']) ?
    $user->data['ddb_cover_upload_conditions_accepted'] :
    FALSE;
}

/**
 * Save usage acceptance.
 *
 * @param bool $value
 *   If TRUE it is accepted else FALSE. Default TRUE.
 *
 * @return bool
 *   TRUE if saved else FALSE.
 */
function _ddb_cover_upload_save_conditions_acceptance($value = TRUE) {
  global $user;

  try {
    $user->data['ddb_cover_upload_conditions_accepted'] = TRUE;
    user_save($user);
  }
  catch (Exception $exception) {
    drupal_set_message(t('Error saving user acceptance of usage conditions'), 'error');
    watchdog_exception('ddb_cover_upload', $exception);

    return FALSE;
  }

  return TRUE;
}

/**
 * Get a title for the form step.
 *
 * @param int $step
 *   Display title depending on steps.
 * @param array $form_state
 *   The state of the form.
 *
 * @return string
 *   The title to display.
 */
function _ddb_cover_upload_get_title($step, array $form_state) {
  if ($step == DDB_COVER_UPLOAD_CONDITIONS) {
    $title = t('Upload cover: @step_title', array('@step_title' => $form_state['step_information'][$step]['step_title']));
  }
  else {
    $title = t('Upload cover: Step @step - @step_title', array('@step' => $step, '@step_title' => $form_state['step_information'][$step]['step_title']));
  }

  return $title;
}

/**
 * Translate file size values from strings calculated bytes.
 *
 * @param string $val
 *   A string representation of file sizes.
 *
 * @return int
 *   A calculated value of bytes.
 */
function _ddb_cover_upload_return_bytes($val) {
  $val = trim($val);
  $last = strtolower($val[strlen($val) - 1]);
  $val = intval($val);
  switch ($last) {
    case 'g':
      $val *= 1024 * 1024 * 1024;
      break;

    case 'm':
      $val *= 1024 * 1024;
      break;

    case 'k':
      $val *= 1024;
      break;
  }

  return $val;
}
