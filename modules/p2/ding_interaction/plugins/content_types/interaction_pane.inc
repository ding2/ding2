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
  'admin info' => 'ding_interaction_admin_info',
  'single' => TRUE,
  'edit form' => 'ding_interaction_content_type_edit_form',
  'render callback' => 'ding_interaction_content_type_render',
  'category' => t('Ding!'),
);

/**
 * Return a summary for the administration interaction in panels.
 */
function ding_interaction_admin_info($subtype, $conf, $context) {
  $output = new stdClass();
  $output->title = t('Interaction');
  $output->content = t('Interaction count: @count', array('@count' => $conf['count'])) . '<br/>';
  return $output;
}

/**
 * Implements hook_content_type_render().
 */
function ding_interaction_content_type_render($subtype, $conf, $panel_args, $context) {
  // Only show on front if serendipity is enabled for the frontpage.
  // See ding_frontpage config at /admin/config/ding/frontend.
  if (drupal_is_front_page() && !variable_get('ding_frontpage_serendipity') && variable_get('ding_frontpage_promoter') != 'serendipity') {
    return;
  }

  // Include the CTools tools that we need.
  ctools_include('ajax');
  // @TODO Change $output to render array and use #attached for files.
  drupal_add_js(drupal_get_path('module', 'ding_interaction') . '/js/ding_interaction.js');
  drupal_add_css(drupal_get_path('module', 'ding_interaction') . '/css/ding_interaction.css');
  $data = ding_interaction_content(NULL, $conf['count']);
  
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
  }
  return $output;
}

/**
 * Implements hook_content_type_edit_form().
 */
function ding_interaction_content_type_edit_form($form, &$form_state) {
  $form['count'] = array(
    '#type' => 'textfield',
    '#title' => t('Count'),
    '#default_value' => (isset($form_state['conf']['count'])) ? $form_state['conf']['count'] : DING_INTERACTION_DEFAULT_COUNT,
    '#description' => t('How many page views should there be between showing this pane.'),
  );

  return $form;
}

/**
 * Implements hook_content_type_edit_form_validate().
 */
function ding_interaction_content_type_edit_form_validate($form, &$form_state) {

}

/**
 * Implements hook_content_type_edit_form_submit().
 */
function ding_interaction_content_type_edit_form_submit($form, &$form_state) {
  $form_state['conf']['count'] = !empty($form_state['values']['count']) ? $form_state['values']['count'] : DING_INTERACTION_DEFAULT_COUNT;
}
