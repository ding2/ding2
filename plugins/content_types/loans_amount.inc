<?php

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t("Ding loans number"),
  'description' => t("Number of loans in user's loan list, for login box area"),
  'single' => TRUE,
  'content_types' => array('loans_amount'),
  'required context' => new ctools_context_required(t('User'), 'user'),
  'category' => t('User'),
);

/**
 * Render the block
 */
function ding_loan_loans_amount_content_type_render($subtype, $conf, $panel_args, $context) {
  $account = isset($context->data) ? $context->data : NULL;

  $block = new stdClass();
  $block->module = 'ding_loan';
  $block->delta = 'loans';

  $list = ding_provider_invoke_page('loan', 'list', $account);

  $amount = $account ? sizeof($list) : NULL;
  
  $block->content = 
    array(
      '#type' => 'markup',
      '#prefix' => '<p class="ding-user-loan-amount">',
      '#markup' => t('Loans: ') . $amount,
      '#suffix' => '</p>',
    );

  return $block;
}

