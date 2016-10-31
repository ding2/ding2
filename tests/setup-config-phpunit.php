<?php

/**
 * @file
 * Setup site for phpunit selenium tests.
 */

// Set default language to english.
variable_set("language_default", (object) array(
  "language" => "en",
  "name" => "English",
  "native" => "English",
  "direction" => "0",
  "enabled" => "1",
  "plurals" => "0",
  "formula" => "",
  "domain" => "",
  "prefix" => "en",
  "weight" => "-9",
  "javascript" => "",
));

// Acivate URL based language negotiation.
variable_set('language_negotiation_language', array(
  'locale-url' => array(
    'callbacks' => array(
      'language' => 'locale_language_from_url',
      'switcher' => 'locale_language_switcher_url',
      'url_rewrite' => 'locale_language_url_rewrite_url',
    ),
    'file' => 'includes/locale.inc',
  ),
  /*'locale-user' => array(
    'callbacks' => array(
      'language' => 'locale_language_from_user',
    ),
    'file' => 'includes/locale.inc',
  ),
  'locale-session' => array(
    'callbacks' => array(
      'language' => 'locale_language_from_session',
      'switcher' => 'locale_language_switcher_session',
      'url_rewrite' => 'locale_language_url_rewrite_session',
    ),
    'file' => 'includes/locale.inc',
  ),*/
  'language-default' => array(
    'callbacks' => array(
      'language' => 'language_from_default',
    ),
  ),
));

// Set priority of language negotiation plugins so URL comes first.
variable_set('locale_language_providers_weight_language', array(
  //'locale-user' => '-6',
  //'locale-session' => '-8',
  'locale-url' => '-10',
  //'locale-browser' => '-7',
  'language-default' => '-9',
));

// Set ting_search_autocomplete settings.
$settings = ting_search_autocomplete_settings();

$settings['index'] = 'scanterm.default';
$settings['facetIndex'] = 'scanphrase.default';

variable_set('ting_search_autocomplete_settings', $settings);
