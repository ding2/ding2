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
  private $apiPaymentsPath = '/v1/payments/';

  public function __construct($secretKey, $checkoutKey, $apiUrl = 'https://api.dibspayment.eu/') {
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
    $curl = curl_init();
    curl_setopt_array($curl, [
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
        'CommercePlatformTag: SOME_STRING_VALUE',
        'content-type: application/*+json'
      ],
    ]);

    $result = curl_exec($curl);

    // @TODO: Error handling, parsing
    $err = curl_error($curl);
    curl_close($curl);

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
    $curl = curl_init();
    curl_setopt_array($curl, [
      CURLOPT_URL => $this->apiUrl . $this->apiPaymentsPath . $paymentId,
      CURLOPT_RETURNTRANSFER => true,
      CURLOPT_ENCODING => "",
      CURLOPT_MAXREDIRS => 10,
      CURLOPT_TIMEOUT => 30,
      CURLOPT_HTTP_VERSION => CURL_HTTP_VERSION_1_1,
      CURLOPT_CUSTOMREQUEST => "GET",
      CURLOPT_HTTPHEADER => [
        'Authorization: ' . $this->secretKey,
        'CommercePlatformTag: DDB CMS'
      ],
    ]);

    $result = curl_exec($curl);
    $err = curl_error($curl);

    // @TODO: Error handling.

    curl_close($curl);

    $data = json_decode($result, TRUE);

    return reset($data);
  }

  public function chargePayment($paymentId, $amount) {
    $curl = curl_init();

    // The gateway supports partial payments, but we will always pay the whole
    // amount.
    $payload = [
      'amount' =>  $amount
    ];

    curl_setopt_array($curl, [
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
        "content-type: application/*+json"
      ],
    ]);

    $result = curl_exec($curl);
    $err = curl_error($curl);

    // @TODO: Error handling.
    // {"message":"Cannot overcharge payment. Reserved amount: 596. Previously charged amount: 596. Tried to charge: 596.","code":"1001","source":"Internal"}


    curl_close($curl);

    $data = json_decode($result, TRUE);

    return $data['chargeId'];
  }
}
