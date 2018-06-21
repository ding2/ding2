<?php

namespace FBS\Model;

class PatronV3
{

    /**
     * @var string|null
     */
    public $birthday = null;

    /**
     * @var Address|null
     */
    public $secondaryAddress = null;

    /**
     * @var string|null Language in which the patron prefers the communication with the
     * library to take place
     */
    public $preferredLanguage = null;

    /**
     * @var Address|null
     */
    public $address = null;

    /**
     * @var string ISIL of preferred pickup branch
     * @required
     */
    public $preferredPickupBranch = null;

    /**
     * @var Period|null If not set then the patron is not on hold
     */
    public $onHold = null;

    /**
     * @var integer Patron identifier to be used in subsequent service calls involving
     * the patron
     * @required
     */
    public $patronId = null;

    /**
     * @var boolean 
     * @required
     */
    public $receiveEmail = null;

    /**
     * @var BlockStatus[]|null A list of block statuses -
     *  if the patron is not blocked then this value is empty or null
     */
    public $blockStatus = null;

    /**
     * @var boolean 
     * @required
     */
    public $receiveSms = null;

    /**
     * @var string|null
     */
    public $emailAddress = null;

    /**
     * @var string|null
     */
    public $phoneNumber = null;

    /**
     * @var string|null
     */
    public $name = null;

    /**
     * @var boolean 
     * @required
     */
    public $receivePostalMail = null;

    /**
     * @var boolean|null True if the user is allowed to create bookings.
     */
    public $allowBookings = null;

    /**
     * @var integer Length of default interest period in days
     * @required
     */
    public $defaultInterestPeriod = null;

    /**
     * @var boolean True if the user is resident in the same municipality as the
     * library
     * @required
     */
    public $resident = null;


}

