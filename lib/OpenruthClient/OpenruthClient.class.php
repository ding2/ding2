<?php
// $Id$

class OpenruthClient {

  /**
   * Our SOAP client.
   **/
  private $client;

  /**
   * The OpenRuth wsdl url.
   **/
  private $wsdl_url;

  /**
   * The OpenRuth agency id.
   **/
  private $agency_id;

  /**
   * Whether we're logging requests.
   */
  private $logging = FALSE;

  /**
   * Start time of request, used for logging.
   */
  private $log_timestamp = NULL;

  /**
   * The salt which will be used to scramble sensitive information in logging
   * across all requests for the page load.
   */
  private static $salt;

  /**
   * Constructor
   */
  public function __construct($wsdl_url, $agency_id) {
    $this->wsdl_url = $wsdl_url;
    $this->agency_id = $agency_id;
    $options = array(
      'features' => SOAP_SINGLE_ELEMENT_ARRAYS,
      'exceptions' => TRUE,
    );
    if (variable_get('openruth_enable_logging', FALSE)) {
      $this->logging = TRUE;
      $options['trace'] = TRUE;
    }
    $this->client = new SoapClient($this->wsdl_url, $options);
    self::$salt = rand();
  }

  /**
   * Log start of request, for adding to log entry later.
   */
  private function log_start() {
    if ($this->logging) {
      $this->log_timestamp = microtime(TRUE);
    }
  }

  /**
   * Log last request, if logging is enabled.
   *
   * @param ...
   *   A variable number of arguments, whose values will be redacted.
   */
  private function log() {
    if ($this->logging) {
      if ($this->log_timestamp) {
        $time = round(microtime(TRUE) - $this->log_timestamp, 2);
        $this->log_timestamp = NULL;
      }
      $sensitive = func_get_args();
      // For some reason PHP doesn't have array_flatten, and this is the
      // shortest alternative.
      $replace_values = array();
      foreach (new RecursiveIteratorIterator(new RecursiveArrayIterator($sensitive)) as $value) {
        $replace_values['>' . $value . '<'] = '>' . substr(md5($value . self::$salt), 0, strlen($value)) . '<';
      }
      if ($time) {
        watchdog('openruth', 'Sending request (@seconds sec): @xml',array('@xml' => strtr($this->client->__getLastRequest(), $replace_values), '@seconds' => $time), WATCHDOG_DEBUG);

      } else {
        watchdog('openruth', 'Sending request: @xml',array('@xml' => strtr($this->client->__getLastRequest(), $replace_values)), WATCHDOG_DEBUG);
      }
      watchdog('openruth', 'Response: @xml',array('@xml' => strtr($this->client->__getLastResponse(), $replace_values)), WATCHDOG_DEBUG);
    }
  }

  /**
   * Get information about an agency's counters
   */
  public function get_agency_counters() {
    $this->log_start();
    $res = $this->client->agencyCounters(array(
             'agencyId' =>  $this->agency_id,
           ));
    $this->log();
    if (isset($res->agencyError)) {
      return $res->agencyError;
    }
    elseif (isset($res->agencyCounters) && isset($res->agencyCounters->agencyCounterInfo)) {
      $result = array();
      foreach ($res->agencyCounters->agencyCounterInfo as $agencyCounterInfo) {
        $result[$agencyCounterInfo->agencyCounter] = $agencyCounterInfo->agencyCounterName;
      }
      return $result;
    }
    else {
      return FALSE;
    }
  }

