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
     *
     * @param string $agencyid ISIL of the agency (e.g. DK-761500)
     * @param array $recordid list of record ids
     * @param array $exclude Identifies the branchIds which are excluded from the result
     * @return Availability[]
     */
    public function getAvailability($agencyid, $recordid, $exclude = null)
    {
        $request = $this->newRequest("GET", "/external/v2/{agencyid}/catalog/availability");
        $request->addParameter("path", "agencyid", $agencyid);
        $request->addParameter("query", "recordid", $recordid);
        $request->addParameter("query", "exclude", $exclude);

        $request->defineResponse(200, "", array('\\FBS\\Model\\Availability'));
        $request->defineResponse("400", 'bad request', null);
        $request->defineResponse("401", 'client unauthorized', null);

        return $request->execute();
    }

    /**
     * Get placement holdings for bibliographical records.
     *
     *
     *  Returns an array of holdings for each bibliographical record together with the total number
     *  of current active reservations.
     *  The holdings lists the materials on each placement, and whether they are available on-shelf or lent out.
     *
     * @param string $agencyid ISIL of the agency (e.g. DK-761500)
     * @param array $recordid Identifies the bibliographical records - The FAUST number.
     * @param array $exclude Identifies the branchIds which are excluded from the result
     * @return HoldingsForBibliographicalRecord[]
     */
    public function getHoldings($agencyid, $recordid, $exclude = null)
    {
        $request = $this->newRequest("GET", "/external/v2/{agencyid}/catalog/holdings");
        $request->addParameter("path", "agencyid", $agencyid);
        $request->addParameter("query", "recordid", $recordid);
        $request->addParameter("query", "exclude", $exclude);

        $request->defineResponse(200, "", array('\\FBS\\Model\\HoldingsForBibliographicalRecord'));
        $request->defineResponse("400", 'bad request', null);
        $request->defineResponse("401", 'client unauthorized', null);

        return $request->execute();
    }


}
