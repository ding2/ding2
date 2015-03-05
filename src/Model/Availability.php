<?php

namespace FBS\Model;

class Availability
{

    /**
     * @var string Bibliographic record DBC OpenSearch:
     * //searchresult/collection/object/identifier
     * @required
     */
    public $recordId = null;

    /**
     * @var boolean True if material can be reserved
     * @required
     */
    public $reservable = null;

    /**
     * @var boolean True if material is available on-shelf at some placement, false if
     * all materials are lent out
     * @required
     */
    public $available = null;


}

