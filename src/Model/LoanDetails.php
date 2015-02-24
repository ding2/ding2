<?php

namespace FBS\Model;

class LoanDetails
{

    /**
     * @property string $recordId Bibliographic record DBC OpenSearch:
     * //searchresult/collection/object/identifier
     */
    public $recordId = null;

    /**
     * @property string $dueDate The date when the material must be returned
     */
    public $dueDate = null;

    /**
     * @property string $loanDate The date when the material was picked up
     */
    public $loanDate = null;

    /**
     * @property string $materialItemNumber Identifies the exact material that has been
     * loaned
     */
    public $materialItemNumber = null;

    /**
     * @property integer $loanId Identifies the loan for use when renewing the loan
     */
    public $loanId = null;


}

