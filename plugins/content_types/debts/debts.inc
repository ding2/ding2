<?php

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('User debt list'),
  'description' => t('The current debts for a user'),
  'single' => TRUE,
  'content_types' => array('list'),
  'required context' => new ctools_context_required(t('User'), 'user'),
  'category' => t('User'),
);

/**
 * Render the block
 */
function ding_debt_debts_content_type_render($subtype, $conf, $panel_args, $context) {
  $preload_debts = &drupal_static('ids');
  $account = isset($context->data) ? $context->data : NULL;
  $preload_ids = array();
  $items = array();
  $debt_list = array();
  $rows = array();
  $row = array();

  $block = new stdClass();
  $block->module = 'ding_debt';
  $block->delta  = 'debts';
  $block->title = t('My debts');

  $debts = ding_provider_invoke_page('debt', 'list', $account);

  if (count($debts) == TRUE) {
    $header = array(
      array('data' => t('Fee date'), 'class' => 'feedate'),
      array('data' => t('Material name'), 'class' => 'feetitle'),
      array('data' => t('Amount'), 'class' => 'feeamount'),
    );
    foreach ($debts as $debt) {
      $row = array(
        array('data' => format_date(strtotime(check_plain($debt->date)), 'date_only'), 'class' => 'feedate'),
        array('data' => $debt->display_name, 'class' => 'feetitle'),
        array('data' => number_format($debt->amount, 2, ',', ' '), 'class' => 'feeamount'),
      );
      $rows[] = $row;
    }
    $table = theme('table', array(
      'header' => $header,
      'rows' => $rows,
    ));
    $block->content = render($table) . render(ding_provider_get_form('ding_debt_debts_form', $debts));
  }
  else {
    $block->content = t('No debts');
  }
  return $block;
}

/**
 * Form for configuring the content type.
 *
 * Not currently used.
 */
function ding_debt_debts_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Implements a drupal form, which implements a pay button and debts data
 */
function ding_debt_debts_form($form, &$form_state, $debts = array()) {

  $form['debt_data'] = array(
    '#type' => 'value',
    '#value' => $debts,
  );

  $form['pay'] = array(
    '#type' => 'submit',
    '#value' => t('Pay debts'),
  );

  return $form;
}

/**
 * Submit handler for the form.
 */
function ding_debt_debts_form_submit($form, &$form_state) {
  global $user;
  $amount = 0;
  $debts = array_filter($form_state['values']['debt_data']);
  foreach ($debts as $debt_id => $debt_data) {
    $amount += $form_state['values']['debt_data'][$debt_id]->amount;
  }

  if ($amount > 0) {
    $params = array('params' => array('debt_ids' => array_keys($debts)));

    $url = ding_provider_invoke('payment', 'get_url', $amount, $params, 'ding_debt_payment_callback');

    if ($url) {
      $form_state['redirect'] = $url;
    }
  }
}

