<?php

namespace FBS;

use Reload\Prancer\SwaggerApi;
use FBS\Model;

class ExternalPatronGroupApi extends SwaggerApi
{

    /**
     * Returns the root group of a specific agency.
     *
     *
     *  
     *  Returns the root of the PatronGroup and the whole groups hierarchy in the specified agency.
     *  
     *
     * @param string $agencyid ISIL of the agency (e.g. DK-761500)
     * @return PatronGroup
     */
    public function getRootGroup($agencyid)
    {
        $request = $this->newRequest("GET", "/external/v1/{agencyid}/patrongroups");
        $request->addParameter("path", "agencyid", $agencyid);

        $request->defineResponse(200, "", '\\FBS\\Model\\PatronGroup');
        $request->defineResponse("400", 'bad request', '\\FBS\\Model\\RestException');
        $request->defineResponse("401", 'client unauthorized', null);

        return $request->execute();
    }


}

