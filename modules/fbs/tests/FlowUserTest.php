<?php

/**
 * @file
 * Test loan flows.
 */

require_once "ProviderTestCase.php";
require_once dirname(__DIR__) . '/vendor/autoload.php';

/**
 * Test user provider functions.
 */
class FlowUserTest extends ProviderTestCase {

  /**
   * Test basic user functions.
   *
   * Testgroup F8
   * Issue DDBFBS-37
   *
   * @group flow
   */
  public function testRenew() {
    $this->provider = 'user';

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
    // Change pincode.
    // Reuse response.
    $this->replies($json_responses);
    $res = $this->providerInvoke('update_pincode', $user, '9999');
    $this->assertNotEmpty($res['creds']);

    // Step 3
    // Check that the previous pincode doesn't work.
    $json_responses = array(
      // Unknown user.
      new Reply(
        array(
          // AuthenticatedPatron.
          'authenticated' => FALSE,
          'patron' => NULL,
        )
      ),
    );

    $this->replies($json_responses);
    $res = $this->providerInvoke('authenticate', '151019463013', '1234');

    $this->assertFalse($res['success']);

    // Step 4
    // Check that the new pincode work.
    $json_responses = array(
      // Unknown user.
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
    $res = $this->providerInvoke('authenticate', '151019463013', '9999');

    $this->assertTrue($res['success']);

  }
}
