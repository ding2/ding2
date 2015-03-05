<?php

namespace FBS\Model;

class CreatePatronRequest
{

    /**
     * @var string 
     * @required
     */
    public $cprNumber = null;

    /**
     * @var string 
     * @required
     */
    public $pincode = null;

    /**
     * @var PatronSettings 
     * @required
     */
    public $patron = null;


}

