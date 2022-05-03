<?php

/**
 * @file
 * Payment provider implementation for Ding!
 */

use Nets\Easy\Checkout;
use Nets\Easy\Notification;
use Nets\Easy\OrderItem;
use Nets\Easy\Exception\PaymentCommunicationException;
use Nets\Easy\Exception\PaymentException;

/**
 * Generate the payment URL to redirect the user to.
 */
function ding_debt_easy_payment_get_url($amount, $params, $callback) {
  // Load the library to get classes used to build the checkout.
  _ding_debt_easy_load_library();

  $params = $params['params'];
  $item_ids = $params['debt_ids'];

  // We assume here that we can get the user's provider id (patron_id) from the
  // session stored information. If not we fall back to 0. The effect of not
  // having this id will be that we can't retry payment if FBS is down or slow.
  // So pending payments that fail at first will hang in pending state. This was
  // the best solution without assuming too much about the provider.
  $patron_id = ding_user_provider_id();
  if (is_null($patron_id)) {
    $patron_id = 0;
    watchdog('ding_debt_easy', 'Unable to get patron id, payment retries is not available', [], WATCHDOG_CRITICAL);
  }

  $checkout = new Checkout();
  $checkout->getOrder()->setCurrency(ding_debt_easy_get_currency());

  /** @var \DingProviderDebt $debt */
  foreach ($params['debts'] as $id => $debt) {
    $item = new OrderItem();
    $item->setReference($id)
      ->setProductName($debt->type)
      ->setQuantity(1)
      ->setUnit('stk')
      // The amount used by the payment gateway is in "øre" hence the
      // conversion as the amount from the provider is in kr.
      ->setUnitPrice($debt->amount * 100);
    $checkout->getOrder()->addOrderItem($item);
  }

  // Set configuration for the checkout.
  $checkout->setIntegrationType(ding_debt_easy_get_integration_type())
    ->setTermsUrl(url(ding_debt_easy_get_term_url(), ['absolute' => TRUE]))
    ->setMerchantTermsUrl(url(ding_debt_easy_get_privacy_url(), ['absolute' => TRUE]))
    ->setReturnUrl(url(ding_debt_easy_get_return_url(), ['absolute' => TRUE]))
    ->setCancelUrl(url(ding_debt_easy_get_cancel_url(), ['absolute' => TRUE]));

  $order_id = _ding_debt_easy_create_order_local($patron_id, $item_ids, $checkout->getOrder()->getTotalAmount());
  $checkout->getOrder()->setReference($order_id);

  // Add notifications (payment.checkout.completed and payment.created).
  $local_record = _ding_debt_easy_get_payment_local($order_id);
  foreach (['payment.checkout.completed', 'payment.cancel.created', 'payment.reservation.created.v2', 'payment.created'] as $type) {
    $notification = new Notification();
    $notification->setName($type)
      ->setAuthorization($local_record['auth'])
      ->setUrl(url(DING_DEBT_EASY_WEBHOOK, ['absolute' => TRUE]));
    $checkout->addNotification($notification);
  }

  // Create payment with the checkout and order as payload.
  $client = _ding_debt_easy_get_client();

  try {
    $res = $client->createPayment($checkout);
  }
  catch (PaymentCommunicationException $exception) {
    watchdog_exception('ding_debt_easy', $exception, 'There is a communication problem with the gateway (Order ID: %order_id)', [
      '%order_id' => $order_id,
    ]);
    drupal_set_message(t('There is a communication problem with the gateway. Please try again later.'));
    _ding_debt_easy_update_status_local($order_id, DING_DEBT_EASY_STATUS_FAILED);
    _ding_debt_easy_remove_personal_info($order_id);

    return DING_DEBT_USER_DEBT_PAGE;
  }
  catch (PaymentException $exception) {
    watchdog_exception('ding_debt_easy', $exception, 'There is a problem with creating the payment for order %order_id', [
      '%order_id' => $order_id,
    ]);
    drupal_set_message(t('There is an error with the payment gateway. Please try again later or contact the library with order ID: %order_id', [
      '%order_id' => $order_id,
    ]));
    _ding_debt_easy_update_status_local($order_id, DING_DEBT_EASY_STATUS_FAILED);
    _ding_debt_easy_remove_personal_info($order_id);

    return DING_DEBT_USER_DEBT_PAGE;
  }

  // Store information about the payment state.
  $payment_id = $res['paymentId'];
  _ding_debt_easy_add_payment_id_local($order_id, $payment_id);

  // Append language code to the URL to change language at the portal.
  $url = $res['hostedPaymentPageUrl'];
  $lang = ding_debt_easy_get_localization();
  if (!empty($lang)) {
    $url .= '&language=' . $lang;
  }

  return $url;
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
    '#weight' => 10,
  ];

  return $form;
}

/**
 * Generate terms form element for the payment page.
 */
function ding_debt_easy_payment_terms() {
  $terms = variable_get('ding_debt_easy_terms', []);

  $form = [];
  $form['ding_debt_easy_terms'] = [
    '#theme' => 'ding_debt_easy_terms',
    '#terms' => $terms['text']['value'],
    '#url' => $terms['url'],
    '#weight' => 20,
  ];

  return $form;
}

/**
 * Generate buttons to submit debts form.
 */
function ding_debt_easy_payment_buttons() {
  $form = [];

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
    '#weight' => 1,
    '#states' => [
      'disabled' => [
        '#ding-debt-debts-form .form-type-checkbox input' => ['checked' => FALSE],
      ],
    ],
  ];

  $form['internal_buttons']['pay_all'] = [
    '#type' => 'submit',
    '#prefix' => '<div class="pay-button">',
    '#value' => t('Pay all debts'),
    '#weight' => 5,
    '#suffix' => '</div>',
    '#submit' => ['ding_debt_debts_form_submit_pay_all'],
  ];

  return $form;
}

/**
 * Added payment status to provider debts.
 *
 * @param \DingProviderDebt[] $debts
 *   Array of provider debt objects.
 *
 * @return DingProviderDebt[]
 *   The debts object enriched with pending and failed status.
 *
 * @throws \DingProviderDoesntImplement
 * @throws \DingProviderNoProvider
 */
function ding_debt_easy_payment_status(array $debts) {
  $patron_id = ding_user_provider_id();
  if (is_null($patron_id)) {
    $patron_id = 0;
    watchdog('ding_debt_easy', 'Unable to get patron id, payment status is not available', [], WATCHDOG_CRITICAL);
  }

  foreach ($debts as &$debt) {
    $record = db_select('ding_debt_easy', 'e')
      ->fields('e')
      ->condition('provider_ids', '%' . $debt->id . '%', 'LIKE')
      ->condition('patron_id', $patron_id)
      ->condition('status', [
        DING_DEBT_EASY_STATUS_COMPLETED,
        DING_DEBT_EASY_STATUS_RESERVED,
        DING_DEBT_EASY_STATUS_PENDING,
        DING_DEBT_EASY_STATUS_FAILED,
      ], 'IN')
      ->orderBy('changed', 'DESC')
      ->execute()
      ->fetchAssoc();

    // To be sure that the "like" statement did not find a sub-string in with
    // the number, this is an extra check.
    $ids = explode(';', $record['provider_ids']);
    if (in_array($debt->id, $ids)) {
      $debt->setStatus($record['status']);
    }
  }

  return $debts;
}
