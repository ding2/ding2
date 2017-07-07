<?php

/**
 * @file
 * Ding Serendipity CTools plugin file.
 */

/**
 * Plugin description.
 */
$plugin = array(
  'title' => t('Ding notifications top menu'),
  'description' => t('Displays status notifications to the user'),
  'admin info' => 'ding_notifications_admin_info',
  'single' => TRUE,
  'edit form' => 'ding_notifications_content_type_edit_form',
  'render callback' => 'ding_notifications_content_type_render',
  'category' => t('Ding!'),
);

/**
 * Return a summary for the administration interaction in panels.
 */
function ding_notifications_admin_info($subtype, $conf, $context) {
  $output = new stdClass();
  $output->title = t('User status list');
  $output->content = t('Notifications displayed: @status', array('@status' => implode(', ', $conf['top_menu_items']))) . '<br/>';
  return $output;
}

/**
 * Implements hook_content_type_render().
 */
function ding_notifications_content_type_render($subtype, $conf, $panel_args, $context) {
  global $user;

  // Create a custom cache_key that is a product of both the user and the
  // configuration.
  $cache_key = DING_NOTIFICATIONS_CACHE_PREFIX . ':' . $user->uid;
  $cache = cache_get($cache_key);

  // Checking out the user page flushes the cache.
  // By doing so we ensure users always see freshly updated notification counts
  // on the user landing page.
  if (isset($cache->expire) && $cache->expire > time() && arg(0) != 'user') {
    return $cache->data;
  }

  if (!ding_user_is_provider_user($user)) {
    $output = new stdClass();
    $output->title = t('User status');
    $output->content = '';

    cache_set($cache_key, $output, 'cache', time() + (60 * 5));
    return $output;
  }
  $content = array();
  $default = array(1, 2, 3, 4);
  $defaults = (isset($conf['top_menu_items'])) ? $conf['top_menu_items'] : $default;
  $uri = entity_uri('user', $user);

  if (module_exists('ding_message')) {
    $num_notifications = ding_message_get_message_count();
    $classes = 'icon-bell notifications-lists';
    if (!$num_notifications) {
      $classes .= ' empty';
    }
    $link_text_t = sprintf('<div data-count="%d" class="notifications-count">%d</div>', $num_notifications, $num_notifications);
    $attr = array(
      'html' => TRUE,
      'fragment' => 'userlists',
      'attributes' => array(
        'title' => t('Notifications: @count', array('@count' => $num_notifications)),
        'class' => array($classes),
      ),
    );
    $content[] = l($link_text_t, 'user', $attr);
  }

  if (isset($defaults['ready_to_pickup'])) {
    $ready_to_pickup = ding_provider_invoke('reservation', 'list', $user, DING_RESERVATION_READY);
    $ready_to_pickup_count = count($ready_to_pickup);

    $classes = 'icon-folder-open notifications-pickup';
    if (!$ready_to_pickup_count) {
      $classes .= ' empty';
    }

    $ready_to_pickup_count_t = sprintf('<div data-count="%d" class="notifications-count">%d</div>', $ready_to_pickup_count, $ready_to_pickup_count);
    $attr = array(
      'html' => TRUE,
      'attributes' => array(
        'title' => t('Ready to Pickup: @count', array('@count' => $ready_to_pickup_count)),
        'class' => array($classes),
      ),
    );
    $content[] = l($ready_to_pickup_count_t, $uri['path'] . '/status-reservations', $attr);
  }

  if (isset($defaults['dept'])) {
    $debts = ding_provider_invoke('debt', 'list', $user);
    $dept_count = count($debts);
    $dept_count_t = sprintf('<div data-count="%d" class="notifications-count">%d</div>', $dept_count, $dept_count);
    $classes = 'icon-legal notifications-fines';
    if (!$dept_count) {
      $classes .= ' empty';
    }
    $attr = array(
      'html' => TRUE,
      'attributes' => array(
        'title' => t('Fines: @count', array('@count' => $dept_count)),
        'class' => array($classes),
      ),
    );
    $content[] = l($dept_count_t, $uri['path'] . '/status/debts', $attr);
  }

  $output = new stdClass();
  if (!empty($content)) {
    $output->title = t('User status');
    $variables = array(
      'items' => $content,
      'title' => '',
      'type' => 'ul',
      'attributes' => array(),
    );
    $output->content = theme_item_list($variables);
  }

  cache_set($cache_key, $output, 'cache', time() + (60 * 5));
  return $output;
}

/**
 * Implements hook_content_type_edit_form().
 */
function ding_notifications_content_type_edit_form($form, &$form_state) {
  $options = ding_notifications_get_top_menu_options();

  $form['top_menu_items'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Select which elements to display'),
    '#default_value' => (isset($form_state['conf']['top_menu_items'])) ? $form_state['conf']['top_menu_items'] : $options,
    '#options' => $options,
  );
  return $form;
}

/**
 * Implements hook_content_type_edit_form_validate().
 */
function ding_notifications_content_type_edit_form_validate($form, &$form_state) {

}

/**
 * Implements hook_content_type_edit_form_submit().
 */
function ding_notifications_content_type_edit_form_submit($form, &$form_state) {
  $options = ding_notifications_get_top_menu_options();
  $form_state['conf']['top_menu_items'] = !empty($form_state['values']['top_menu_items']) ? $form_state['values']['top_menu_items'] : $options;
}

/**
 * Get pane options for the notifications pane admin config form.
 *
 * @return array
 *   Array of available pane options for notifications top menu.
 */
function ding_notifications_get_top_menu_options() {
  $options = array(
    'ready_to_pickup' => t('Ready to pickup'),
    'dept' => t('Dept'),
  );

  return $options;
}
