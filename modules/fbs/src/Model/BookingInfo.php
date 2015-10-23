<?php

namespace FBS\Model;

class BookingInfo
{

    /**
     * @var integer The preferred number of materials
     * @required
     */
    public $preferredMaterials = null;

    /**
     * @var Period The booking period information containing the start and the end date
     * @required
     */
    public $period = null;


}

