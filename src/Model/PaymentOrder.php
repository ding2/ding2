<?php

namespace FBS\Model;

class PaymentOrder
{

    /**
     * @property string $orderId Order Id from payment gateway
     */
    public $orderId = null;

    /**
     * @property array $feeId Array of fees fully covered by the order
     */
    public $feeId = null;


}

