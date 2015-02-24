<?php

namespace FBS\Model;

class RestException
{

    /**
     * @property string $errorCode An error code
     */
    public $errorCode = null;

    /**
     * @property array $validationErrors Array of validation errors found on input to a
     * service
     */
    public $validationErrors = null;

    /**
     * @property string $correlationId CorrelationId that can be used to help FBS
     * supporters track down the root cause of the problem in server logs
     */
    public $correlationId = null;

    /**
     * @property string $message A message describing the error. Suitable for logging,
     * not to be presented to the end-user
     */
    public $message = null;


}

