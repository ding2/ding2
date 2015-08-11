<?php

namespace FBS\Model;

class ReservationDetails
{

    /**
     * @var string The FAUST number
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
     * @var ILLBibliographicRecord Additional bibliographic information for
     * inter-library loans
     */
    public $ilBibliographicRecord = null;

    /**
     * @var string 
     * @required
     */
    public $state = null;

    /**
     * @var integer The number in the reservation queue.
     */
    public $numberInQueue = null;

    /**
     * @var string The reservation number. Will be present if the reservation is ready
     * for pickup (the state is 'readyForPickup')
     */
    public $pickupNumber = null;


}

