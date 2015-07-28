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
     * @var AgencyLocation Placement location
     */
    public $location = null;

    /**
     * @var AgencySublocation Placement sublocation
     */
    public $sublocation = null;

    /**
     * @var AgencyDepartment Placement department
     */
    public $department = null;

    /**
     * @var AgencyBranch Placement branch
     * @required
     */
    public $branch = null;


}

