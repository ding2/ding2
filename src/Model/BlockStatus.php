<?php

namespace FBS\Model;

class BlockStatus
{

    /**
     * @property string $blockedReason Reason code for block
     * @required
     */
    public $blockedReason = null;

    /**
     * @property string $blockedSince
     * @required
     */
    public $blockedSince = null;

    /**
     * @property string $message Message about block
     * @required
     */
    public $message = null;


}

