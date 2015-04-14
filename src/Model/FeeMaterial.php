<?php

namespace FBS\Model;

class FeeMaterial
{

    /**
     * @var string Bibliographic record DBC OpenSearch:
     * //searchresult/collection/object/identifier
     * @required
     */
    public $recordId = null;

    /**
     * @var Periodical Present if material is a periodical
     */
    public $periodical = null;

    /**
     * @var string Name of the material group that the material belongs to
     * @required
     */
    public $materialGroupName = null;

    /**
     * @var string Identifies the exact material covered by the fee
     * @required
     */
    public $materialItemNumber = null;


}

