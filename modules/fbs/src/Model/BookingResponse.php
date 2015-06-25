<?php

namespace FBS\Model;

class BookingResponse
{

    /**
     * @var string The operation result
     * @required
     */
    public $result = null;

    /**
     * @var Booking The booking data as returned by the create/update operation
     */
    public $booking = null;


}

