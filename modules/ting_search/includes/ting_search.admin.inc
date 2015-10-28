<?php
/**
 * @file
 * Admin page callback file for the ting search module.
 */

/**
 * Configure ting search settings for this site.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function ting_search_admin_settings($form_state) {
  $form = array();
  
  $display_message = 'Your search gave more than %s results. Try to search more specific or use the facets to filter the result.';

  $form['ting_search'] = array(
    '#type' => 'fieldset',
    '#title' => t('Ting search settings'),
    '#tree' => FALSE,
  );

  // Set ting search results per page. Used on the ting search page to determine
  // the initial amount of search results to display.
  $form['ting_search']['ting_search_results_per_page'] = array(
    '#type' => 'textfield',
    '#title' => t('Default results per page'),
    '#description' => t('Enter the number of results desplayed on the search page by default.'),
    '#default_value' => variable_get('ting_search_results_per_page', 10),
  );

  // Set ting search number of facets. Used on the ting search page to determine
  // how many facets to display in the facet browser.
  $form['ting_search']['ting_search_number_of_facets'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of facets'),
    '#description' => t('Enter the number of facets the search engine should show.'),
    '#default_value' => variable_get('ting_search_number_of_facets', 25),
  );

  $form['ting_search']['ting_search_register_serie_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Serie title'),
    '#description' => t('Specify the searchstring to be used for searching against serie titles. Use @serietitle as a placeholder for the serietitle'),
    '#default_value' => variable_get('ting_search_register_serie_title', 'phrase.titleSeries="@serietitle"'),
  );

  // The default sort option. Used by ting search execute to set the default
  // sort option.
  $form['ting_search']['ting_search_default_sort'] = array(
    '#type' => 'select',
    '#title' => t('Default sorting'),
    '#options' => ting_search_sort_options(),
    '#default_value' => variable_get('ting_search_default_sort', ''),
    '#description' => t('Set the default sorting for search results.'),
  );

  $form['ting_search']['ting_search_result_message'] = array(
    '#type' => 'item',
    '#attributes' => array('class' => array('description')),
    '#title' => t('Display message'),
    '#markup' => t($display_message),
    '#description' => t('Message to display when search has more than x results. The token %s will be substituted by the number choosen.'),
  );
  
  if ( t($display_message) != $display_message ) {
    $form['ting_search']['ting_search_result_message']['#description'] .= '<br/>' . t('Translated from: %n.', array('%n' => $display_message));
  }

  $form['ting_search']['ting_search_result_message_limit'] = array(
    '#type' => 'textfield',
    '#title' => t('Display message at'),
    '#default_value' => variable_get('ting_search_result_message_limit', 100),
    '#description' => t('The limit at wich the message is to be displayed.'),
  );

  return system_settings_form($form);
}