  /**
   * Holdings information (agency info, location, availability etc.) about an given item.
   */
  public function get_holdings($ids) {
    $this->log_start();
    $res = $this->client->holdings(array(
             'agencyId' =>  $this->agency_id,
             'itemId' => $ids,
           ));
    $this->log();
    if (isset($res->agencyError)) {
      return $res->agencyError;
    }
    elseif (isset($res->holding)) {
      $holdings = array();
      foreach ($res->holding as $holding) {
        $available = $holding->agencyHoldings->itemAvailability == 'copies available for loan and reservation';
        $reservable = $available || $holding->agencyHoldings->itemAvailability == 'no copies available, but item can be reserved';
        $h = array(
          'local_id' => $holding->itemId,
          'available' => $available,
          'reservable' => $reservable,
          'show_reservation_button' => $reservable,
          'holdings' => array(),
          'reserved_count' => (int) $holding->ordersCount,
          'issues' => array(),
        );

        $total = 0;
        $available = 0;
        if ($holding->itemHoldings) {
          foreach ($holding->itemHoldings as $itemHolding) {
            $holding_reservable = FALSE;
            $fields = array('itemLocation', 'itemComingLocation');

            foreach ($fields as $field) {
              if (isset($itemHolding->{$field})){
                foreach ($itemHolding->{$field} as $itemLocation) {
                  if ($itemLocation->bookingAllowed) {
                    $holding_reservable = TRUE;
                  }
                  $total += $itemLocation->copiesCount;
                  $available += $itemLocation->copiesAvailableCount;
                  $parts = array();
                  if (isset($itemLocation->agencyBranchId->agencyBranchName)) {
                    $parts[] = $itemLocation->agencyBranchId->agencyBranchName;
                  }
                  if (isset($itemLocation->agencyDepartmentId->agencyDepartmentName)) {
                    $parts[] = $itemLocation->agencyDepartmentId->agencyDepartmentName;
                  }
                  if (isset($itemLocation->agencyCollectionId->agencyCollectionName)) {
                    $parts[] = $itemLocation->agencyCollectionId->agencyCollectionName;
                  }
                  if (isset($itemLocation->agencyPlacementId->agencyPlacementName)) {
                    $parts[] = $itemLocation->agencyPlacementId->agencyPlacementName;
                  }
                  if ($parts) {
                    $h['holdings'][] = join(' → ', $parts);
                  }
                }
              }
            }

            if (isset($itemHolding->itemSerialPartId) ||
              isset($itemHolding->itemSerialPartVolume) ||
              isset($itemHolding->itemSerialPartIssue)) {
              $issue = array(
                'local_id' => $itemHolding->itemSerialPartId,
                'reservable' => $holding_reservable,
              );
              $h['issues'][$itemHolding->itemSerialPartVolume][$itemHolding->itemSerialPartIssue] = $issue;
            }
          }
        }
        $h['total_count'] = $total;
        $h['reservable_count'] = $available;
        if (sizeof($h['issues'])) {
          $h['holdings'] = array_unique($h['holdings']);
        }
        $holdings[$holding->itemId] = $h;
      }
      return $holdings;
    }
    else {
      return FALSE;
    }
  }

  /**
   * Renewing one or more loans
   */
  public function renew_loan($username, $copy_ids) {
    $this->log_start();
    $res = $this->client->renewLoan(array(
             'agencyId' =>  $this->agency_id,
             'userId' => $username,
             'copyId' => $copy_ids,
      ));
    $this->log($username);
    if (isset($res->renewLoanError)) {
      return $res->renewLoanError;
    }
    elseif (isset($res->renewLoan)) {
      $result = array();
      foreach ($res->renewLoan as $renewLoan) {
        $result[$renewLoan->copyId] = isset($renewLoan->renewLoanError) ? $renewLoan->renewLoanError : TRUE;
      }
      return $result;
    }
    else {
      return FALSE;
    }
  }

  /**
   * Booking an item
   */
  public function book_item($username, $provider_id, $count, $start_date, $end_date, $pickup_branch) {
    $this->log_start();
    $res = $this->client->bookItem(array(
             'agencyId' =>  $this->agency_id,
             'userId' => $username,
             // 'bookingNote' => '',
             'agencyCounter' => $pickup_branch,
             'itemId' =>$provider_id,
             'bookingTotalCount' => $count,
             'bookingStartDate' => $start_date,
             'bookingEndDate' => $end_date,

      ));
    $this->log($username);
    if (isset($res->bookingError)) {
      return $res->bookingError;
    }
    elseif (isset($res->bookingOk)) {
      return TRUE;
    }
    else {
      return FALSE;
    }
  }

  /**
   * Making a reservation in the local system
   */
  public function order_item($username, $provider_id, $expiry, $pickup_branch) {
    $this->log_start();
    $res = $this->client->orderItem(array(
             'agencyId' =>  $this->agency_id,
             'userId' => $username,
             // 'orderNote' => '',
             'orderLastInterestDate' => $expiry,
             'agencyCounter' => $pickup_branch,
             'orderOverRule' => FALSE,
             'orderPriority' => 'normal',
             'orderItemId' => array(
               'itemId' => $provider_id,
             ),
      ));
    $this->log($username);
    if (isset($res->orderItemError)) {
      return $res->orderItemError;
    }
    elseif (isset($res->orderItem)) {
      $result = array();
      foreach ($res->orderItem as $orderItem) {
        $result[$orderItem->orderItemId->itemId] = isset($orderItem->orderItemError) ? $orderItem->orderItemError : TRUE;
      }
      return $result;
    }
    else {
      return FALSE;
    }
  }

  /**
   * Get information about number of copies in a booking available at various times
   */
  public function booking_info() {}

