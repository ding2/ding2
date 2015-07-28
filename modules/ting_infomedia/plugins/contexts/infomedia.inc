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
 * Create a context, either from manual configuration or from an argument on the URL.
 *
 * @param $empty
 *   If true, just return an empty context.
 * @param $data
 *   If from settings form, an array as from a form. If from argument, a string.
 * @param $conf
 *   TRUE if the $data is coming from admin configuration, FALSE if it's from a URL arg.
 *
 * @return
 *   a Context object/
 */
function ting_infomedia_context_create_infomedia($empty, $data = NULL, $conf = FALSE) {
  $context = new ctools_context('infomedia');
  $context->plugin = 'infomedia';
  return $context;
}

function infomedia_settings_form($conf, $external = FALSE) {
  $form = array();
  return $form;
}
