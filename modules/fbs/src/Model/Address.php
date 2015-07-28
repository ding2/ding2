<?php

namespace FBS\Model;

class Address
{

    /**
     * @var string 
     * @required
     */
    public $country = null;

    /**
     * @var string 
     * @required
     */
    public $city = null;

    /**
     * @var string Street and number
     * @required
     */
    public $street = null;

    /**
     * @var string 
     * @required
     */
    public $postalCode = null;


}

