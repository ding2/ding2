<?php

namespace FBS\Model;

class AuthenticationRequest
{

    /**
     * @var string The pincode that belongs to the libraryCardNumber in plain text
     * @required
     */
    public $pincode = null;

    /**
     * @var string Identifies a libraryCard.
     *  This can be either a physical card or a CPR number that is used as a
     * libraryCard
     * @required
     */
    public $libraryCardNumber = null;


}

