<?php

/**
 * @file
 * Configuration of module.
 */

/**
 * Implements hook_form_FORM_ID_alter().
 */
function ting_subsearch_translate_form_opensearch_admin_settings_alter(&$form, &$form_state) {

  $facets = array();
  foreach (variable_get('ding_facetbrowser_facets', array()) as $facet) {
    $facets[] = $facet['name'];
  }

  if (!in_array('facet.genreCategory', $facets)) {
    drupal_set_message(
      t(
        'Translated search requires !facet. Please insert on !adminpage',
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

  $form['subsearch_settings']['subsearch_translate']['#type'] = 'fieldset';
  $form['subsearch_settings']['subsearch_translate']['#title'] = t('Translation Settings');
  $form['subsearch_settings']['subsearch_translate']['#tree'] = FALSE;
  $form['subsearch_settings']['subsearch_translate']['#description'] = t('With translated subsearch you get the option for translated keys when the challenge is passed.');

  $form['subsearch_settings']['subsearch_translate']['ting_subsearch_translate_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Google translation service url'),
    '#default_value' => variable_get('ting_subsearch_translate_url', 'https://www.googleapis.com/language/translate/v2'),
  );

  $form['subsearch_settings']['subsearch_translate']['ting_subsearch_translate_google_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Google Cloud Translation API key'),
    '#description' => t('You need to have an API key configured with billing for this to work. take a look at <a href="https://cloud.google.com/translate/pricing">Pricing</a>'),
    '#default_value' => variable_get('ting_subsearch_translate_google_key', ''),
  );

  $form['subsearch_settings']['subsearch_translate']['ting_subsearch_translate_factor'] = array(
    '#type' => 'textfield',
    '#title' => t('Ratio between nonfiction and fiction'),
    '#description' => t('The percent of nonfiction more than fiction to trigger the translation'),
    '#default_value' => variable_get('ting_subsearch_translate_factor', 50),
  );

  $form['subsearch_settings']['subsearch_translate']['ting_subsearch_translate_min_hits'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum translations hits'),
    '#description' => t('The minimum number of hit for a given translation before showing the box. Set it to \'0\' to always show the box.'),
    '#default_value' => variable_get('ting_subsearch_translate_min_hits', 0),
  );
}
