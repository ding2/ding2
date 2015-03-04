<?php

namespace FBS\Model;

class PincodeChange
{

    /**
     * @property string $pincode The new pincode for the libraryCard
     * @required
     */
    public $pincode = null;

    /**
     * @property string $libraryCardNumber Identifies the libraryCard for which the
     * pincode is to be changed.
     *  This can be either a physical card or the CPR number, that is used as a
     * libraryCard
     * @required
     */
    public $libraryCardNumber = null;


}

