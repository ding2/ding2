<?php

namespace FBS\Model;

class Material
{

    /**
     * @property string $itemNumber Identifies the material
     * @required
     */
    public $itemNumber = null;

    /**
     * @property boolean $available True if material is available on-shelf, false if
     * lent out
     * @required
     */
    public $available = null;


}

