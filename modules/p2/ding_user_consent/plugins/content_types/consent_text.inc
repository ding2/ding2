<?php

/**
 * @file
 * Ding Consent CTools plugin file.
 */

$plugin = array(
  'title' => t('Ding consent text'),
  'description' => t('Consent text.'),
  'single' => TRUE,
  'category' => t('Ding!'),
);

/**
 * Implements hook_content_type_render().
 */
function ding_user_consent_consent_text_content_type_render($subtype, $conf, $panel_args, $context) {

  $block = new stdClass();

  $block->title = t('Samtykke og opbevaring af information om tidligere lån');

  $block->content = '<p>' . t('Hvis du ikke giver biblioteket tilladelse til at gemme information om dine lån, må vi kun gemme dem i 30 dage.') . '</p><p>' . t('Log ind og rediger din brugerprofil for at give tilladelse til at gemme dine lån ud over 30 dage. Du kan altid fjerne tilladelsen igen hvis du fortryder. Hvis du vælger at fjerne tilladelsen vil information om lån ældre end 30 dage blive slettet permanent.') . '</p>';

  return $block;
}
