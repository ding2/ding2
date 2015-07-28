<?php

namespace FBS\Model;

class PaymentOrder
{

    /**
     * @var string Order Id from payment gateway
     * @required
     */
    public $orderId = null;

    /**
     * @var integer[] Array of fees fully covered by the order
     * @required
     */
    public $feeIds = null;


}

