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

  $debts = ding_provider_invoke('debt', 'list', $account);

  if ($debts) {
    $internal_debts = array_filter($debts, '_ding_debt_filter_payable');
    $external_debts = array_filter($debts, '_ding_debt_filter_nonpayable');
    $build = ding_provider_get_form('ding_debt_debts_form', $internal_debts, $external_debts);
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
function ding_debt_debts_form($form, &$form_state, $internal_debts, $external_debts) {
  if (variable_get('ding_debt_external_show_introtext', TRUE)) {
    $ding_debt_external_introtext = variable_get('ding_debt_external_introtext', _ding_debt_external_introtext_default());

    $form['external_introtext'] = [
      '#markup' => check_markup($ding_debt_external_introtext['value'], $ding_debt_external_introtext['format']),
    ];
  }

  if (variable_get('ding_debt_enable_internal', TRUE)) {
    if (variable_get('ding_debt_enable_external', TRUE) && variable_get('ding_debt_internal_title', '')) {
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
        // Yeah, this is extremely hacky, but DIBS payments are being phased out,
        // so refactoring ding_dibs so we can include the contents of these blocks
        // isn't worth the efford.
        if ($provider === 'ding_dibs') {
          $block = ding_dibs_block_view('dibs-cards-supported');
          $form['cards_header'] = [
            '#prefix' => '<h3>',
            '#suffix' => '</h3>',
            '#markup' => check_plain($block['subject']),
          ];

          $form['cards_body'] = [
            '#markup' => $block['content'],
          ];

          $block = ding_dibs_block_view('dibs-terms-of-sale');
          $form['terms_header'] = [
            '#prefix' => '<h3>',
            '#suffix' => '</h3>',
            '#markup' => check_plain($block['subject']),
          ];

          $form['terms_body'] = [
            '#markup' => $block['content'],
          ];
        }

        $form['accept_terms'] = array(
          '#type' => 'checkbox',
          '#title' => t('I accept the terms of service'),
          '#required' => TRUE,
        );

        $form['internal_buttons'] = [
          '#type' => 'container',
          '#attributes' => [
            'class' => ['pay-buttons'],
          ],
          '#tree' => FALSE,
        ];

        $form['internal_buttons']['pay_selected'] = array(
          '#type' => 'submit',
          '#prefix' => '<div class="pay-button">',
          '#value' => t('Pay selected debts'),
          '#suffix' => '</div>',
          '#submit' => array('ding_debt_debts_form_submit_pay_selected'),
          '#states' => array(
            'disabled' => array(
              ':input[name="accept_terms"]' => array('checked' => FALSE),
            ),
          ),
        );

        $form['internal_buttons']['pay_all'] = array(
          '#type' => 'submit',
          '#prefix' => '<div class="pay-button">',
          '#value' => t('Pay all debts'),
          '#suffix' => '</div>',
          '#submit' => array('ding_debt_debts_form_submit_pay_all'),
          '#states' => array(
            'disabled' => array(
              ':input[name="accept_terms"]' => array('checked' => FALSE),
            ),
          ),
        );
      }
    }
  }

  if (variable_get('ding_debt_enable_external', FALSE)) {
    if (variable_get('ding_debt_enable_internal', TRUE) && variable_get('ding_debt_external_title', '')) {
      $form['external_title'] = [
        '#prefix' => '<h2>',
        '#suffix' => '</h2>',
        '#markup' => check_plain(variable_get('ding_debt_external_title', '')),
      ];
    }

    $form['external_debts'] = ding_debt_list_items($external_debts);

    $total = array_reduce($external_debts, function ($total, $debt) {
      return $total + $debt->amount - $debt->amount_paid;
    }, 0);

    $form['external_total'] = array(
      '#type' => 'item',
      '#prefix' => '<div class="total-amount">',
      '#suffix' => '</div>',
      '#markup' => t('Total') . ': <span class="amount">' . number_format($total, 2, ',', ' ') . ' ' . t('Kr') . '</span>',
    );

    if (variable_get('ding_debt_external_show_extra_information', TRUE)) {
      $ding_debt_external_extra_information = variable_get('ding_debt_external_extra_information', _ding_debt_external_extra_information_default());

      $form['external_extra_information'] = [
        '#markup' => check_markup($ding_debt_external_extra_information['value'], $ding_debt_external_extra_information['format']),
      ];
    }

    if (variable_get('ding_debt_enable_external_button', FALSE)) {
      $text = variable_get('ding_debt_external_button_text', '');
      $url = variable_get('ding_debt_external_button_url', '');

      $form['external_buttons'] = [
        '#type' => 'container',
        '#attributes' => [
          'class' => ['pay-buttons'],
        ],
        '#tree' => FALSE,
      ];

      $options = [
        'attributes' => [
          'class' => 'external-payment',
          'target' => '_blank',
        ],
      ];
      $form['external_buttons']['external_link'] = [
        '#markup' => l($text, $url, $options),
      ];
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
