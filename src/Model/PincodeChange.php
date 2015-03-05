<?php

namespace FBS\Model;

class PincodeChange
{

    /**
     * @var string The new pincode for the libraryCard
     * @required
     */
    public $pincode = null;

    /**
     * @var string Identifies the libraryCard for which the pincode is to be changed.
     *  This can be either a physical card or the CPR number, that is used as a
     * libraryCard
     * @required
     */
    public $libraryCardNumber = null;


}

