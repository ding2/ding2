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
      // invoiced fees can't be paid online.
      if ( !$debt->invoice_number ) {
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
 * Implements a drupal form, which implements a pay button and debts data
 */
function ding_debt_debts_form($form, &$form_state, $debts = array(), $has_invoiced_fees, $total_amount) {
  ding_debt_form_details($form, $debts, $has_invoiced_fees, $total_amount);

  if ($total_amount) {
    $form['debt_data'] = array(
      '#type' => 'value',
      '#value' => $debts,
    );

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

  return $form;
}

/**
 * Helper function to render the details of the debt form
 */
function ding_debt_form_details(&$form, $debts, $has_invoiced_fees, $total_amount) {
  $options = array();
  $header = array(
    'fee_date' => t('Fee date'),
    'title' => t('Title'),
    'type' => t('Fee type'),
    'amount' => t('Amount'),
  );

  foreach ($debts as $debt) {
    $options[$debt->id] = array(
      '#disabled' => $debt->is_invoice,
      'fee_date' => array(
        'data' => format_date(strtotime(check_plain($debt->date)), 'date_only'),
        'class' => 'feedate',
      ),
      'title' => array(
        'data' => $debt->display_name,
        'class' => 'feetitle',
      ),
      'type' => array(
        'data' => t($debt->type),
        'class' => 'feetype',
      ),
      'amount' => array(
        'data' => ( $debt->is_invoice ) ? number_format(($debt->amount - $debt->amount_paid), 2, ',', ' ') . ' <span class="note">*</span>' : number_format(($debt->amount - $debt->amount_paid), 2, ',', ' '),
        'class' => 'feeamount',
      ),
    );
  }

  // add total
  $options['total_amount'] = array(
    '#disabled' => TRUE,
    'fee_date' => array(
      'data' => t('Total'),
      'class' => 'feedate',
      'header' => TRUE
    ),
    'title' => array(
      'data' => '',
      'class' => 'feetitle',
      'header' => TRUE
    ),
    'type' => array(
      'data' => '',
      'class' => 'feetype',
      'header' => TRUE
    ),
    'amount' => array(
      'data' => number_format($total_amount, 2, ',', ' '),
      'class' => 'feeamount',
      'header' => TRUE
    ),
  );

  if ($has_invoiced_fees) {
    $options['invoice-note'] = array(
      '#disabled' => TRUE,
      'fee_date' => array(
        'data' => '',
        'class' => 'fee-invoice-note',
        'header' => TRUE
      ),
      'title' => array(
        'data' => t("* Invoiced fees can't be paid online."),
        'class' => 'fee-invoice-note',
        'header' => TRUE
      ),
      'type' => array(
        'data' => '',
        'class' => 'fee-invoice-note',
        'header' => TRUE
      ),
      'amount' => array(
        'data' => '',
        'class' => 'fee-invoice-note',
        'header' => TRUE
      ),
    );
  }
  $form['debts'] = array(
    '#type' => 'tableselect_form',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('No Debt'),
    '#process' => array('ding_base_element_process_tableselect_form', '_ding_debt_debt_disable'),
    '#weight' => -1,
  );
}

/**
 * Process function to disable checkboxes for unpayable debts.
 */
function _ding_debt_debt_disable($element) {
  foreach ($element['#options'] as $key => $choice) {
    if (isset($choice['#disabled']) && $choice['#disabled']) {
      $element[$key]['#disabled'] = TRUE;
      $element[$key]['#attributes']['title'] = t('Not payable here');
    }
  }
  return $element;
}


/**
 * Submit handler for the pay all submit button.
 */
function ding_debt_debts_form_submit_pay_all($form, &$form_state) {
  $amount = 0;
  $debts = array_filter($form_state['values']['debt_data']);
  foreach ($debts as $debt_id => $debt_data) {
    if ( !$form_state['values']['debt_data'][$debt_id]->invoice_number ) {
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
  $debts = array();
  foreach (array_filter($form_state['values']['debts']) as $debt_id => $debt_data) {
    if ( !$form_state['values']['debt_data'][$debt_id]->invoice_number  ) {
      $amount += $form_state['values']['debt_data'][$debt_id]->amount;
      $amount -= $form_state['values']['debt_data'][$debt_id]->amount_paid;
      $debts[$debt_id] = $form_state['values']['debt_data'][$debt_id];
    }
  }
  ding_debt_debts_perform_payment($debts, $amount, $form_state);

}

/**
 * Performs the payment
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

