<?php

namespace FBS\Model;

class CreateBooking
{

    /**
     * @var string The record ID
     * @required
     */
    public $recordId = null;

    /**
     * @var integer The preferred number of materials
     * @required
     */
    public $preferredMaterials = null;

    /**
     * @var string Additional information about this booking
     */
    public $note = null;

    /**
     * @var Period The booking period information containing the start and the end date
     * @required
     */
    public $period = null;

    /**
     * @var integer The minimum number of materials
     * @required
     */
    public $minimumMaterials = null;

    /**
     * @var integer The patron group ID for this booking
     * @required
     */
    public $patronGroupId = null;

    /**
     * @var boolean True if automatic forward is active for this booking
     * @required
     */
    public $automaticForwardLoan = null;

    /**
     * @var string The branch that provides the material for booking
     * @required
     */
    public $requestedFromBranchId = null;

    /**
     * @var string The delivery branch identifier
     * @required
     */
    public $deliverBranchId = null;


}

