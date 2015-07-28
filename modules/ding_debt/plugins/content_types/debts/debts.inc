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
 * Render the block.
 */
function ding_debt_debts_content_type_render($subtype, $conf, $panel_args, $context) {
  $account = isset($context->data) ? $context->data : NULL;
  $total_amount = 0;
  $has_invoiced_fees = FALSE;

  $block = new stdClass();
  $block->module = 'ding_debt';
  $block->delta  = 'debts';
  $block->title = t('My debts');

  $debts = ding_provider_invoke_page('debt', 'list', $account);

  if (count($debts) == TRUE) {
    foreach ($debts as $debt) {
      // Invoiced fees can't be paid online.
      if (!$debt->invoice_number) {
        $total_amount += $debt->amount;
        $total_amount -= $debt->amount_paid;
        $debt->is_invoice = FALSE;
      }
      else {
        $debt->is_invoice = TRUE;
        $has_invoiced_fees = TRUE;
      }
    }
    $build = ding_provider_get_form('ding_debt_debts_form', $debts, $has_invoiced_fees, $total_amount);
    $block->content = render($build);
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
 * Implements a drupal form, which implements a pay button and debts data.
 */
function ding_debt_debts_form($form, &$form_state, $debts, $has_invoiced_fees, $total_amount) {
  ding_debt_form_details($form, $debts, $has_invoiced_fees, $total_amount);

  if ($total_amount) {
    // Init debts.
    if (!isset($debts)) {
      $debts = array();
    }

    $form['debt_data'] = array(
      '#type' => 'value',
      '#value' => $debts,
    );

    $provider = ding_provider_get_provider_module_name('payment');
    if (!empty($provider)) {
      $form['pay_selected'] = array(
        '#type' => 'submit',
        '#prefix' => '<div class="pay-button">',
        '#value' => t('Pay selected debts'),
        '#suffix' => '</div>',
        '#submit' => array('ding_debt_debts_form_submit_pay_selected'),
      );

      $form['pay_all'] = array(
        '#type' => 'submit',
        '#prefix' => '<div class="pay-button">',
        '#value' => t('Pay all debts'),
        '#suffix' => '</div>',
        '#submit' => array('ding_debt_debts_form_submit_pay_all'),
      );
    }
  }

  return $form;
}

/**
 * Helper function to render the details of the debt form.
 */
function ding_debt_form_details(&$form, $debts, $has_invoiced_fees, $total_amount) {
  foreach ($debts as $debt) {
    $item = array(
      '#type' => 'material_item',
      '#id' => $debt->id,
      '#title' => $debt->display_name,
      '#information' => array(
        'fee_date' => array(
          'label' => t('Created date'),
          'data' => format_date(strtotime(check_plain($debt->date)), 'ding_material_lists_date'),
          'class' => 'fee-date',
          '#weight' => 0,
        ),
        'fee_type' => array(
          'label' => t('Fee cause'),
          'data' => $debt->type,
          'class' => 'fee-type',
          '#weight' => 4,
        ),
        'amount' => array(
          'label' => t('Amount'),
          'data' => $debt->is_invoice ? number_format(($debt->amount - $debt->amount_paid), 2, ',', ' ') . ' ' . t('Kr') . ' <span class="note">*</span>' : number_format(($debt->amount - $debt->amount_paid), 2, ',', ' ') . ' ' . t('Kr'),
          'class' => 'fee_amount',
          '#weight' => 8,
        ),
      ),
      '#disabled' => (bool) $debt->invoice_number,
    );

    // Add material number if available.
    if (isset($debt->material_number)) {
      $item['#information']['material-number'] = array(
        'label' => t('Material no.'),
        'data' => $debt->material_number,
        'class' => 'material-number',
        '#weight' => -4,
      );
    }

    // Add the debt to the form.
    $form['debts'][$debt->id] = $item;
  }

  // Add item with the total amount.
  $form['total'] = array(
    '#type' => 'item',
    '#prefix' => '<div class="total-amount">',
    '#suffix' => '</div>',
    '#markup' => t('Total') . ': <span class="amount">' . number_format($total_amount, 2, ',', ' ') . ' ' . t('Kr') . '</span>',
  );

  if ($has_invoiced_fees) {
    $form['notice'] = array(
      '#type' => 'item',
      '#prefix' => '<div class="messages warning">',
      '#suffix' => '</div>',
      '#markup' => t("* Invoiced fees can't be paid online."),
    );
  }
}

/**
 * Submit handler for the pay all submit button.
 */
function ding_debt_debts_form_submit_pay_all($form, &$form_state) {
  $amount = 0;
  $debts = $form_state['values']['debt_data'];
  foreach ($debts as $debt_id => $debt_data) {
    if (!$form_state['values']['debt_data'][$debt_id]->invoice_number) {
      $amount += $form_state['values']['debt_data'][$debt_id]->amount;
      $amount -= $form_state['values']['debt_data'][$debt_id]->amount_paid;
    }
    else {
      unset($debts[$debt_id]);
    }
  }
  ding_debt_debts_perform_payment($debts, $amount, $form_state);
}

/**
 * Submit handler for the pay selected submit button.
 */
function ding_debt_debts_form_submit_pay_selected($form, &$form_state) {
  $amount = 0;
  $payments = array();
  $debts = $form_state['values']['debt_data'];
  foreach ($debts as $debt_id => $debt_data) {
    if (!empty($form_state['values'][$debt_id])) {
      if (!$debt_data->invoice_number) {
        $amount += $form_state['values']['debt_data'][$debt_id]->amount;
        $amount -= $form_state['values']['debt_data'][$debt_id]->amount_paid;
        $payments[$debt_id] = $form_state['values']['debt_data'][$debt_id];
      }
    }
  }
  ding_debt_debts_perform_payment($payments, $amount, $form_state);
}

/**
 * Performs the payment.
 */
function ding_debt_debts_perform_payment($debts, $amount, &$form_state) {
  if ($amount > 0) {
    $params = array(
      'params' => array(
        'debt_ids' => array_keys($debts),
        'debts' => $debts,
      ),
    );
    $url = ding_provider_invoke('payment', 'get_url', $amount, $params, 'ding_debt_payment_callback');

    if ($url) {
      $form_state['redirect'] = $url;
    }
  }
}

