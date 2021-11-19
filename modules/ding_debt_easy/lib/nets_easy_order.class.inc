<?php

/**
 * @file
 * Representation of nets easy order.
 */

/**
 * @class NetsEasyOrder
 *
 * Representation of nets easy order.
 */
class NetsEasyOrder {

  private $currency = 'DKK';
  private $reference = '';
  private $orderItems = [];

  /**
   * Get currency for this order.
   *
   * @return string
   *   Return the currency (default: DKK)
   */
  public function getCurrency() {
    return $this->currency;
  }

  /**
   * Set currency.
   *
   * @param string $currency
   *   The currency to use (should be a three letter string)
   *
   * @return $this
   */
  public function setCurrency($currency) {
    $this->currency = $currency;

    return $this;
  }

  /**
   * Get reference.
   *
   * @return string
   *   The reference string.
   */
  public function getReference() {
    return $this->reference;
  }

  /**
   * Set reference
   *
   * @param string $reference
   *   The reference to set.
   *
   * @return $this
   */
  public function setReference($reference) {
    $this->reference = $reference;

    return $this;
  }

  /**
   * Add order item to this order.
   *
   * @param \NetsEasyOrderItem $orderItem
   *   Order item.
   *
   * @return $this
   */
  public function addOrderItem($orderItem) {

    $exists = FALSE;
    foreach ($this->orderItems as $index => $item) {
      if ($orderItem->getReference() === $item->getReference()) {
        $exists = TRUE;
      }
    }

    if (!$exists) {
      $this->orderItems[] = $orderItem;
    }

    return $this;
  }

  /**
   * Remove order item based on item reference.
   *
   * @param string $reference
   *   Order item reference.
   */
  public function removeOrderItem($reference) {
    /** @var NetsEasyOrderItem $item */
    foreach ($this->orderItems as $index => $item) {
      if ($reference === $item->getReference()) {
        unset($this->orderItems[$index]);
      }
    }
  }

  /**
   * Change the order to an array that can be converted to json.
   *
   * @return array
   *   The order with items as an array.
   */
  public function toArray() {
    $order = [
      'items' => [],
      'amount' => 0,
      'currency' => $this->getCurrency(),
      'reference' => $this->getReference(),
   ];

    /** @var \NetsEasyOrderItem $item */
    foreach ($this->orderItems as $item) {
      $order['items'][] = $item->toArray();
      $order['amount'] += $item->getTotalAmount();
    }

    return $order;
  }
}
