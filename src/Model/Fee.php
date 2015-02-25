<?php

namespace FBS\Model;

class Fee
{

    /**
     * @property boolean $payableByClient true if the client system is allowed to offer
     * payment for the fee, false if not allowed
     */
    public $payableByClient = null;

    /**
     * @property number $amount The amount to pay, in the currency of the agency
     */
    public $amount = null;

    /**
     * @property string $paidDate If the fee has been paid in full, this will be set to
     * the date of the final payment, otherwise not set
     */
    public $paidDate = null;

    /**
     * @property FeeMaterial[] $material Set if fee covers materials
     */
    public $material = null;

    /**
     * @property string $reasonMessage Human readable free text message about the
     * reason for the fee, presentable to an end user (language is likely
     *  to be the mother tongue of the agency)
     */
    public $reasonMessage = null;

    /**
     * @property string $dueDate Expected payment due date
     */
    public $dueDate = null;

    /**
     * @property string $type Can be used to distinguish between different types of
     * fees
     */
    public $type = null;

    /**
     * @property string $creationDate The date the fee was created
     */
    public $creationDate = null;

    /**
     * @property string $feeId Identifies the fee, used when registering a payment that
     * covers the fee
     */
    public $feeId = null;


}

