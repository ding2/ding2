<?php

namespace FBS\Model;

class PaymentConfirmationV2
{

    /**
     * @var string Order Id from payment gateway
     * @required
     */
    public $orderId = null;

    /**
     * @var string|null set if fee was registered when using the orderId, unset
     * otherwise (see paymentStatus for reason)
     */
    public $confirmationId = null;

    /**
     * @var integer 
     * @required
     */
    public $feeId = null;

    /**
     * @var string 
     * @required
     */
    public $paymentStatus = null;


}

