<?php
/**
 * @file
 * Insert ting object plugin
 */

/**
 * Implements hook_wysiwyg_plugin().
 */
function ting_token_tingTokenInsert_plugin() {
  $plugins['tingTokenInsert'] = array(
    'title' => t('Insert ting object'),
    'icon file' => 'icon.png',
    // TODO dass?
    'icon title' => t('Insert ting objects dass'),
    'settings' => array(),
  );
  return $plugins;
}
