<?php

namespace FBS\Model;

class Availability
{

    /**
     * @var string The FAUST number of the Bibliographic record
     * @required
     */
    public $recordId = null;

    /**
     * @var boolean True if materials can be reserved
     * @required
     */
    public $reservable = null;

    /**
     * @var boolean True if materials is available on-shelf at some placement, false if
     * all materials are lent out
     * @required
     */
    public $available = null;


}

