<?php

namespace FBS\Model;

class PatronSettings
{

    /**
     * @property string $emailAddress Required if patron should receive email
     * notifications
     */
    public $emailAddress = null;

    /**
     * @property string $phoneNumber Required if patron should receive SMS
     * notifications
     */
    public $phoneNumber = null;

    /**
     * @property string $preferredPickupBranch ISIL-number of preferred pickup branch
     */
    public $preferredPickupBranch = null;

    /**
     * @property Period $onHold If not set then the patron is not on hold
     */
    public $onHold = null;

    /**
     * @property boolean $receiveEmail
     */
    public $receiveEmail = null;

    /**
     * @property boolean $receivePostalMail
     */
    public $receivePostalMail = null;

    /**
     * @property boolean $receiveSms
     */
    public $receiveSms = null;


}

