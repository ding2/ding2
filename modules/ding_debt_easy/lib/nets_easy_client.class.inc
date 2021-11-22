<?php

namespace Nets\Easy;

/**
 * @class Client
 *
 */
class Client {
  private $secretKey;
  private $checkoutKey;
  private $apiUrl;

  public function __construct($secretKey, $checkoutKey, $apiUrl = 'https://api.dibspayment.eu/v1/payments') {
    $this->secretKey = $secretKey;
    $this->checkoutKey = $checkoutKey;
    $this->apiUrl = $apiUrl;
  }

  /**
   * Create payment at the gateway.
   *
   * @param \Nets\Easy\Checkout $checkout
   *   The
   *
   * @return array
   *   Will return the paymentId and if hosted payment type the
   *   hostedPaymentPageUrl to redirect to.
   */
  public function createPayment($checkout) {
    $ch = curl_init($this->apiUrl);
    curl_setopt_array($ch, [
      CURLOPT_URL => "https://test.api.dibspayment.eu/v1/payments",
      CURLOPT_RETURNTRANSFER => true,
      CURLOPT_ENCODING => "",
      CURLOPT_MAXREDIRS => 10,
      CURLOPT_TIMEOUT => 30,
      CURLOPT_HTTP_VERSION => CURL_HTTP_VERSION_1_1,
      CURLOPT_CUSTOMREQUEST => "POST",
      CURLOPT_POSTFIELDS => $checkout->toJson(),
      CURLOPT_HTTPHEADER => [
        'Authorization: ' . $this->secretKey,
        'CommercePlatformTag: SOME_STRING_VALUE',
        'content-type: application/*+json'
      ],
    ]);

    $result = curl_exec($ch);

    // @TODO: Error handling, parsing
    $err = curl_error($ch);
    curl_close($ch);

    // Decode result from json payload.
    $data = json_decode($result, TRUE);

    // @TODO: Error handling, parsing the $data object.
    // 500
//    {
//      "message": "string",
//      "code": "string",
//      "source": "string"
//    }
    // 400
//    {
//          "errors": {
//          "property1": [
//            "string"
//          ],
//            "property2": [
//            "string"
//          ]
//        }
//    }

    // If not hosted:
//    {
//      "paymentId": "0260000060003b7b47f0833960dc60d6"
//    }
    // Else
//    {
//      "paymentId": "xxxxx",
//      "hostedPaymentPageUrl": "https://test.checkout.dibspayment.eu/hostedpaymentpage/?checkoutKey=xxxxx"
//    }

    return $data;
  }

  public function fetchPayment($paymentId) {

  }

  private function buildCheckout() {

  }
}
