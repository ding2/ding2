<?php

/**
 * @file
 * Payment provider implementation for Ding!
 */

use Nets\Easy\Checkout;
use Nets\Easy\Client;
use Nets\Easy\OrderItem;

/**
 * Generate the payment URL to redirect the user to.
 */
function ding_debt_easy_payment_get_url($amount, $params, $callback) {
  _ding_debt_easy_load_client();
  $params = $params['params'];

  // Create order ref, this is just an internal id (if this was a web-shop this
  // would be the order id).
  $ref = substr(sha1(implode($params['debt_ids'], ',')), 9);

  $checkout = new Checkout();
  $checkout->getOrder()->setCurrency(ding_debt_easy_get_currency())
    ->setReference($ref);

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
  global $user;
  $checkout->setConsumeReference($user->uid)
    ->setConsumeMail($user->mail);

  // Create payment with the checkout and order as payload.
  $config = ding_debt_easy_get_api_config();
  $client = new Client($config['secret'], $config['checkout'], $config['endpoint']);
  $res = $client->createPayment($checkout);

  // @TODO: What to do with embedded checkout.

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
