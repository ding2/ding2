<?php

namespace FBS\Model;

class HoldingsForBibliographicalRecord
{

    /**
     * @var string Identifies the bibliographical record for the available materials,
     *  The FAUST number
     * @required
     */
    public $recordId = null;

    /**
     * @var boolean True if there is any reservable materials
     * @required
     */
    public $reservable = null;

    /**
     * @var Holdings[] An array of holdings for the materials matching the
     * bibliographical record, as distributed across branches,
     *  departments and locations
     * @required
     */
    public $holdings = null;


}

