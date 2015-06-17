<?php

/**
 * @file
 * Handles user debts.
 */

/**
 * Implements provider debt, list.
 *
 * @param object $account
 *   User to get debt listing for.
 *
 * @return array
 *   Debt information.
 */
function fbs_debt_list($account) {
  $result = array();

  $res = fbs_service()->Payment->getFees(fbs_service()->agencyId, fbs_patron_id($account), FALSE, FALSE);

  foreach ($res as $fee) {
    $id = $fee->feeId;

    $data = array(
      'date' => $fee->creationDate,
      'display_name' => $fee->reasonMessage,
      // FBS only provides the amount left to be paid on each fee, so this
      // will only reflect that.
      'amount' => $fee->amount,
      // And the only thing we can do here is set it to zero, as the original
      // amount isn't available.
      'amount_paid' => 0,
      'invoice_number' => NULL,
      'type' => $fee->reasonMessage,
    );

    if (!empty($fee->materials)) {
      // As ding only support one material number, we just grab the first.
      $material_ids = array();
      foreach ($fee->materials as $material) {
        $material_ids[] = $material->materialItemNumber;
      }

      // If there's only one material, use its title as display_name;
      if (count($material_ids) == 1) {
        $entity = ding_entity_load(ding_provider_build_entity_id(reset($material_ids)));
        $data['display_name'] = $entity->getTitle();
      }
      $data['material_number'] = implode(', ', $material_ids);
    }

    $result[$id] = new DingProviderDebt($id, $data);

  }

  return $result;
}

/**
 * Implements provider debt, payment_received.
 *
 * @param object $account
 *   User to register payment for.
 * @param array $debt_ids
 *   Depts paid for.
 * @param string $order_id
 *   Transaction id.
 *
 * @return bool
 *   Success or not.
 */
function fbs_debt_payment_received($account, $debt_ids = array(), $order_id = NULL) {
  $payment_order = new FBS\Model\PaymentOrder();
  $payment_order->orderId = $order_id;
  $payment_order->feeIds = array();
  foreach ($debt_ids as $debt_id) {
    $payment_order->feeIds[] = $debt_id;
  }
  $res = fbs_service()->Payment->payFees(fbs_service()->agencyId, fbs_patron_id($account), $payment_order);

  foreach ($res as $confirmation) {
    if ($confirmation->paymentStatus !== 'paymentRegistered') {
      $variables = array(
        '@patron_id' => fbs_patron_id($account),
        '@order_id' => $order_id,
        '@fee_id' => implode(', ', $debt_ids),
      );
      watchdog('fbs', 'Could not register payment for patron @patron_id, order id @order_id, fee id @fee_id', $variables, WATCHDOG_ERROR);
      return FALSE;
    }
  }

  return TRUE;
}
