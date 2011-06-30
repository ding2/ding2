<?php

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('User loan list'),
  'description' => t('The current loans for a user'),
  'single' => TRUE,
  'content_types' => array('list'),
  'required context' => new ctools_context_required(t('User'), 'user'),
  'category' => t('User'),
);

/*
 * Additional dateformat, used by format_date().
 */
variable_set('date_format_ding_loan_short', 'd.m.Y');

/**
 * Render the block
 */
function ding_loan_loans_content_type_render($subtype, $conf, $panel_args, $context) {
  $account = isset($context->data) ? $context->data : NULL;
  $items = array();
  $ids = array();

  $block = new stdClass();
  $block->module = 'ding_loan';
  $block->delta = 'loans';
  $block->title = t('Loan list');

  $list = ding_provider_invoke_page('loan', 'list', $account);
  foreach ($list as $item) {
    $ids[] = $item->ding_entity_id;
  }
  // Preload all entities.
  ding_entity_load_multiple($ids);

  $block->content = ding_provider_get_form('ding_loan_loans_form', $account, $list);
  return $block;
}

/**
 * Adding the admin form, to be able to control the required context
 */
function ding_loan_loans_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Implements a drupal form, which show a list of reservations
 */
function ding_loan_loans_form($form, &$form_state, $account, $items = array()) {
  $options = array();
  $destination = drupal_get_destination();
  $header = array(
    'title' => t('Title'),
    'loan_date' => t('Loan date'),
    'expiry' => t('Return date'),
    'operations' => '',
  );
  uasort($items, 'ding_loan_sort_expiry');

  $form['account'] = array(
    '#type' => 'value',
    '#value' => $account,
  );

  $form['items'] = array(
    '#type' => 'value',
    '#value' => $items,
  );

  foreach ($items as $id => $item) {
    $item->creator = 'fake';
    $entity = $item->entity;
    $options[$item->id] = array(
      'title' => array(
        'data' => array(
          isset($entity) ? ting_object_view($entity, 'user_list') : array('#markup' => $item->display_name),
          array(
            '#type' => 'markup',
            '#prefix' => '<p class="order-id">',
            '#markup' => t('Material no. @mat_no', array('@mat_no' => $item->materials_number))
            '#suffix' => '</p>',
          ),
        ),
      ),
      'loan_date' => format_date(strtotime(check_plain($item->loan_date)), 'ding_loan_short'),
      'expiry' => format_date(strtotime(check_plain($item->expiry)), 'ding_loan_short'),
      'operations' => array(
        'data' =>  array(
          '#type' => 'link',
          '#title' => t('Edit'),
          '#href' => 'user/' . $account->uid . '/loan/' . $item->id . '/renew',
          '#options' => array('query' => $destination),
        ),
      ),
    );
  }

  $form['loans'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('No loans'),
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Renew selected'),
  );

  return $form;
}

/**
 * Validate function for the form.
 */
// function ding_reservation_list_form_validate($form, &$form_state) { }

/**
 * Submit handler for the form.
 */
function ding_loan_loans_form_submit($form, &$form_state) {
  $ids = array();
  foreach (array_filter($form_state['values']['loans']) as $id) {
    if ($form_state['values']['items'][$id]->renewable) {
      $ids[] = $id;
    }
  }

  $result = ding_provider_invoke('loan', 'renew', $form_state['values']['account'], $ids);
  foreach ($result as $id => $status) {
    if ($object = $form_state['values']['items'][$id]->entity) {
      $title = $object->title;
    }
    else {
      $title = $item->display_name;
    }
    // @todo Better feedback.
    switch ($status) {
      case DingProviderLoan::STATUS_RENEWED:
        drupal_set_message(t('"@title renewed"', array('@title' => $title)));
        break;
      case DingProviderLoan::STATUS_NOT_RENEWED:
        drupal_set_message(t('"@title not renewed"', array('@title' => $title)), 'warning');
        break;
      default:
        watchdog('ding_loan', 'Unknown renewal status code @code.', array('@code' => $status), WATCHDOG_ERROR);
    }
  }
}

