<?php

namespace FBS\Model;

class RestValidatorDetails
{

    /**
     * @property string $path Path to field that has validation error. Format is
     * 'serviceMethod.argument.field',
     *  where 'field' is a dot-seperated path through the JSON-structure.
     * @required
     */
    public $path = null;

    /**
     * @property string $message Description of why the field is invalid. Suitable for
     * logging.
     * @required
     */
    public $message = null;


}

