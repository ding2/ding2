<?php

namespace FBS\Model;

class PatronSettings
{

    /**
     * @var string|null Required if patron should receive email notifications
     *  Existing email addresses are overwritten with this value
     *  If left empty existing email addresses are deleted
     */
    public $emailAddress = null;

    /**
     * @var string|null Required if patron should receive SMS notifications
     *  Existing phonenumbers are overwritten with this value
     *  If left empty existing phonenumbers are deleted
     */
    public $phoneNumber = null;

    /**
     * @var string ISIL-number of preferred pickup branch
     * @required
     */
    public $preferredPickupBranch = null;

    /**
     * @var Period|null If not set then the patron is not on hold
     */
    public $onHold = null;

    /**
     * @var boolean 
     * @required
     */
    public $receiveEmail = null;

    /**
     * @var boolean This field is deprecated and is no longer used
     * @required
     */
    public $receivePostalMail = null;

    /**
     * @var boolean 
     * @required
     */
    public $receiveSms = null;


}

