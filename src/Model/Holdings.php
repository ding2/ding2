<?php

namespace FBS\Model;

class Holdings
{

    /**
     * @property array $materials Materials that belongs to this placement
     */
    public $materials = null;

    /**
     * @property AgencyLocation $location Placement location
     */
    public $location = null;

    /**
     * @property AgencySublocation $sublocation Placement sublocation
     */
    public $sublocation = null;

    /**
     * @property AgencyDepartment $department Placement department
     */
    public $department = null;

    /**
     * @property AgencyBranch $branch Placement branch
     */
    public $branch = null;


}

