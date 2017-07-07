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
 * Render the block.
 */
function ding_loan_loans_content_type_render($subtype, $conf, $panel_args, $context) {
  // Define basic block object.
  $block = new stdClass();
  $block->module = 'ding_loan';
  $block->delta = 'loans';
  $block->title = t('Loan list');
  $block->content = t('You do not currently have any loans.');

  // Get loans from the provider.
  $account = isset($context->data) ? $context->data : NULL;

  $loans = FALSE;
  if (module_exists('ding_session_cache')) {
    $loans = ding_session_cache_get('ding_loan', 'list');
  }

  if (!$loans) {
    $loans = ding_provider_invoke_page('loan', 'list', $account);

    // Pre-load all entities to speed up the page.
    $ids = array();
    foreach ($loans as $item) {
      $ids[] = $item->ding_entity_id;
    }
    ding_entity_load_multiple($ids);

    // Add the pre-load entity to each loan, if the entity exists.
    foreach ($loans as $id => &$item) {
      // Accessing the entity ref. will load the entity from the data well. So
      // this is intentional not assigned to any thing.
      $item->entity;
    }

    // Store the loans into ding session cache.
    if (module_exists('ding_session_cache')) {
      ding_session_cache_set('ding_loan', 'list', $loans);
    }
  }

  // Set block content, with loans form if any loans exists.
  if (!empty($loans)) {
    $block->content = ding_provider_get_form('ding_loan_loans_form', $account, $loans);
  }

  return $block;
}

/**
 * Adding the admin form, to be able to control the required context.
 */
function ding_loan_loans_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Implements a drupal form, which show a list of reservations.
 */
function ding_loan_loans_form($form, &$form_state, $account, $loans = array()) {
  // Sort loans base on expire date.
  uasort($loans, 'ding_loan_sort_expiry');

  // Split the loans into groups based on the expiry date.
  $groups = _ding_loan_loans_group_loans_by_date($loans);

  $form['actions_container'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('actions-container', 'js-actions-container-fixed'),
    ),
  );

  // Store account information in the form (on server site).
  $form['account'] = array(
    '#type' => 'value',
    '#value' => $account,
  );

  // Store the loan list in the form (on server site).
  $form['items'] = array(
    '#type' => 'value',
    '#value' => $loans,
  );

  $any_renewable = FALSE;
  foreach ($groups as $gid => $group) {
    // Counter to ensure that the "select all" checkbox is disabled if all loans
    // in group are disabled.
    $disabled_count = 0;

    // Add title item (grouping by due dates).
    $form['loans'][$gid]['title'] = array(
      '#type' => 'checkbox',
      '#title' => $group['title'],
      '#prefix' => '<div class="select-all ' . $gid . '">',
      '#suffix' => '</div>',
      '#attached' => array(
        'js' => array(
          drupal_get_path('module', 'ding_loan') . '/js/ding_loan.js',
        ),
      ),
    );

    foreach ($group['loans'] as $loan) {
      // Try to get entity for the loan.
      $entity = $loan->entity;
      $raw_title = $entity->getTitle();

      if (!is_object($entity) || $entity->reply == FALSE) {
        // Patron have this item in loans list, but opensearch can't find this
        // record for current agencyId, so we load it separately.
        // Here we are loading TingClientObject.
        $checked_entity = ting_get_object($loan->ding_entity_id);

        // But we need TingEntity instance, so here we are populating this.
        $ting_entity = new TingEntity();
        $ting_entity->ding_entity_id = $entity->ding_entity_id;
        $ting_entity->reply = $checked_entity;

        // Fetching raw title of the loaded item.
        $raw_title = $ting_entity->getTitle();
      }

      // Add title link.
      $uri = entity_uri('ting_object', $entity);
      $title = l($raw_title, $uri['path']);

      // Add creator(s).
      $creators = $entity->creators;

      // Add type.
      $mat_type = $entity->type;

      $item = array(
        '#type' => 'material_item',
        '#loan' => $loan,
        '#id' => $loan->id,
        '#creators' => $creators,
        '#material_type' => $mat_type,
        '#title' => $title,
        '#cover' => field_view_field('ting_object', $entity, 'ting_cover', 'user_list'),
        '#information' => array(
          'loan_date' => array(
            'label' => t('Loan date'),
            'data' => format_date(strtotime(check_plain($loan->loan_date)), 'ding_material_lists_date'),
            'class' => 'loan-date',
            '#weight' => 0,
          ),
          'expiry' => array(
            'label' => t('Return date'),
            'data' => format_date(strtotime(check_plain($loan->expiry)), 'ding_material_lists_date'),
            'class' => 'expire-date',
            '#weight' => 4,
          ),
        ),
        '#disabled' => !$loan->renewable,
      );

      // Add material number.
      if (isset($loan->materials_number)) {
        $item['#information']['material_number'] = array(
          'label' => t('Material no.'),
          'data' => $loan->materials_number,
          'class' => 'material-number',
          '#weight' => 8,
        );
      }

      // Add extra information if it's a periodical. There is an exception
      // because the notes field is also used to set library information for
      // inter library loans but only when they are ready for pick-up.
      if (!empty($loan->notes) && !($loan->ill_status)) {
        $item['#information']['periodical_number'] = array(
          'label' => t('Periodical no.'),
          'data' => check_plain($loan->notes),
          'class' => 'periodical-number',
          '#weight' => -4,
        );
      }

      // If not renewable set message.
      if (empty($loan->renewable)) {
        $disabled_count++;
        $item['#material_message'] = array(
          'message' => t('This material can not be renewed'),
          'class' => 'messages warning',
        );
      }

      // Add the reservation to the form.
      $form['loans'][$gid][$loan->id] = $item;
    }

    // Check if the "Select all" for this group should be disabled.
    if (count($group['loans']) == $disabled_count) {
      $form['loans'][$gid]['title']['#disabled'] = TRUE;
    }
    else {
      $any_renewable = TRUE;
    }
  }

  if ($any_renewable === TRUE) {
    $form['actions_container']['select_all'] = array(
      '#type' => 'checkbox',
      '#title' => t('Renew all'),
      '#attached' => array(
        'js' => array(
          drupal_get_path('module', 'ding_loan') . '/js/ding_loan.js',
        ),
      ),
    );
  }

  // Add the renew buttons.
  $form['actions_container']['actions_top'] = array(
    '#prefix' => '<div class="action-buttons">',
    '#suffix' => '</div>',
    '#weight' => 0,
  );

  $form['actions_container']['actions_top']['submit_first'] = array(
    '#type' => 'submit',
    '#prefix' => '<div class="renew-loan-button action-button">',
    '#value' => t('Renew selected (@count)', array('@count' => 0)),
    '#suffix' => '</div>',
  );

  $form['actions_container']['actions_top']['renew_all'] = array(
    '#type' => 'markup',
    '#prefix' => '<div class="renew-all action-all action-button js-renew-all">',
    '#markup' => '<a href="#">' . t('Renew all') . '</a>',
    '#suffix' => '</div>',
  );

  return $form;
}

