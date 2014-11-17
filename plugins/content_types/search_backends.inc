<?php
/**
 * @file
 * Panels pane to display the different search engine(s) available as radio
 * input fields (facets).
 */

$plugin = array(
  'title' => t('Ting search - backend engines'),
  'description' => t("Display the search engines as facets."),
  'single' => TRUE,
  'content_types' => array('ting_search'),
  'render callback' => 'ting_search_backend_engines_content_type_render',
  'category' => t('Ting'),
  'render last' => TRUE,
  'required context' => new ctools_context_required(t('Keywords'), 'string'),
);

/**
 * Render the ting search results amount block.
 */
function ting_search_backend_engines_content_type_render($subtype, $conf, $panel_args, $context) {
  $options = array();

  // Find search backends.
  $backends = search_get_info();
  $default = search_get_default_module_info();
  $default_value = $default['module'];

  // Search keys.
  $keys = NULL;
  if (!empty($context) && isset($context->data)) {
    $keys = $context->data;
  }

  // Create options for each backend.
  foreach ($backends as $name => $backend) {
    // Get conditions (facets etc.).
    $conditions = NULL;
    if (isset($backend['conditions_callback']) && function_exists($backend['conditions_callback'])) {
      // Build an optional array of more search conditions.
      $conditions = $backend['conditions_callback']($keys);
    }

    // Create search path.
    $path = 'search/' . $backend['path'] . '/' . $keys;
    if (empty($conditions['sort'])) {
      // Remove sort condition, if is the empty string.
      unset($conditions['sort']);
    }

    // Create the option as a link.
    $txt = format_string('Search @backend', array('@backend' => $backend['title']));
    $title = l(t($txt), $path, array('query' => $conditions));

    // Set default value.
    if (arg(1) == $backend['module']) {
      $default_value = $backend['module'];
    }

    // Add default option to the start of the array.
    if ($default['module'] == $backend['module']) {
      array_unshift($options, $title);
    }
    else {
      $options[$backend['module']] = $title;
    }
  }

  // Create a form with the radio buttons.
  $form = drupal_get_form('ting_search_backend_engines_form', $options, $default_value);

  // Create the output.
  $block = new stdClass();
  $block->content = $form;

  return $block;
}

/**
 * Implements hook_form().
 *
 * Defines the select search engine backend with radio buttons.
 */
function ting_search_backend_engines_form($form, &$form_state, $options, $default) {
  $form = array(
    '#token' => FALSE,
    '#attached' => array(
      'js' => array(
        // Script to handle usability in the frontend (clicks).
        drupal_get_path('module', 'ting_search') . '/js/ting_search_backends.js',
      ),
    ),
  );

  $form['backends'] = array(
    '#type' => 'fieldset',
    '#title' => t('Search in'),
  );

  $form['backends']['searches'] = array(
    '#type' => 'radios',
    '#required' => FALSE,
    '#options' => $options,
    '#default_value' => $default,
  );

  return $form;
}

/**
 * Enable admin settings page.
 */
function ting_search_backend_engines_content_type_edit_form($form, &$form_state) {
  return $form;
}

