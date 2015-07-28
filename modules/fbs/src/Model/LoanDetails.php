<?php

namespace FBS\Model;

class LoanDetails
{

    /**
     * @var string Bibliographic record DBC OpenSearch:
     * //searchresult/collection/object/identifier
     * @required
     */
    public $recordId = null;

    /**
     * @var string 
     * @required
     */
    public $loanType = null;

    /**
     * @var Periodical Present if material is a periodical
     */
    public $periodical = null;

    /**
     * @var string The date when the material must be returned
     * @required
     */
    public $dueDate = null;

    /**
     * @var string The date when the material was picked up
     * @required
     */
    public $loanDate = null;

    /**
     * @var string Name of the material group that the material belongs to
     * @required
     */
    public $materialGroupName = null;

    /**
     * @var string Identifies the exact material that has been loaned
     * @required
     */
    public $materialItemNumber = null;

    /**
     * @var integer Identifies the loan for use when renewing the loan
     * @required
     */
    public $loanId = null;


}

