<?php

namespace FBS\Model;

class Material
{

    /**
     * @var string Identifies the material
     * @required
     */
    public $itemNumber = null;

    /**
     * @var boolean True if material is available on-shelf, false if lent out
     * @required
     */
    public $available = null;


}

