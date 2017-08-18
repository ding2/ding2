<?php

/**
 * @file
 * Ding Serendipity CTools plugin file.
 */

/**
 * Plugin description.
 */
$plugin = array(
  'title' => t('Ding interaction pane'),
  'description' => t('Displays interaction to the user'),
  'single' => TRUE,
  'edit form' => 'ding_interaction_content_type_edit_form',
  'render callback' => 'ding_interaction_content_type_render',
  'category' => t('Ding!'),
);

/**
 * Implements hook_content_type_render().
 */
function ding_interaction_content_type_render($subtype, $conf, $panel_args, $context) {
  // Include the CTools tools that we need.
  ctools_include('ajax');
  // @TODO Change $output to render array and use #attached for files.
  drupal_add_js(drupal_get_path('module', 'ding_interaction') . '/js/ding_interaction.js');
  drupal_add_css(drupal_get_path('module', 'ding_interaction') . '/css/ding_interaction.css');

  $extra = $module_list = array();

  // Force select an interaction depending on get parameters.
  if (!empty($_GET['interaction']) && user_access('administer personalisation')) {
    $module_list[$_GET['interaction']] = module_invoke($_GET['interaction'], 'ding_interaction_info');
    if (!empty($_GET['interaction_extra'])) {
      $extra = $_GET['interaction_extra'];
    }
  }

  $data = ding_interaction_content($module_list, variable_get('ding_interaction_page_count', DING_INTERACTION_DEFAULT_COUNT), $extra);

  $output = new stdClass();
  if ($data) {
    $close_btn = l(t('Close'), '', array('attributes' => array('class' => array('close-btn'))));

    $help_text = empty($data['more_title']) ? "" : l(
      $data['more_title'],
      $data['more_url'],
      array(
        "attributes" => array(
          "class" => "view-all-link",
        ),
      )
    );

    $output->title = '';
    $output->content = theme('ding_interaction_pane_content', array(
      'title' => $data['title'],
      'data' => $data['data'],
      'close_btn' => $close_btn,
      'help_text' => $help_text,
    ));
    $output->css_class = isset($data['css_class']) ? $data['css_class'] : "default-interaction";

    // The lazy_pane module adds a pane placeholder, with the default pane
    // classes. This extra class is used to style the pane, only if it's
    // actually adding content.
    $output->css_class .= ' ding-interaction-true-pane';
  }

  return $output;
}

/**
 * Implements hook_content_type_edit_form().
 */
function ding_interaction_content_type_edit_form($form, &$form_state) {
  return $form;
}
