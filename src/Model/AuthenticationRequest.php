<?php

namespace FBS\Model;

class AuthenticationRequest
{

    /**
     * @property string $pincode The pincode that belongs to the libraryCardNumber in
     * plain text
     */
    public $pincode = null;

    /**
     * @property string $libraryCardNumber Identifies a libraryCard.
     *  This can be either a physical card or a CPR number that is used as a
     * libraryCard
     */
    public $libraryCardNumber = null;


}

