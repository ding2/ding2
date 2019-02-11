<?php

/**
 * @file
 * Object with the ILL request.
 */

 /**
  * DingIllRequest.
  */
class DingIllRequest {
  private $orderId;
  private $pids;
  private $pickUpBranch;
  private $name;
  private $address;
  private $email;
  private $phone;

  /**
   * Set the ILL request order ID.
   *
   * @var string $order_id
   *   The ILL request order ID returned from OpenPlatform on a successful
   *   request.
   */
  public function setId($order_id) {
    $this->orderId = $order_id;
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
   * @var string $branch_id
   *   The branch ID of the branch where the material should be picked up.
   */
  public function setPickupBranch($branch_id) {
    $this->pickUpBranch = $branch_id;
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

}
