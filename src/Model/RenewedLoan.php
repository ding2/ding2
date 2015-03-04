<?php

namespace FBS\Model;

class RenewedLoan
{

    /**
     * @property LoanDetails $loanDetails The loan that was attempted renewed
     * @required
     */
    public $loanDetails = null;

    /**
     * @property string[] $renewalStatus indicates if renewal was succesful or denied -
     * including the reason for denial.
     * @required
     */
    public $renewalStatus = null;


}

