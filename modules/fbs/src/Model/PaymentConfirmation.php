<?php

namespace FBS\Model;

class PaymentConfirmation
{

    /**
     * @var string Order Id from payment gateway
     * @required
     */
    public $orderId = null;

    /**
     * @var string set if fee was registered when using the orderId, unset otherwise
     * (see paymentStatus for reason)
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

