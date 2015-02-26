<?php

/**
 * @file
 * Test loan provider functions.
 */

require_once "ProviderTestCase.php";
require_once 'FBS.php';
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
  function t($str) {
    return $str;
  }
}

/**
 * Test user provider functions.
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
      new Reply(
        array(
          // Array of...
          array(
            // Loan.
            'isRenewable' => TRUE,
            'loanDetails' => array(
              // LoanDetails.
              'recordId' => '870970-basis:29440425',
              'dueDate' => '2015-04-01',
              'loanDate' => '2015-02-26',
              'materialItemNumber' => 34134,
              'loanId' => 234,
            ),
            'renewalStatusList' => array(),
          ),
        )
      ),

      new Reply(
        array(
          // Array of...
          array(
            // Loan.
            'isRenewable' => TRUE,
            'loanDetails' => array(
              // LoanDetails.
              'recordId' => '870970-basis:29440425',
              'dueDate' => '2015-04-01',
              'loanDate' => '2015-02-26',
              'materialItemNumber' => 34134,
              'loanId' => 234,
            ),
            'renewalStatusList' => array(),
          ),
          array(
            // Loan.
            'isRenewable' => FALSE,
            'loanDetails' => array(
              // LoanDetails.
              'recordId' => '870970-basis:29264007',
              'dueDate' => '2015-04-02',
              'loanDate' => '2014-01-01',
              'materialItemNumber' => 3423134,
              'loanId' => 879879,
            ),
            'renewalStatusList' => array(
              'Come on, let someone else read it.',
            ),
          ),
        )
      ),
    );
    $httpclient = $this->getHttpClient($json_responses);

    // Run through tests.
    $fbs = fbs_service('1234', '', $httpclient, NULL, TRUE);

    $user = (object) array(
      'fbs_patron_id' => '123',
    );

    // Check success.
    $res = $this->providerInvoke('list', $user);
    $expected = array(
      234 => new DingProviderLoan(234, array(
        'ding_entity_id' => '870970-basis:29440425',
        // 'display_name' , # optional
        'loan_date' => '2015-02-26',
        'expiry' => '2015-04-01',
        'renewable' => TRUE,
        'materials_number' => 34134,
        // 'author', #optional
        // 'publication_year', #optional
        // 'notes',
      )),
    );
    $this->assertEquals($expected, $res);

    $res = $this->providerInvoke('list', $user);
    $expected = array(
      234 => new DingProviderLoan(234, array(
        'ding_entity_id' => '870970-basis:29440425',
        'loan_date' => '2015-02-26',
        'expiry' => '2015-04-01',
        'renewable' => TRUE,
        'materials_number' => 34134,
      )),

      879879 => new DingProviderLoan(879879, array(
        'ding_entity_id' => '870970-basis:29264007',
        'loan_date' => '2014-01-01',
        'expiry' => '2015-04-02',
        'renewable' => FALSE,
        'materials_number' => 3423134,
      )),
    );
    $this->assertEquals($expected, $res);

  }
}
