<?php

namespace FBS\Model;

class AuthenticatedPatronV3
{

    /**
     * @var boolean True if patron successfully authenticated.
     *  If false then either the user is not known in the FBS, or an invalid
     * combination of authentication parameters
     *  has been used.
     * @required
     */
    public $authenticated = null;

    /**
     * @var PatronV3|null Only available if patron exists in FBS and was succesfully
     * authenticated.
     */
    public $patron = null;


}

