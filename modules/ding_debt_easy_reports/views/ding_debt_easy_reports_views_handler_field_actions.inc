<?php

/**
 * @file
 * Handler class for the new field 'actions'
 */

/**
 * @class
 * Actions link handler for changing order status.
 */
class ding_debt_easy_reports_views_handler_field_actions extends views_handler_field {

  /**
   * @{inheritdoc}
   */
  public function render($values) {
    $output = '';

    if (DING_DEBT_EASY_STATUS_FAILED === $values->ding_debt_easy_status) {
      $name = t('Resolve', [], ['context' => 'ding_debt_easy_reports']);
      $url = '/admin/config/payment/ding_debt_easy/reports/' . $values->ding_debt_easy_order_id . '/' . DING_DEBT_EASY_STATUS_COMPLETED;
      $output .= l($name, $url, [
        'attributes' => [
          'class' => ['actions', 'use-ajax'],
          'title' => t('Mark record as completed'),
        ],
        'html' => FALSE,
      ]);
    }

    return $output;
  }

  /**
   * Do nothing, leave query blank, we render the contents
   */
  public function query() {
    // Nothing to see here.
  }

}
