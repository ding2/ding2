<?php

namespace FBS;

use Reload\Prancer\SwaggerApi;
use FBS\Model;

class ExternalPlacementApi extends SwaggerApi
{

    /**
     * Get branches for an agency.
     *
     *
     *  Returns array of branches.
     *  Can be used for giving the patron the option of choosing a preferred branch or where to pick up
     *  reservations.
     *
     * @param string $agencyid ISIL of the agency (e.g. DK-761500)
     * @return AgencyBranch[]
     */
    public function getBranches($agencyid)
    {
        $request = $this->newRequest("GET", "/external/v1/{agencyid}/branches");
        $request->addParameter("path", "agencyid", $agencyid);

        $request->defineResponse(200, "", array('\\FBS\\Model\\AgencyBranch'));
        $request->defineResponse("400", 'bad request', null);
        $request->defineResponse("401", 'client unauthorized', null);

        return $request->execute();
    }

    /**
     * Get translations from department identifiers to displayable text.
     *
     *
     *  Returns array of departments.
     *
     * @param string $agencyid ISIL of the agency (e.g. DK-761500)
     * @return AgencyDepartment[]
     */
    public function getDepartments($agencyid)
    {
        $request = $this->newRequest("GET", "/external/v1/{agencyid}/departments");
        $request->addParameter("path", "agencyid", $agencyid);

        $request->defineResponse(200, "", array('\\FBS\\Model\\AgencyDepartment'));
        $request->defineResponse("400", 'bad request', null);
        $request->defineResponse("401", 'client unauthorized', null);

        return $request->execute();
    }

    /**
     * Get translations from location identifiers to displayable text.
     *
     *
     *  Returns array of locations.
     *
     * @param string $agencyid ISIL of the agency (e.g. DK-761500)
     * @return AgencyLocation[]
     */
    public function getLocations($agencyid)
    {
        $request = $this->newRequest("GET", "/external/v1/{agencyid}/locations");
        $request->addParameter("path", "agencyid", $agencyid);

        $request->defineResponse(200, "", array('\\FBS\\Model\\AgencyLocation'));
        $request->defineResponse("400", 'bad request', null);
        $request->defineResponse("401", 'client unauthorized', null);

        return $request->execute();
    }

    /**
     * Get translations from sub-location identifiers to displayable text.
     *
     *
     *  Returns array ofsub-locations.
     *
     * @param string $agencyid ISIL of the agency (e.g. DK-761500)
     * @return AgencySublocation[]
     */
    public function getSublocations($agencyid)
    {
        $request = $this->newRequest("GET", "/external/v1/{agencyid}/sublocations");
        $request->addParameter("path", "agencyid", $agencyid);

        $request->defineResponse(200, "", array('\\FBS\\Model\\AgencySublocation'));
        $request->defineResponse("400", 'bad request', null);
        $request->defineResponse("401", 'client unauthorized', null);

        return $request->execute();
    }


}

