<?php

/**
 * @file
 * Payment provider implementation for Ding!
 */

use Nets\Easy\Order;
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

  $order = new Order();
  $order->setCurrency(ding_debt_easy_get_currency())
    ->setReference($ref);

  /** @var \DingProviderDebt $debt */
  foreach ($params['debts'] as $id => $debt) {
    $item = new OrderItem();
    $item->setReference($id)
      ->setProductName($debt->type)
      ->setQuantity(1)
      ->setUnit('')
      ->setUnitPrice($debt->amount*100);
    $order->addOrderItem($item);
  }

  // @TODO: Move this logic into the client Checkout.
  // Create checkout payload
  $payload = [
    'checkout' => [
      'integrationType' => ding_debt_easy_get_integration_type(),
      'termsUrl' => url(ding_debt_easy_get_term_url(), ['absolute' => TRUE]),
      'merchantTermsUrl'  => url(ding_debt_easy_get_privacy_url(), ['absolute' => TRUE]),
      // We need to only reserve the payment. The charging will be done after
      // provider has accepted API call.
      'charge' => FALSE,
      // Limit data stored in the browser at nets: the checkout will not remember
      // the current consumer on this device.
      'publicDevice' => TRUE,
      //'url' => 'ONLY WITH Embedded checkout to load order from'
      'appearance' => [
        'displayOptions' => [
          'showMerchantName' => TRUE,
          'showOrderSummary' => TRUE,
        ],
      ],
      // FBS handles information about the consumer, so Nets should not ask for
      // address etc.
      'merchantHandlesConsumerData' => TRUE,
      'consumer' => [
        // @TODO: get real data.
        'reference' => "user-id-2034",
        'email' => "john.doe@example.com",
      ],
      'returnUrl' => url(ding_debt_easy_get_return_url(), ['absolute' => TRUE]),
      'cancelUrl' => url(ding_debt_easy_get_cancel_url(), ['absolute' => TRUE]),
    ],
    'order' => $order->toArray(),
  ];



  $t = json_encode($payload, JSON_PRETTY_PRINT);
  $t1=0;

  // Create payment


  // Redirect based on payment URL.


  return 'payment/dibs/redirect/';
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
