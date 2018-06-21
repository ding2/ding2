<?php

namespace FBS\Model;

class FeeV2
{

    /**
     * @var boolean true if the client system is allowed to offer payment for the fee,
     * false if not allowed
     * @required
     */
    public $payableByClient = null;

    /**
     * @var float The amount to pay, in the currency of the agency
     * @required
     */
    public $amount = null;

    /**
     * @var string|null If the fee has been paid in full, this will be set to the date
     * of the final payment, otherwise not set
     */
    public $paidDate = null;

    /**
     * @var FeeMaterialV2[] Set if fee covers materials
     * @required
     */
    public $materials = null;

    /**
     * @var string Human readable free text message about the reason for the fee,
     * presentable to an end user (language is likely
     *  to be the mother tongue of the agency)
     * @required
     */
    public $reasonMessage = null;

    /**
     * @var string|null Expected payment due date
     */
    public $dueDate = null;

    /**
     * @var string Can be used to distinguish between different types of fees
     * @required
     */
    public $type = null;

    /**
     * @var string The date the fee was created
     * @required
     */
    public $creationDate = null;

    /**
     * @var integer Identifies the fee, used when registering a payment that covers the
     * fee
     * @required
     */
    public $feeId = null;


}

