<?php

/**
 * @file
 * Test loan flows.
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
class FlowLoanTest extends ProviderTestCase {

  /**
   * Test renewing of loans.
   *
   * Testgroup F5
   * Issue DDBFBS-34
   *
   * @group flow
   */
  public function testRenew() {
    $this->provider = 'loan';
    // Define DingEntity.
    $this->requireDing('ding_entity', 'ding_entity.module');
    // Define DingProviderUserException.
    $this->requireDing('ding_provider', 'ding_provider.exceptions.inc');
    // Define DingProviderLoan.
    $this->requireDing('ding_provider', 'ding_provider.loan.inc');

    // The due date we expect on the renewed loan.
    $renewed_due_date = date('Y-m-d', time() + 24 * 60 * 60);

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
              'materialGroupName' => 'Material group',
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
              'materialGroupName' => 'Material group',
              'materialItemNumber' => 3423134,
              'loanId' => 879879,
            ),
            'renewalStatusList' => array(
              'Come on, let someone else read it.',
            ),
          ),
        )
      ),

      new Reply(
        array(
          // Array of...
          array(
            // RenewedLoan.
            'loanDetails' => array(
              // LoanDetails.
              'recordId'  => '870970-basis:29440425',
              'dueDate' => $renewed_due_date,
              'loanDate' => '2015-02-26',
              'materialGroupName' => 'Material group',
              'materialItemNumber' => 34134,
              'loanId' => 234,
            ),
            'renewalStatus' => array(
              'renewed',
            ),
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
              'dueDate' => $renewed_due_date,
              'loanDate' => '2015-02-26',
              'materialGroupName' => 'Material group',
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
              'materialGroupName' => 'Material group',
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

    $this->replies($json_responses);

    $user = (object) array(
      'creds' => array(
        'patronId' => '123',
      ),
    );

    // Get initial list.
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

    // Renew a loan.
    $res = $this->providerInvoke('renew', $user, array(234));
    $expected = array(
      234 => DingProviderLoan::STATUS_RENEWED,
    );
    $this->assertEquals($expected, $res);

    // Check that the loan has been updated.
    $res = $this->providerInvoke('list', $user);
    $expected = array(
      234 => new DingProviderLoan(234, array(
        'ding_entity_id' => '870970-basis:29440425',
        'loan_date' => '2015-02-26',
        'expiry' => $renewed_due_date,
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

  /**
   * Test renewing of loans that cannot be renewed.
   *
   * Testgroup F6
   * Issue DDBFBS-35
   *
   * @group flow
   */
  public function testRenewFailure() {
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
              'materialGroupName' => 'Material group',
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
              'materialGroupName' => 'Material group',
              'materialItemNumber' => 3423134,
              'loanId' => 879879,
            ),
            'renewalStatusList' => array(
              'Come on, let someone else read it.',
            ),
          ),
        )
      ),

      new Reply(
        array(
          // Array of...
          array(
            // RenewedLoan.
            'loanDetails' => array(
              // LoanDetails.
              'recordId'  => '870970-basis:29264007',
              'dueDate' => '2015-04-02',
              'loanDate' => '2014-01-01',
              'materialGroupName' => 'Material group',
              'materialItemNumber' => 3423134,
              'loanId' => 879879,
            ),
            'renewalStatus' => array(
              'deniedReserved',
            ),
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
              'materialGroupName' => 'Material group',
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
              'materialGroupName' => 'Material group',
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
    $this->replies($json_responses);

    $user = (object) array(
      'creds' => array(
        'patronId' => '123',
      ),
    );

    // Get initial list.
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

    // Renew a loan.
    $res = $this->providerInvoke('renew', $user, array(879879));
    $expected = array(
      879879 => DingProviderLoan::STATUS_NOT_RENEWED,
    );
    $this->assertEquals($expected, $res);

    // Check that the loan has been updated.
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
