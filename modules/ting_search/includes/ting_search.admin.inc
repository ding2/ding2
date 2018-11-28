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

  $form['ting_search']['search_strings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Search strings'),
    '#description' => t('Search strings are used to build links to new search results based on field values. You can supply both search string and query values e.g. for facets separated by ?. As an example the following search string will link author name to a phrase search for the author with language set to Danish: phrase.creator="@author"?facets[]=facet.language:dansk.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['ting_search']['search_strings']['ting_search_register_serie_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Serie title'),
    '#description' => t(
      'Specify the search-string to be used for searching against serie titles. 
      Use @serietitle as a placeholder for the serietitle'
    ),
    '#default_value' => variable_get(
      'ting_search_register_serie_title',
      'phrase.titleSeries="@serietitle"'
    ),
  );

  $form['ting_search']['search_strings']['ting_search_register_author'] = array(
    '#type' => 'textfield',
    '#title' => t('Author'),
    '#description' => t(
      'Specify the search-string to be used for searching against author name. 
      Use @author as a placeholder for the author with "first name + lastname" 
      or @author_inverted for "last name + first name.'
    ),
    '#default_value' => variable_get(
      'ting_search_register_author',
      'phrase.creator="@author"'
    ),
  );

  $form['ting_search']['search_strings']['ting_search_register_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject'),
    '#description' => t(
      'Specify the search-string to be used for searching against subjects. 
      Use @subject as a placeholder for the subject.'
    ),
    '#default_value' => variable_get(
      'ting_search_register_subject',
      'phrase.subject="@subject"'
    ),
  );

  // The default sort option. Used by ting search execute to set the default
  // sort option.
  $form['ting_search']['ting_search_default_sort'] = array(
    '#type' => 'select',
    '#title' => t('Default sorting'),
    '#options' => ting_search_sort_form_options(),
    '#default_value' => variable_get('ting_search_default_sort', ''),
    '#description' => t('Set the default sorting for search results.'),
  );

  $form['ting_search']['ting_search_form_style'] = array(
    '#type' => 'select',
    '#title' => t('Search form style'),
    '#options' => array(
      TING_SEARCH_FORM_STYLE_NORMAL => t('Normal'),
      TING_SEARCH_FORM_STYLE_EXTENDED => t('Extended'),
    ),
    '#default_value' => variable_get('ting_search_form_style', TING_SEARCH_FORM_STYLE_NORMAL),
  );

  return system_settings_form($form);
}
