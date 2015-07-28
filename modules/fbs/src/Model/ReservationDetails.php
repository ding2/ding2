<?php

namespace FBS\Model;

class ReservationDetails
{

    /**
     * @var string DBC OpenSearch: //searchresult/collection/object/identifier
     * @required
     */
    public $recordId = null;

    /**
     * @var string ISIL-number of pickup branch
     * @required
     */
    public $pickupBranch = null;

    /**
     * @var string The date when the patron is no longer interested in the reserved
     * material
     * @required
     */
    public $expiryDate = null;

    /**
     * @var integer Identifies the reservation for use when updating or deleting the
     * reservation
     * @required
     */
    public $reservationId = null;

    /**
     * @var string Set if reserved material is available for loan
     */
    public $pickupDeadline = null;

    /**
     * @var string 
     * @required
     */
    public $loanType = null;

    /**
     * @var string 
     * @required
     */
    public $dateOfReservation = null;

    /**
     * @var Periodical Present if material is a periodical
     */
    public $periodical = null;

    /**
     * @var string 
     * @required
     */
    public $state = null;

    /**
     * @var integer The number in the reservation queue.
     */
    public $numberInQueue = null;


}

