<?php

namespace FBS\Model;

class HoldingsForBibliographicalRecordV3
{

    /**
     * @var string Identifies the bibliographical record for the available materials,
     *  The FAUST number
     * @required
     */
    public $recordId = null;

    /**
     * @var integer Total number of current active reservations for the bibliographical
     * record
     * @required
     */
    public $reservations = null;

    /**
     * @var boolean True if there is any reservable materials
     * @required
     */
    public $reservable = null;

    /**
     * @var HoldingsV3[] An array of holdings for the materials matching the
     * bibliographical record, as distributed across branches,
     *  departments and locations
     * @required
     */
    public $holdings = null;


}

