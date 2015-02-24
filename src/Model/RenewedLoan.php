<?php

namespace FBS\Model;

class RenewedLoan
{

    /**
     * @property LoanDetails $loanDetails The loan that was attempted renewed
     */
    public $loanDetails = null;

    /**
     * @property array $renewalStatus indicates if renewal was succesful or denied -
     * including the reason for denial.
     */
    public $renewalStatus = null;


}

