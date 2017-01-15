<?php

namespace FBS;

use Reload\Prancer\SwaggerApi;
use FBS\Model;

class ExternalBookingApi extends SwaggerApi
{

    /**
     * Retrieve all bookings made by the patron.
     *
     *
     *  
     *  Returns an array of booking details in one of the following states
     *  
     *  - active
     *  - fulfilled
     *  - beingFulfilled
     *  
     *  Bookings having any other state will not be received.
     *  
     *
     * @param string $agencyid ISIL of the agency (e.g. DK-761500)
     * @param integer $patronid the ID of the patron that owns the bookings
     * @return Booking[]
     */
    public function getBookings($agencyid, $patronid)
    {
        $request = $this->newRequest("GET", "/external/v1/{agencyid}/patrons/{patronid}/bookings");
        $request->addParameter("path", "agencyid", $agencyid);
        $request->addParameter("path", "patronid", $patronid);

        $request->defineResponse(200, "", array('\\FBS\\Model\\Booking'));
        $request->defineResponse("400", 'bad request com.dantek.dl.rest.RestException', null);
        $request->defineResponse("401", 'client unauthorized', null);
        $request->defineResponse("404", 'patron not found', null);

        return $request->execute();
    }

    /**
     * Create a new bookings for the patron.
     *
     *
     *  
     *  Given a CreateBookingBatch, it creates a list of bookings and returns an array of BookingResponse.
     *  
     *  
     *  Each response element contains a result of the creation and if ALL results have the value success
     *  the created Booking is returned. Otherwise the field is null.
     *  
     *  
     *  No booking is created if ANY element in the CreateBookingBatch fails to be created
     *  
     *  
     *  The result of the creation can have the following values:
     *  
     *  - success
     *  - notEnoughMaterials
     *  - notUpdatable
     *  - patronDoesNotHavePermission
     *  - other
     *  
     *  
     *
     * @param string $agencyid ISIL of the agency (e.g. DK-761500)
     * @param integer $patronid the ID of the patron that owns the bookings
     * @param CreateBookingBatch $batch information about bookings that are going to be created
     * @return BookingResponse[]
     */
    public function createBookings($agencyid, $patronid, Model\CreateBookingBatch $batch)
    {
        $request = $this->newRequest("POST", "/external/v1/{agencyid}/patrons/{patronid}/bookings");
        $request->addParameter("path", "agencyid", $agencyid);
        $request->addParameter("path", "patronid", $patronid);
        $request->addParameter("body", "batch", $batch);

        $request->defineResponse(200, "", array('\\FBS\\Model\\BookingResponse'));
        $request->defineResponse("400", 'bad request com.dantek.dl.rest.RestException', null);
        $request->defineResponse("401", 'client unauthorized', null);
        $request->defineResponse("404", 'patron not found', null);

        return $request->execute();
    }

    /**
     * Update existing bookings
     *
     *
     *  
     *  Given an UpdateBookingBatch, it updates the list of existing bookings and returns an array of BookingResponse.
     *  
     *  
     *  Each response element contains a result of the update operation and the updated Booking if the operation
     *  succeeds. On failure, the result field is updated accordingly and the booking is set to null.
     *  
     *  
     *  The result of the creation can have the following values:
     *  
     *  - success
     *  - notEnoughMaterials
     *  - notUpdatable
     *  - patronDoesNotHavePermission
     *  - other
     *  
     *  
     *
     * @param string $agencyid
     * @param integer $patronid the ID of the patron that owns the bookings
     * @param UpdateBookingBatch $batch information about bookings that are going to be updated
     * @return BookingResponse[]
     */
    public function updateBookings($agencyid, $patronid, Model\UpdateBookingBatch $batch)
    {
        $request = $this->newRequest("PUT", "/external/v1/{agencyid}/patrons/{patronid}/bookings");
        $request->addParameter("path", "agencyid", $agencyid);
        $request->addParameter("path", "patronid", $patronid);
        $request->addParameter("body", "batch", $batch);

        $request->defineResponse(200, "", array('\\FBS\\Model\\BookingResponse'));
        $request->defineResponse("400", 'bad request com.dantek.dl.rest.RestException', null);
        $request->defineResponse("401", 'client unauthorized', null);
        $request->defineResponse("404", 'patron not found', null);

        return $request->execute();
    }

    /**
     * Deletes bookings with the specified IDs.
     *
     *
     *  
     *  Deletes the bookings corresponding to the given booking IDs
     *  
     *
     * @param string $agencyid ISIL of the agency (e.g. DK-761500)
     * @param integer $patronid the ID of the patron that owns the bookings
     * @return void
     */
    public function deleteBookings($agencyid, $patronid)
    {
        $request = $this->newRequest("DELETE", "/external/v1/{agencyid}/patrons/{patronid}/bookings");
        $request->addParameter("path", "agencyid", $agencyid);
        $request->addParameter("path", "patronid", $patronid);

        $request->defineResponse(204, "", null);
        $request->defineResponse("400", 'bad request com.dantek.dl.rest.RestException', null);
        $request->defineResponse("401", 'client unauthorized', null);
        $request->defineResponse("404", 'patron not found', null);

        return $request->execute();
    }


}

