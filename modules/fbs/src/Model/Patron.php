<?php

namespace FBS\Model;

class Patron
{

    /**
     * @var string
     */
    public $birthday = null;

    /**
     * @var Address
     */
    public $coAddress = null;

    /**
     * @var Address
     */
    public $address = null;

    /**
     * @var string ISIL of preferred pickup branch
     * @required
     */
    public $preferredPickupBranch = null;

    /**
     * @var Period If not set then the patron is not on hold
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
     * @var BlockStatus[] A list of block statuses -
     *  if the patron is not blocked then this value is empty or null
     */
    public $blockStatus = null;

    /**
     * @var boolean 
     * @required
     */
    public $receiveSms = null;

    /**
     * @var string
     */
    public $emailAddress = null;

    /**
     * @var string
     */
    public $phoneNumber = null;

    /**
     * @var string
     */
    public $name = null;

    /**
     * @var boolean 
     * @required
     */
    public $receivePostalMail = null;

    /**
     * @var boolean True if the user is allowed to create bookings.
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

