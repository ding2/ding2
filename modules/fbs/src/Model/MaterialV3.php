<?php

namespace FBS\Model;

class MaterialV3
{

    /**
     * @var string Identifies the material
     * @required
     */
    public $itemNumber = null;

    /**
     * @var MaterialGroup Name of the material group that the material belongs to
     * @required
     */
    public $materialGroup = null;

    /**
     * @var Periodical|null Present if material is a periodical
     */
    public $periodical = null;

    /**
     * @var boolean True if material is available on-shelf, false if lent out
     * @required
     */
    public $available = null;


}

