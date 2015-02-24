<?php

namespace FBS\Model;

class AuthenticatedPatron
{

    /**
     * @property boolean $authenticated True if patron successfully authenticated.
     *  If false then either the user is not known in the FBS, or an invalid
     * combination of authentication parameters
     *  has been used.
     */
    public $authenticated = null;

    /**
     * @property Patron $patron Only available if patron exists in FBS and was
     * succesfully authenticated.
     */
    public $patron = null;


}

