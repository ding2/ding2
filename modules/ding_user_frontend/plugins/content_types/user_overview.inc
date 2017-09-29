<?php
/**
 * @file
 * User overview with links to user pages.
 */

$plugin = array(
  'title' => t('User overview'),
  'description' => t('The current users overview.'),
  'single' => TRUE,
  'content_types' => array('user'),
  'required context' => new ctools_context_required(t('User'), 'user'),
  'category' => t('User'),
  'render callback' => 'ding_user_frontend_user_overview_content_type_render',
);

/**
 * Implements hook_content_type_render().
 */
function ding_user_frontend_user_overview_content_type_render($subtype, $conf, $panel_args, $context) {
  $account = $context->data;

  $block = new stdClass();
  $block->content = '';

  $list_title = t('Library user status');

  $list = array(
    DING_USER_FRONTEND_LIST_RESERVATIONS_READY => array(),
    DING_USER_FRONTEND_LIST_RESERVATIONS => array(),
    DING_USER_FRONTEND_LIST_LOANS_OVERDUE => array(),
    DING_USER_FRONTEND_LIST_LOANS => array(),
    DING_USER_FRONTEND_LIST_DEPTS => array(),
  );

  // Add specials.
  try {
    ding_user_get_creds($account);
    $uri = entity_uri('user', $account);

    // Fines.
    $count = count(ding_provider_invoke('debt', 'list', $account));
    if ($count > 0) {
      $class = 'fines';
    } else {
      $class = 'default';
    }
    $list[DING_USER_FRONTEND_LIST_DEPTS] = array(
      'data' =>
      '<a href="' . url($uri['path'] . '/status-debts') . '" class="signature-label"><span class="icon"></span>' . t('Fines') . '</a>' . '<span class="label warn">' . $count . '</span>',
      'class' => array($class),
    );

    // Loans overdue.
    $loans = ding_provider_invoke('loan', 'list', $account);
    $overdues = 0;
    $today = date('Y-m-d', REQUEST_TIME);
    foreach ($loans as $loan) {
      if ($loan->expiry < $today) {
        $overdues++;
      }
    }

    if ($overdues > 0) {
      $list[DING_USER_FRONTEND_LIST_LOANS_OVERDUE] = array(
        'data' =>
        '<a href="' . url($uri['path'] . '/status-loans') . '" class="signature-label"><span class="icon"></span>' . t('Loans overdue') . '</a>' . '<span class="label warn">' . $overdues . '</span>',
        'class' => array('warn'),
      );
    }
    else {
      unset($list[DING_USER_FRONTEND_LIST_LOANS_OVERDUE]);
    }

    // Reservations ready.
    $readys = count(ding_provider_invoke('reservation', 'list', $account, DING_RESERVATION_READY));
    if ($readys > 0) {
      $list[DING_USER_FRONTEND_LIST_RESERVATIONS_READY] = array(
        'data' =>
        '<a href="' . url($uri['path'] . '/status-reservations-ready') . '" class="signature-label"><span class="icon"></span>' . t('Reservations ready for pick-up') . '</a>' . '<span class="label ready">' . $readys . '</span>',
        'class' => array('ready'),
      );
    }
    else {
      unset($list[DING_USER_FRONTEND_LIST_RESERVATIONS_READY]);
    }

    // All Reservations.
    $count = count(ding_provider_invoke('reservation', 'list', $account, DING_RESERVATION_NOT_READY));
    $list[DING_USER_FRONTEND_LIST_RESERVATIONS] = array(
      'data' =>
      '<a href="' . url($uri['path'] . '/status-reservations') . '" class="signature-label"><span class="icon"></span>' . t('Reservations') . '</a>' . '<span class="label">' . $count . '</span>',
      'class' => array('reservations'),
    );

    // Loans.
    $loans = ding_provider_invoke('loan', 'list', $account);
    $count = count($loans) - $overdues;
    $list[DING_USER_FRONTEND_LIST_LOANS] = array(
      'data' =>
      '<a href="' . url($uri['path'] . '/status-loans', array('fragment' => 'anchor-loans')) . '" class="signature-label"><span class="icon"></span>' . t('Loans') . '</a>' . '<span class="label">' . $count . '</span>',
      'class' => array('loan'),
    );
  }
  catch (Exception $e) {
    watchdog_exception('ding_list', $e);
  }

  $block->content = array(
    '#theme' => 'item_list',
    '#title' => $list_title,
    '#items' => $list,
    '#type' => 'ul',
    '#attributes' => array('class' => array('list-links', 'specials')),
  );

  return $block;
}
