<?php

namespace FBS\Model;

class Availability
{

    /**
     * @property string $recordId Bibliographic record DBC OpenSearch:
     * //searchresult/collection/object/identifier
     * @required
     */
    public $recordId = null;

    /**
     * @property boolean $reservable True if material can be reserved
     * @required
     */
    public $reservable = null;

    /**
     * @property boolean $available True if material is available on-shelf at some
     * placement, false if all materials are lent out
     * @required
     */
    public $available = null;


}

