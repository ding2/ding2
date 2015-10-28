<?php

namespace FBS\Model;

class ReservationResponse
{

    /**
     * @var boolean True if all reservation were create successfully otherwise false
     * @required
     */
    public $success = null;

    /**
     * @var ReservationResult[] Result of each reservation
     * @required
     */
    public $reservationResults = null;


}

