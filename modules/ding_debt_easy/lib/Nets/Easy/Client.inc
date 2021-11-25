<?php

namespace Nets\Easy;

use Nets\Easy\Exception\PaymentCommunicationException;
use Nets\Easy\Exception\PaymentException;

/**
 * @class Client
 * Client to send request to the payment gateway Nets easy.
 */
class Client {
  private $secretKey;
  private $checkoutKey;
  private $apiUrl;
  private $apiPaymentsPath = '/v1/payments/';

  public function __construct($secretKey, $checkoutKey, $apiUrl = 'https://api.dibspayment.eu/') {
    $this->secretKey = $secretKey;
    $this->apiUrl = $apiUrl;

    // The checkout key is only used during embedded checkout process
    // (not implemented yet).
    $this->checkoutKey = $checkoutKey;
  }

  /**
   * Create payment at the gateway.
   *
   * @param \Nets\Easy\Checkout $checkout
   *   Checkout order representation (the request to send to the gateway).
   *
   * @return array
   *   Will return the paymentId and if hosted payment type the
   *   hostedPaymentPageUrl to redirect to.
   *
   * @throws \Nets\Easy\Exception\PaymentCommunicationException
   * @throws \Nets\Easy\Exception\PaymentException
   */
  public function createPayment($checkout) {
    $ch = curl_init();
    curl_setopt_array($ch, [
      CURLOPT_URL => $this->apiUrl . $this->apiPaymentsPath,
      CURLOPT_RETURNTRANSFER => true,
      CURLOPT_ENCODING => "",
      CURLOPT_MAXREDIRS => 10,
      CURLOPT_TIMEOUT => 30,
      CURLOPT_HTTP_VERSION => CURL_HTTP_VERSION_1_1,
      CURLOPT_CUSTOMREQUEST => "POST",
      CURLOPT_POSTFIELDS => $checkout->toJson(),
      CURLOPT_HTTPHEADER => [
        'Authorization: ' . $this->secretKey,
        'CommercePlatformTag: DDB CMS',
        'content-type: application/*+json',
      ],
    ]);

    $response = curl_exec($ch);
    $code = curl_getinfo($ch, CURLINFO_HTTP_CODE);
    $err = curl_error($ch);
    curl_close($ch);

    // Decode result from json payload.
    if (201 === $code) {
      return json_decode($response, TRUE);
    }

    // Handle errors.
    $this->genericErrorHandling($err, $code, $response);
  }

  /**
   * Fetch information about at payment at the gateway.
   *
   * @param string $paymentId
   *   ID of the payment to fetch.
   *
   * @return array
   *   Data about the payment as defined at the gateway.
   *
   * @throws \Nets\Easy\Exception\PaymentCommunicationException
   * @throws \Nets\Easy\Exception\PaymentException
   */
  public function fetchPayment($paymentId) {
    $ch = curl_init();
    curl_setopt_array($ch, [
      CURLOPT_URL => $this->apiUrl . $this->apiPaymentsPath . $paymentId,
      CURLOPT_RETURNTRANSFER => true,
      CURLOPT_ENCODING => "",
      CURLOPT_MAXREDIRS => 10,
      CURLOPT_TIMEOUT => 30,
      CURLOPT_HTTP_VERSION => CURL_HTTP_VERSION_1_1,
      CURLOPT_CUSTOMREQUEST => "GET",
      CURLOPT_HTTPHEADER => [
        'Authorization: ' . $this->secretKey,
        'CommercePlatformTag: DDB CMS',
        'content-type: application/*+json',
      ],
    ]);

    $response = curl_exec($ch);
    $code = curl_getinfo($ch, CURLINFO_HTTP_CODE);
    $err = curl_error($ch);
    curl_close($ch);

    // Decode result from json payload.
    if (200 === $code) {
      $data = json_decode($response, TRUE);
      return reset($data);
    }

    // Handle errors.
    $this->genericErrorHandling($err, $code, $response);
  }

  /**
   * Charge payment (capture) at the gateway.
   *
   * @param string $paymentId
   *   The payment id to charge.
   * @param int $amount
   *   The amount to charge of the payment.
   *
   * @return string
   *   The ID of the charge made.
   *
   * @throws \Nets\Easy\Exception\PaymentCommunicationException
   * @throws \Nets\Easy\Exception\PaymentException
   */
  public function chargePayment($paymentId, $amount) {
    $ch = curl_init();

    // The gateway supports partial payments, but we will always pay the whole
    // amount.
    $payload = [
      'amount' =>  $amount
    ];

    curl_setopt_array($ch, [
      CURLOPT_URL => $this->apiUrl . $this->apiPaymentsPath . $paymentId . '/charges',
      CURLOPT_RETURNTRANSFER => true,
      CURLOPT_ENCODING => "",
      CURLOPT_MAXREDIRS => 10,
      CURLOPT_TIMEOUT => 30,
      CURLOPT_HTTP_VERSION => CURL_HTTP_VERSION_1_1,
      CURLOPT_CUSTOMREQUEST => "POST",
      CURLOPT_POSTFIELDS => json_encode($payload),
      CURLOPT_HTTPHEADER => [
        'Authorization: ' . $this->secretKey,
        'CommercePlatformTag: DDB CMS',
        "content-type: application/*+json",
      ],
    ]);

    $response = curl_exec($ch);
    $code = curl_getinfo($ch, CURLINFO_HTTP_CODE);
    $err = curl_error($ch);
    curl_close($ch);

    // Decode result from json payload.
    if (201 === $code) {
      $data = json_decode($response, TRUE);
      return $data['chargeId'];
    }

    // Handle errors.
    $this->genericErrorHandling($err, $code, $response);
  }

  /**
   * Helper to handle errors.
   *
   * @param string $err
   *   Error message form the http client.
   * @param int $code
   *   Http status code from the http client.
   * @param string|array $response
   *   The response from the http client.
   *
   * @throws PaymentCommunicationException
   * @throws PaymentException
   */
  private function genericErrorHandling($err, $code, $response) {
    if (!empty($err)) {
      throw new PaymentCommunicationException($err, $code);
    }

    if (empty($response) && !in_array($code, ['400', '500'])) {
      throw new PaymentCommunicationException('Unknown error in connection to the payment gateway (' . $code . ')', $code);
    }

    // Decode response.
    $response = json_decode($response, TRUE);

    // See https://nets-devs.isotop.se/nets-easy/en-EU/api/payment-v1/ for
    // information about the data returned from Nets on 500 and 400.
    if (500 === $code) {
      if (!empty($response['message'])) {
        throw new PaymentException($response['message'], $response['code']);
      }
    }

    if (400 === $code) {
      if (!empty($response['errors'])) {
        foreach ($response['errors'] as $property => $message) {
          throw new PaymentException($property . ' - ' . $message, $code);
        }
      }
      if (!empty($response['message'])) {
        throw new PaymentException($response['message'], $code);
      }
    }

    // Ensure all other throws unknown error exception. This is safe as this is
    // the last check in the functions above, so this should always throw an
    // exception.
    $msg = 'Unknown error in connection to the payment gateway';
    throw new PaymentCommunicationException(empty($response['message']) ? $msg : $response['message'], $code);
  }

}
