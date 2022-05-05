<?php

namespace Nets\Easy;

/**
 * Representation of Nets Easy order.
 */
class Checkout {
  private $integrationType;
  private $termsUrl;
  private $merchantTermsUrl;
  private $returnUrl;
  private $cancelUrl;
  private $order;
  private $notifications = [];

  /**
   * Default constructor.
   */
  public function __construct() {
    $this->order = new Order();
  }

  /**
   * Get integration type.
   *
   * @return string
   *   The integration type (HostedPaymentPage or EmbeddedCheckout).
   */
  public function getIntegrationType() {
    return $this->integrationType;
  }

  /**
   * Set integration type.
   *
   * @param string $integrationType
   *   The integration type (HostedPaymentPage or EmbeddedCheckout).
   *
   * @return $this
   */
  public function setIntegrationType($integrationType) {
    $this->integrationType = $integrationType;

    return $this;
  }

  /**
   * Get terms declaration URL.
   *
   * @return string
   *   The URL to terms declaration.
   */
  public function getTermsUrl() {
    return $this->termsUrl;
  }

  /**
   * Set terms declaration URL.
   *
   * @param string $termsUrl
   *   The URL to use for terms declaration.
   *
   * @return $this
   */
  public function setTermsUrl($termsUrl) {
    $this->termsUrl = $termsUrl;

    return $this;
  }

  /**
   * Get privacy declaration URL.
   *
   * @return string
   *   The URL to privacy declaration.
   */
  public function getMerchantTermsUrl() {
    return $this->merchantTermsUrl;
  }

  /**
   * Get privacy declaration URL.
   *
   * @param string $merchantTermsUrl
   *   The URL to privacy declaration.
   *
   * @return $this
   */
  public function setMerchantTermsUrl($merchantTermsUrl) {
    $this->merchantTermsUrl = $merchantTermsUrl;

    return $this;
  }

  /**
   * Get return URL.
   *
   * @return string
   *   The return URL to use.
   */
  public function getReturnUrl() {
    return $this->returnUrl;
  }

  /**
   * Set return URL.
   *
   * @param string $returnUrl
   *   The URL to set as return URL.
   *
   * @return $this
   */
  public function setReturnUrl($returnUrl) {
    $this->returnUrl = $returnUrl;

    return $this;
  }

  /**
   * Get cancel URL.
   *
   * @return string
   *   The cancel URL to use.
   */
  public function getCancelUrl() {
    return $this->cancelUrl;
  }

  /**
   * Set cancel URL.
   *
   * @param string $cancelUrl
   *   The URL to set as cancel URL.
   *
   * @return $this
   */
  public function setCancelUrl($cancelUrl) {
    $this->cancelUrl = $cancelUrl;

    return $this;
  }

  /**
   * Get order.
   *
   * @return \Nets\Easy\Order
   *   The order for this checkout.
   */
  public function getOrder() {
    return $this->order;
  }

  /**
   * Set order.
   *
   * @param Order $order
   *   Set order to the checkout.
   *
   * @return $this
   */
  public function setOrder(Order $order) {
    $this->order = $order;

    return $this;
  }

  /**
   * Get notifications.
   *
   * @return \Nets\Easy\Notification[]
   *   The notifications for this checkout.
   */
  public function getNotifications() {
    return $this->notifications;
  }

  /**
   * Set notifications.
   *
   * @param Notification[] $notifications
   *   Set notifications to the checkout.
   *
   * @return $this
   */
  public function setNotifications(array $notifications) {
    $this->notifications = $notifications;

    return $this;
  }

  /**
   * Add single notification.
   *
   * @param \Nets\Easy\Notification $notification
   *   Notification to add.
   *
   * @return $this
   */
  public function addNotification(Notification $notification) {
    $this->notifications[] = $notification;

    return $this;
  }

  /**
   * Build and encoded the checkout as json string.
   *
   * @return array
   *   The complete order that matches the payment gateways format.
   */
  public function toArray() {
    $checkout = [
      'checkout' => [
        'integrationType' => $this->getIntegrationType(),
        'termsUrl' => $this->getTermsUrl(),
        'merchantTermsUrl'  => $this->getMerchantTermsUrl(),
        // We need to only reserve the payment. The charging will be done after
        // provider has accepted API call.
        'charge' => FALSE,
        // Limit data stored in the browser at Nets: the checkout will not
        // remember the current consumer on this device.
        'publicDevice' => TRUE,
        // 'url' => 'ONLY WITH Embedded checkout to load order from'
        'appearance' => [
          'displayOptions' => [
            'showMerchantName' => TRUE,
            'showOrderSummary' => TRUE,
          ],
        ],
        'consumerType' => [
          'supportedTypes' => ['B2C'],
          'default' => 'B2C',
        ],
        // Ding2 handles information about the consumer, so Nets should not ask
        // for address etc.
        'merchantHandlesConsumerData' => TRUE,
        'returnUrl' => $this->returnUrl,
        'cancelUrl' => $this->cancelUrl,
      ],
      'order' => $this->getOrder()->toArray(),
    ];

    // Add notifications (web-hooks) to the array.
    if (!empty($this->getNotifications())) {
      $checkout['notifications'] = [
        'webhooks' => [],
      ];
      foreach ($this->getNotifications() as $notification) {
        $checkout['notifications']['webhooks'][] = $notification->toArray();
      }
    }

    return $checkout;
  }

}
