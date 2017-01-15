<?php

namespace FBS;

use Reload\Prancer\SwaggerApi;
use FBS\Model;

class ExternalMaterialLoansApi extends SwaggerApi
{

    /**
     * Get list of current loans by the patron.
     *
     *
     *  Returns an array of loans.
     *  
     *  
     *  If a loan is not renewable then the field renewalStatus will contain a list of one or more of these values:
     *  
     *  - deniedReserved
     *  - deniedMaxRenewalsReached
     *  - deniedLoanerIsBlocked
     *  - deniedMaterialIsNotLoanable
     *  - deniedMaterialIsNotFound
     *  - deniedLoanerNotFound
     *  - deniedLoaningProfileNotFound
     *  - deniedOtherReason
     *  
     *  
     *  If any other value is encountered then it must be treated as 'deniedOtherReason'.
     *  
     *  The response contains the field loanDetails.loanType, which can be any of these values:
     *  
     *  - loan
     *  - interLibraryLoan
     *  
     *  
     *  The values are subject to change. If an unrecognized value is encountered, it should be treated as 'other' .
     *  
     *
     * @param string $agencyid ISIL of the agency (e.g. DK-761500)
     * @param integer $patronid the patron that owns the loans
     * @return Loan[]
     */
    public function getLoans($agencyid, $patronid)
    {
        $request = $this->newRequest("GET", "/external/v1/{agencyid}/patrons/{patronid}/loans");
        $request->addParameter("path", "agencyid", $agencyid);
        $request->addParameter("path", "patronid", $patronid);

        $request->defineResponse(200, "", array('\\FBS\\Model\\Loan'));
        $request->defineResponse("400", 'bad request', null);
        $request->defineResponse("401", 'client unauthorized', null);
        $request->defineResponse("404", 'patron not found', null);

        return $request->execute();
    }

    /**
     * Renew loans.
     *
     *
     *  Returns an array of the updated loans.
     *  
     *  If the materials could not be renewed, the return date will be unchanged.
     *  
     *
     *  The response field renewalStatus will contain a list of one or more of these values:
     *  
     *  - renewed
     *  - deniedReserved
     *  - deniedMaxRenewalsReached
     *  - deniedLoanerIsBlocked
     *  - deniedMaterialIsNotLoanable
     *  - deniedMaterialIsNotFound
     *  - deniedLoanerNotFound
     *  - deniedLoaningProfileNotFound
     *  - deniedOtherReason
     *  
     *  
     *  If any other value is encountered then it must be treated as 'deniedOtherReason'.
     *  
     *  The response contains the field loanDetails.loanType, which can be any of these values:
     *  
     *  - loan
     *  - interLibraryLoan
     *  
     *  
     *  The values are subject to change. If an unrecognized value is encountered, it should be treated as 'other' .
     *  
     *
     * @param string $agencyid ISIL of the agency (e.g. DK-761500)
     * @param integer $patronid the patron that owns the loans
     * @param array $materialLoanIds a list of loanId to be renewed
     * @return RenewedLoan[]
     */
    public function renewLoans($agencyid, $patronid, $materialLoanIds)
    {
        $request = $this->newRequest("POST", "/external/v1/{agencyid}/patrons/{patronid}/loans/renew");
        $request->addParameter("path", "agencyid", $agencyid);
        $request->addParameter("path", "patronid", $patronid);
        $request->addParameter("body", "materialLoanIds", $materialLoanIds);

        $request->defineResponse(200, "", array('\\FBS\\Model\\RenewedLoan'));
        $request->defineResponse("400", 'bad request', null);
        $request->defineResponse("401", 'client unauthorized', null);
        $request->defineResponse("404", 'patron not found', null);

        return $request->execute();
    }

    /**
     * Retrieves material loans for the given booking ID.
     *
     *
     *  
     *  Retrieves an array of BookingLoan corresponding to the given booking ID.
     *  
     *
     * @param string $agencyid ISIL of the agency (e.g. DK-761500)
     * @param integer $patronid the ID of the patron that owns the bookings
     * @param string $bookingid
     * @return BookingLoan[]
     */
    public function getBookingLoans($agencyid, $patronid, $bookingid)
    {
        $request = $this->newRequest("GET", "/external/v1/{agencyid}/patrons/{patronid}/loans/{bookingid}");
        $request->addParameter("path", "agencyid", $agencyid);
        $request->addParameter("path", "patronid", $patronid);
        $request->addParameter("path", "bookingid", $bookingid);

        $request->defineResponse(200, "", array('\\FBS\\Model\\BookingLoan'));
        $request->defineResponse("400", 'bad request com.dantek.dl.rest.RestException', null);
        $request->defineResponse("401", 'client unauthorized', null);
        $request->defineResponse("404", 'patron not found', null);

        return $request->execute();
    }


}

