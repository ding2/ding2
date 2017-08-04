<?php

namespace FBS\Model;

class UpdatePatronRequest
{

    /**
     * @var PatronSettings|null Set this if patron details are to be changed
     */
    public $patron = null;

    /**
     * @var PincodeChange|null Set this if pincode is to be changed
     */
    public $pincodeChange = null;


}

