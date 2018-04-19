<?php

namespace FBS\Model;

class LoanDetailsV2
{

    /**
     * @var string The FAUST number of the bibliographic record
     * @required
     */
    public $recordId = null;

    /**
     * @var string The loan type, either <b>loan</b> or <b>interLibraryLoan</b>
     * @required
     */
    public $loanType = null;

    /**
     * @var MaterialGroup Material group that the material belongs to
     * @required
     */
    public $materialGroup = null;

    /**
     * @var Periodical|null Present if material is a periodical
     */
    public $periodical = null;

    /**
     * @var string The date when the material must be returned
     * @required
     */
    public $dueDate = null;

    /**
     * @var ILLBibliographicRecord|null Additional bibliographic information for
     * inter-library loans
     */
    public $ilBibliographicRecord = null;

    /**
     * @var string The date when the material was picked up
     * @required
     */
    public $loanDate = null;

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

