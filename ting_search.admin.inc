<?php
/**
 * @file
 * Admin page callback file for the ting module.
 */

/**
 * Form builder; Configure ting settings for this site.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function ting_search_admin_settings($form_state) {
  $form = array();

  $form['ting_search'] = array(
    '#type' => 'fieldset',
    '#title' => t('Ting search settings'),
    '#tree' => FALSE,
  );

  $form['ting_search']['ting_search_results_per_page'] = array(
    '#type' => 'textfield',
    '#title' => t('Default results per page'),
    '#description' => t('Enter the number of results desplayed on the search page by default.'),
    '#default_value' => variable_get('ting_search_results_per_page', 10),
  );
  $form['ting_search']['ting_search_number_of_facets'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of facets'),
    '#description' => t('Enter the number of facets the search engine should use.'),
    '#default_value' => variable_get('ting_search_number_of_facets', 25),
  );
  $form['ting_search']['ting_search_default_sort'] = array(
    '#type' => 'select',
    '#title' => t('Default sorting'),
    '#options' => ting_search_sort_options(),
    '#default_value' => variable_get('ting_search_default_sort', ''),
    '#description' => t('Set the default sorting for search results..'),
  );

  return system_settings_form($form);
}