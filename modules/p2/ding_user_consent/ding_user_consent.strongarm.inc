<?php

/**
 * @file
 * ding_user_consent.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function ding_user_consent_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ding_user_consent_loan_history_store_description';
  $strongarm->value = array(
    'value' => '<p><span>Gem dine tidligere lån og få en mere personlig oplevelse på bibliotekets hjemmeside:</span></p><ul><li>Se dine dine tidligere lån når du er logget ind på hjemmesiden - også lån fra andre biblioteker</li><li>Få anbefalet bøger og andre materialer for dig.&nbsp;Du får anbefalingerne her på siden, og du kan altid afmelde dig igen.</li></ul>',
    'format' => 'ding_wysiwyg',
  );
  $export['ding_user_consent_loan_history_store_description'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ding_user_consent_loan_history_store_description_first_time';
  $strongarm->value = array(
    'value' => '<p>Biblioteket tilbyder dig følgende nye muligheder</p><ul><li>Følg de emner du synes er interessante</li><li>Gem dine tidligere hjemlån i en liste</li><li>Lav dine egne lister over materialer du finder på biblioteket</li></ul><p>For at benytte disse muligheder, skal du tillade at vi opbevarer disse personlige data for dig.</p><p>Du kan altid fravælge dette igen senere hvormed vi sletter disse data.</p>',
    'format' => 'ding_wysiwyg',
  );
  $export['ding_user_consent_loan_history_store_description_first_time'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ding_user_consent_loan_history_store_title';
  $strongarm->value = 'Dine private data';
  $export['ding_user_consent_loan_history_store_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ding_user_consent_loan_history_store_title_first_time';
  $strongarm->value = 'Dine private data';
  $export['ding_user_consent_loan_history_store_title_first_time'] = $strongarm;

  return $export;
}
