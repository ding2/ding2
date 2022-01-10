<?php
/**
 * @file
 * Adds views support for showing reports.
 */

/**
 * Implements hook_views_data().
 */
function ding_debt_easy_views_data() {
  $data = [];

  $data['ding_debt_easy']['table']['group'] = 'Ding Debt Easy';
  $data['ding_debt_easy']['table']['base'] = [
    'field' => 'id',
    'title' => 'Ding Debt Easy',
    'help' => t('Nets Easy payment information.'),
  ];

  $data['ding_debt_easy']['id'] = [
    'title' => t('Row id'),
    'help' => t('The consent record id.'),
    'field' => [
      'handler' => 'views_handler_field_numeric',
    ],
    'sort' => [
      'handler' => 'views_handler_sort',
    ],
    'filter' => [
      'handler' => 'views_handler_filter_numeric',
    ],
  ];

  $data['ding_debt_easy']['order_id'] = [
    'title' => t('Order ID'),
    'help' => t('Local order id.'),
    'field' => [
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ],
    'sort' => [
      'handler' => 'views_handler_sort',
    ],
    'filter' => [
      'handler' => 'views_handler_filter',
    ],
  ];

  $data['ding_debt_easy']['payment_id'] = [
    'title' => t('Payment ID'),
    'help' => t('Payment ID at the gateway.'),
    'field' => [
      'handler' => 'views_handler_field',
    ],
    'sort' => [
      'handler' => 'views_handler_sort',
    ],
    'filter' => [
      'handler' => 'views_handler_filter',
    ],
  ];

  $data['ding_debt_easy']['charge_id'] = [
    'title' => t('Charge ID'),
    'help' => t('Charge ID at the gateway.'),
    'field' => [
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ],
    'sort' => [
      'handler' => 'views_handler_sort',
    ],
    'filter' => [
      'handler' => 'views_handler_filter',
    ],
  ];

  $data['ding_debt_easy']['provider_ids'] = [
    'title' => t('Provider IDs'),
    'help' => t('Provider IDs at the provider.'),
    'field' => [
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ],
    'sort' => [
      'handler' => 'views_handler_sort',
    ],
    'filter' => [
      'handler' => 'views_handler_filter',
    ],
  ];

  // The amount should not be numeric as features has an issue with the
  // separator value when set to "none". So it fald back to "," as separator
  // which make ever value over 1000 to 1,000 with then aging is divide with 100
  // to make into kr. which the endes up being 0.01 and not 10.00 as expected.
  $data['ding_debt_easy']['amount'] = [
    'title' => t('Amount'),
    'help' => t('The payment amount.'),
    'field' => [
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ],
    'sort' => [
      'handler' => 'views_handler_sort',
    ],
    'filter' => [
      'handler' => 'views_handler_filter_numeric',
    ],
  ];

  $data['ding_debt_easy']['status'] = [
    'title' => t('Status'),
    'help' => t('The payment status.'),
    'field' => [
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ],
    'sort' => [
      'handler' => 'views_handler_sort',
    ],
    'filter' => [
      'handler' => 'views_handler_filter_equality',
    ],
  ];

  $data['ding_debt_easy']['retries'] = [
    'title' => t('Retries'),
    'help' => t('Number of payment retries.'),
    'field' => [
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ],
    'sort' => [
      'handler' => 'views_handler_sort',
    ],
    'filter' => [
      'handler' => 'views_handler_filter_numeric',
    ],
  ];

  $data['ding_debt_easy']['changed'] = [
    'title' => t('Changed date'),
    'help' => t('Last time the record was updated.'),
    'field' => [
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ],
    'sort' => [
      'handler' => 'views_handler_sort_date',
    ],
    'filter' => [
      'handler' => 'views_handler_filter_date',
    ],
    'argument' => [
      'handler' => 'views_handler_argument_date',
    ],
  ];

  $data['ding_debt_easy']['actions'] = [
    'title' => t('Actions'),
    'help' => t('Mark as completed.'),
    'field' => [
      'handler' => 'ding_debt_easy_reports_views_handler_field_actions',
      'click sortable' => FALSE,
    ],
  ];

  return $data;
}
