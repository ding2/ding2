<?php

namespace Nets\Easy;

/**
 * @class Checkout
 *
 * Representation of nets easy order.
 */
class Checkout {
  private $integrationType;
  private $termsUrl;
  private $merchantTermsUrl;
  private $consumer = [
    'reference' => '',
    'email' => '',
  ];
  private $returnUrl;
  private $cancelUrl;
  private $order;

  /**
   * Default constructor.
   */
  public function __construct() {
    $this->order = new Order();
  }

  /**
   * @return string
   */
  public function getIntegrationType() {
    return $this->integrationType;
  }

  /**
   * @param string $integrationType
   *
   * @return $this
   */
  public function setIntegrationType($integrationType) {
    $this->integrationType = $integrationType;

    return $this;
  }

  /**
   * @return string
   */
  public function getTermsUrl() {
    return $this->termsUrl;
  }

  /**
   * @param string $termsUrl
   *
   * @return $this
   */
  public function setTermsUrl($termsUrl) {
    $this->termsUrl = $termsUrl;

    return $this;
  }

  /**
   * @return string
   */
  public function getMerchantTermsUrl() {
    return $this->merchantTermsUrl;
  }

  /**
   * @param string $merchantTermsUrl
   *
   * @return $this
   */
  public function setMerchantTermsUrl($merchantTermsUrl) {
    $this->merchantTermsUrl = $merchantTermsUrl;

    return $this;
  }

  /**
   * @return string
   */
  public function getConsumerReference() {
    return $this->consumer['reference'];
  }

  /**
   * @param string $reference
   *
   * @return $this
   */
  public function setConsumeReference($reference) {
    $this->consumer['reference'] = $reference;

    return $this;
  }

  /**
   * @return string
   */
  public function getConsumerMail() {
    return $this->consumer['email'];
  }

  /**
   * @param string $mail
   *
   * @return $this
   */
  public function setConsumeMail($mail) {
    $this->consumer['email'] = $mail;

    return $this;
  }

  /**
   * @return string
   */
  public function getReturnUrl() {
    return $this->returnUrl;
  }

  /**
   * @param string $returnUrl
   *
   * @return $this
   */
  public function setReturnUrl($returnUrl) {
    $this->returnUrl = $returnUrl;

    return $this;
  }

  /**
   * @return string
   */
  public function getCancelUrl() {
    return $this->cancelUrl;
  }

  /**
   * @param string $cancelUrl
   *
   * @return $this
   */
  public function setCancelUrl($cancelUrl) {
    $this->cancelUrl = $cancelUrl;

    return $this;
  }

  /**
   * @return \Nets\Easy\Order
   */
  public function getOrder() {
    return $this->order;
  }

  /**
   * @param string $order
   *
   * @return $this
   */
  public function setOrder($order) {
    $this->order = $order;

    return $this;
  }

  /**
   * Build and encoded the checkout as json string.
   *
   * @return false|string
   *   JSON string or FALSE on error.
   */
  public function toJson() {
    $payload = [
      'checkout' => [
        'integrationType' => $this->getIntegrationType(),
        'termsUrl' => $this->getTermsUrl(),
        'merchantTermsUrl'  => $this->getMerchantTermsUrl(),
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
        'consumerType' => [
          'supportedTypes' => [ 'B2C' ],
          'default' => 'B2C',
        ],
        // FBS handles information about the consumer, so Nets should not ask for
        // address etc.
        'merchantHandlesConsumerData' => TRUE,
        'consumer' => $this->consumer,
        'returnUrl' => $this->returnUrl,
        'cancelUrl' => $this->cancelUrl,
      ],
      'order' => $this->getOrder()->toArray(),
    ];

    return json_encode($payload);
  }
}
