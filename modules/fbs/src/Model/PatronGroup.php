<?php

namespace FBS\Model;

class PatronGroup
{

    /**
     * @var integer The number of all members in this group, including descendants
     * @required
     */
    public $membersCount = null;

    /**
     * @var integer The patron group identifier
     * @required
     */
    public $patronGroupId = null;

    /**
     * @var string The name of the group
     * @required
     */
    public $name = null;

    /**
     * @var string The description of the group
     * @required
     */
    public $description = null;

    /**
     * @var PatronGroup[] The array of child groups of this group
     */
    public $childGroups = null;


}

