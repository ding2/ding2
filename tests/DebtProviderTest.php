<?php

/**
 * @file
 * Test debt provider functions.
 */

require_once "ProviderTestCase.php";
require_once dirname(__DIR__) . '/vendor/autoload.php';

if (!function_exists('t')) {
  /**
   * DingProviderLoan::__construct() calls this, mock it.
   */
  function t($str) {
    return $str;
  }
}

/**
 * Test debt provider functions.
 */
class ProviderTest extends ProviderTestCase {

  /**
   * Test debt list.
   */
  public function testList() {
    $this->provider = 'debt';
    // Define DingEntity.
    $this->requireDing('ding_entity', 'ding_entity.module');
    // // Define DingProviderUserException.
    // $this->requireDing('ding_provider', 'ding_provider.exceptions.inc');
    // Define DingProviderLoan.
    $this->requireDing('ding_provider', 'ding_provider.debt.inc');

    $json_responses = array(
      new Reply(
        array(
          // Array of...
          array(
            // Fee.
            'payableByClient' => TRUE,
            'amount' => '99.99',
            'paidDate' => NULL,
            'materials' => array(
              // Array of...
              array(
                // FeeMaterial.
                'recordId' => 123,
                'materialGroupName' => 'Material group',
                'materialItemNumber' => 321,
              ),
            ),
            'reasonMessage' => 'You were late.',
            'dueDate' => '2015-09-09',
            'type' => 'late',
            'creationDate' => '2015-03-09',
            'feeId' => 555,
          ),
        )
      ),
    );

    $this->replies($json_responses);

    $user = (object) array(
      'creds' => array(
        'patronId' => '123',
      ),
    );

    $res = $this->providerInvoke('list', $user);
    $expected = array(
      '555' => new DingProviderDebt('555', array(
        'date' => '2015-03-09',
        'display_name' => 'You were late.',
        'amount' => '99.99',
        'amount_paid' => 0,
        'invoice_number' => NULL,
        'type' => 'late',
      ))
    );
    $this->assertEquals($expected, $res);
  }

  /**
   * Test debt payment_received.
   */
  public function testPaymentRecieved() {
    $this->provider = 'debt';
    // Define DingEntity.
    $this->requireDing('ding_entity', 'ding_entity.module');
    // // Define DingProviderUserException.
    // $this->requireDing('ding_provider', 'ding_provider.exceptions.inc');
    // Define DingProviderLoan.
    $this->requireDing('ding_provider', 'ding_provider.debt.inc');

    $json_responses = array(
      new Reply(
        array(
          // Array of...
          array(
            // PaymentConfirmation.
            'orderId' => 'order-123',
            'confirmationId' => 1,
            'feeId' => 1,
            'paymentStatus' => 'paymentRegistered',
          ),
          array(
            // PaymentConfirmation.
            'orderId' => 'order-123',
            'confirmationId' => 2,
            'feeId' => 2,
            'paymentStatus' => 'paymentRegistered',
          ),
        )
      ),
    );

    $this->replies($json_responses);

    $user = (object) array(
      'creds' => array(
        'patronId' => '123',
      ),
    );

    $res = $this->providerInvoke('payment_received', $user, array(1, 2), 'order-123');
    $this->assertTrue($res);
  }
}
