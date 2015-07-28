<?php

/**
 * @file
 * Test user provider functions.
 */

require_once "ProviderTestCase.php";
require_once dirname(__DIR__) . '/vendor/autoload.php';

/**
 * Test user provider functions.
 */
class UserProviderTest extends ProviderTestCase {

  /**
   * Test user authenticate.
   */
  public function testAuthenticate() {
    $this->provider = 'user';

    $json_responses = array(
      new Reply(
        array(
          // AuthenticatedPatron.
          'authenticated' => TRUE,
          'patron' => array(
            // Patron.
            'birthday' => '1976-05-03',
            'coAddress' => NULL,
            'address' => array(
              // Address
              'country' => 'Danmark',
              'city' => 'Ølstykke',
              'street' => 'Svendsvej 1',
              'postalCode' => '3650',
            ),
            // ISIL of Horsens Bibliotek
            'preferredPickupBranch' => 'DK-761500',
            'onHold' => NULL,
            'patronId' => 72,
            'receiveEmail' => FALSE,
            'blockStatus' => NULL,
            'receiveSms' => TRUE,
            'emailAddress' => NULL,
            'phoneNumber' => '61331330',
            'name' => 'Patron One',
            'receivePostalMail' => FALSE,
            'defaultInterestPeriod' => NULL,
            'resident' => TRUE,
          ),
        )
      ),

      // Unknown user.
      new Reply(
        array(
          // AuthenticatedPatron.
          'authenticated' => FALSE,
          'patron' => NULL,
        )
      ),

      // Blocked user.
      new Reply(
        array(
          // AuthenticatedPatron.
          'authenticated' => FALSE,
          'patron' => NULL,
        )
      ),
    );
    $this->replies($json_responses);

    // Check success.
    $res = $this->providerInvoke('authenticate', '111111', '1111');
    $expected = array(
      'success' => TRUE,
      'user' => array(
        'mail' => NULL,
        'data' => array(
          'display_name' => 'Patron One',
        ),
        'private' => array(
          'branch' => 'DK-761500',
        ),
        'blocked' => FALSE,
      ),
      'creds' => array(
        'patronId' => 72,
        'name' => 'Patron One',
        'phone' => '61331330',
        'mail' => '',
        'phone_notification' => TRUE,
        'mail_notification' => FALSE,
        'preferred_branch' => 'DK-761500',
        'interest_period' => 0,
        'library_card_number' => '111111'
      ),
    );
    $this->assertEquals($expected, $res);

    // Check failure.
    $res = $this->providerInvoke('authenticate', '151019463013', 'banana');
    $expected = array(
      'success' => FALSE,
    );
    $this->assertEquals($expected, $res);

    // Check blocked user (PAT9)
    $res = $this->providerInvoke('authenticate', '999999', '9999');
     $expected = array(
      'success' => FALSE,
    );
    $this->assertEquals($expected, $res);
}

