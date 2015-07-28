<?php

/**
 * @file
 * Test loan provider functions.
 */

require_once "ProviderTestCase.php";
require_once dirname(__DIR__) . '/vendor/autoload.php';

if (!function_exists('ding_provider_build_entity_id')) {
  /**
   * Loan list calls this, mock it.
   */
  function ding_provider_build_entity_id($id, $agency = '') {
    return $id . ($agency ? ":" . $agency : '');
  }
}


if (!function_exists('t')) {
  /**
   * DingProviderLoan::__construct() calls this, mock it.
   */
  function t($str, $replace = array()) {
    return strtr($str, $replace);
  }
}

/**
 * Test loan provider functions.
 */
class LoanProviderTest extends ProviderTestCase {

  /**
   * Test loan list.
   */
  public function testList() {
    $this->provider = 'loan';
    // Define DingEntity.
    $this->requireDing('ding_entity', 'ding_entity.module');
    // Define DingProviderUserException.
    $this->requireDing('ding_provider', 'ding_provider.exceptions.inc');
    // Define DingProviderLoan.
    $this->requireDing('ding_provider', 'ding_provider.loan.inc');

    $json_responses = array(
      // TCLL1: Patron (PAT10) has no loans
      new Reply(
        array()
      ),

      // TCLL2: Patron (PAT11) has a renewable loan
      new Reply(
        array(
          // Array of...
          array(
            // Loan.
            'isRenewable' => TRUE,
            'loanDetails' => array(
              // LoanDetails.
              'recordId' => '870970-basis:06686923',
              'dueDate' => '2016-04-25',
              'loanDate' => '2015-04-01T12:05:13.383',
              'materialGroupName' => 'somewhat strict',
              'materialItemNumber' => '4025573671',
              'loanId' => 80,
            ),
            'renewalStatusList' => array("renewed"), // Giver ingen mening for et første lån
          ),
        )
      ),

      // TCLL3: Patron (PAT12) has a loan that has reached max limit of renewables
      /**new Reply(
        array(
          // Array of...
          array(
            // Loan.
            'isRenewable' => FALSE,
            'loanDetails' => array(
              // LoanDetails.
              'recordId' => 'RECID31',
              'dueDate' => 'DUEDATE31',
              'loanDate' => 'LOANDATE31',
              'materialGroupName' => 'Material group',
              'materialItemNumber' => 'ITEMNUM31',
              'loanId' => 31,
            ),
            'renewalStatusList' => array(
              'deniedMaxRenewalsReached',
            ),
          ),
        )
      ), **/

      // TCLL4: Patron (PAT13) with multiple loans, both renewable and not
      /**new Reply(
        array(
          // Array of...
          array(
            // Loan.
            'isRenewable' => TRUE,
            'loanDetails' => array(
              // LoanDetails.
              'recordId' => 'RECID32',
              'dueDate' => 'DUEDATE32',
              'loanDate' => 'LOANDATE32',
              'materialGroupName' => 'Material group',
              'materialItemNumber' => 'ITEMNUM32',
              'loanId' => 32,
            ),
            'renewalStatusList' => array(),
          ),
          array(
            // Loan.
            'isRenewable' => TRUE,
            'loanDetails' => array(
              // LoanDetails.
              'recordId' => 'RECID33',
              'dueDate' => 'DUEDATE33',
              'loanDate' => 'LOANDATE33',
              'materialGroupName' => 'Material group',
              'materialItemNumber' => 'ITEMNUM33',
              'loanId' => 33,
            ),
            'renewalStatusList' => array(),
          ),
          array(
            // Loan.
            'isRenewable' => FALSE,
            'loanDetails' => array(
              // LoanDetails.
              'recordId' => 'RECID34',
              'dueDate' => 'DUEDATE34',
              'loanDate' => 'LOANDATE34',
              'materialGroupName' => 'Material group',
              'materialItemNumber' => 'ITEMNUM34',
              'loanId' => 34,
            ),
            'renewalStatusList' => array(
              'deniedReserved',
            ),
          ),
          array(
            // Loan.
            'isRenewable' => FALSE,
            'loanDetails' => array(
              // LoanDetails.
              'recordId' => 'RECID35',
              'dueDate' => 'DUEDATE35',
              'loanDate' => 'LOANDATE35',
              'materialGroupName' => 'Material group',
              'materialItemNumber' => 'ITEMNUM35',
              'loanId' => 35,
            ),
            'renewalStatusList' => array(
              'deniedOtherReason',
            ),
          ),
        )
      ), **/

      // Some simple periodical rendering tests.
      new Reply(
        array(
          // Array of...
          array(
            // Loan.
            'isRenewable' => TRUE,
            'loanDetails' => array(
              // LoanDetails.
              'recordId' => '870970-basis:06686923',
              'dueDate' => '2016-04-25',
              'loanDate' => '2015-04-01T12:05:13.383',
              'materialGroupName' => 'somewhat strict',
              'materialItemNumber' => '4025573671',
              'loanId' => 80,
              'periodical' => array(
                // Periodical.
                'volume' => 2,
                'volumeYear' => 2011,
                'volumeNumber' => 3,
              ),
            ),
            'renewalStatusList' => array(),
          ),
          array(
            // Loan.
            'isRenewable' => TRUE,
            'loanDetails' => array(
              // LoanDetails.
              'recordId' => '870970-basis:06686923',
              'dueDate' => '2016-04-25',
              'loanDate' => '2015-04-01T12:05:13.383',
              'materialGroupName' => 'somewhat strict',
              'materialItemNumber' => '4025573671',
              'loanId' => 81,
              'periodical' => array(
                // Periodical.
                'volume' => 4,
                'volumeYear' => NULL,
                'volumeNumber' => NULL,
              ),
            ),
            'renewalStatusList' => array(),
          )
        )
      ),

    );
    $this->replies($json_responses);

    // TCLL1: Loaner (PAT10) with no loans
    $user = (object) array(
      'creds' => array(
        'patronId' => '81',
      ),
    );

    // Check success.
    $res = $this->providerInvoke('list', $user);
    $expected = array();
    $this->assertEquals($expected, $res);


    // TCLL2: Loaner (PAT11) with renewable loan
    $user = (object) array(
      'creds' => array(
        'patronId' => '84',
      ),
    );

    $res = $this->providerInvoke('list', $user);
    $expected = array(
      80 => new DingProviderLoan(80, array(
        'ding_entity_id' => '870970-basis:06686923',
        'loan_date' => '2015-04-01T12:05:13.383',
        'expiry' => '2016-04-25',
        'renewable' => TRUE,
        'materials_number' => '4025573671',
      )),
    );
    $this->assertEquals($expected, $res);

    // TCLL3: Loaner (PAT12) with non-renewable loan (max reached)
    // Kan pt. ikke testes, da materialegrupper/profiler ikke understøtter fornyelsesregler korrekt
   /** $user = (object) array(
      'creds' => array(
        'patronId' => '85',
      ),
    );

    $res = $this->providerInvoke('list', $user);
    $expected = array(
      31 => new DingProviderLoan(31, array(
        'ding_entity_id' => 'RECID31',
        'loan_date' => 'LOANDATE31',
        'expiry' => 'DUEDATE31',
        'renewable' => FALSE,
        'materials_number' => 'ITEMNUM31',
      )),
    );
    $this->assertEquals($expected, $res); **/

    // TCLL4: Loaner (PAT13) with renewable loan
    // Kan pt. ikke testes, da materialegrupper/profiler ikke understøtter fornyelsesregler korrekt
   /** $user = (object) array(
      'creds' => array(
        'patronId' => '86',
      ),
    );

    $res = $this->providerInvoke('list', $user);
    $expected = array(
      32 => new DingProviderLoan(32, array(
        'ding_entity_id' => 'RECID32',
        'loan_date' => 'LOANDATE32',
        'expiry' => 'DUEDATE32',
        'renewable' => TRUE,
        'materials_number' => 'ITEMNUM32',
      )),

      33 => new DingProviderLoan(33, array(
        'ding_entity_id' => 'RECID33',
        'loan_date' => 'LOANDATE33',
        'expiry' => 'DUEDATE33',
        'renewable' => TRUE,
        'materials_number' => 'ITEMNUM33',
      )),

       34 => new DingProviderLoan(34, array(
        'ding_entity_id' => 'RECID34',
        'loan_date' => 'LOANDATE34',
        'expiry' => 'DUEDATE34',
        'renewable' => FALSE,
        'materials_number' => 'ITEMNUM34',
      )),

      35 => new DingProviderLoan(35, array(
        'ding_entity_id' => 'RECID35',
        'loan_date' => 'LOANDATE35',
        'expiry' => 'DUEDATE35',
        'renewable' => FALSE,
        'materials_number' => 'ITEMNUM35',
      )),
    );
    $this->assertEquals($expected, $res); **/

    $user = (object) array(
      'creds' => array(
        'patronId' => '84',
      ),
    );

    $res = $this->providerInvoke('list', $user);
    $expected = array(
      80 => new DingProviderLoan(80, array(
        'ding_entity_id' => '870970-basis:06686923',
        'loan_date' => '2015-04-01T12:05:13.383',
        'expiry' => '2016-04-25',
        'renewable' => TRUE,
        'materials_number' => '4025573671',
        'notes' => 'Issue 2.3, 2011',
      )),
      81 => new DingProviderLoan(81, array(
        'ding_entity_id' => '870970-basis:06686923',
        'loan_date' => '2015-04-01T12:05:13.383',
        'expiry' => '2016-04-25',
        'renewable' => TRUE,
        'materials_number' => '4025573671',
        'notes' => 'Issue 4',
      )),
    );
    $this->assertEquals($expected, $res);

  }

