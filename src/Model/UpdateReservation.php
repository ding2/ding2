<?php

namespace FBS\Model;

class UpdateReservation
{

    /**
     * @property string $expiryDate The date where the patron is no longer interested
     * in the reserved material.
     *  If not set, a date will be calculated from the libraries default interest
     * period
     */
    public $expiryDate = null;

    /**
     * @property string $pickupBranch ISIL-number of pickup branch.
     *  If not set, will default to patrons preferred pickup branch
     */
    public $pickupBranch = null;

    /**
     * @property integer $reservationId Identifies the reservation
     */
    public $reservationId = null;


}

