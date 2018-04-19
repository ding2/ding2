<?php

namespace FBS\Model;

class ILLBibliographicRecord
{

    /**
     * @var string|null The author of the material
     */
    public $author = null;

    /**
     * @var string|null ISBN-information from the bibliographic record
     */
    public $isbn = null;

    /**
     * @var string|null Issue number of a periodical
     */
    public $periodicalNumber = null;

    /**
     * @var string|null Edition-information from the bibliographic record
     */
    public $edition = null;

    /**
     * @var string|null Language of the requested material.
     */
    public $language = null;

    /**
     * @var string|null Bibliographic category from danMARC2 008 *t
     */
    public $bibliographicCategory = null;

    /**
     * @var string|null The title of the material
     */
    public $title = null;

    /**
     * @var string|null Publication date of an item component, or article.
     */
    public $publicationDateOfComponent = null;

    /**
     * @var string The FAUST number
     * @required
     */
    public $recordId = null;

    /**
     * @var string|null ISSN-information from the bibliographic record
     */
    public $issn = null;

    /**
     * @var string|null
     */
    public $placeOfPublication = null;

    /**
     * @var string Type of the requested material - from danMARC2 009 *a+*g (general
     * and specific)
     * @required
     */
    public $mediumType = null;

    /**
     * @var string|null Volume name of a periodical
     */
    public $periodicalVolume = null;

    /**
     * @var string|null Publisher of the requested material.
     */
    public $publisher = null;

    /**
     * @var string|null Publication date of the requested material.
     */
    public $publicationDate = null;


}

