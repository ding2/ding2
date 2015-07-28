<?php

namespace FBS;

use Reload\Prancer\SwaggerApi;
use FBS\Model;

class ExternalAuthenticationApi extends SwaggerApi
{

    /**
     * Authenticate the client system.
     *
     *
     *  The other services can only be used by an authenticated client system. This service authenticates the client
     *  system to be able to use the other services.
     *  The response contains a session key which must be supplied in the HTTP header 'X-Session' of all subsequent
     *  service calls.
     *  The session key can timeout (yielding HTTP Status code 401 on a service call),
     *  and if this happens the client system must login again.
     *
     * @param string $agencyid ISIL of the agency to log into (e.g. DK-761500)
     * @param Login $login credentials for the client system
     * @return ExternalAPIUserInfo
     */
    public function login($agencyid, Model\Login $login)
    {
        $request = $this->newRequest("POST", "/external/v1/{agencyid}/authentication/login");
        $request->addParameter("path", "agencyid", $agencyid);
        $request->addParameter("body", "login", $login);

        $request->defineResponse(200, "", '\\FBS\\Model\\ExternalAPIUserInfo');
        $request->defineResponse("400", 'bad request', '\\FBS\\Model\\RestException');
        $request->defineResponse("403", 'invalid client credentials', null);

        return $request->execute();
    }


}

