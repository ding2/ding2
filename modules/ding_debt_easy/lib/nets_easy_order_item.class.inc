<?php

namespace Nets\Easy;

/**
 * @class NetsEasyOrderItem
 *
 * Representation of Nets order item.
 */
class OrderItem {
  private $reference = '';
  private $productName = '';
  private $quantity = 0;
  private $unit = '';
  private $unitPrice = 0;

  /**
   * @return string
   */
  public function getReference() {
    return $this->reference;
  }

  /**
   * @param string $reference
   *
   * @return $this
   */
  public function setReference($reference) {
    $this->reference = $reference;

    return $this;
  }

  /**
   * @return string
   */
  public function getProductName() {
    return $this->productName;
  }

  /**
   * @param string $productName
   *
   * @return $this
   */
  public function setProductName($productName) {
    $this->productName = $productName;

    return $this;
  }

  /**
   * @return int
   */
  public function getQuantity() {
    return $this->quantity;
  }

  /**
   * @param int $quantity
   *
   * @return $this
   */
  public function setQuantity($quantity) {
    $this->quantity = $quantity;

    return $this;
  }

  /**
   * @return string
   */
  public function getUnit() {
    return $this->unit;
  }

  /**
   * @param string $unit
   *
   * @return $this
   */
  public function setUnit($unit) {
    $this->unit = $unit;

    return $this;
  }

  /**
   * @return int
   */
  public function getUnitPrice() {
    return $this->unitPrice;
  }

  /**
   * @param int $unitPrice
   *
   * @return $this
   */
  public function setUnitPrice($unitPrice) {
    $this->unitPrice = $unitPrice;

    return $this;
  }

  /**
   * @return float|int
   */
  public function getTotalAmount() {
    return $this->quantity * $this->unitPrice;
  }

  /**
   * @return array
   */
  public function toArray() {
    $item = [
      'reference' => $this->getReference(),
      'name' => $this->getProductName(),
      'quantity' => $this->getQuantity(),
      'unit' => $this->getUnit(),
      'unitPrice' => $this->getUnitPrice(),
    ];
    $item['grossTotalAmount'] = $this->getTotalAmount();
    $item['netTotalAmount'] = $this->getTotalAmount();

    return $item;
  }
}
