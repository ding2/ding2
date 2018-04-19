<?php

namespace FBS\Model;

class BookingBranchInfoV3
{

    /**
     * @var string The branch ID
     * @required
     */
    public $branchId = null;

    /**
     * @var integer The gross number of available materials
     * @required
     */
    public $grossNumberAvailable = null;

    /**
     * @var BookingInfo[] Details about requested booking information
     * @required
     */
    public $bookingInfo = null;


}

