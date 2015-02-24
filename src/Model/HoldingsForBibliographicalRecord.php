<?php

namespace FBS\Model;

class HoldingsForBibliographicalRecord
{

    /**
     * @property string $recordId Identifies the bibliographical record for the
     * available material,
     *  DBC OpenSearch: //searchresult/collection/object/identifier
     */
    public $recordId = null;

    /**
     * @property boolean $reservable True if there is any reservable material
     */
    public $reservable = null;

    /**
     * @property array $holdings An array of holdings for the material matching the
     * bibliographical record, as distributed across branches,
     *  departments and locations
     */
    public $holdings = null;


}