  /**
   * Test loan renew.
   */
  public function testRenew() {
    $this->provider = 'loan';
    // Define DingEntity.
    $this->requireDing('ding_entity', 'ding_entity.module');
    // Define DingProviderUserException.
    $this->requireDing('ding_provider', 'ding_provider.exceptions.inc');
    // Define DingProviderLoan.
    $this->requireDing('ding_provider', 'ding_provider.loan.inc');

    $json_responses = array(
      new Reply(
        array()
      ),
      new Reply(
        array(
          // Array of...
          array(
            // RenewedLoan.
            'loanDetails' => array(
              // LoanDetails.
              'recordId'  => '870970-basis:25364244',
              'dueDate' => '2015-04-11',                // ændres
              'loanDate' => '2015-04-01T14:30:12.499',  // ændres?
              'materialGroupName' => 'somewhat strict',
              'materialItemNumber' => '3829213450',
              'loanId' => '83',
            ),
            'renewalStatus' => array(
              'renewed',
            ),
          ),
        )
      ),
    );
    $this->replies($json_responses);

    // TCLR1: Patron (PAT10)renews empty list of loans
    $user = (object) array(
      'creds' => array(
        'patronId' => '81',
      ),
    );

    // Check success.
    $res = $this->providerInvoke('renew', $user, array());
    $expected = array();
    $this->assertEquals($expected, $res);


    // TCLR2: Patron (PAT14) renews loan (* OBS STATE CHANGES)
    $user = (object) array(
      'creds' => array(
        'patronId' => '87',
      ),
    );

    // Check success.
    $res = $this->providerInvoke('renew', $user, array(83));
    $expected = array(
      83 => DingProviderLoan::STATUS_RENEWED
    );
    $this->assertEquals($expected, $res);


    // TCLR3: Patron (PAT14) tries to renew un-renewable loan
    /** $user = (object) array(
      'creds' => array(
        'patronId' => '87',
      ),
    );

    // Check success.
    $res = $this->providerInvoke('renew', $user, array(1, 2, 3));
    $expected = array(
      1 => DingProviderLoan::STATUS_RENEWED,
      2 => DingProviderLoan::STATUS_NOT_RENEWED,
      3 => DingProviderLoan::STATUS_NOT_RENEWED,
    );
    $this->assertEquals($expected, $res); **/


    // TCLR4: Patron (PAT14) renews multiple loans, both renewable and not (* OBS STATE CHANGES)
    /**$user = (object) array(
      'creds' => array(
        'patronId' => '87',
      ),
    );

    // Check success.
    $res = $this->providerInvoke('renew', $user, array(1, 2, 3));
    $expected = array(
      1 => DingProviderLoan::STATUS_RENEWED,
      2 => DingProviderLoan::STATUS_NOT_RENEWED,
      3 => DingProviderLoan::STATUS_NOT_RENEWED,
    );
    $this->assertEquals($expected, $res); **/


  }

}
