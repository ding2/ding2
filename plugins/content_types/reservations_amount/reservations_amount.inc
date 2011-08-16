<?php

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t("Ding reservation number"),
  'description' => t("Number of reservation in user's reservation list, for login box area"),
  'single' => TRUE,
  'content_types' => array('reservation_amount'),
  'required context' => new ctools_context_required(t('User'), 'user'),
  'category' => t('User'),
);

/**
 * Render the block
 */
function ding_reservation_reservations_amount_content_type_render($subtype, $conf, $panel_args, $context) {
  $account = isset($context->data) ? $context->data : NULL;

  $block = new stdClass();
  $block->module = 'ding_reservation';
  $block->delta = 'reservations';

  $list = ding_provider_invoke_page('reservation', 'list', $account);

  $amount = $account ? sizeof($list) : NULL;
  
  $block->content = 
    array(
      '#type' => 'markup',
      '#prefix' => '<p class="ding-user-reservation-amount">',
      '#markup' => t('Reservations: ') . $amount,
      '#suffix' => '</p>',
    );

  return $block;
}


