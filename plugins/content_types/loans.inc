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

    if (!is_object($entity)) {
      // @todo Add dependency or refactor it.
      $entity = ding_reservation_replace_entity($item);
    }
    $options[$item->id] = array(
      '#disabled' => $item->renewable,
      'title' => array(
        'data' => array(
          $entity ? ting_object_view($entity, 'user_list') : array('#markup' => $item->display_name),
        ),
        'class' => 'title',
      ),
      'loan_date' => array(
          'data' => format_date(strtotime(check_plain($item->loan_date)), 'custom', 'd/m/Y'),
          'class' => 'created-date',
        ),
      'expiry' => array(
          'data' => format_date(strtotime(check_plain($item->expiry)), 'custom', 'd/m/Y'),
          'class' => 'expire-date',
        ),
      'operations' => array(
        'data' =>  array(
        ),
        'class' => 'operations',
      ),
    );

    if ($item->materials_number) {
      $options[$item->id]['title']['data'][] = array(
        '#type' => 'markup',
        '#prefix' => '<p class="order-id">',
        '#markup' => t('Material no. @mat_no', array('@mat_no' => $item->materials_number)),
        '#suffix' => '</p>',
      );
    }
    if ($item->renewable) {
      $options[$item->id]['operations']['data'][] = array(
          '#type' => 'submit',
          '#prefix' => '<div class="renew-loan-button">',
          '#value' => t('Renew'),
          '#submit' => array('ding_loan_loans_form_renew_submit'),
          '#loan_id' => $item->id,
          '#name' => 'renew-' . $item->id, // Needed so form API can tell them
                                           // apart.
          '#disabled' => !$item->renewable,
          '#suffix' => '</div>',
      );
    }
  }

  $form['loans'] = array(
    '#type' => 'tableselect_form',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('No loans'),
    '#process' => array('ding_base_element_process_tableselect_form', '_ding_loan_loans_disable'),
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#prefix' => '<div class="renew-loan-button">',
    '#value' => t('Renew selected'),
    '#suffix' => '</div>',
  );

  return $form;
}


/**
 * Process function to disable checkboxes for unrenewable materials.
 */
function _ding_loan_loans_disable($element) {
  foreach ($element['#options'] as $key => $choice) {
    if (isset($choice['#disabled']) && !$choice['#disabled']) {
      $element[$key]['#disabled'] = TRUE;
      $element[$key]['#attributes']['title'] = t('Not renewable');
    }
  }
  return $element;
}

/**
 * Submit handler for the form.
 */
function ding_loan_loans_form_submit($form, &$form_state) {
  $ids = array();
  foreach (array_filter($form_state['values']['loans']) as $id) {
    // The loans array has _form_options array, henc the is_string check.
    if (is_string($id) && $form_state['values']['items'][$id]->renewable) {
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
    switch ($status['state']) {
      case DingProviderLoan::STATUS_RENEWED:
        drupal_set_message(t('"@title renewed"', array('@title' => $title)));
        break;
      case DingProviderLoan::STATUS_NOT_RENEWED:
        if ($status['message'] == 'maxNofRenewals') {
          $rmessage = t('Maximum number of renewals reached');
        } elseif ($status['message'] == 'copyIsReserved') {
          $message = t('The material is reserved by another loaner');
        } else {
          $message = t('Unable to renew material');
        }
        drupal_set_message(t('"@title not renewed: @message"', array('@title' => $title, '@message' => $message)), 'warning');
        break;
      default:
        watchdog('ding_loan', 'Unknown renewal status code @code.', array('@code' => $status), WATCHDOG_ERROR);
    }
  }
}

/**
 *
 */
function ding_loan_loans_form_renew_submit($form, &$form_state) {
  form_set_value($form['loans'], array($form_state['triggering_element']['#loan_id']), $form_state);
  ding_loan_loans_form_submit($form, $form_state);
}

