<?php
/**
 * @file
 * Implements the OpenruthClient library to talk with the web-service.
 */

class OpenruthClient {

  /**
   * Our SOAP client.
   */
  private $client;

  /**
   * The OpenRuth wsdl url.
   */
  private $wsdl_url;

  /**
   * The OpenRuth agency id.
   */
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
   * Constructor.
   */
  public function __construct($wsdl_url, $agency_id) {
    $this->wsdl_url = $wsdl_url;
    $this->agency_id = $agency_id;
    $options = array(
      'features' => SOAP_SINGLE_ELEMENT_ARRAYS,
      'exceptions' => TRUE,
    );

    // Enable logging.
    if (variable_get('openruth_enable_logging', FALSE)) {
      $this->logging = TRUE;
      $options['trace'] = TRUE;
    }

    // User proxy.
    $proxy = variable_get('openruth_proxy', array());
    if (!empty($proxy) && !empty($proxy['host'])) {
      $options['proxy_host'] = $proxy['host'];
      $options['proxy_port'] = $proxy['port'];
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
      timer_start('openruth_net');
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
      timer_stop('openruth_net');
      if ($this->log_timestamp) {
        $time = round(microtime(TRUE) - $this->log_timestamp, 2);
        $this->log_timestamp = NULL;
      }
      $sensitive = func_get_args();
      // For some reason PHP doesn't have array_flatten, and this is the
      // shortest alternative.
      $replace_values = array();
      foreach (new RecursiveIteratorIterator(new RecursiveArrayIterator($sensitive)) as $value) {
        $replace_values['>' . $value . '<'] = '>' . drupal_substr(md5($value . self::$salt), 0, drupal_strlen($value)) . '<';
      }
      if (isset($time)) {
        watchdog('openruth', 'Sending request (@seconds sec): @xml', array(
          '@xml' => strtr($this->client->__getLastRequest(), $replace_values),
          '@seconds' => $time,
        ), WATCHDOG_DEBUG);
      }
      else {
        watchdog('openruth', 'Sending request: @xml', array('@xml' => strtr($this->client->__getLastRequest(), $replace_values)), WATCHDOG_DEBUG);
      }
      watchdog('openruth', 'Response: @xml', array('@xml' => strtr($this->client->__getLastResponse(), $replace_values)), WATCHDOG_DEBUG);
    }
  }

  /**
   * Holdings information (agency info, location, availability etc.) about an
   * given item.
   */
  public function get_holdings($ids) {
    $this->log_start();
    $res = $this->client->holdings(array(
      'agencyId' => $this->agency_id,
      'itemId' => $ids,
    ));

    $this->log();

    return $res;
  }

  /**
   * Renewing one or more loans.
   */
  public function renew_loan($username, $copy_ids) {
    $this->log_start();
    $res = $this->client->renewLoan(array(
      'agencyId' => $this->agency_id,
      'userId' => $username,
      'copyId' => $copy_ids,
    ));
    $this->log($username);
    if (isset($res->renewLoanError)) {
      return $res->renewLoanError;
    }
    elseif (isset($res->renewLoan)) {
      $result = array();
      foreach ($res->renewLoan as $renew_loan) {
        $result[$renew_loan->copyId] = isset($renew_loan->renewLoanError) ? $renew_loan->renewLoanError : TRUE;
      }
      return $result;
    }
    else {
      return FALSE;
    }
  }

