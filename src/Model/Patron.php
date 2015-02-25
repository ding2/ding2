<?php

namespace FBS\Model;

class Patron
{

    /**
     * @property string $birthday
     */
    public $birthday = null;

    /**
     * @property Address $coAddress
     */
    public $coAddress = null;

    /**
     * @property Address $address
     */
    public $address = null;

    /**
     * @property string $preferredPickupBranch ISIL of preferred pickup branch
     */
    public $preferredPickupBranch = null;

    /**
     * @property Period $onHold If not set then the patron is not on hold
     */
    public $onHold = null;

    /**
     * @property integer $patronId Patron identifier to be used in subsequent service
     * calls involving the patron
     */
    public $patronId = null;

    /**
     * @property boolean $receiveEmail
     */
    public $receiveEmail = null;

    /**
     * @property BlockStatus[] $blockStatus A list of block statuses -
     *  if the patron is not blocked then this value is empty or null
     */
    public $blockStatus = null;

    /**
     * @property boolean $receiveSms
     */
    public $receiveSms = null;

    /**
     * @property string $emailAddress
     */
    public $emailAddress = null;

    /**
     * @property string $phoneNumber
     */
    public $phoneNumber = null;

    /**
     * @property string $name
     */
    public $name = null;

    /**
     * @property boolean $receivePostalMail
     */
    public $receivePostalMail = null;

    /**
     * @property integer $defaultInterestPeriod Length of default interest period in
     * days
     */
    public $defaultInterestPeriod = null;

    /**
     * @property boolean $resident True if the user is resident in the same
     * municipality as the library
     */
    public $resident = null;


}

