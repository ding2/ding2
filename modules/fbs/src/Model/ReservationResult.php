<?php

namespace FBS\Model;

class ReservationResult
{

    /**
     * @var string Recordid of the record to reserve
     * @required
     */
    public $recordId = null;

    /**
     * @var string The reservation result
     * @required
     */
    public $result = null;

    /**
     * @var PeriodicalReservation|null Periodical information of the reservation
     */
    public $periodical = null;

    /**
     * @var ReservationDetails|null The reservation data as returned by the
     * create/update operation
     */
    public $reservationDetails = null;


}

