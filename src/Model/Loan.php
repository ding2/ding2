<?php

namespace FBS\Model;

class Loan
{

    /**
     * @var boolean indicates whether this loan can be renewed
     * @required
     */
    public $isRenewable = null;

    /**
     * @var LoanDetails The loan that was attempted renewed
     * @required
     */
    public $loanDetails = null;

    /**
     * @var string[] if isRenewable == false then this states the reasons for denial
     * @required
     */
    public $renewalStatusList = null;


}

