<?php
/**
 * @file
 * Adds views support for showing reports.
 */

/**
 * Implements hook_views_data().
 */
function ding_debt_easy_views_data() {
  $data = array();

  $data['ding_debt_easy']['table']['group'] = 'Ding Debt Easy';
  $data['ding_debt_easy']['table']['base'] = array(
    'field' => 'id',
    'title' => 'Ding Debt Easy',
    'help' => t('Nets Easy payment information.'),
  );

  $data['ding_debt_easy']['id'] = array(
    'title' => t('Row id'),
    'help' => t('The consent record id.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );

  $data['ding_debt_easy']['order_id'] = array(
    'title' => t('Order ID'),
    'help' => t('Local order id.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter',
    ),
  );

  $data['ding_debt_easy']['payment_id'] = array(
    'title' => t('Payment ID'),
    'help' => t('Payment ID at the gateway.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter',
    ),
  );

  $data['ding_debt_easy']['charge_id'] = array(
    'title' => t('Charge ID'),
    'help' => t('Charge ID at the gateway.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter',
    ),
  );

  $data['ding_debt_easy']['provider_ids'] = array(
    'title' => t('Provider IDs'),
    'help' => t('Provider IDs at the provider.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter',
    ),
  );

  $data['ding_debt_easy']['amount'] = array(
    'title' => t('Amount'),
    'help' => t('The payment amount.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );

  $data['ding_debt_easy']['status'] = array(
    'title' => t('Status'),
    'help' => t('The payment status.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_equality',
    ),
  );

  $data['ding_debt_easy']['retries'] = array(
    'title' => t('Retries'),
    'help' => t('Number of payment retries.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );

  $data['ding_debt_easy']['changed'] = array(
    'title' => t('Changed date'),
    'help' => t('Last time the record was updated.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    ),
  );

  return $data;
}
