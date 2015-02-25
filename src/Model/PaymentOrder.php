<?php

namespace FBS\Model;

class PaymentOrder
{

    /**
     * @property string $orderId Order Id from payment gateway
     */
    public $orderId = null;

    /**
     * @property string[] $feeId Array of fees fully covered by the order
     */
    public $feeId = null;


}