  /**
   * Test user update_pincode.
   */
  public function testUpdatePincode() {
    $this->provider = 'user';

    $json_responses = array(
      new Reply(
        array(
          // AuthenticatedPatron.
          'authenticated' => TRUE,
          'patron' => array(
            // Patron.
            'birthday' => '1976-05-03',
            'coAddress' => NULL,
            'address' => array(
              // Address
              'country' => 'Danmark',
              'city' => 'Ølstykke',
              'street' => 'Svendsvej 1',
              'postalCode' => '3650',
            ),
            // ISIL of Vesterbro bibliotek
            'preferredPickupBranch' => 'DK-761500',
            'onHold' => NULL,
            'patronId' => 72,
            'receiveEmail' => FALSE,
            'blockStatus' => NULL,
            'receiveSms' => TRUE,
            'emailAddress' => NULL,
            'phoneNumber' => '61331330',
            'name' => 'Patron One',
            'receivePostalMail' => FALSE,
            'defaultInterestPeriod' => NULL,
            'resident' => TRUE,
          ),
        )
      ),
      new Reply(
        array(
          // AuthenticatedPatron.
          'authenticated' => TRUE,
          'patron' => array(
            // Patron.
            'birthday' => '1976-05-03',
            'coAddress' => NULL,
            'address' => array(
              // Address
              'country' => 'Danmark',
              'city' => 'Ølstykke',
              'street' => 'Svendsvej 1',
              'postalCode' => '3650',
            ),
            // ISIL of Horsens bibliotek
            'preferredPickupBranch' => 'DK-761500',
            'onHold' => NULL,
            'patronId' => 72,
            'receiveEmail' => FALSE,
            'blockStatus' => NULL,
            'receiveSms' => TRUE,
            'emailAddress' => NULL,
            'phoneNumber' => '61331330',
            'name' => 'Patron One',
            'receivePostalMail' => FALSE,
            'defaultInterestPeriod' => NULL,
            'resident' => TRUE,
          ),
        )
      ),
      new Reply(
        array(
          // AuthenticatedPatron.
          'authenticated' => TRUE,
          'patron' => array(
            // Patron.
            'birthday' => '1976-05-03',
            'coAddress' => NULL,
            'address' => array(
              // Address
              'country' => 'Danmark',
              'city' => 'Ølstykke',
              'street' => 'Svendsvej 1',
              'postalCode' => '3650',
            ),
            // ISIL of Vesterbro bibliotek
            'preferredPickupBranch' => 'DK-761500',
            'onHold' => NULL,
            'patronId' => 72,
            'receiveEmail' => FALSE,
            'blockStatus' => NULL,
            'receiveSms' => TRUE,
            'emailAddress' => NULL,
            'phoneNumber' => '61331330',
            'name' => 'Patron One',
            'receivePostalMail' => FALSE,
            'defaultInterestPeriod' => NULL,
            'resident' => TRUE,
          ),
        )
      ),
      new Reply(
        array(
          // AuthenticatedPatron.
          'authenticated' => TRUE,
          'patron' => array(
            // Patron.
            'birthday' => '1976-05-03',
            'coAddress' => NULL,
            'address' => array(
              // Address
              'country' => 'Danmark',
              'city' => 'Ølstykke',
              'street' => 'Svendsvej 1',
              'postalCode' => '3650',
            ),
            // ISIL of Horsens bibliotek
            'preferredPickupBranch' => 'DK-761500',
            'onHold' => NULL,
            'patronId' => 72,
            'receiveEmail' => FALSE,
            'blockStatus' => NULL,
            'receiveSms' => TRUE,
            'emailAddress' => NULL,
            'phoneNumber' => '61331330',
            'name' => 'Patron One',
            'receivePostalMail' => FALSE,
            'defaultInterestPeriod' => NULL,
            'resident' => TRUE,
          ),
        )
      ),
    );
    $this->replies($json_responses);

    $patron1 = (object) array(
      'creds' => array(
        'patronId' => 72,
        'library_card_number' => '111111'
      ),
    );

    // Change pincode from 1111 to 0000
    $res = $this->providerInvoke('update_pincode', $patron1, '0000');
    $expected = array(
      'creds' => array(
        'patronId' => 72,
        'name' => 'Patron One',
        'phone' => '61331330',
        'mail' => '',
        'phone_notification' => TRUE,
        'mail_notification' => FALSE,
        'preferred_branch' => 'DK-761500',
        'interest_period' => 0,
        'library_card_number' => '111111'
      ),
    );
    $this->assertEquals($expected, $res);


    // Check that the new pincode works.
    $res = $this->providerInvoke('authenticate', '111111', '0000');
    $expected = array(
      'success' => TRUE,
      'user' => array(
        'mail' => NULL,
        'data' => array(
          'display_name' => 'Patron One',
        ),
        'private' => array(
          'branch' => 'DK-761500',
        ),
        'blocked' => FALSE,
      ),
      'creds' => array(
        'patronId' => 72,
        'name' => 'Patron One',
        'phone' => '61331330',
        'mail' => '',
        'phone_notification' => TRUE,
        'mail_notification' => FALSE,
        'preferred_branch' => 'DK-761500',
        'interest_period' => 0,
        'library_card_number' => '111111'
      ),
    );
    $this->assertEquals($expected, $res);

    // Change pincode back from 0000 to 1111
    $res = $this->providerInvoke('update_pincode', $patron1, '1111');
    $expected = array(
      'creds' => array(
        'patronId' => 72,
        'name' => 'Patron One',
        'phone' => '61331330',
        'mail' => '',
        'phone_notification' => TRUE,
        'mail_notification' => FALSE,
        'preferred_branch' => 'DK-761500',
        'interest_period' => 0,
        'library_card_number' => '111111'
      ),
    );
    $this->assertEquals($expected, $res);


    // Check that the new pincode works.
    $res = $this->providerInvoke('authenticate', '111111', '1111');
    $expected = array(
      'success' => TRUE,
      'user' => array(
        'mail' => NULL,
        'data' => array(
          'display_name' => 'Patron One',
        ),
        'private' => array(
          'branch' => 'DK-761500',
        ),
        'blocked' => FALSE,
      ),
      'creds' => array(
        'patronId' => 72,
        'name' => 'Patron One',
        'phone' => '61331330',
        'mail' => '',
        'phone_notification' => TRUE,
        'mail_notification' => FALSE,
        'preferred_branch' => 'DK-761500',
        'interest_period' => 0,
        'library_card_number' => '111111'
      ),
    );
    $this->assertEquals($expected, $res);
  }
}
