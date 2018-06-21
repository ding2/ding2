<?php

namespace FBS\Model;

class Periodical
{

    /**
     * @var string|null
     */
    public $volume = null;

    /**
     * @var string|null
     */
    public $volumeYear = null;

    /**
     * @var string A representation of the periodica volume information that is
     * suitable for display
     * @required
     */
    public $displayText = null;

    /**
     * @var string|null
     */
    public $volumeNumber = null;


}

