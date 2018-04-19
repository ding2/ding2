<?php

namespace FBS\Model;

class BookingLoanV2
{

    /**
     * @var string The name of the patron that owns the booking
     * @required
     */
    public $patronName = null;

    /**
     * @var boolean indicates whether this loan can be renewed
     * @required
     */
    public $isRenewable = null;

    /**
     * @var LoanDetailsV2 The loan that was attempted renewed
     * @required
     */
    public $loanDetails = null;

    /**
     * @var string[] if isRenewable == false then this states the reasons for denial
     * @required
     */
    public $renewalStatusList = null;


}

