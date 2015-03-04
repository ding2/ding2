<?php

namespace FBS\Model;

class RestException
{

    /**
     * @property string $errorCode An error code
     * @required
     */
    public $errorCode = null;

    /**
     * @property RestValidatorDetails[] $validationErrors Array of validation errors
     * found on input to a service
     * @required
     */
    public $validationErrors = null;

    /**
     * @property string $correlationId CorrelationId that can be used to help FBS
     * supporters track down the root cause of the problem in server logs
     * @required
     */
    public $correlationId = null;

    /**
     * @property string $message A message describing the error. Suitable for logging,
     * not to be presented to the end-user
     * @required
     */
    public $message = null;


}