/**
 * Submit handler for the form.
 */
function ding_loan_loans_form_submit($form, &$form_state) {
  $ids = array();
  foreach ($form_state['values']['items'] as $item) {
    if ($item->renewable && $form_state['values'][$item->id]) {
      $ids[] = $item->id;
    }
  }
  if (empty($ids)) {
    return;
  }

  $error_messages = array(
    DingProviderLoan::STATUS_NOT_RENEWED => t('Unable to renew material'),
    DingProviderLoan::STATUS_RENEWAL_NUM_EXCEEDED => t('Maximum number of renewals reached'),
    DingProviderLoan::STATUS_RENEWAL_RESERVED => t('The material is reserved by another loaner'),
  );

  $clear_cache = FALSE;

  $result = ding_provider_invoke('loan', 'renew', $form_state['values']['account'], $ids);
  foreach ($result as $id => $status) {
    // Try to get entity for the item.
    $entity = $form_state['values']['items'][$id]->entity;
    if (!is_object($entity) || $entity->reply == FALSE) {
      // Build pseudo entity based on provider information.
      $entity = ding_provider_get_pseudo_entity($item->ding_entity_id);
      $title = $entity->getTitle() ? $entity->getTitle() : $item->display_name;
    }
    else {
      // Create title from entity object.
      $title = $entity->getTitle();
    }

    // @todo Better feedback.
    switch ($status) {
      case DingProviderLoan::STATUS_RENEWED:
      case DingProviderLoan::STATUS_RENEWAL_REQUESTED:
        drupal_set_message(t('"@title renewed"', array('@title' => $title)));
        $clear_cache = TRUE;
        break;

      case DingProviderLoan::STATUS_NOT_RENEWED:
      case DingProviderLoan::STATUS_RENEWAL_NUM_EXCEEDED:
      case DingProviderLoan::STATUS_RENEWAL_RESERVED:
        drupal_set_message(t('"@title: @message"', array(
          '@title' => $title,
          '@message' => $error_messages[$status],
        )), 'warning');
        break;

      default:
        watchdog('ding_loan', 'Unknown renewal status code @code.', array('@code' => $status), WATCHDOG_ERROR);
    }
  }

  // Clear session cache.
  if ($clear_cache && module_exists('ding_session_cache')) {
    ding_session_cache_clear('ding_loan', 'list');
  }
}

/**
 * Renew load submit handler.
 */
function ding_loan_loans_form_renew_submit($form, &$form_state) {
  form_set_value($form['loans'], array($form_state['triggering_element']['#loan_id']), $form_state);
  ding_loan_loans_form_submit($form, $form_state);
}

/**
 * Helper function to group loans by their due dates.
 */
function _ding_loan_loans_group_loans_by_date($loans) {
  $groups = array();
  $today = date('Y-m-d', REQUEST_TIME);

  foreach ($loans as $loan) {
    if ($loan->expiry < $today) {
      // Loans that are overdue.
      if (!isset($groups['overdue'])) {
        $groups['overdue'] = array(
          'title' => t('Loans overdue'),
          'loans' => array(),
        );
      }
      $groups['overdue']['loans'][$loan->id] = $loan;
    }
    elseif ($loan->expiry == $today) {
      // Loans that should be handed in today.
      if (!isset($groups['due'])) {
        $groups['due'] = array(
          'title' => t('Loans due today'),
          'loans' => array(),
        );
      }
      $groups['due']['loans'][$loan->id] = $loan;
    }
    else {
      // Loans that are to be handed in in x days.
      if (!isset($groups[$loan->expiry])) {
        $time = strtotime($loan->expiry);
        $due_in = t('Due in @count, @date', array(
          '@count' => format_interval($time - strtotime("-1 Day"), 2),
          '@date' => date('d/m/y', $time),
        ));
        $groups[$loan->expiry] = array(
          'title' => $due_in,
          'loans' => array(),
        );
      }
      $groups[$loan->expiry]['loans'][$loan->id] = $loan;
    }
  }

  return $groups;
}
