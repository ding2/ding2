<?php

namespace FBS\Model;

class Material
{

    /**
     * @property string $itemNumber Identifies the material
     */
    public $itemNumber = null;

    /**
     * @property boolean $available True if material is available on-shelf, false if
     * lent out
     */
    public $available = null;


}

