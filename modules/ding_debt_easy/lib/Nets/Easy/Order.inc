<?php

namespace Nets\Easy;

/**
 * Representation of Nets Easy order.
 */
class Order {

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
   * @param OrderItem $orderItem
   *   Order item.
   *
   * @return $this
   */
  public function addOrderItem(OrderItem $orderItem) {

    $exists = FALSE;
    foreach ($this->orderItems as $item) {
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
    /** @var OrderItem $item */
    foreach ($this->orderItems as $index => $item) {
      if ($reference === $item->getReference()) {
        unset($this->orderItems[$index]);
      }
    }
  }

  /**
   * Get the orders total amount.
   *
   * @return int
   *   The order items amount summed up.
   */
  public function getTotalAmount() {
    $amount = 0;
    foreach ($this->orderItems as $item) {
      $amount += $item->getTotalAmount();
    }

    return $amount;
  }

  /**
   * Covert the order to an array matching the format required by the API .
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

    /** @var OrderItem $item */
    foreach ($this->orderItems as $item) {
      $order['items'][] = $item->toArray();
    }
    $order['amount'] = $this->getTotalAmount();

    return $order;
  }

}
