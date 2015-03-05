<?php

namespace FBS\Model;

class UpdatePatronRequest
{

    /**
     * @var PatronSettings Set this if patron details are to be changed
     */
    public $patron = null;

    /**
     * @var PincodeChange Set this if pincode is to be changed
     */
    public $pincodeChange = null;


}

