<?php

/**
 * @file
 * Configuration of module.
 */

/**
 * Implements hook_form_FORM_ID_alter().
 */
function ting_subsearch_secondary_form_ting_admin_ting_settings_alter(&$form, &$form_state) {

  $facets = array();
  foreach (variable_get('ding_facetbrowser_facets', array()) as $facet) {
    $facets[] = $facet['name'];
  }

  if (!in_array('facet.genreCategory', $facets)) {
    drupal_set_message(
      t(
        'Secondary search requires !facet. Please insert on !adminpage',
        array(
          '!facet' => 'facet.genreCategory',
          '!adminpage' => l(
            t('Configure facets'),
            'admin/config/ting/facets'
          ),
        )
      ),
      'warning'
    );
  }

  $form['subsearch_settings']['#type'] = 'fieldset';
  $form['subsearch_settings']['#title'] = t('Ting Subsearch');
  $form['subsearch_settings']['#description'] = t('Feature modules allow additional searches to be made based on predefined conditions.');
  $form['subsearch_settings']['#tree'] = FALSE;

  $form['subsearch_settings']['secondary_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Secondary Ting Search settings'),
  );

  $form['subsearch_settings']['secondary_settings']['trigger'] = array(
    '#type' => 'fieldset',
    '#title' => t('Trigger'),
  );

  $form['subsearch_settings']['secondary_settings']['trigger']['ting_subsearch_secondary_min'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum number of results'),
    '#default_value' => variable_get('ting_subsearch_secondary_min', 10),
    '#description' => t('How few is minimum in order to trigger secondary search.'),

  );

  $form['subsearch_settings']['secondary_settings']['trigger']['ting_subsearch_secondary_max'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum number of results'),
    '#default_value' => variable_get('ting_subsearch_secondary_max', 100),
    '#description' => t('How many is maximum in order to trigger secondary search.'),
  );

  $form['subsearch_settings']['secondary_settings']['trigger']['ting_subsearch_secondary_factor'] = array(
    '#type' => 'textfield',
    '#title' => t('Challenge: Factor for calculating ratio between nonfiction and fiction'),
    '#default_value' => variable_get('ting_subsearch_secondary_factor', 2),
    '#description' => t('The condition is as following (nonfiction / factor) > fiction'),
  );

  $form['subsearch_settings']['secondary_settings']['trigger']['ting_subsearch_secondary_result_min'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum number of results for secondary search'),
    '#default_value' => variable_get('ting_subsearch_secondary_result_min', 100),
  );

  $form['subsearch_settings']['secondary_settings']['ting_subsearch_secondary_agency'] = array(
    '#type' => 'textfield',
    '#title' => t('Secondary Agency'),
    '#default_value' => variable_get('ting_subsearch_secondary_agency', ''),
    '#description' => t('The agency for the secondary well configuration'),
  );

  $form['subsearch_settings']['secondary_settings']['ting_subsearch_secondary_profile'] = array(
    '#type' => 'textfield',
    '#title' => t('Secondary Search profile'),
    '#default_value' => variable_get('ting_subsearch_secondary_profile', ''),
    '#description' => t('The Search profile for the secondary well configuration'),
  );

  $form['subsearch_settings']['secondary_settings']['ting_subsearch_secondary_search_link'] = array(
    '#type' => 'textfield',
    '#title' => t('Secondary link'),
    '#description' => t('Could be something link https://bibliotek.dk/da/search/work?search_block_form=[keys] where [keys] are substituted with the searchphrase.'),
    '#default_value' => variable_get('ting_subsearch_secondary_search_link', ''),
  );

  $form['subsearch_settings']['secondary_settings']['ting_subsearch_secondary_search_link_text'] = array(
    '#type' => 'textfield',
    '#title' => t('Secondary link text'),
    '#default_value' => variable_get('ting_subsearch_secondary_search_link_text', ''),
    '#description' => t('Name of the secondary provider. Could be bibliotek.dk'),
  );

  $form['subsearch_settings']['secondary_settings']['ting_subsearch_secondary_number_of_results'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of results to show'),
    '#default_value' => variable_get('ting_subsearch_secondary_number_of_results', 4),
    '#description' => t('How many results should be shown from secondary well provider.'),
  );
  $form['subsearch_settings']['secondary_settings']['ting_subsearch_secondary_position'] = array(
    '#type' => 'radios',
    '#title' => t('Position of message'),
    '#options' => array(
      'before' => t('Before'),
      'after' => t('After'),
    ),
    '#default_value' => variable_get('ting_subsearch_secondary_position', 'before'),
    '#description' => t('Should the message be positioned before or after the search result?'),
  );
}
