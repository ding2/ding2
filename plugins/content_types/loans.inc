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
  // 'render callback' => 'ding_reservation_list_content_type_render',
  'required context' => new ctools_context_required(t('User'), 'user'),
  'category' => t('User'),
);

/**
 * Render the block
 */
function ding_loan_loans_content_type_render($subtype, $conf, $panel_args, $context) {
  $account = isset($context->data) ? $context->data : NULL;
  $items = array();

  $block = new stdClass();
  $block->module = 'ding_loan';
  $block->delta = 'loans';
  $block->title = t('Loan list');

  $list = ding_provider_invoke_page('loan', 'list', $account);

  $ids = array();
  foreach ($list as $item) {
    $ids[] = $item->ding_entity_id;
  }
  // Preload all entities.
  ding_entity_load_multiple($ids);

  $block->content = ding_provider_get_form('ding_loan_loans_form', $list);
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
function ding_loan_loans_form($form, &$form_state, $items = array()) {
  $options = array();
  $destination = drupal_get_destination();
  $header = array(
    'title' => t('Title'),
    'loan_date' => t('Loan date'),
    'expiry' => t('Return date'),
    'operations' => '',
  );
  uasort($items, 'ding_loan_sort_expiry');

  foreach ($items as $id => $item) {
    $item->creator = 'fake';
    $entity = $item->entity;
    $options[$item->id] = array(
      'title' => array(
        'data' => isset($entity) ? ting_object_view($item->entity, 'user_list') : array('#markup' => $item->display_name),
      ),
      'loan_date' => check_plain($item->loan_date),
      'expiry' => check_plain($item->expiry),
      'operations' => array(
        'data' =>  array(
          '#type' => 'link',
          '#title' => t('Edit'),
          '#href' => 'reservations/' . $item->id . '/edit',
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


  // $form['loans'] = array(
  //   '#type' => 'checkboxes',
  //   '#options' => $checkboxes,
  // );
  // $form['submit'] = array(
  //   '#type' => 'submit',
  //   '#value' => t('Submit reservations'),
  // );
  return $form;
}

/**
 * Validate function for the form.
 */
// function ding_reservation_list_form_validate($form, &$form_state) { }

/**
 * Submit handler for the form.
 */
// function ding_reservation_list_form_submit($form, &$form_state) {
//   global $user;
//   foreach ($form_state['values']['reservations'] as $key => $entity_id) {
//     if ($key == $entity_id) {
//       ding_provider_invoke('reservation', 'delete', $user, $entity_id);
//     }
//   }
// }
