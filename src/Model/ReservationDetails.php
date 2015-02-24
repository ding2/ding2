<?php

namespace FBS\Model;

class ReservationDetails
{

    /**
     * @property string $recordId DBC OpenSearch:
     * //searchresult/collection/object/identifier
     */
    public $recordId = null;

    /**
     * @property string $pickupBranch ISIL-number of pickup branch
     */
    public $pickupBranch = null;

    /**
     * @property string $expiryDate The date when the patron is no longer interested in
     * the reserved material
     */
    public $expiryDate = null;

    /**
     * @property integer $reservationId Identifies the reservation for use when
     * updating or deleting the reservation
     */
    public $reservationId = null;

    /**
     * @property string $pickupDeadline Set if reserved material is available for loan
     */
    public $pickupDeadline = null;

    /**
     * @property string $dateOfReservation
     */
    public $dateOfReservation = null;

    /**
     * @property string $state
     */
    public $state = null;

    /**
     * @property integer $numberInQueue The number in the reservation queue.
     */
    public $numberInQueue = null;


}

