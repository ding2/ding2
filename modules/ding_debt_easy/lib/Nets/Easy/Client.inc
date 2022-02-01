<?php

namespace Nets\Easy;

use GuzzleHttp\Client as HttpClient;
use GuzzleHttp\Exception\ClientException;
use Nets\Easy\Exception\PaymentCommunicationException;
use Nets\Easy\Exception\PaymentException;

/**
 * Client to send request to the payment gateway at Nets Easy.
 */
class Client {
  private $httpClient;
  private $secretKey;
  private $checkoutKey;
  private $apiUrl;
  private $apiPaymentsPath = '/v1/payments/';

  public function __construct(HttpClient $httpClient, $secretKey, $checkoutKey, $apiUrl = 'https://api.dibspayment.eu/') {
    $this->httpClient = $httpClient;
    $this->secretKey = $secretKey;
    $this->apiUrl = $apiUrl;

    // The checkout key is only used during embedded checkout process
    // (not implemented yet).
    $this->checkoutKey = $checkoutKey;
  }

  /**
   * Create payment at the gateway.
   *
   * @param Checkout $checkout
   *   Checkout order representation (the request to send to the gateway).
   *
   * @return array
   *   Will return the paymentId and if hosted payment type the
   *   hostedPaymentPageUrl to redirect to.
   *
   * @throws \GuzzleHttp\Exception\GuzzleException
   * @throws \Nets\Easy\Exception\PaymentCommunicationException
   * @throws \Nets\Easy\Exception\PaymentException
   */
  public function createPayment(Checkout $checkout) {
    $options = [
      'headers' => $this->defaultHeaders(),
      'body' => json_encode($checkout->toArray()),
    ];

    try {
      $response = $this->httpClient->request('POST', $this->apiUrl . $this->apiPaymentsPath, $options);
    } catch (ClientException $exception) {
      throw new PaymentCommunicationException($exception->getMessage(), $exception->getCode());
    }

    // Decode result from json payload.
    if (201 === $response->getStatusCode()) {
      return json_decode($response->getBody()->getContents(), TRUE);
    }

    // Handle errors.
    $this->genericErrorHandling($response->getStatusCode(), $response->getBody()->getContents());
  }

  /**
   * Fetch information about a payment at the gateway.
   *
   * @param string $paymentId
   *   ID of the payment to fetch.
   *
   * @return array
   *   Data about the payment as defined at the gateway.
   *
   * @throws \GuzzleHttp\Exception\GuzzleException
   * @throws \Nets\Easy\Exception\PaymentCommunicationException
   * @throws \Nets\Easy\Exception\PaymentException
   */
  public function fetchPayment($paymentId) {
    $options = [
      'headers' => $this->defaultHeaders(),
    ];

    try {
      $response = $this->httpClient->request('GET', $this->apiUrl . $this->apiPaymentsPath . $paymentId, $options);
    } catch (ClientException $exception) {
      throw new PaymentCommunicationException($exception->getMessage(), $exception->getCode());
    }

    // Decode result from json payload.
    if (200 === $response->getStatusCode()) {
      $data = json_decode($response->getBody()->getContents(), TRUE);
      return reset($data);
    }

    // Handle errors.
    $this->genericErrorHandling($response->getStatusCode(), $response->getBody()->getContents());
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
   * @throws \GuzzleHttp\Exception\GuzzleException
   * @throws \Nets\Easy\Exception\PaymentCommunicationException
   * @throws \Nets\Easy\Exception\PaymentException
   */
  public function chargePayment($paymentId, $amount) {
    $options = [
      'headers' => $this->defaultHeaders(),
      'body' => json_encode([
        'amount' => $amount,
      ]),
    ];

    try {
      $response = $this->httpClient->request('POST', $this->apiUrl . $this->apiPaymentsPath . $paymentId . '/charges', $options);
    } catch (ClientException $exception) {
      throw new PaymentCommunicationException($exception->getMessage(), $exception->getCode());
    }

    // Decode result from json payload.
    if (201 === $response->getStatusCode()) {
      $data = json_decode($response->getBody()->getContents(), TRUE);
      return $data['chargeId'];
    }

    // Handle errors.
    $this->genericErrorHandling($response->getStatusCode(), $response->getBody()->getContents());
  }

  /**
   * Helper to handle errors.
   *
   * @param int $code
   *   Http status code from the http client.
   * @param string|array $body
   *   The body from the http request.
   *
   * @throws \Nets\Easy\Exception\PaymentCommunicationException
   * @throws \Nets\Easy\Exception\PaymentException
   */
  private function genericErrorHandling($code, $body) {
    if (empty($body) && !in_array($code, ['400', '500'])) {
      throw new PaymentCommunicationException('Unknown error in connection to the payment gateway (' . $code . ')', $code);
    }

    // Decode response.
    $body = json_decode($body, TRUE);

    // See https://nets-devs.isotop.se/nets-easy/en-EU/api/payment-v1/ for
    // information about the data returned from Nets on 500 and 400.
    if (500 === $code) {
      if (!empty($body['message'])) {
        throw new PaymentException($body['message'], $body['code']);
      }
    }

    if (400 === $code) {
      if (!empty($body['errors'])) {
        $properties = array_keys($body['errors']);
        $property = reset($properties);
        throw new PaymentException($property . ' - ' . reset($body['errors'][$property]), $code);
      }
      if (!empty($body['message'])) {
        throw new PaymentException($body['message'], $code);
      }
    }

    // Ensure all other throws unknown error exception. This is safe as this is
    // the last check in the functions above, so this should always throw an
    // exception.
    $msg = 'Unknown error in connection to the payment gateway';
    throw new PaymentCommunicationException(empty($body['message']) ? $msg : $body['message'], $code);
  }

  /**
   * Default http headers needed to communicate with the gateway.
   *
   * @return array
   *   Headers array indexed by header name.
   */
  private function defaultHeaders() {
    return [
      'Authorization' => $this->secretKey,
      'Content-Type' => 'application/*+json',
      'CommercePlatformTag' => 'DDB CMS',
    ];
  }

}
