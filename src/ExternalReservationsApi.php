<?php

namespace FBS;

use Reload\Prancer\SwaggerApi;
use FBS\Model;

class ExternalReservationsApi extends SwaggerApi
{

    /**
     * Get all unfulfilled reservations made by the patron.
     *
     *
     *  Returns an array of reservation details.
     *  When the patron picks up the reserved materials,
     *  the reservation will no longer be returned.
     *  Expired or deleted reservations will not be returned.
     *
     *  The response contains reservation state, which can be any of these values:
     *  
     *      - reserved
     *      - readyForPickup
     *      - interLibraryReservation
     *      - other
     *  
     *  The values are subject to change. If an unregognized value is encountered, it should be treated as 'other'
     *  .
     *  The response contains loanType, which can be any of these values:
     *  
     *      - loan
     *      - interLibraryLoan
     *  
     *  The values are subject to change. If an unregognized value is encountered, it should be treated as 'other'
     *  .
     *
     * @param string $agencyid ISIL of the agency (e.g. DK-761500)
     * @param integer $patronid the patron that owns the reservations
     * @return ReservationDetails[]
     */
    public function getReservations($agencyid, $patronid)
    {
        $request = $this->newRequest("GET", "/external/v1/{agencyid}/patrons/{patronid}/reservations");
        $request->addParameter("path", "agencyid", $agencyid);
        $request->addParameter("path", "patronid", $patronid);

        $request->defineResponse(200, "", array('\\FBS\\Model\\ReservationDetails'));
        $request->defineResponse("400", 'bad request', '\\FBS\\Model\\RestException');
        $request->defineResponse("401", 'client unauthorized', null);

        return $request->execute();
    }

    /**
     * Create new reservations for the patron.
     *
     *
     *  Returns an array of reservation details for the created reservations.
     *  
     *  The response contains reservation state, which can be any of these values:
     *  
     *      - reserved
     *      - readyForPickup
     *      - interLibraryReservation
     *      - other
     *  
     *  The values are subject to change. If an unregognized value is encountered, it should be treated as 'other'.
     *  The response contains loanType, which can be any of these values:
     *  
     *      - loan
     *      - interLibraryLoan
     *  
     *  The values are subject to change. If an unregognized value is encountered, it should be treated as 'other'
     *  .
     *
     * @param string $agencyid ISIL of the agency (e.g. DK-761500)
     * @param integer $patronid the patron that makes the reservations
     * @param CreateReservationBatch $createReservationBatch the reservations to be created
     * @return ReservationDetails[]
     */
    public function addReservations($agencyid, $patronid, Model\CreateReservationBatch $createReservationBatch)
    {
        $request = $this->newRequest("POST", "/external/v1/{agencyid}/patrons/{patronid}/reservations");
        $request->addParameter("path", "agencyid", $agencyid);
        $request->addParameter("path", "patronid", $patronid);
        $request->addParameter("body", "createReservationBatch", $createReservationBatch);

        $request->defineResponse(200, "", array('\\FBS\\Model\\ReservationDetails'));
        $request->defineResponse("400", 'bad request', '\\FBS\\Model\\RestException');
        $request->defineResponse("401", 'client unauthorized', null);
        $request->defineResponse("404", 'patron not found', null);

        return $request->execute();
    }

    /**
     * Update existing reservations.
     *
     *
     *  Returns an array of the updated reservation details.
     *  
     *  The response contains reservation state, which can be any of these values:
     *  
     *      - reserved
     *      - readyForPickup
     *      - interLibraryReservation
     *      - other
     *  
     *  The values are subject to change. If an unregognized value is encountered, it should be treated as 'other'.
     *  The response contains loanType, which can be any of these values:
     *  
     *      - loan
     *      - interLibraryLoan
     *  
     *  The values are subject to change. If an unregognized value is encountered, it should be treated as 'other'
     *  .
     *
     * @param string $agencyid ISIL of the agency (e.g. DK-761500)
     * @param integer $patronid the patron that owns the reservations
     * @param UpdateReservationBatch $reservations the reservations to be updated
     * @return ReservationDetails[]
     */
    public function updateReservations($agencyid, $patronid, Model\UpdateReservationBatch $reservations)
    {
        $request = $this->newRequest("PUT", "/external/v1/{agencyid}/patrons/{patronid}/reservations");
        $request->addParameter("path", "agencyid", $agencyid);
        $request->addParameter("path", "patronid", $patronid);
        $request->addParameter("body", "reservations", $reservations);

        $request->defineResponse(200, "", array('\\FBS\\Model\\ReservationDetails'));
        $request->defineResponse("400", 'bad request', '\\FBS\\Model\\RestException');
        $request->defineResponse("401", 'client unauthorized', null);

        return $request->execute();
    }

    /**
     * Delete existing reservations.
     *
     *
     *
     * @param string $agencyid ISIL of the agency (e.g. DK-761500)
     * @param integer $patronid the patron that owns the reservations
     * @param array $reservationid a list of reservation ids for reservations that are to be deleted
     * @return void
     */
    public function deleteReservations($agencyid, $patronid, $reservationid)
    {
        $request = $this->newRequest("DELETE", "/external/v1/{agencyid}/patrons/{patronid}/reservations");
        $request->addParameter("path", "agencyid", $agencyid);
        $request->addParameter("path", "patronid", $patronid);
        $request->addParameter("query", "reservationid", $reservationid);

        $request->defineResponse(204, "", null);
        $request->defineResponse("400", 'bad request', '\\FBS\\Model\\RestException');
        $request->defineResponse("401", 'client unauthorized', null);

        return $request->execute();
    }


}

