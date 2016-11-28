<?php

/**
 * @file
 * View all lists.
 */

$plugin = array(
  'title' => t('Lists'),
  'description' => t('Lists.'),
  'single' => TRUE,
  'content_types' => array('user'),
  'required context' => new ctools_context_required(t('User'), 'user'),
  'category' => t('Dinglist'),
  'render callback' => 'ding_list_lists_content_type_render',
);

/**
 * Implements hook_content_type_render().
 */
function ding_list_lists_content_type_render($subtype, $conf, $panel_args, $context) {
  drupal_add_css(drupal_get_path('module', 'ding_list') . '/css/ding-list-view.css');
  $account = $context->data;

  $block = new stdClass();
  $block->content = '';

  $groups = array(
    'specials' => array(
      'title' => t('Library user status'),
      'lists' => array(
        DING_LIST_TYPE_SPECIAL_DEPTS => array(),
        DING_LIST_TYPE_SPECIAL_LOANS_OVERDUE => array(),
        DING_LIST_TYPE_SPECIAL_RESERVATIONS_READY => array(),
        DING_LIST_TYPE_SPECIAL_RESERVATIONS => array(),
        DING_LIST_TYPE_SPECIAL_LOANS => array(),
      ),
    ),
    'userlists' => array(
      'title' => t('My library'),
      'lists' => array(
        DING_LIST_TYPE_SEARCHES => array(),
        DING_LIST_TYPE_LISTS => array(),
        DING_LIST_TYPE_FOLLOW_AUTHOR => array(),
        DING_LIST_TYPE_BOOKS_READ => array(),
        DING_LIST_TYPE_REMEMBER => array(),
        DING_ENTITY_RATING_LIST => array(),
        DING_LIST_TYPE_USER_LIST => array(),
      ),
      'sort' => 'ding_list_custom_sort_changed',
    ),
  );

  if (variable_get('user_consent_activate')) {
    $groups['specials']['lists'][DING_LIST_TYPE_LOAN_HISTORY] = array();
  }

  $lists = ding_list_get_lists(NULL, $account);
  if ($lists !== FALSE) {
    foreach ($lists as $list) {
      $list_type = ding_base_get_value('ding_type', $list, 'field_list_type');
      $list_label = check_plain(entity_label('ding_type', $list));

      foreach ($groups as $group_name => $group) {
        if (isset($group['lists'][$list_type])) {
          $uri = entity_uri('ding_type', $list);
          switch ($group_name) {
            case 'users':
              $groups[$group_name]['lists'][$list_type][] = array(
                'data' =>
                '<a href="' . url($uri['path']) . '" class="signature-label"><span class="icon"></span>' . $list_label . '</a>',
                'class' => array(drupal_html_class($list_type)),
                '#list' => $list,
              );
              break;

            case 'userlists':
              $notifications = ding_message_get_ding_list_notification($list);
              $notout = '';
              if (!empty($notifications)) {
                $notout = l($notifications, 'list/' . $list->id, array('html' => TRUE, 'attributes' => array('class' => array('label'))));
              }

              $groups[$group_name]['lists'][$list_type][] = array(
                'data' =>
                '<a href="' . url($uri['path']) . '" class="signature-label"><span class="icon"></span>' . $list_label . '</a>' . $notout,
                'class' => array(drupal_html_class($list_type)),
                '#list' => $list,
              );
              break;

            case 'specials':
              $items = ding_base_get_items('ding_type', $list, 'field_list_objects');

              $groups[$group_name]['lists'][$list_type][] = array(
                'data' =>
                '<a href="' . url($uri['path']) . '" class="signature-label"><span class="icon"></span>' . $list_label . '</a>',
                'class' => array(drupal_html_class($list_type)),
                '#list' => $list,
              );
              break;
          }
        }
      }
    }
  }

  // Add specials.
  try {
    ding_user_get_creds($account);
    $uri = entity_uri('user', $account);

    // Fines.
    $count = count(ding_provider_invoke('debt', 'list', $account));
    $groups['specials']['lists']['special_depts'][] = array(
      'data' =>
      '<a href="' . url($uri['path'] . '/status/debts') . '" class="signature-label"><span class="icon"></span>' . t('Fines') . '</a>' . '<span class="label warn">' . $count . '</span>',
      'class' => array('fines'),
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
      $groups['specials']['lists']['special_loans_overdue'][] = array(
        'data' =>
        '<a href="' . url($uri['path'] . '/status') . '" class="signature-label"><span class="icon"></span>' . t('Loans overdue') . '</a>' . '<span class="label warn">' . $overdues . '</span>',
        'class' => array('warn'),
      );
    }
    else {
      unset($groups['specials']['lists']['special_loans_overdue']);
    }

    // Reservations ready.
    $readys = count(ding_provider_invoke('reservation', 'list', $account, DING_RESERVATION_READY));
    if ($readys > 0) {
      $groups['specials']['lists']['special_reservations_ready'][] = array(
        'data' =>
        '<a href="' . url($uri['path'] . '/status/reservations') . '" class="signature-label"><span class="icon"></span>' . t('Reservations ready for pick-up') . '</a>' . '<span class="label ready">' . $readys . '</span>',
        'class' => array('ready'),
      );
    }
    else {
      unset($groups['specials']['lists']['special_reservations_ready']);
    }

    // All Reservations.
    $count = $readys + count(ding_provider_invoke('reservation', 'list', $account, DING_RESERVATION_NOT_READY));
    $groups['specials']['lists']['special_reservations'][] = array(
      'data' =>
      '<a href="' . url($uri['path'] . '/status/reservations') . '" class="signature-label"><span class="icon"></span>' . t('Reservations') . '</a>' . '<span class="label">' . $count . '</span>',
      'class' => array('reservations'),
    );

    // Loans.
    $loans = ding_provider_invoke('loan', 'list', $account);
    $count = count(ding_provider_invoke('loan', 'list', $account));
    $groups['specials']['lists']['special_loans'][] = array(
      'data' =>
      '<a href="' . url($uri['path'] . '/status') . '" class="signature-label"><span class="icon"></span>' . t('Loans') . '</a>' . '<span class="label">' . $count . '</span>',
      'class' => array('loan'),
    );
  }
  catch (Exception $e) {
    watchdog_exception('ding_list', $e);
  }

  // Remove groups with no list, and sort groups.
  foreach ($groups as $group_key => $group) {
    if (count($group['lists']) == 0) {
      unset($groups[$group_key]);
    }

    if (isset($group['sort']) && function_exists($group['sort'])) {
      uasort($groups[$group_key]['lists'], $group['sort']);
    }
  }

  reset($groups);

  $block->content = array('#theme' => 'ding_list_lists', '#groups' => $groups);
  return $block;
}

/**
 * A custom sorting function.
 */
function ding_list_custom_sort_changed($a, $b) {
  if ($a && $b) {
    if ($a[0]['#list']->changed == $b[0]['#list']->changed) {
      return 0;
    }
    return ($a[0]['#list']->changed > $b[0]['#list']->changed) ? -1 : 1;
  }
}
