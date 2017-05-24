<?php

/**
 * @file
 * Ding Campaign CTools plugin file.
 */

$plugin = array(
  'title' => t('Relevant campaigns'),
  'description' => t('Display ad-like campaigns'),
  'single' => TRUE,
  'defaults' => array(
    'ding_campaign_count' => 3,
    'ding_campaign_offset' => 0,
  ),
  'required context' => array(
    new ctools_context_optional(t('Page node'), 'node'),
    new ctools_context_optional(t('Related library'), 'node'),
    new ctools_context_optional(t('Search term'), 'string'),
    new ctools_context_optional(t('Taxonomy term'), array('entity:taxonomy_term', 'taxonomy_term')),
  ),
  'category' => t('Ding!'),
);

/**
 * Implements hook_content_type_render().
 */
function ding_campaign_campaign_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $context_data = array(
    'page' => isset($context[0]->data) ? $context[0]->data : NULL,
    'library' => isset($context[1]->data) ? $context[1]->data : NULL,
    'search_term' => isset($context[2]->data) ? $context[2]->data : NULL,
    'taxonomy_term' => isset($context[3]->data) ? $context[3]->data : NULL,
  );
  $count = $conf['ding_campaign_count'];
  $offset = $conf['ding_campaign_offset'];
  // Set default value if it was not set in panel settings.
  $style = (!empty($conf['ding_campaign_image_style'])) ? $conf['ding_campaign_image_style'] : 'medium';

  $block->content = ding_campaign_display($context_data, $count, $offset, $style);

  return $block;
}

/**
 * Implements hook_content_type_edit_form().
 */
function ding_campaign_campaign_content_type_edit_form($form, &$form_state) {

  $form['ding_campaign_count'] = array(
    '#type' => 'textfield',
    '#title' => t('Campaign count'),
    '#description' => t('The maximum number of campaigns to display'),
    '#default_value' => (isset($form_state['conf']['ding_campaign_count'])) ? $form_state['conf']['ding_campaign_count'] : 3,
    '#size' => 2,
    '#maxlength' => 2,
  );

  $form['ding_campaign_offset'] = array(
    '#type' => 'textfield',
    '#title' => t('Campaign offset'),
    '#description' => t('Which campaign should we count from when returning campaigns. This is used to avoid displaying the same campaigns when using multiple campaign panes on the same panel. Use 0 to return the most relevant campaigns.'),
    '#default_value' => (isset($form_state['conf']['ding_campaign_offset'])) ? $form_state['conf']['ding_campaign_offset'] : 0,
    '#size' => 3,
    '#maxlength' => 3,
  );

  $form['ding_campaign_image_style'] = array(
    '#type' => 'select',
    '#title' => t('Campaign image width'),
    '#description' => t('Applicable for image campaigns. Image will be resized to selected width, height will be selected automatically.'),
    '#options' => array(
      'ding_campaign_p_25' => t('25% (280px)'),
      'ding_campaign_p_33' => t('33% (380px)'),
      'ding_campaign_p_50' => t('50% (580px)'),
      'ding_campaign_p_66' => t('66% (780px)'),
      'ding_campaign_p_75' => t('75% (880px)'),
      'ding_campaign_p_100' => t('100% (1200px)'),

    ),
    '#default_value' => (isset($form_state['conf']['ding_campaign_image_style'])) ? $form_state['conf']['ding_campaign_image_style'] : 'ding_campaign_p_25',
  );

  drupal_add_css(drupal_get_path('module', 'ding_campaign') . '/css/ding_campaign.admin.css');

  return $form;
}

/**
 * Implements hook_content_type_edit_form_validate().
 */
function ding_campaign_campaign_content_type_edit_form_validate($form, &$form_state) {
  // Sanitise the submitted values.
  $values = array(
    'ding_campaign_count' => 1,
    'ding_campaign_offset' => 0,
  );
  foreach ($values as $value => $min_value) {
    $val = trim($form_state['values'][$value]);
    $count = intval($val);

    // Give an error if a value less than 1 was entered.
    if (!empty($val) && $count < $min_value) {
      form_set_error($value, t('%value must be a number larger than zero.',
          array(
            '%value' => drupal_ucfirst(str_replace('_', ' ', $value)),
          )));
    }
    // Otherwise, store the sanitised value in the form state.
    else {
      $form_state['values'][$value] = $count;
    }
  }
}

/**
 * Implements hook_content_type_edit_form_submit().
 */
function ding_campaign_campaign_content_type_edit_form_submit($form, &$form_state) {
  $form_state['conf']['ding_campaign_count'] = $form_state['values']['ding_campaign_count'];
  $form_state['conf']['ding_campaign_offset'] = $form_state['values']['ding_campaign_offset'];
  $form_state['conf']['ding_campaign_image_style'] = $form_state['values']['ding_campaign_image_style'];
}
