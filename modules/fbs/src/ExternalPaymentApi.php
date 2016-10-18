<?php

namespace FBS;

use Reload\Prancer\SwaggerApi;
use FBS\Model;

class ExternalPaymentApi extends SwaggerApi
{

    /**
     * List of fees in FBS for the patron with all available information about the fee.
     *
     *
     *  Returns array of fees.
     *  If the fee covers loaned materials, information about the materials is returned.
     *  Each fee in the response includes a 'type', which is used to distinguish between different types of
     *  fees.
     *  If the material exists no more, which is the case for fees that are related to closed interlibraryloans,
     *  then the fee is still returned, but without material information
     *  The list of available types currently is
     *  
     *  fee
     *  compensation
     *  
     *  While the type can be used by client systems to look up a suitable display message for the end user, it is
     *  important that unrecognized types are treated as 'other'.
     *
     * @param string $agencyid ISIL of the agency (e.g. DK-761500)
     * @param integer $patronid the patron that owns the fees
     * @param boolean $includepaid true if all paid/unpaid fees should be included, false if only unpaid fees should
     *                     be included; default=false
     * @param boolean $includenonpayable true if fees that are not payable through a CMS system should be included (for read
     *                           only access); default=false
     * @return Fee[]
     */
    public function getFees($agencyid, $patronid, $includepaid, $includenonpayable)
    {
        $request = $this->newRequest("GET", "/external/v1/{agencyid}/patron/{patronid}/fees");
        $request->addParameter("path", "agencyid", $agencyid);
        $request->addParameter("path", "patronid", $patronid);
        $request->addParameter("query", "includepaid", $includepaid);
        $request->addParameter("query", "includenonpayable", $includenonpayable);

        $request->defineResponse(200, "", array('\\FBS\\Model\\Fee'));
        $request->defineResponse("400", 'bad request', null);
        $request->defineResponse("401", 'client unauthorized', null);

        return $request->execute();
    }

    /**
     * Pay fees.
     *
     *
     *  Returns array of payment confirmations for each fee.
     *  This call is used to inform FBS that a payment have been completed successful from the payment gateway
     *  through the CMS client system. The payment contain the order ID from the payment gateway (e.g. dibs) and the
     *  fee identifiers for fees covered by the payment. It is expected that a fee has been paid in full when covered
     *  by a payment order. The client system is not allowed to offer partial payment of individual fees.
     *  The paymentStatus on the response can be any of these values:
     *  
     *    - paymentRegistered
     *    - paymentRegisteredByDifferentOrderId
     *    - paymentNotAllowedByClient
     *  
     *  If any other value is encountered, it should be treated as yet another reason for not registerering payment of
     *  a fee using the specified order id.
     *  Multiple calls to pay a fee with the same
     *  order Id will return the same confirmationId, and the payment will have paymentStatus=='paymentRegistered'.
     *  If a fee has already been paid using a different orderId then no confirmationId is provided, and the
     *  payment will have paymentStatus=='paymentRegisteredByDifferentOrderId'.
     *  If the client system was not allowed to offer payment of a fee, then no confirmationId is provided, and the
     *  payment will have paymentStatus=='paymentNotAllowedByClient'.
     *
     * @param string $agencyid ISIL of the agency (e.g. DK-761500)
     * @param integer $patronid the patron that owns the fees
     * @param PaymentOrder $paymentOrder registration of fees covered by a payment order
     * @return PaymentConfirmation[]
     */
    public function payFees($agencyid, $patronid, Model\PaymentOrder $paymentOrder)
    {
        $request = $this->newRequest("POST", "/external/v1/{agencyid}/patron/{patronid}/payment");
        $request->addParameter("path", "agencyid", $agencyid);
        $request->addParameter("path", "patronid", $patronid);
        $request->addParameter("body", "paymentOrder", $paymentOrder);

        $request->defineResponse(200, "", array('\\FBS\\Model\\PaymentConfirmation'));
        $request->defineResponse("400", 'bad request', null);
        $request->defineResponse("401", 'client unauthorized', null);

        return $request->execute();
    }


}

