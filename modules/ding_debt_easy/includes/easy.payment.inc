<?php

/**
 * @file
 * Payment provider implementation for Ding!
 */

use Nets\Easy\Checkout;
use Nets\Easy\OrderItem;

/**
 * Generate the payment URL to redirect the user to.
 */
function ding_debt_easy_payment_get_url($amount, $params, $callback) {
  global $user;

  // Load the library to get classes used to build the checkout.
  _ding_debt_easy_load_library();

  $params = $params['params'];
  $item_ids = $params['debt_ids'];

  $order_id = _ding_debt_easy_get_order_id_local($user->uid, $item_ids);

  $checkout = new Checkout();
  $checkout->getOrder()->setCurrency(ding_debt_easy_get_currency())
    ->setReference($order_id);

  /** @var \DingProviderDebt $debt */
  foreach ($params['debts'] as $id => $debt) {
    $item = new OrderItem();
    $item->setReference($id)
      ->setProductName($debt->type)
      ->setQuantity(1)
      ->setUnit('stk')
      ->setUnitPrice($debt->amount*100);
    $checkout->getOrder()->addOrderItem($item);
  }

  // Set configuration for the checkout.
  $checkout->setIntegrationType(ding_debt_easy_get_integration_type())
    ->setTermsUrl(url(ding_debt_easy_get_term_url(), ['absolute' => TRUE]))
    ->setMerchantTermsUrl(url(ding_debt_easy_get_privacy_url(), ['absolute' => TRUE]))
    ->setReturnUrl(url(ding_debt_easy_get_return_url(), ['absolute' => TRUE]))
    ->setCancelUrl(url(ding_debt_easy_get_cancel_url(), ['absolute' => TRUE]));

  // Set user information
  $checkout->setConsumeReference($user->uid)
    ->setConsumeMail($user->mail);

  // Create payment with the checkout and order as payload.
  $client = _ding_debt_easy_get_client();
  $res = $client->createPayment($checkout);

  // @TODO: What to do with embedded checkout.
  // @TODO: Error handling - exceptions from client.

  // @TODO: Create internal order id.

  // Store information about the payment state.
  $payment_id = $res['paymentId'];
  _ding_debt_easy_add_payment_id_local($order_id, $payment_id);

  return $res['hostedPaymentPageUrl'];
}

/**
 * Generate support cards form element for the payment page.
 */
function ding_debt_easy_payment_cards_supported() {
  drupal_add_css(drupal_get_path('module', 'ding_debt_easy') . '/css/ding_debt_easy.css');
  $cards = ding_debt_easy_get_payment_types();

  $form = [];
  $form['ding_debt_easy_cards'] = [
    '#theme' => 'ding_debt_easy_cards_supported',
    '#cards' => $cards,
  ];

  return $form;
}

/**
 * Generate terms form element for the payment page.
 */
function ding_debt_easy_payment_terms() {
  $terms =  variable_get('ding_debt_easy_terms', []);

  $form = [];
  $form['ding_debt_easy_terms'] = [
    '#theme' => 'ding_debt_easy_terms',
    '#terms' => $terms['text']['value'],
    '#url' => $terms['url'],
  ];

  return $form;
}
