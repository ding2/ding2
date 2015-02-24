<?php

namespace FBS\Model;

class UpdatePatronRequest
{

    /**
     * @property PatronSettings $patron Set this if patron details are to be changed
     */
    public $patron = null;

    /**
     * @property PincodeChange $pincodeChange Set this if pincode is to be changed
     */
    public $pincodeChange = null;


}

