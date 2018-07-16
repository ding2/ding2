<?php

/**
 * Create a $plugin array which will be used
 */
$plugin = array(
  'title' => t("infomedia"),
  'description' => t('A single Infomedia data element.'),
  'context' => 'ting_infomedia_context_create_infomedia',  // func to create context
  'context name' => 'infomedia',
  'settings form' => 'infomedia_settings_form',
  'keyword' => 'infomedia',
  'placeholder form' => array(
    '#type' => 'textfield',
    '#description' => t('Enter ID for this Infomedia article.'),
  ),
);

/**
 * Create a context, either from manual configuration or from an argument on the
 * URL.
 */
function ting_infomedia_context_create_infomedia($empty, $data = NULL, $conf = FALSE) {
  $context = new ctools_context('infomedia');
  $context->plugin = 'infomedia';

  return $context;
}

/**
 * Implements infomedia_settings_form().
 *
 * It's need to make the panels plugin work.
 */
function infomedia_settings_form($conf, $external = FALSE) {
  $form = array();
  return $form;
}
