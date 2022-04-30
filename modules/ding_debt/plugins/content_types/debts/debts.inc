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

  $block = new stdClass();
  $block->module = 'ding_debt';
  $block->delta  = 'debts';
  $block->title = t('My debts');
  $block->content = '';

  $debts = ding_provider_invoke('debt', 'list', $account);

  // Try to enrich debts with payment processing status information.
  if (ding_provider_implements('payment', 'status')) {
    $debts = ding_provider_invoke('payment', 'status', $debts);
  }

  if ($debts) {
    $internal_debts = array_filter($debts, '_ding_debt_filter_payable');
    $external_debts = array_filter($debts, '_ding_debt_filter_nonpayable');

    if (variable_get('ding_debt_show_introtext', TRUE)) {
      $ding_debt_introtext = variable_get('ding_debt_introtext', _ding_debt_introtext_default());

      $block->content .= '<div class="debt-body">'.check_markup($ding_debt_introtext['value'], $ding_debt_introtext['format']).'</div>';
    }

    $has_internal = !empty($internal_debts) && variable_get('ding_debt_enable_internal', TRUE);
    if ($has_internal) {
      $build = ding_provider_get_form('ding_debt_debts_form', $internal_debts, $external_debts);
      $block->content .= render($build);
    }

    if (!empty($external_debts) && variable_get('ding_debt_enable_external', FALSE)) {
      $externals = array(
        '#theme' => 'ding_debt_external',
        '#title' => check_plain(variable_get('ding_debt_external_title', '')),
        '#debts' => ding_debt_list_items($external_debts),
        '#total' => array_reduce($external_debts, function ($total, $debt) {
          return $total + $debt->amount - $debt->amount_paid;
        }, 0),
        '#extra_information' => variable_get('ding_debt_external_extra_information', _ding_debt_external_extra_information_default()),
        '#button' => array(
          'enabled' => variable_get('ding_debt_enable_external_button', FALSE),
          'text' => variable_get('ding_debt_external_button_text', ''),
          'url' => variable_get('ding_debt_external_button_url', ''),
        ),
        '#has_internal' => $has_internal,
    );
      $block->content .= render($externals);
    }
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
function ding_debt_debts_form($form, &$form_state, $internal_debts, $external_debts) {
  $has_internal = !empty($internal_debts) && variable_get('ding_debt_enable_internal', TRUE);
  $has_external = !empty($external_debts) && variable_get('ding_debt_enable_external', FALSE);

  // Cop out early if there's no debts.
  if (!$has_internal && !$has_external) {
    $form['no_debts'] = [
      '#markup' => t("There's no unpaid debts."),
    ];

    return $form;
  }

  if ($has_internal) {
    if ($has_external && variable_get('ding_debt_internal_title', '')) {
      $form['internal_title'] = [
        '#prefix' => '<h2>',
        '#suffix' => '</h2>',
        '#markup' => check_plain(variable_get('ding_debt_internal_title', '')),
      ];
    }

    $form['internal_debts'] = ding_debt_list_items($internal_debts);

    $total = array_reduce($internal_debts, function ($total, $debt) {
      return $total + $debt->amount - $debt->amount_paid;
    }, 0);

    $form['internal_total'] = array(
      '#type' => 'item',
      '#prefix' => '<div class="total-amount">',
      '#suffix' => '</div>',
      '#markup' => t('Total') . ': <span class="amount">' . number_format($total, 2, ',', ' ') . ' ' . t('Kr') . '</span>',
    );

    // Pass debts to submit handler.
    $form['debt_data'] = array(
      '#type' => 'value',
      '#value' => $internal_debts,
    );

    if (variable_get('ding_debt_enable_internal_button', TRUE)) {
      $provider = ding_provider_get_provider_module_name('payment');
      if (!empty($provider)) {
        if (ding_provider_implements('payment', 'cards_supported')) {
          $form += ding_provider_invoke('payment', 'cards_supported');
        }
        if (ding_provider_implements('payment', 'terms')) {
          $form += ding_provider_invoke('payment', 'terms');
        }
        if (ding_provider_implements('payment', 'buttons')) {
          $form += ding_provider_invoke('payment', 'buttons');
        }
      }
    }
  }

  return $form;
}

/**
 * Helper function to render the details of the debt form.
 */
function ding_debt_list_items($debts) {
  $items = [];

  foreach ($debts as $debt) {
    $item = array(
      '#type' => 'material_item',
      '#id' => $debt->id,
      '#title' => $debt->display_name,
      '#material_type' => $debt->material_type,
      '#information' => array(
        'fee_date' => array(
          'label' => t('Fee date'),
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
          'data' => number_format($debt->amount - $debt->amount_paid, 2, ',', ' ') . ' ' . t('Kr'),
          'class' => 'fee_amount',
          '#weight' => 8,
        ),
      ),
      '#disabled' => !$debt->payable,
    );

    if (!is_null($debt->status)) {
      $item['#information']['status'] = array(
        'label' => t('Payment status', array(), array('context' => 'ding_debt')),
        'data' => t($debt->status, array(), array('context' => 'ding_debt')),
        'class' => 'fee_status',
        '#weight' => 12,
      );

      // Disable payment checkbox as this debt is under payment.
      $item['#disabled'] = 'TRUE';
    }

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
    $items[] = $item;
  }

  return $items;
}

/**
 * Submit handler for the pay all submit button.
 */
function ding_debt_debts_form_submit_pay_all($form, &$form_state) {
  $amount = 0;
  $debts = $form_state['values']['debt_data'];
  foreach ($debts as $debt_id => $debt_data) {
    // Remove payments that are not payable, do to having a gateway payment
    // status. If they have a status they are already being processed and should
    // not be part of a new payment.
    if (!is_null($debt_data->status)) {
      unset($debts[$debt_id]);
      continue;
    }

    $amount += $form_state['values']['debt_data'][$debt_id]->amount;
    $amount -= $form_state['values']['debt_data'][$debt_id]->amount_paid;
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
      $amount += $form_state['values']['debt_data'][$debt_id]->amount;
      $amount -= $form_state['values']['debt_data'][$debt_id]->amount_paid;
      $payments[$debt_id] = $form_state['values']['debt_data'][$debt_id];
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
