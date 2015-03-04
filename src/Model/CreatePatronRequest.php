<?php

namespace FBS\Model;

class CreatePatronRequest
{

    /**
     * @property string $cprNumber
     * @required
     */
    public $cprNumber = null;

    /**
     * @property string $pincode
     * @required
     */
    public $pincode = null;

    /**
     * @property PatronSettings $patron
     * @required
     */
    public $patron = null;


}

