<?php

namespace FBS\Model;

class UpdateReservation
{

    /**
     * @var string The date where the patron is no longer interested in the reserved
     * material.
     *  If not set, a date will be calculated from the libraries default interest
     * period
     */
    public $expiryDate = null;

    /**
     * @var string ISIL-number of pickup branch.
     *  If not set, will default to patrons preferred pickup branch
     */
    public $pickupBranch = null;

    /**
     * @var integer Identifies the reservation
     * @required
     */
    public $reservationId = null;


}

