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
  function t($str, $replace = array()) {
    return strtr($str, $replace);
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
        array()
      ),
      new Reply(
        array(
          // Array of...
          array(
            // Fee.
            'payableByClient' => TRUE,
            'amount' => 100,
            'paidDate' => NULL,
            'materials' => array(),
            'reasonMessage' => 'For sent afleveret',
            'dueDate' => '2015-04-07',
            'type' => 'fee',
            'creationDate' => '2015-04-07',
            'feeId' => 56,
          ),
          array(
            // Fee.
            'payableByClient' => TRUE,
            'amount' => 150,
            'paidDate' => NULL,
            'materials' => array(),
            'reasonMessage' => 'Erstatning',
            'dueDate' => '2015-04-07',
            'type' => 'compensation',
            'creationDate' => '2015-04-07',
            'feeId' => 57,
          ),
          array(
            // Fee.
            'payableByClient' => TRUE,
            'amount' => 200,
            'paidDate' => NULL,
            'materials' => array(
              // Array of...
              array(
                // FeeMaterial.
                'recordId' => '870970-basis:29415226',
                'materialGroupName' => 'somewhat strict',
                'materialItemNumber' => '3829213434',
              ),
            ),
            'reasonMessage' => 'bestillingsgebyr',
            'dueDate' => '2015-04-07',
            'type' => 'fee',
            'creationDate' => '2015-04-07',
            'feeId' => 58,
          ),
        )
      ),
    );

    $this->replies($json_responses);

    // TCD1: PAT1 has no debt
    $user = (object) array(
      'creds' => array(
        'patronId' => '72',
      ),
    );

    $res = $this->providerInvoke('list', $user);
    $expected = array();
    $this->assertEquals($expected, $res);

    // TCD2: PAT2 has three unpaid fees and one paid (not shown fees)
    $user = (object) array(
      'creds' => array(
        'patronId' => '73',
      ),
    );

    $res = $this->providerInvoke('list', $user);
    $expected = array(
      56 => new DingProviderDebt(56, array(
        'date' => '2015-04-07',
        'display_name' => 'For sent afleveret',
        'amount' => 100.0,
        'amount_paid' => 0,
        'invoice_number' => NULL,
        'type' => 'fee',
      )),
      57 => new DingProviderDebt(57, array(
        'date' => '2015-04-07',
        'display_name' => 'Erstatning',
        'amount' => 150.0,
        'amount_paid' => 0,
        'invoice_number' => NULL,
        'type' => 'compensation',
      )),
      58 => new DingProviderDebt(58, array(
        'date' => '2015-04-07',
        'display_name' => 'bestillingsgebyr',
        'amount' => 200.0,
        'amount_paid' => 0,
        'invoice_number' => NULL,
        'type' => 'fee',
        'material_number' => '3829213434'
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
            'orderId' => '42',
            'confirmationId' => 2,
            'feeId' => 60,
            'paymentStatus' => 'paymentRegistered',
          ),
        )
      ),
    );

    $this->replies($json_responses);

    $user = (object) array(
      'creds' => array(
        'patronId' => '74',
      ),
    );

    // No problem with repeating this call on same fee as long as same orderId
    $res = $this->providerInvoke('payment_received', $user, array(60), '42');
    $this->assertTrue($res);
  }
}
