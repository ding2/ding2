<?php
/**
 * @file
 * ding_ekurser.oembed_provider.inc
 */

/**
 * Implements hook_default_oembed_provider().
 */
function ding_ekurser_default_oembed_provider() {
  $export = array();

  $provider = new stdClass();
  $provider->disabled = FALSE; /* Edit this to true to make a default provider disabled initially */
  $provider->api_version = 1;
  $provider->name = 'eKurser';
  $provider->title = 'eKurser';
  $provider->endpoint = 'http://www.ekurser.nu/oembed/';
  $provider->scheme = 'http://www.ekurser.nu/kursus/*';
  $export['eKurser'] = $provider;

  return $export;
}
