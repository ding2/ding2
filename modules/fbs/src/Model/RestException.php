<?php

namespace FBS\Model;

class RestException
{

    /**
     * @var string An error code
     * @required
     */
    public $errorCode = null;

    /**
     * @var RestValidatorDetails[] Array of validation errors found on input to a
     * service
     * @required
     */
    public $validationErrors = null;

    /**
     * @var string CorrelationId that can be used to help FBS supporters track down the
     * root cause of the problem in server logs
     * @required
     */
    public $correlationId = null;

    /**
     * @var string A message describing the error. Suitable for logging, not to be
     * presented to the end-user
     * @required
     */
    public $message = null;


}