  /**
   * Booking an item.
   */
  public function book_item($username, $provider_id, $count, $start_date, $end_date, $pickup_branch) {
    $this->log_start();
    $res = $this->client->bookItem(array(
      'agencyId' => $this->agency_id,
      'userId' => $username,
      // 'bookingNote' => '',
      'agencyCounter' => $pickup_branch,
      'itemId' => $provider_id,
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
   * Making a reservation in the local system.
   */
  public function order_item($username, $item_id, $count, $order_date, $expiry, $pickup_branch) {
    // Support periodicals.
    if (is_array($item_id)) {
      $order_item_id = array(
        'itemId' => $item_id[0],
        'itemSerialPartId' => $item_id[1],
      );
    }
    else {
      $order_item_id = array(
        'itemId' => $item_id,
      );
    }
    $this->log_start();
    $res = $this->client->orderItem(array(
      'agencyId' => $this->agency_id,
      'userId' => $username,
      // 'orderNote' => '',
      'orderLastInterestDate' => $expiry,
      'agencyCounter' => $pickup_branch,
      'orderOverRule' => FALSE,
      'orderPriority' => 'normal',
      'orderItemId' => $order_item_id,
    ));
    $this->log($username);
    if (isset($res->orderItemError)) {
      return $res->orderItemError;
    }
    elseif (isset($res->orderItem)) {
      $result = array();
      foreach ($res->orderItem as $order_item) {
        $result[$order_item->orderItemId->itemId] = isset($order_item->orderItemError) ? $order_item->orderItemError : TRUE;
      }
      return $result;
    }
    else {
      return FALSE;
    }
  }

  /**
   * Get information about number of copies in a booking available at various
   * times.
   */
  public function booking_info() {
  }

  /**
   * Updating details about a booking.
   */
  public function update_booking() {
  }

  /**
   * Cancelling a booking of an item.
   */
  public function cancel_booking($bookings_id) {
    $this->log_start();
    $res = $this->client->cancelBooking(array(
      'agencyId' => $this->agency_id,
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
   * Get information about an Agency.
   */
  public function get_agency_info() {
    $agency_info = array();
    $this->log_start();
    $res = $this->client->agencyCounters(array(
      'agencyId' => $this->agency_id,
    ));
    $this->log();
    if ($res->agencyCounters instanceof stdClass) {
      $agency_info = array(
        'agencyId' => $res->agencyCounters->agencyId,
        'agencyName' => $res->agencyCounters->agencyName,
        'orderActivePeriod' => $res->agencyCounters->orderActivePeriod,
      );
    }
    return (object) $agency_info;

  }
  /**
   * Get list of agencycounters.
   *
   * @return Array
   */
  public function get_agencycounters() {
    $agencys = array();
    $this->log_start();
    $res = $this->client->agencyCounters(array(
      'agencyId' => $this->agency_id,
    ));
    $this->log();
    if ($res->agencyCounters instanceof stdClass && is_array($res->agencyCounters->agencyCounterInfo)) {
      foreach ($res->agencyCounters->agencyCounterInfo as $agency) {
        $agencys[$agency->agencyCounter] = $agency->agencyCounterName;
      }
      return $agencys;
    }
    return NULL;
  }

  /**
   * Updating details about a reservation in the local system.
   */
  public function update_order($order_id, $pickup_branch, $expiry) {
    $this->log_start();
    $res = $this->client->updateOrder(array(
      'agencyId' => $this->agency_id,
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
   * Deleting a reservation.
   */
  public function cancel_order($order_id) {
    $this->log_start();
    $res = $this->client->cancelOrder(array(
      'agencyId' => $this->agency_id,
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
   * Changing user info (pin-code, contact, preferences etc.).
   */
  public function update_userinfo($name, $pass, $changes) {
    static $mapping = array(
      'pass' => 'userPinCodeNew',
      'mail' => 'userEmail',
      'mobile_phone' => 'userMobilePhone',
      'reminder' => 'userPreReturnReminder',
      'first_name' => 'userFirstName',
      'last_name' => 'userLastName',
      'preferred_branch' => 'agencyCounter',
      'reservation_pause_start' => 'userAbsenceStartDate',
      'reservation_pause_stop' => 'userAbsenceEndDate',
    );
    $args = array(
      'agencyId' => $this->agency_id,
      'userId' => $name,
      'userPinCode' => $pass,
    );
    foreach ($mapping as $from => $to) {
      if (isset($changes[$from])) {
        $args[$to] = $changes[$from];
      }
    }

    $this->log_start();
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
   * Performing a user check.
   *
   * Checks whether the user exists in the system and user's various rights
   * and parameters.
   *
   * @param string $username
   *   The users login name/number.
   * @param string $pin_code
   *   The users pin-code.
   *
   * @return mixed
   *   UserCheck response object, a string error message or FALSE.
   */
  public function user_check($username, $pin_code) {
    $this->log_start();
    $res = $this->client->userCheck(array(
      'agencyId' => $this->agency_id,
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
   * User's status, includings loans, orders, ILLs and fines.
   */
  public function user_status($username, $pin_code) {
    $this->log_start();
    $res = $this->client->userStatus(array(
      'agencyId' => $this->agency_id,
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
   * Paying user fines.
   */
  public function add_payment($username, $amount, $transaction_id = NULL) {
    $params = array(
      'agencyId' => $this->agency_id,
      'userId' => $username,
      'feeAmountPaid' => $amount,
    );
    if ($transaction_id) {
      $params['userPaymentTransactionId'] = $transaction_id;
    }

    $this->log_start();
    $res = $this->client->userPayment($params);
    $this->log();
    if (isset($res->userPaymentError)) {
      watchdog('openruth', 'openRuth error: %response', array(
        '%response' => $res->userPaymentError,
      ), WATCHDOG_CRITICAL);
      return FALSE;
    }
    elseif (isset($res->userPaymentOk)) {
      return TRUE;
    }
    else {
      return FALSE;
    }
  }
}
