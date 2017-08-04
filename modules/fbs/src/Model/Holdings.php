<?php

namespace FBS\Model;

class Holdings
{

    /**
     * @var Material[] Materials that belongs to this placement
     * @required
     */
    public $materials = null;

    /**
     * @var AgencyLocation|null Placement location
     */
    public $location = null;

    /**
     * @var AgencySublocation|null Placement sublocation
     */
    public $sublocation = null;

    /**
     * @var AgencyDepartment|null Placement department
     */
    public $department = null;

    /**
     * @var AgencyBranch Placement branch
     * @required
     */
    public $branch = null;


}

