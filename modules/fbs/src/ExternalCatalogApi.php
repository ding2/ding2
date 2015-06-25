<?php

namespace FBS;

use Reload\Prancer\SwaggerApi;
use FBS\Model;

class ExternalCatalogApi extends SwaggerApi
{

    /**
     * Get availability of bibliographical records.
     *
     *
     *  Returns an array of availability for each bibliographical record.
     *
     * @param string $agencyid ISIL of the agency (e.g. DK-761500)
     * @param array $recordid list of record ids
     * @return Availability[]
     */
    public function getAvailability($agencyid, $recordid)
    {
        $request = $this->newRequest("GET", "/external/v1/{agencyid}/catalog/availability");
        $request->addParameter("path", "agencyid", $agencyid);
        $request->addParameter("query", "recordid", $recordid);

        $request->defineResponse(200, "", array('\\FBS\\Model\\Availability'));
        $request->defineResponse("400", 'bad request', null);
        $request->defineResponse("401", 'client unauthorized', null);

        return $request->execute();
    }

    /**
     * Retrieves all booking information for each branch of an agency for bookings that ends after the current date.
     *
     *
     *  
     *  Returns an array of BookingBranchInfo which contains:
     *  
     *  - the branch ID
     *  - gross number of available materials for that branch
     *  - array of BookingInfo for the given bibliographic record, containing the booking Period and the number of
     *  preferred materials
     *  
     *  
     *  
     *  This is to highlight when materials are available for a new potential booking.
     *  
     *
     * @param string $agencyid ISIL of the agency (e.g. DK-761500)
     * @param string $recordid identifies the bibliographical record, i.e. the FAUST number
     * @return BookingBranchInfo[]
     */
    public function bookingInformation($agencyid, $recordid)
    {
        $request = $this->newRequest("GET", "/external/v1/{agencyid}/catalog/bookingInformation/{recordid}");
        $request->addParameter("path", "agencyid", $agencyid);
        $request->addParameter("path", "recordid", $recordid);

        $request->defineResponse(200, "", array('\\FBS\\Model\\BookingBranchInfo'));
        $request->defineResponse("400", 'bad request com.dantek.dl.rest.RestException', null);
        $request->defineResponse("401", 'client unauthorized', null);
        $request->defineResponse("404", 'patron not found', null);

        return $request->execute();
    }

    /**
     * Get placement holdings for bibliographical records.
     *
     *
     *  Returns an array of holdings for each bibliographical record.
     *  The holdings lists the materials on each placement, and whether they are available on-shelf or lent out.
     *
     * @param string $agencyid ISIL of the agency (e.g. DK-761500)
     * @param array $recordid Identifies the bibliographical records - The FAUST number.
     * @return HoldingsForBibliographicalRecord[]
     */
    public function getHoldings($agencyid, $recordid)
    {
        $request = $this->newRequest("GET", "/external/v1/{agencyid}/catalog/holdings");
        $request->addParameter("path", "agencyid", $agencyid);
        $request->addParameter("query", "recordid", $recordid);

        $request->defineResponse(200, "", array('\\FBS\\Model\\HoldingsForBibliographicalRecord'));
        $request->defineResponse("400", 'bad request', null);
        $request->defineResponse("401", 'client unauthorized', null);

        return $request->execute();
    }


}

