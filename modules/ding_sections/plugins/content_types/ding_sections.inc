<?php
/**
 * Custom display for sections.
 */
$plugin = [
  'title' => t('Section Group'),
  'description' => t('Display Sections in a "Themes"-like manner.'),
  'category' => t('Ding!'),
  'single' => TRUE,
  'edit form' => 'ding_sections_content_type_edit_form',
  'render callback' => 'ding_sections_content_type_render',
];

/**
 * Panel pane settings form.
 */
function ding_sections_content_type_edit_form($form, &$form_state) {
  form_load_include($form_state, 'inc', 'ding_sections', 'plugins/content_types/ding_sections');

  $conf = $form_state['conf'];

  // Render selected terms.
  $form['ding_sections_wrapper']['sections_content']['sections_content_wrapper']['ding_sections_sections']['selected_sections'] = [
    '#prefix' => '<div id="ding_sections-selected-sections">',
    '#suffix' => '</div>',
    '#theme' => 'ding_sections_items_table',
    '#tree' => TRUE,
  ];

  $delta = 0;
  $weight = 0;
  $max_weight = $weight;
  $section_count = NULL;
  $filter_count = NULL;

  if (isset($form_state['values']['selected_sections_count'])) {
    $section_count = $form_state['values']['selected_sections_count'];
  }
  else {
    $section_count = empty($form_state['values']['selected_sections']) ? 1 : count($form_state['values']['selected_sections']);
  }

  if (!empty($conf['selected_sections'])) {
    $delta = count($conf['selected_sections']);
    foreach ($conf['selected_sections'] as $key => $term) {
      $weight = $term['weight'];
      $max_weight = ($max_weight < $weight) ? $weight : $max_weight;
      $form['ding_sections_wrapper']['sections_content']['sections_content_wrapper']['ding_sections_sections']['selected_sections'][$key] = _ding_sections_selected_term($key, $term, $weight);
    }
  }

  // Add new term field.
  $weight = ++$max_weight;
  for (; $delta < $section_count; $delta++) {
    $key = $delta;
    $form['ding_sections_wrapper']['sections_content']['sections_content_wrapper']['ding_sections_sections']['selected_sections'][$key] = _ding_sections_selected_term($key, NULL, $weight);
  }

  $form['ding_sections_wrapper']['sections_content']['sections_content_wrapper']['ding_sections_sections']['add_section'] = [
    // Used to identify the button in validate/submit handler(s).
    '#name' => 'add_section',
    '#parents' => ['ding_sections_sections', 'add_section'],
    '#type' => 'submit',
    '#value' => t('Add content'),
    '#weight' => 1,
    '#submit' => ['ding_sections_add_section_submit'],
    '#limit_validation_errors' => [['selected_sections']],
    '#ajax' => [
      'wrapper' => 'ding_sections-selected-sections',
      'callback' => 'ding_sections_js_add_section',
      'method' => 'replace',
      'effect' => 'fade',
    ],
  ];

  return $form;
}

/**
 * Edit form submit function.
 */
function ding_sections_content_type_edit_form_submit($form, $form_state) {
  // Removing empty terms.
  if (!empty($form_state['values']['selected_sections'])) {
    foreach ($form_state['values']['selected_sections'] as $key => $term) {
      if (empty($term['term'])) {
        unset($form_state['values']['selected_sections'][$key]);
      }
      else {
        _ding_sections_get_term_tid($key, $term, $form_state);
      }
    }
  }

  // Anything in $form_state['conf'] will be saved automatically.
  _ding_sections_content_type_form_save($form_state);
}

/**
 * Render panel pane.
 */
function ding_sections_content_type_render($subtype, $conf, $args, $context) {
  $tids = [];
  $sort = [];
  foreach ($conf['selected_sections'] as $selected_term) {
    $tids[] = $selected_term['tid'];
    $sort[$selected_term['tid']] = $selected_term['weight'];
  }
  $args = implode(',', $tids);

  $view = views_get_view('ding_sections');
  $view->set_display('ding_sections_groups');
  $view->set_arguments([$args]);
  $view->execute();

  $data = $view->result;
  foreach ($data as $datum) {
    $datum->weight = $sort[$datum->tid];
  }

  array_multisort(array_map(function ($element) {
    return $element->weight;
  }, $data), SORT_ASC, $data);


  $view->result = $data;
  $result = $view->preview();

  $block = new stdClass();
  $block->content = $result;
  return $block;
}
