<?php

namespace FBS\Model;

class Address
{

    /**
     * @property string $country
     * @required
     */
    public $country = null;

    /**
     * @property string $city
     * @required
     */
    public $city = null;

    /**
     * @property string $street Street and number
     * @required
     */
    public $street = null;

    /**
     * @property string $postalCode
     * @required
     */
    public $postalCode = null;


}

