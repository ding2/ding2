<?php

namespace FBS\Model;

class Login
{

    /**
     * @property string $password Clear text password
     * @required
     */
    public $password = null;

    /**
     * @property string $username Username for the client system
     * @required
     */
    public $username = null;


}

