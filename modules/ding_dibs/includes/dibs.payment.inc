<?php
/**
 * @file
 * Payment provider implementation for Ding!
 */

/**
 * Generate the payment URL to redirect the user to.
 */
function ding_dibs_payment_get_url($amount, $params, $callback) {
  if (!empty($params['params']['debt_ids'])) {
    $params['order_info_long'] = array();
    $params['order_info_short'] = t('Library dues: @value', array(
      '@value' => implode(', ', $params['params']['debt_ids']),
    ));
  }

  $transaction_hash = ding_dibs_payment_prepare($amount, $params, $callback, FALSE);

  return 'payment/dibs/redirect/' . $transaction_hash;
}

/**
 * Generate support cards form element for the payment page.
 */
function ding_dibs_payment_cards_supported() {
  $form = [];

  $block = ding_dibs_block_view('dibs-cards-supported');
  $form['cards_header'] = [
    '#prefix' => '<h3>',
    '#suffix' => '</h3>',
    '#markup' => check_plain($block['subject']),
  ];

  $form['cards_body'] = [
    '#markup' => $block['content'],
  ];

  return $form;
}

/**
 * Generate terms form element for the payment page.
 */
function ding_dibs_payment_terms() {
  $form = [];

  $block = ding_dibs_block_view('dibs-terms-of-sale');
  $form['terms_header'] = [
    '#prefix' => '<h3>',
    '#suffix' => '</h3>',
    '#markup' => check_plain($block['subject']),
  ];

  $form['terms_body'] = [
    '#markup' => $block['content'],
  ];

  return $form;
}

/**
 * Generate buttons to submit debts form.
 */
function ding_dibs_payment_buttons() {
  $form = [];

  $form['accept_terms'] = [
    '#type' => 'checkbox',
    '#title' => t('I accept the terms of service'),
    '#required' => TRUE,
  ];

  $form['internal_buttons'] = [
    '#type' => 'container',
    '#attributes' => [
      'class' => ['pay-buttons'],
    ],
    '#tree' => FALSE,
  ];

  $form['internal_buttons']['pay_selected'] = [
    '#type' => 'submit',
    '#prefix' => '<div class="pay-button">',
    '#value' => t('Pay selected debts'),
    '#suffix' => '</div>',
    '#submit' => ['ding_debt_debts_form_submit_pay_selected'],
    '#states' => [
      'disabled' => [
        ':input[name="accept_terms"]' => ['checked' => FALSE],
      ],
    ],
  ];

  $form['internal_buttons']['pay_all'] = [
    '#type' => 'submit',
    '#prefix' => '<div class="pay-button">',
    '#value' => t('Pay all debts'),
    '#suffix' => '</div>',
    '#submit' => ['ding_debt_debts_form_submit_pay_all'],
    '#states' => [
      'disabled' => [
        ':input[name="accept_terms"]' => ['checked' => FALSE],
      ],
    ],
  ];

  return $form;
}
