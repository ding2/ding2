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
  $total_amount = 0;
  $has_invoiced_fees = FALSE;

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
      // invoiced fees can't be paid online.
      $is_invoice = TRUE;
      if ( !$debt->invoice_number ) {
        $total_amount += $debt->amount;
        $total_amount -= $debt->amount_paid;
        $is_invoice = FALSE;
      } else {
        $has_invoiced_fees = TRUE;
      }
      $row = array(
        array('data' => format_date(strtotime(check_plain($debt->date)), 'date_only'), 'class' => 'feedate'),
        array('data' => $debt->display_name, 'class' => 'feetitle'),
        array('data' => ( $is_invoice ) ? number_format(($debt->amount - $debt->amount_paid), 2, ',', ' ') . ' <span class="note">*</span>' : number_format(($debt->amount - $debt->amount_paid), 2, ',', ' '), 'class' => 'feeamount'),
      );
      $rows[] = $row;
    }

    // add total
    $row = array(
      array('data' => t('Total'), 'class' => 'feedate', 'header' => TRUE),
      array('data' => '', 'class' => 'feetitle', 'header' => TRUE),
      array('data' => number_format($total_amount, 2, ',', ' '), 'class' => 'feeamount', 'header' => TRUE),
    );
    $rows[] = $row;

    if ( $has_invoiced_fees ) {
      // add note
      $row = array(
        array('data' => '', 'class' => 'fee-invoice-note'),
        array('data' => t("* Invoiced fees can't be paid online."), 'class' => 'fee-invoice-note'),
        array('data' => '', 'class' => 'fee-invoice-note'),
      );
      $rows[] = $row;
    }

    $table = theme('table', array(
      'header' => $header,
      'rows' => $rows,
    ));

    if ( $total_amount ) {
      $build = ding_provider_get_form('ding_debt_debts_form', $debts);
    }

    $block->content = render($table) . render($build);

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
    '#prefix' => '<div class="pay-button">',
    '#value' => t('Pay debts'),
    '#suffix' => '</div>',
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
    if ( !$form_state['values']['debt_data'][$debt_id]->invoice_number ) {
      $amount += $form_state['values']['debt_data'][$debt_id]->amount;
      $amount -= $form_state['values']['debt_data'][$debt_id]->amount_paid;
    } else {
      unset($debts[$debt_id]);
    }
  }

  if ($amount > 0) {
    $params = array('params' => array('debt_ids' => array_keys($debts)));

    $url = ding_provider_invoke('payment', 'get_url', $amount, $params, 'ding_debt_payment_callback');

    if ($url) {
      $form_state['redirect'] = $url;
    }
  }
}

