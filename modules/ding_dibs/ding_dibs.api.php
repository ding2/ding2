<?php

/**
 * @file
 * Ding DIBS module API.
 */

/**
 * Hook executed after payment capture is done by DIBS.
 *
 * This hook is implemented for extension of actions which can be done on stage
 *   when payment is accepted by DIBS system.
 *
 * For example: After the payment operation is completed we need to send
 *   some operation data which is still present in $transaction array to another
 *   webservice which provides automation of company accounting.
 *
 * @param array $transaction
 *   Transaction data.
 */
function hook_ding_dibs_capture_accepted(array $transaction) {
  // @code
}
