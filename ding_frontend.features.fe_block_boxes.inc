<?php
/**
 * @file
 * ding_frontend.features.fe_block_boxes.inc
 */

/**
 * Implements hook_default_fe_block_boxes().
 */
function ding_frontend_default_fe_block_boxes() {
  $export = array();

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Footer adresse';
  $fe_block_boxes->format = 'ding_wysiwyg';
  $fe_block_boxes->machine_name = 'footer_adresse';
  $fe_block_boxes->body = '<p>Bibliotek - Gadenavn 1 - 1234 Bynavn - Telefon: 12 34 56 78 - <a href="mailto:bibliotek@example.com">bibliotek@example.com</a></p>';

  $export['footer_adresse'] = $fe_block_boxes;

  return $export;
}
