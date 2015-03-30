<?php

/**
 * @file
 * Test user provider functions.
 */

require_once "ProviderTestCase.php";
require_once 'includes/classes/FBS.php';
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
            'blockStatus' => array(
              // Array of...
              array(
                // Blockstatus.
                'blockedReason' => '3424',
                'blockedSince' => '1993-10-15',
                'message' => 'You are dead.',
              ),
            ),
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

    // Check success.
    $res = $this->providerInvoke('authenticate', '151019463013', '1234');
    $expected = array(
      'success' => TRUE,
      'user' => array(
        'mail' => 'onkel@danny.dk',
        'data' => array(
          'display_name' => 'Dan Turrell',
        ),
        'private' => array(
          'branch' => 113,
        ),
        'blocked' => FALSE,
      ),
      'creds' => array(
        'patronId' => 234143,
        'name' => 'Dan Turrell',
        'phone' => '80345210',
        'mail' => 'onkel@danny.dk',
        'phone_notification' => NULL,
        'mail_notification' => NULL,
        'preferred_branch' => '113',
        'interest_period' => 30,
      ),
    );
    $this->assertEquals($expected, $res);

    // Check failure.
    $res = $this->providerInvoke('authenticate', '151019463013', 'banana');
    $expected = array(
      'success' => FALSE,
    );
    $this->assertEquals($expected, $res);

    // Check blocked.
    $res = $this->providerInvoke('authenticate', '151019463013', '1234');
    $expected = array(
      'success' => TRUE,
      'user' => array(
        'mail' => 'onkel@danny.dk',
        'data' => array(
          'display_name' => 'Dan Turrell',
        ),
        'private' => array(
          'branch' => 113,
        ),
        'blocked' => TRUE,
        'blocks' => array(
          'You are dead.',
        ),
      ),
      'creds' => array(
        'patronId' => 234143,
        'name' => 'Dan Turrell',
        'phone' => '80345210',
        'mail' => 'onkel@danny.dk',
        'phone_notification' => NULL,
        'mail_notification' => NULL,
        'preferred_branch' => '113',
        'interest_period' => 30,
      ),
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
            'birthday' => '1946-10-15',
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
      new Reply(
        array(
          // AuthenticatedPatron.
          'authenticated' => TRUE,
          'patron' => array(
            // Patron.
            'birthday' => '1946-10-15',
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

    $user = (object) array(
      'creds' => array(
        'patronId' => '123',
      ),
    );

    // Check success.
    $res = $this->providerInvoke('update_pincode', $user, '9999');
    $expected = array(
      'creds' => array(
        'patronId' => 234143,
        'name' => 'Dan Turrell',
        'phone' => '80345210',
        'mail' => 'onkel@danny.dk',
        'phone_notification' => NULL,
        'mail_notification' => NULL,
        'preferred_branch' => '113',
        'interest_period' => 30,
      ),
    );
    $this->assertEquals($expected, $res);


    // Check that the new pincode works.
    $res = $this->providerInvoke('authenticate', '151019463013', '9999');
    $expected = array(
      'success' => TRUE,
      'user' => array(
        'mail' => 'onkel@danny.dk',
        'data' => array(
          'display_name' => 'Dan Turrell',
        ),
        'private' => array(
          'branch' => 113,
        ),
        'blocked' => FALSE,
      ),
      'creds' => array(
        'patronId' => 234143,
        'name' => 'Dan Turrell',
        'phone' => '80345210',
        'mail' => 'onkel@danny.dk',
        'phone_notification' => NULL,
        'mail_notification' => NULL,
        'preferred_branch' => '113',
        'interest_period' => 30,
      ),
    );
    $this->assertEquals($expected, $res);
  }
}
