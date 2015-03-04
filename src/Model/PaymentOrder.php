<?php

namespace FBS\Model;

class PaymentOrder
{

    /**
     * @property string $orderId Order Id from payment gateway
     * @required
     */
    public $orderId = null;

    /**
     * @property string[] $feeId Array of fees fully covered by the order
     * @required
     */
    public $feeId = null;


}

