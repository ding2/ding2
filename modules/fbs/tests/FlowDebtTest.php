<?php

/**
 * @file
 * Test loan flows.
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
class FlowDebtTest extends ProviderTestCase {

  /**
   * Test basic user functions.
   *
   * Testgroup F9
   * Issue DDBFBS-38
   *
   * @group flow
   */
  public function testBasic() {
    $this->provider = 'user';
    // Define DingEntity.
    $this->requireDing('ding_entity', 'ding_entity.module');
    // // Define DingProviderUserException.
    // $this->requireDing('ding_provider', 'ding_provider.exceptions.inc');
    // Define DingProviderLoan.
    $this->requireDing('ding_provider', 'ding_provider.debt.inc');

    // Step 1
    // Login.
    $json_responses = array(
      new Reply(
        array(
          // AuthenticatedPatron.
          'authenticated' => TRUE,
          'patron' => array(
            // Patron.
            'birthday' => '1946-03-19',
            'coAddress' => NULL,
            'address' => array(
              // Address
              'country' => 'Danmark',
              'city' => 'København',
              'street' => 'Alhambravej 1',
              'postalCode' => '1826',
            ),
            // ISIL of Vesterbro bibliotek
            'preferredPickupBranch' => '113',
            'onHold' => NULL,
            'patronId' => 234143,
            'recieveEmail' => TRUE,
            'blockStatus' => NULL,
            'recieveSms' => FALSE,
            'emailAddress' => 'onkel@danny.dk',
            'phoneNumber' => '80345210',
            'name' => 'Dan Turrell',
            'receivePostalMail' => FALSE,
            'defaultInterestPeriod' => 30,
            'resident' => TRUE,
          ),
        )
      ),
    );

    $this->replies($json_responses);

    $res = $this->providerInvoke('authenticate', '151019463013', '1234');

    $this->assertTrue($res['success']);
    $user = (object) array('creds' => $res['creds']);

    // Step 2
    // List fees.
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
          array(
            // Fee.
            'payableByClient' => TRUE,
            'amount' => '9.99',
            'paidDate' => NULL,
            'materials' => array(
              // Array of...
              array(
                // FeeMaterial.
                'recordId' => 43,
                'materialGroupName' => 'Material group',
                'materialItemNumber' => 523,
              ),
            ),
            'reasonMessage' => 'You were late.',
            'dueDate' => '2015-09-09',
            'type' => 'late',
            'creationDate' => '2015-03-09',
            'feeId' => 556,
          ),
          array(
            // Fee.
            'payableByClient' => TRUE,
            'amount' => '9.99',
            'paidDate' => NULL,
            'materials' => array(
              // Array of...
              array(
                // FeeMaterial.
                'recordId' => 24,
                'materialGroupName' => 'Material group',
                'materialItemNumber' => 3424,
              ),
            ),
            'reasonMessage' => 'You were late.',
            'dueDate' => '2015-09-09',
            'type' => 'late',
            'creationDate' => '2015-03-09',
            'feeId' => 557,
          ),
          array(
            // Fee.
            'payableByClient' => TRUE,
            'amount' => '9.99',
            'paidDate' => NULL,
            'materials' => array(
              // Array of...
              array(
                // FeeMaterial.
                'recordId' => 423,
                'materialGroupName' => 'Material group',
                'materialItemNumber' => 434,
              ),
            ),
            'reasonMessage' => 'You were late.',
            'dueDate' => '2015-09-09',
            'type' => 'late',
            'creationDate' => '2015-03-09',
            'feeId' => 558,
          ),
        )
      ),
    );
    $this->replies($json_responses);
    $this->provider = 'debt';
    $res = $this->providerInvoke('list', $user);
    $this->assertCount(4, $res);

    // Step 3
    // Pay off two fees.
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
    $res = $this->providerInvoke('payment_received', $user, array(556, 557), 'order-123');
    $this->assertTrue($res);

    $paid_date = date('Y-m-d');
    // Step 4
    // Check that fees is now paid.
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
          array(
            // Fee.
            'payableByClient' => TRUE,
            'amount' => '0',
            'paidDate' => $paid_date,
            'materials' => array(
              // Array of...
              array(
                // FeeMaterial.
                'recordId' => 43,
                'materialGroupName' => 'Material group',
                'materialItemNumber' => 523,
              ),
            ),
            'reasonMessage' => 'You were late.',
            'dueDate' => '2015-09-09',
            'type' => 'late',
            'creationDate' => '2015-03-09',
            'feeId' => 556,
          ),
          array(
            // Fee.
            'payableByClient' => TRUE,
            'amount' => '0',
            'paidDate' => $paid_date,
            'materials' => array(
              // Array of...
              array(
                // FeeMaterial.
                'recordId' => 24,
                'materialGroupName' => 'Material group',
                'materialItemNumber' => 3424,
              ),
            ),
            'reasonMessage' => 'You were late.',
            'dueDate' => '2015-09-09',
            'type' => 'late',
            'creationDate' => '2015-03-09',
            'feeId' => 557,
          ),
          array(
            // Fee.
            'payableByClient' => TRUE,
            'amount' => '9.99',
            'paidDate' => NULL,
            'materials' => array(
              // Array of...
              array(
                // FeeMaterial.
                'recordId' => 423,
                'materialGroupName' => 'Material group',
                'materialItemNumber' => 434,
              ),
            ),
            'reasonMessage' => 'You were late.',
            'dueDate' => '2015-09-09',
            'type' => 'late',
            'creationDate' => '2015-03-09',
            'feeId' => 558,
          ),
        )
      ),
    );

    $this->replies($json_responses);
    $res = $this->providerInvoke('list', $user);
    $this->assertCount(4, $res);
    $this->assertEquals($res[556]->amount, $res[556]->amount_paid);
    $this->assertEquals($res[557]->amount, $res[557]->amount_paid);
    $this->assertEquals(0, $res[555]->amount_paid);
    $this->assertEquals(0, $res[558]->amount_paid);
  }
}
