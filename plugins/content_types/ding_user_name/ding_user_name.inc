<?php

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Ding username'),
  'icon' => 'icon_user.png',
  'description' => t("Username, for login box area"),
  'description' => t('ding_user_name description.'),
  'single' => TRUE,
  'content_types' => array('ding_user_name'),
  'render callback' => 'ding_user_ding_user_name_type_render',
  'required context' => new ctools_context_required(t('User'), 'user'),
  'category' => t('User'),
);


/**
 * Render callback function
 */
function ding_user_ding_user_name_type_render($subtype, $conf, $panel_args, $context) {

  $block = new stdClass();

  $account = isset($context->data) ? $context->data : NULL;
  
  $display_name = $account ? $account->data['display_name'] : NULL;
  
  $block->content = 
    array(
      '#type' => 'markup',
      '#prefix' => '<p class="ding-user-name">',
      '#markup' => $display_name,
      '#suffix' => '</p>',
    );

  return $block;
  
}

