<?php

namespace FBS\Model;

class RenewedLoan
{

    /**
     * @var LoanDetails The loan that was attempted renewed
     * @required
     */
    public $loanDetails = null;

    /**
     * @var string[] indicates if renewal was succesful or denied - including the
     * reason for denial.
     * @required
     */
    public $renewalStatus = null;


}

