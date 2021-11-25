<?php

namespace Nets\Easy;

/**
 * Representation of Nets order item.
 */
class OrderItem {

  private $reference = '';
  private $productName = '';
  private $quantity = 0;
  private $unit = '';
  private $unitPrice = 0;

  /**
   * Get order item reference (order item id).
   *
   * @return string
   *   The reference.
   */
  public function getReference() {
    return $this->reference;
  }

  /**
   * Set order item references (order item id).
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
   * Get product name for this order item.
   *
   * @return string
   *   The product name.
   */
  public function getProductName() {
    return $this->productName;
  }

  /**
   * Set product name for this order item.
   *
   * @param string $productName
   *   The product name.
   *
   * @return $this
   */
  public function setProductName($productName) {
    $this->productName = $productName;

    return $this;
  }

  /**
   * Get the number (quantity) of items.
   *
   * @return int
   *   The quantity.
   */
  public function getQuantity() {
    return $this->quantity;
  }

  /**
   * Set the number (quantity) of items.
   *
   * @param int $quantity
   *   The quantity.
   *
   * @return $this
   */
  public function setQuantity($quantity) {
    $this->quantity = $quantity;

    return $this;
  }

  /**
   * Get the unit of the item.
   *
   * @return string
   *   The unit.
   */
  public function getUnit() {
    return $this->unit;
  }

  /**
   * Set the unit of the item.
   *
   * @param string $unit
   *   The unit.
   *
   * @return $this
   */
  public function setUnit($unit) {
    $this->unit = $unit;

    return $this;
  }

  /**
   * Get unit price.
   *
   * @return int
   *   The unit price.
   */
  public function getUnitPrice() {
    return $this->unitPrice;
  }

  /**
   * Set unit price.
   *
   * @param int $unitPrice
   *   The unit price.
   *
   * @return $this
   */
  public function setUnitPrice($unitPrice) {
    $this->unitPrice = $unitPrice;

    return $this;
  }

  /**
   * Get the total amount base on unit and unit price.
   *
   * @return float|int
   *   The total amount for this item.
   */
  public function getTotalAmount() {
    return $this->quantity * $this->unitPrice;
  }

  /**
   * Covert the order item to an array matching the format required by the API .
   *
   * @return array
   *   The order item as an array.
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
