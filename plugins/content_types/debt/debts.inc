<?php

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('User debt list'),
  'description' => t('The current debts for a user'),
  'single' => TRUE,
  'content_types' => array('list'),
  'required context' => new ctools_context_required(t('User'), 'user'),
  'category' => t('User'),
);

/**
 * Render the block
 */
function ding_debt_debts_content_type_render($subtype, $conf, $panel_args, $context) {
  $preload_debts = &drupal_static('ids');
  $account              = isset($context->data) ? $context->data : NULL;
  $preload_ids          = array();
  $items                = array();
  $debt_list     = array();

  $block         = new stdClass();
  $block->module = 'ding_debt';
  $block->delta  = 'debts';

  $block->title = t('My debts');
  $block->content = 'asdf';

  $debts = ding_provider_invoke_page('debt', 'list', $account);

  $block->content = ding_provider_get_form('ding_debt_debts_form', $debts);

  return $block;
}

/**
 * Form for configuring the content type.
 *
 * Not currently used.
 */
function ding_debt_debts_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Implements a drupal form, which show a list of debts
 */
function ding_debt_debts_form($form, &$form_state, $debts = array()) {
  $header = array(
    'date' => t('Date'),
    'amount' => t('Amount'),
    'note' => t('Note'),
  );

  $options = array();

  foreach ($debts as $id => $debt) {
    $options[$id] = array(
      'date' => array(
        'data' => format_date(strtotime(check_plain($debt->date)), 'date_only'),
        'class' => 'date',
      ),
      'amount' => array(
        'data' => number_format($debt->amount, 2, ',', ' '),
        'class' => 'amount',
      ),
      'note' => array(
        'data' => check_plain($debt->note),
        'class' => 'note',
      ),
    );
  }

  $form['debt_data'] = array(
    '#type' => 'value',
    '#value' => $debts,
  );

  $form['debts'] = array(
    '#type' => 'tableselect_form',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('No debts'),
  );

  $form['pay'] = array(
    '#type' => 'submit',
    '#value' => t('Pay debts'),
  );

  return $form;
}

/**
 * Submit handler for the form.
 */
function ding_debt_debts_form_submit($form, &$form_state) {
  global $user;
  $amount = 0;

  $debts = array_filter($form_state['values']['debts']);

  foreach ($debts as $debt_id) {
    $amount += $form_state['values']['debt_data'][$debt_id]->amount;
  }

  if ($amount > 0) {
    $params = array('params' => array('debt_ids' => $debts));

    $url = ding_provider_invoke('payment', 'get_url', $amount, $params, 'ding_debt_payment_callback');

    if ($url) {
      $form_state['redirect'] = $url;
    }
  }
}

