<?php

namespace FBS\Model;

class PatronSettings
{

    /**
     * @var string Required if patron should receive email notifications
     */
    public $emailAddress = null;

    /**
     * @var string Required if patron should receive SMS notifications
     */
    public $phoneNumber = null;

    /**
     * @var string ISIL-number of preferred pickup branch
     * @required
     */
    public $preferredPickupBranch = null;

    /**
     * @var Period If not set then the patron is not on hold
     */
    public $onHold = null;

    /**
     * @var boolean 
     * @required
     */
    public $receiveEmail = null;

    /**
     * @var boolean 
     * @required
     */
    public $receivePostalMail = null;

    /**
     * @var boolean 
     * @required
     */
    public $receiveSms = null;


}

