<?php

namespace FBS;

use Reload\Prancer\SwaggerApi;
use FBS\Model;

class ExternalConfigurationApi extends SwaggerApi
{

    /**
     * Get a configuration setting based on a configuration key.
     *
     *
     *  Returns a string representation of the setting.
     *  Note: If the settings for the key is a list of values, this method is not suitable for getting the settings.
     *  The list of available configuration settings will be distributed
     *  seperately to the clients that needs them, along with a description on how
     *  the settings is encoded in the string representation.
     *
     * @param string $agencyid ISIL of the agency (e.g. DK-761500)
     * @param string $key the configuration key to look up
     * @return string
     */
    public function getConfiguration($agencyid, $key)
    {
        $request = $this->newRequest("GET", "/external/v1/{agencyid}/configuration/{key}");
        $request->addParameter("path", "agencyid", $agencyid);
        $request->addParameter("path", "key", $key);

        $request->defineResponse(200, "", '\\FBS\\Model\\string');
        $request->defineResponse("400", 'bad request', null);
        $request->defineResponse("401", 'client unauthorized', null);
        $request->defineResponse("404", 'key not found', null);

        return $request->execute();
    }

    /**
     * Get a configuration setting based on a configuration key.
     *
     *
     *  Returns an array of strings representation of the setting.
     *  This method is suitable for keys that has a list of values.
     *  The list of available configuration settings will be distributed
     *  seperately to the clients that needs them, along with a description on how
     *  the settings is encoded in the string representation.
     *
     * @param string $agencyid ISIL of the agency (e.g. DK-761500)
     * @param string $key the configuration key to look up
     * @return string[]
     */
    public function getConfigurationList($agencyid, $key)
    {
        $request = $this->newRequest("GET", "/external/v1/{agencyid}/configuration/{key}/list");
        $request->addParameter("path", "agencyid", $agencyid);
        $request->addParameter("path", "key", $key);

        $request->defineResponse(200, "", array('\\FBS\\Model\\string'));
        $request->defineResponse("400", 'bad request', null);
        $request->defineResponse("401", 'client unauthorized', null);
        $request->defineResponse("404", 'key not found', null);

        return $request->execute();
    }


}

