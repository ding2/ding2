<?php

namespace FBS\Model;

class PaymentConfirmation
{

    /**
     * @property string $orderId Order Id from payment gateway
     */
    public $orderId = null;

    /**
     * @property string $confirmationId set if fee was registered when using the
     * orderId, unset otherwise (see paymentStatus for reason)
     */
    public $confirmationId = null;

    /**
     * @property string $feeId
     */
    public $feeId = null;

    /**
     * @property string $paymentStatus
     */
    public $paymentStatus = null;


}

