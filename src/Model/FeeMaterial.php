<?php

namespace FBS\Model;

class FeeMaterial
{

    /**
     * @property string $recordId Bibliographic record DBC OpenSearch:
     * //searchresult/collection/object/identifier
     * @required
     */
    public $recordId = null;

    /**
     * @property string $materialItemNumber Identifies the exact material covered by
     * the fee
     * @required
     */
    public $materialItemNumber = null;


}

