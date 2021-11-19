<?php

class NetsEasyClient {
  private $secretKey;
  private $checkoutKey;
  private $apiUrl;

  public function __construct($secretKey, $checkoutKey, $apiUrl = 'https://api.dibspayment.eu/v1/payments') {
    $this->secretKey = $secretKey;
    $this->checkoutKey = $checkoutKey;
    $this->apiUrl = $apiUrl;
  }

  public function createPayment(array $order, $integrationType = 'HostedPaymentPage') {

//    $payload = file_get_contents('payload.json');
//    assert(json_decode($payload) && json_last_error() == JSON_ERROR_NONE);
//
//    $ch = curl_init($this->apiUrl);
//    curl_setopt($ch, CURLOPT_CUSTOMREQUEST, 'POST');
//    curl_setopt($ch, CURLOPT_POSTFIELDS, $payload);
//    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
//    curl_setopt($ch, CURLOPT_HTTPHEADER, array(
//      'Content-Type: application/json',
//      'Accept: application/json',
//      'Authorization: ' . $this->secretKey));
//    $result = curl_exec($ch);

    // Error handling, parsing
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
//      "paymentId": "0260000060003b7b47f0833960dc60d6",
//      "hostedPaymentPageUrl": "https://test.checkout.dibspayment.eu/hostedpaymentpage/?checkoutKey=090284ec577876"
//    }
  }

  public function fetchPayment($paymentId) {

  }

  private function buildCheckout() {

  }
}
