<?php

/**
 * Get list of unpayed fees
 */
function openruth_debt_list($account) {
   $creds = ding_user_get_creds($account);
   $result = array();
   $status = _openruth_user_status($creds);

   if (isset($status->fees->fee)) {
     foreach ($status->fees->fee as $res) {
       $result[$res->feeDate] = new DingProviderDebt($res->feeDate, array(
         'date' => $res->feeDate,
         'display_name' => $res->itemDisplayTitle,
         'pickup_branch_id' => $res->agencyCounter,
         'amount' => $res->feeAmount,
         'type' => $res->feeType,
       ));
     }
   }

   return $result;
}
