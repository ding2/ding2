<?php

namespace FBS\Model;

class Loan
{

    /**
     * @property boolean $isRenewable indicates whether this loan can be renewed
     * @required
     */
    public $isRenewable = null;

    /**
     * @property LoanDetails $loanDetails The loan that was attempted renewed
     * @required
     */
    public $loanDetails = null;

    /**
     * @property string[] $renewalStatusList if isRenewable == false then this states
     * the reasons for denial
     * @required
     */
    public $renewalStatusList = null;


}

