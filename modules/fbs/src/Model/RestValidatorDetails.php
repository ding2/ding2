<?php

namespace FBS\Model;

class RestValidatorDetails
{

    /**
     * @var string Path to field that has validation error. Format is
     * 'serviceMethod.argument.field',
     *  where 'field' is a dot-seperated path through the JSON-structure.
     * @required
     */
    public $path = null;

    /**
     * @var string Description of why the field is invalid. Suitable for logging.
     * @required
     */
    public $message = null;


}

