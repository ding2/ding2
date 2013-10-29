<?php
/**
 * @file
 * Panels pane to display the different search engine(s) available as radio input
 * fields (facets).
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
  $block = new stdClass();

  $links = array();

  // Find search backends.
  $backends = search_get_info();
  $default = search_get_default_module_info();


  $keys = NULL;
  if (!empty($context) && isset($context->data)) {
    $keys = $context->data;
  }

  foreach ($backends as $name => $backend) {
    // Get conditions (facets etc.).
    $conditions = NULL;
    if (isset($backend['conditions_callback']) && function_exists($backend['conditions_callback'])) {
      // Build an optional array of more search conditions.
      $conditions = $backend['conditions_callback']($keys);
    }

    // Create search path.
    $path = 'search/' . $backend['path'] . '/' . $keys;
    if (!empty($conditions)) {
      $path .= '?';
      // Conditions found, we need to add them (facets and sort).
      // @todo: is there a better way to do this?
      foreach ($conditions as $index => $condition) {
        if (is_array($condition)) {
          foreach ($condition as $i => $value) {
            $path .= $index . '[' . $i . ']=' . $value . '&';
          }
        }
        else {
          if (!empty($condition)) {
            $path .= $index . '=' . $condition . '&';
          }
        }
      }
      $path = substr($path, 0, -1);
    }

    $weight = 0;
    if ($default['module'] == $backend['module']) {
      $weight = -50;
    }
    $links[$name] = array(
      '#theme' => 'link',
      '#text' => t($backend['title']),
      '#path' => $path,
      '#options' => array(
        'attributes' => array(
          'title' => $backend['title'],
        ),
        'html' => FALSE,
      ),
      '#weight' => $weight,
    );
  }

  $block->title = t('Search backends');
  $block->content = $links;

  return $block;
}

/**
 * Enable admin settings page.
 */
function ting_search_backend_engines_content_type_edit_form($form, &$form_state) {
  return $form;
}