  /**
   * Updating details about a booking
   */
  public function update_booking() {}

  /**
   * Cancelling a booking of an item
   */
  public function cancel_booking($bookings_id) {
    $this->log_start();
    $res = $this->client->cancelBooking(array(
             'agencyId' =>  $this->agency_id,
             'bookingId' => $bookings_id,
      ));
    $this->log();
    if (isset($res->bookingError)) {
      return $res->bookingError;
    }
    elseif (isset($res->bookingOk)) {
      return TRUE;
    }
    else {
      return FALSE;
    }
  }

  /**
   * Updating details about a reservation in the local system
   */
  public function update_order($order_id, $pickup_branch, $expiry) {
    $this->log_start();
    $res = $this->client->updateOrder(array(
             'agencyId' =>  $this->agency_id,
             'orderId' => $order_id,
             'orderNote' => '',
             'orderLastInterestDate' => $expiry,
             'agencyCounter' => $pickup_branch,
      ));
    $this->log();
    if (isset($res->updateOrderError)) {
      return $res->updateOrderError;
    }
    elseif (isset($res->updateOrderOk)) {
      return TRUE;
    }
    else {
      return FALSE;
    }
  }

  /**
   * Deleting a reservation
   */
  public function cancel_order($order_id) {
    $this->log_start();
    $res = $this->client->cancelOrder(array(
             'agencyId' =>  $this->agency_id,
             'orderId' => $order_id,
      ));
    $this->log();
    if (isset($res->cancelOrderError)) {
      return $res->cancelOrderError;
    }
    elseif (isset($res->cancelOrderOk)) {
      return TRUE;
    }
    else {
      return FALSE;
    }
  }

  /**
   * Changing userinfo (pincode, contact, preferences etc.)
   */
  public function update_userinfo($name, $pass, $changes) {
    static $mapping = array(
      'pass' => 'userPinCodeNew',
      'mail' => 'userEmail',
      // 'phone' => 'userTelephone', // No?
      'mobile_phone' => 'userMobilePhone',
      'reminder' => 'userPreReturnReminder',
      'first_name' => 'userFirstName',
      'last_name' => 'userLastName',
      'preferred_branch' => 'agencyCounter',
    );
    $this->log_start();
    $args = array(
             'agencyId' =>  $this->agency_id,
             'userId' => $name,
             'userPinCode' => $pass,
    );
    foreach ($mapping as $from => $to) {
      if (isset($changes[$from])) {
        $args[$to] = $changes[$from];
      }
    }

    $res = $this->client->updateUserInfo($args);
    $this->log($name, $pass);
    if (isset($res->userError)) {
      return $res->userError;
    }
    elseif (isset($res->updateUserInfoOk)) {
      return TRUE;
    }
    else {
      return FALSE;
    }
  }

  /**
   * Performing a user check (whether the user exists in the system and user's various rights and parameters)
   *
   * @return mixed
   *   UserCheck response object, a string error message or FALSE.
   */
  public function user_check($username, $pin_code) {
    $res = $this->client->userCheck(array(
             'agencyId' =>  $this->agency_id,
             'userId' => $username,
             'userPinCode' => $pin_code,
      ));
    $this->log($username, $pin_code);
    if (isset($res->userError)) {
      return $res->userError;
    }
    elseif (isset($res->userCheck)) {
      return $res->userCheck;
    }
    else {
      return FALSE;
    }
  }

  /**
   * User's status, includings loans, orders, ILLs and fines
   */
  public function user_status($username, $pin_code) {
    $this->log_start();
    $res = $this->client->userStatus(array(
             'agencyId' =>  $this->agency_id,
             'userId' => $username,
             'userPinCode' => $pin_code,
      ));
    $this->log($username, $pin_code);
    if (isset($res->userError)) {
      return $res->userError;
    }
    elseif (isset($res->userStatus)) {
      return $res->userStatus;
    }
    else {
      return FALSE;
    }
  }

  /**
   * paying user fines
   */
  public function user_payment($username, $amount, $transaction_id = NULL) {
    $this->log_start();
    $params = array(
      'agencyId' =>  $this->agency_id,
      'userId' => $username,
      'feeAmountPaid' => $amount,
    );
    if ($transaction_id) {
      $params['userPaymentTransactionId'] = $transaction_id;
    }

    $res = $this->client->userPayment($params);
    $this->log($username);
    if (isset($res->userPaymentError)) {
      return $res->userPaymentError;
    }
    elseif (isset($res->userPaymentOk)) {
      return TRUE;
    }
    else {
      return FALSE;
    }
  }

}