<?php

namespace FBS\Model;

class PatronSettingsV3
{

    /**
     * @var string|null Required if patron should receive email notifications
     *  Existing email addresses are overwritten with this value
     *  If left empty existing email addresses are deleted
     */
    public $emailAddress = null;

    /**
     * @var string|null Language in which the patron prefers the communication with the
     * library to take place
     *  If left empty default library language will be used
     */
    public $preferredLanguage = null;

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

