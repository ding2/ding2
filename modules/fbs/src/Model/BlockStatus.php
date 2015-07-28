<?php

namespace FBS\Model;

class BlockStatus
{

    /**
     * @var string Reason code for block
     * @required
     */
    public $blockedReason = null;

    /**
     * @var string 
     * @required
     */
    public $blockedSince = null;

    /**
     * @var string Message about block
     * @required
     */
    public $message = null;


}

