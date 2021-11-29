<?php
/**
 * @file
 * ding_debt_easy_reports.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function ding_debt_easy_reports_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'ding_debt_easy_reports';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'ding_debt_easy';
  $view->human_name = 'Ding debt easy reports';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Ding debt easy reports';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer easy reports';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Antal elementer';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Alle -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Forskydning';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« første';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ forrige';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'næste ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'sidste »';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['row_class'] = 'status-[status]';
  $handler->display->display_options['style_options']['columns'] = array(
    'amount' => 'amount',
    'order_id' => 'order_id',
    'provider_ids' => 'provider_ids',
    'expression' => 'expression',
    'changed' => 'changed',
    'status' => 'status',
  );
  $handler->display->display_options['style_options']['class'] = 'ding-debt-easy-report';
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'amount' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'order_id' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'provider_ids' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'expression' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'changed' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Footer: Global: Text area */
  $handler->display->display_options['footer']['area']['id'] = 'area';
  $handler->display->display_options['footer']['area']['table'] = 'views';
  $handler->display->display_options['footer']['area']['field'] = 'area';
  $handler->display->display_options['footer']['area']['content'] = '<h3>Status forklaring</h3>

<ul>
<li><strong>Created</strong>: betaling opret ved Nets for at kan viderestille brugeren. Brugeren har <strong>ikke</strong> oplyst kort information endnu</li>
<li><strong>Reserved</strong>: betaling reserveret på brugerens kort.</li>
<li><strong>Pending</strong>: betaling reserveret på brugerens kort men ikke lykkes endnu at gennemføre mod FBS</li>
<li><strong>Completed</strong>: betaling gennemført og afsluttet.</li>
<li><strong>Failed</strong>: betaling er fejlet (men store sikkerhed ved FBS). Betaling reserveret endnu.</li>
</ul>
';
  $handler->display->display_options['footer']['area']['format'] = 'ding_wysiwyg';
  /* Field: Amount (raw) */
  $handler->display->display_options['fields']['amount']['id'] = 'amount';
  $handler->display->display_options['fields']['amount']['table'] = 'ding_debt_easy';
  $handler->display->display_options['fields']['amount']['field'] = 'amount';
  $handler->display->display_options['fields']['amount']['ui_name'] = 'Amount (raw)';
  $handler->display->display_options['fields']['amount']['label'] = '';
  $handler->display->display_options['fields']['amount']['exclude'] = TRUE;
  $handler->display->display_options['fields']['amount']['element_label_colon'] = FALSE;
  /* Field: Ding Debt Easy: Order ID */
  $handler->display->display_options['fields']['order_id']['id'] = 'order_id';
  $handler->display->display_options['fields']['order_id']['table'] = 'ding_debt_easy';
  $handler->display->display_options['fields']['order_id']['field'] = 'order_id';
  /* Field: Ding Debt Easy: Provider IDs */
  $handler->display->display_options['fields']['provider_ids']['id'] = 'provider_ids';
  $handler->display->display_options['fields']['provider_ids']['table'] = 'ding_debt_easy';
  $handler->display->display_options['fields']['provider_ids']['field'] = 'provider_ids';
  /* Field: Amount (/100) */
  $handler->display->display_options['fields']['expression']['id'] = 'expression';
  $handler->display->display_options['fields']['expression']['table'] = 'views';
  $handler->display->display_options['fields']['expression']['field'] = 'expression';
  $handler->display->display_options['fields']['expression']['ui_name'] = 'Amount (/100)';
  $handler->display->display_options['fields']['expression']['label'] = 'Beløb';
  $handler->display->display_options['fields']['expression']['precision'] = '0';
  $handler->display->display_options['fields']['expression']['expression'] = '[amount] / 100';
  /* Field: Ding Debt Easy: Changed date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'ding_debt_easy';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'Date';
  $handler->display->display_options['fields']['changed']['date_format'] = 'short';
  $handler->display->display_options['fields']['changed']['second_date_format'] = 'ding_date_only';
  /* Field: Ding Debt Easy: Status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'ding_debt_easy';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  /* Sort criterion: Ding Debt Easy: Changed date */
  $handler->display->display_options['sorts']['changed']['id'] = 'changed';
  $handler->display->display_options['sorts']['changed']['table'] = 'ding_debt_easy';
  $handler->display->display_options['sorts']['changed']['field'] = 'changed';
  $handler->display->display_options['sorts']['changed']['order'] = 'DESC';
  $handler->display->display_options['sorts']['changed']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['changed']['expose']['label'] = 'Date';
  $handler->display->display_options['sorts']['changed']['granularity'] = 'minute';
  /* Sort criterion: Ding Debt Easy: Status */
  $handler->display->display_options['sorts']['status']['id'] = 'status';
  $handler->display->display_options['sorts']['status']['table'] = 'ding_debt_easy';
  $handler->display->display_options['sorts']['status']['field'] = 'status';
  $handler->display->display_options['sorts']['status']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['status']['expose']['label'] = 'Status';
  /* Filter criterion: Ding Debt Easy: Status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'ding_debt_easy';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Status';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['remember_roles'] = array(
    2 => '2',
  );
  $handler->display->display_options['filters']['status']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['status']['group_info']['label'] = 'Status';
  $handler->display->display_options['filters']['status']['group_info']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Pending',
      'operator' => '=',
      'value' => 'pending',
    ),
    2 => array(
      'title' => 'Created',
      'operator' => '=',
      'value' => 'created',
    ),
    3 => array(
      'title' => 'Failed',
      'operator' => '=',
      'value' => 'failed',
    ),
    4 => array(
      'title' => 'Completed',
      'operator' => '=',
      'value' => 'completed',
    ),
    5 => array(
      'title' => 'Reserved',
      'operator' => '=',
      'value' => 'reserved',
    ),
  );

  /* Display: Reports */
  $handler = $view->new_display('page', 'Reports', 'page');
  $handler->display->display_options['display_description'] = 'Administrative payment reports';
  $handler->display->display_options['path'] = 'admin/config/payment/ding_debt_easy/reports';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Reports';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['ding_debt_easy_reports'] = array(
    t('Master'),
    t('Ding debt easy reports'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Antal elementer'),
    t('- Alle -'),
    t('Forskydning'),
    t('« første'),
    t('‹ forrige'),
    t('næste ›'),
    t('sidste »'),
    t('<h3>Status forklaring</h3>

<ul>
<li><strong>Created</strong>: betaling opret ved Nets for at kan viderestille brugeren. Brugeren har <strong>ikke</strong> oplyst kort information endnu</li>
<li><strong>Reserved</strong>: betaling reserveret på brugerens kort.</li>
<li><strong>Pending</strong>: betaling reserveret på brugerens kort men ikke lykkes endnu at gennemføre mod FBS</li>
<li><strong>Completed</strong>: betaling gennemført og afsluttet.</li>
<li><strong>Failed</strong>: betaling er fejlet (men store sikkerhed ved FBS). Betaling reserveret endnu.</li>
</ul>
'),
    t('.'),
    t(','),
    t('Order ID'),
    t('Provider IDs'),
    t('Beløb'),
    t('Date'),
    t('Status'),
    t('Reports'),
    t('Administrative payment reports'),
  );
  $export['ding_debt_easy_reports'] = $view;

  return $export;
}
