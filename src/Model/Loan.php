<?php

namespace FBS\Model;

class Loan
{

    /**
     * @property boolean $isRenewable indicates whether this loan can be renewed
     */
    public $isRenewable = null;

    /**
     * @property LoanDetails $loanDetails The loan that was attempted renewed
     */
    public $loanDetails = null;

    /**
     * @property string[] $renewalStatusList if isRenewable == false then this states
     * the reasons for denial
     */
    public $renewalStatusList = null;


}

