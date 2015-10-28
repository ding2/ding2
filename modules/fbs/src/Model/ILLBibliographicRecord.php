<?php

namespace FBS\Model;

class ILLBibliographicRecord
{

    /**
     * @var string The author of the material
     */
    public $author = null;

    /**
     * @var string ISBN-information from the bibliographic record
     */
    public $isbn = null;

    /**
     * @var string Issue number of a periodical
     */
    public $periodicalNumber = null;

    /**
     * @var string Edition-information from the bibliographic record
     */
    public $edition = null;

    /**
     * @var string Language of the requested material.
     */
    public $language = null;

    /**
     * @var string Bibliographic category from danMARC2 008 *t
     */
    public $bibliographicCategory = null;

    /**
     * @var string The title of the material
     */
    public $title = null;

    /**
     * @var string Publication date of an item component, or article.
     */
    public $publicationDateOfComponent = null;

    /**
     * @var string The FAUST number
     * @required
     */
    public $recordId = null;

    /**
     * @var string ISSN-information from the bibliographic record
     */
    public $issn = null;

    /**
     * @var string
     */
    public $placeOfPublication = null;

    /**
     * @var string Type of the requested material - from danMARC2 009 *a+*g (general
     * and specific)
     * @required
     */
    public $mediumType = null;

    /**
     * @var string Volume name of a periodical
     */
    public $periodicalVolume = null;

    /**
     * @var string Publisher of the requested material.
     */
    public $publisher = null;

    /**
     * @var string Publication date of the requested material.
     */
    public $publicationDate = null;


}

