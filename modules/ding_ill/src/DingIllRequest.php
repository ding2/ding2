<?php

/**
 * @file
 * Object with the ILL request.
 */

/**
 * DingIllRequest.
 */
class DingIllRequest {
  private $address;
  private $email;
  private $name;
  private $orderId;
  private $orderType = 'normal';
  private $phone;
  private $pids;
  private $pickUpBranch;
  private $pin;
  private $token;

  /**
   * Set the ILL request order ID.
   *
   * @var string $orderId
   *   The ILL request order ID returned from OpenPlatform on a successful
   *   request.
   */
  public function setId($orderId) {
    $this->orderId = $orderId;
  }

  /**
   * Get the ILL request order ID.
   *
   * @var string
   *   The order ID of the ILL request from a successful OpenPlatform order
   *   request.
   */
  public function getId() {
    return $this->orderId;
  }

  /**
   * Set pickup branch.
   *
   * @var string $branchId
   *   The branch ID of the branch where the material should be picked up.
   */
  public function setPickupBranch($branchId) {
    $this->pickUpBranch = $branchId;
  }

  /**
   * Get the pickup branch ID.
   *
   * @return string
   *   The branch ID of the branch where the requested material ends up.
   */
  public function getPickupBranch() {
    return $this->pickUpBranch;
  }

  /**
   * Set the name of the patron making the ILL request.
   *
   * @param string $name
   *   The name of the patron.
   */
  public function setName($name) {
    $this->name = $name;
  }

  /**
   * Get the name of the patron making the ILL request.
   *
   * @return string
   *   The name of the patron making the ILL request.
   */
  public function getName() {
    return $this->name;
  }

  /**
   * Set the address of the patron making the ILL request.
   *
   * @param string $address
   *   The address of the patron making the ILL request.
   */
  public function setAddress($address) {
    $this->address = $address;
  }

  /**
   * Get the address of the patron making the ILL request.
   *
   * @return string
   *   The address of the patron making the ILL request.
   */
  public function getAddress() {
    return $this->address;
  }

  /**
   * Set the email of the patron making the ILL request.
   *
   * @var string $email
   *   The email of the patron making the ILL request.
   */
  public function setEmail($email) {
    $this->email = $email;
  }

  /**
   * Get the email of the patron making the ILL request.
   *
   * @return string
   *   The email address of the patron making the ILL request.
   */
  public function getEmail() {
    return $this->email;
  }

  /**
   * Set the phone number of the patron making the ILL request.
   *
   * @param string $phone
   *   The phone number of the patron making the ILL request.
   */
  public function setPhone($phone) {
    $this->phone = $phone;
  }

  /**
   * Get the phone number of the patron making the ILL request.
   *
   * @return string
   *   The phone number of the patron making the ILL request.
   */
  public function getPhone() {
    return $this->phone;
  }

  /**
   * Set the materials to request.
   *
   * @var array $pids
   *   The PIDs for them materials you want to make an ILL request on.
   */
  public function setMaterials(array $pids) {
    $this->pids = $pids;
  }

  /**
   * Return materials from the request.
   *
   * @return array
   *   The PIDs of the materials for the request.
   */
  public function getMaterials() {
    return $this->pids;
  }

  /**
   * Set the order type.
   *
   * @param string $orderType
   *   The type of order.
   */
  public function setOrderType($orderType) {
    $this->orderType = $orderType;
  }

  /**
   * Get the order type.
   *
   * @return string
   *   The order type.
   */
  public function getOrderType() {
    return $this->orderType;
  }

  /**
   * Set the token for the request.
   *
   * @param string $token
   *   The request token.
   */
  public function setToken($token) {
    $this->token = $token;
  }

  /**
   * Get the request token.
   *
   * @return string
   *   The request token generated from library and user information.
   */
  public function getToken() {
    return $this->token;
  }

  /**
   * Set pin code for the patron.
   *
   * @param string $pin
   *   The patron's pin code.
   */
  public function setPin($pin) {
    $this->pin = $pin;
  }

  /**
   * Get the patron's pin code.
   *
   * @return string
   *   The patron's pin code.
   */
  public function getPin() {
    return $this->pin;
  }

}
