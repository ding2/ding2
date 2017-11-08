<?php
/**
 * @file
 * Handling of BPI channels.
 */

use Bpi\Sdk\Item\Channel;
use Bpi\Sdk\Item\Subscription;

// We want to reuse some helper functions.
require_once __DIR__ . '/bpi.syndicate.inc';
require_once __DIR__ . '/bpi.user.inc';

/**
 * Key for storing data in session.
 */
define('BPI_CHANNEL_ALL_FACETS_KEY', 'BPI_CHANNEL_ALL_FACETS');

/**
 * Define channels page markup.
 *
 * @return array
 *   Form structure.
 *
 * @ingroup forms
 */
function bpi_channel_list_form(array $form, array &$form_state, $items = NULL) {
  if (bpi_service_is_configured()) {
    bpi_check_bpi_user();

    drupal_add_library('system', 'drupal.ajax');

    if ($items === NULL) {
      $query_form = array(
        '#type' => 'container',
        '#attributes' => array(
          'class' => array(
            'bpi-query',
          ),
        ),
      );

      $query_form['bpi_search'] = array(
        '#type' => 'container',
        '#attributes' => array(
          'class' => array('bpi-search'),
        ),
      );

      $query_form['bpi_search']['bpi_search_query'] = array(
        '#type' => 'textfield',
        '#default_value' => _bpi_get_current_search_phrase(),
        '#description' => t('Search in title and description'),
      );

      $query_form['bpi_search']['bpi_search_actions'] = array(
        '#type' => 'container',
        '#attributes' => array(
          'class' => array(
            drupal_html_class('container-inline'),
          ),
        ),
      );

      $query_form['bpi_search']['bpi_search_actions']['bpi_search_submit'] = array(
        '#type' => 'submit',
        '#value' => t('Search'),
      );

      if (_bpi_get_current_search_phrase()) {
        $query_form['bpi_search']['bpi_search_actions']['bpi_search_reset'] = array(
          '#type' => 'item',
          '#markup' => l(t('Reset search'), current_path(), array(
            'query' => NULL,
            'attributes' => array(
              'class' => array('button'),
            ),
          )),
        );
      }

      $items = bpi_channel_search_get_items();
      bpi_channel_build_search_facets($query_form);
    }

    $total_items = $items ? $items->total : 0;
    $page_size = _bpi_get_query_parameter('amount', BPI_DEFAULT_PAGE_SIZE);
    pager_default_initialize($total_items, $page_size);

    $result_form = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array(
          'bpi-result',
        ),
      ),
    );

    if ($items && $items->count() > 0) {
      $result_form['bpi_search_info'] = array(
        '#type' => 'container',
        '#attributes' => array(
          'class' => array('bpi-search-info', 'container-inline'),
        ),
      );

      $current_page = pager_find_page();
      $items_from = $current_page * $page_size + 1;
      $items_to = min(($current_page + 1) * $page_size, $total_items);

      $result_form['bpi_search_info']['bpi_search_paging_info'] = array(
        '#type' => 'item',
        '#markup' => ($items_from < $items_to
                      ? t('Showing items @from–@to of @total', array(
                        '@from' => $items_from,
                        '@to' => $items_to,
                        '@total' => $total_items,
                      ))
                      : t('Showing item @from of @total', array(
                        '@from' => $items_from,
                        '@total' => $total_items,
                      ))),
      );

      $result_form['bpi_search_info']['bpi_search_amount'] = array(
        '#type' => 'select',
        '#title' => t('Page size'),
        '#options' => drupal_map_assoc(array(10, 20, 50, 100)),
        '#default_value' => _bpi_get_query_parameter('amount', BPI_DEFAULT_PAGE_SIZE),
        '#attributes' => array(
          'onchange' => 'form.submit()',
        ),
      );
    }
    else {
      $result_form['bpi_search_amount'] = array(
        '#type' => 'hidden',
      );
    }

    $result_form['bpi_search_results'] = array(
      '#type' => 'item',
      '#markup' => theme('bpi_channel_list', array(
        'items' => $items,
        'empty' => t('No channels found'),
      )),
    );
    $result_form['bpi_search_results']['#prefix'] = '<div class="bpi-search-result bpi-channel-list">';
    $result_form['bpi_search_results']['#suffix'] = '</div>';

    $result_form['bpi_search_pager'] = array(
      '#type' => 'item',
      '#markup' => theme('pager'),
    );

    $query_form['loading'] = array(
      '#type' => 'item',
      '#markup' => '<div class="loading"><div class="message">' . t('Please wait') . '</div></div>',
    );

    $form['bpi_actions'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array(
          'action-links',
        ),
      ),
    );

    $form['bpi_query'] = $query_form;
    $form['bpi_result'] = $result_form;

    $form['#attributes']['class'][] = 'bpi';
    $form['#attached']['css'][] = drupal_get_path('module', 'bpi') . '/css/bpi-admin.styles.css';
    $form['#attached']['js'][] = drupal_get_path('module', 'bpi') . '/js/bpi-admin.js';
    $form['#submit'][] = 'bpi_channel_list_form_submit';
  }

  return $form;
}

/**
 * Custom submit handler for syndication page form.
 *
 * @param array $form
 *   Form structure.
 * @param array $form_state
 *   Form state values.
 *
 * @see bpi_syndicate_page_form()
 *
 * @ingroup forms
 */
function bpi_channel_list_form_submit(array $form, array &$form_state) {
  $bpi_query = array();
  $sorting = _bpi_get_current_sorting();
  if (!empty($sorting)) {
    $bpi_query[BPI_QUERY_SORT_NAME] = $sorting;
  }
  $values = $form_state['values'];

  if (isset($values['bpi_search_amount']) && intval($values['bpi_search_amount']) > 0) {
    $bpi_query['amount'] = intval($values['bpi_search_amount']);
  }

  if (isset($values['bpi_search_query']) && trim($values['bpi_search_query'])) {
    $bpi_query[BPI_SEARCH_PHRASE_KEY] = trim($values['bpi_search_query']);
  }

  if (isset($values['bpi_facets'])) {
    foreach ($values['bpi_facets'] as $key => $value) {
      $selected_values = is_array($value) ? array_keys(array_filter($value)) : $value;
      if (!empty($selected_values)) {
        if (!isset($bpi_query['filter'])) {
          $bpi_query['filter'] = array();
        }
        $bpi_query['filter'][$key] = $selected_values;
      }
    }
  }

  // Redirect to search results.
  drupal_goto('admin/bpi/channel', array('query' => _bpi_build_query($bpi_query, TRUE)));
}

/**
 * Channel list view.
 *
 * @return array
 *   The view.
 */
function bpi_channel_list() {
  return array(
    'bpi_channel_subscription_form' => drupal_get_form('bpi_channel_subscription_form'),
    'bpi_channel_list_form' => drupal_get_form('bpi_channel_list_form'),
  );
}

/**
 * Show all channels or channels having a user as administrator or editor.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 *
 * @return array
 *   The form.
 */
function bpi_channel_user_list_form(array $form, array &$form_state) {
  $user_id = count($form_state['build_info']['args']) > 0 ? $form_state['build_info']['args'][0] : bpi_get_current_bpi_user_id();
  $items = bpi_get_channels_by_user($user_id);
  return bpi_channel_list_form($form, $form_state, $items);
}

/**
 * Channel user list view.
 *
 * @return array
 *   The view.
 */
function bpi_channel_user_list() {
  return array(
    'bpi_channel_subscription_form' => drupal_get_form('bpi_channel_subscription_form'),
    'bpi_channel_user_list_form' => drupal_get_form('bpi_channel_user_list_form'),
  );
}

/**
 * Define channels page markup.
 *
 * @return array
 *   Form structure.
 *
 * @ingroup forms
 */
function bpi_channel_subscription_list_form(array $form, array &$form_state) {
  $user_id = count($form_state['build_info']['args']) > 0 ? $form_state['build_info']['args'][0] : bpi_get_current_bpi_user_id();
  $items = array();
  $user = bpi_get_user($user_id);
  if ($user) {
    $channelIds = array();
    $subscriptions = $user->getSubscriptions();
    if ($subscriptions) {
      foreach ($subscriptions as $subscription) {
        if (bpi_channel_is_channel_subscription($subscription)) {
          $filter = $subscription->getFilter();
          if (isset($filter['channels']) && count($filter['channels']) === 1) {
            $channelIds[] = $filter['channels'][0];
          }
        }
      }
    }
    $items = $channelIds ? bpi_get_channels_by_ids($channelIds) : array();
  }
  return bpi_channel_list_form($form, $form_state, $items);
}

/**
 * Subscription list view.
 *
 * @return array
 *   The view.
 */
function bpi_channel_subscription_list() {
  return array(
    'bpi_channel_subscription_form' => drupal_get_form('bpi_channel_subscription_form'),
    'bpi_channel_subscription_list_form' => drupal_get_form('bpi_channel_subscription_list_form'),
  );
}

/**
 * Create form for creating/deleting channel subscriptions.
 */
function bpi_channel_subscription_form() {
  return array(
    '#type' => 'form',
    '#action' => '/admin/bpi/channel/subscription',
    '#id' => 'bpi-channel-subscription-form',
    'channel_id' => array(
      '#type' => 'hidden',
      '#value' => '',
    ),
    'command' => array(
      '#type' => 'hidden',
      '#value' => '',
    ),
    'redirect' => array(
      '#type' => 'hidden',
      '#value' => request_uri(),
    ),
    'script' => array(
      '#type' => 'item',
      '#markup' => '<script>
var BpiChannel = {
  subscribe: function(channelId) {
    var form = document.getElementById("bpi-channel-subscription-form");
    form.command.value = "subscribe";
    form.channel_id.value = channelId;
    form.submit();
  },
  unsubscribe: function(channelId) {
    var form = document.getElementById("bpi-channel-subscription-form");
    form.command.value = "unsubscribe";
    form.channel_id.value = channelId;
    form.submit();
  }
};
</script>',
    ),
  );
}

/**
 * Show channel details.
 *
 * @param string $channel_id
 *   The channel id.
 *
 * @return string
 *   The rendered view.
 */
function bpi_channel_view($channel_id) {
  $channel = bpi_get_channel($channel_id);

  if (!$channel) {
    return '';
  }

  $bpi = bpi_client_instance();
  $nodes = $bpi->searchNodes(array(
    'filter' => array(
      'channels' => array($channel->getId()),
    ),
  ));

  $content = theme('bpi_channel_view', array(
    'channel' => $channel,
    'has_new_content' => bpi_channel_has_new_content($channel),
    'nodes' => bpi_nodelist_to_array($nodes),
  ));

  bpi_channel_set_channel_viewed_at($channel_id);

  return $content;
}

/**
 * Check if channel has new content.
 *
 * A channel has new content if it contains content not viewed (in a list) by
 * the current user.
 *
 * @return bool
 *   true iff the channel has new content.
 */
function bpi_channel_has_new_content(Channel $channel) {
  $node_last_added_at = $channel->getNodeLastAddedAt();
  $channel_viewed_at = bpi_channel_get_channel_viewed_at($channel->getId());
  return $channel_viewed_at !== NULL && $node_last_added_at !== NULL && $node_last_added_at > $channel_viewed_at;
}

/**
 * Mark a channel as viewed by the current user.
 *
 * @param string $channel_id
 *   The channel id.
 */
function bpi_channel_set_channel_viewed_at($channel_id) {
  global $user;

  $data = isset($user->data['bpi_channel']) ? $user->data['bpi_channel'] : array();
  $channel_data = isset($data['channel_data']) ? $data['channel_data'] : array();
  $channel_data[$channel_id]['last_viewed_at'] = new \DateTime();
  $data['channel_data'] = $channel_data;

  user_save($user, array('data' => array('bpi_channel' => $data)));
}

/**
 * Get time when a channel was last viewed by the current user.
 *
 * @param string $channel_id
 *   The channel id.
 *
 * @return \DateTime|NULL
 *   The time when the channel was last viewed.
 */
function bpi_channel_get_channel_viewed_at($channel_id) {
  global $user;

  return isset(
    $user->data['bpi_channel'],
    $user->data['bpi_channel']['channel_data'],
    $user->data['bpi_channel']['channel_data'][$channel_id],
    $user->data['bpi_channel']['channel_data'][$channel_id]['last_viewed_at']) ?
    $user->data['bpi_channel']['channel_data'][$channel_id]['last_viewed_at'] : NULL;
}

/**
 * Channel edit form. Also used for creating new channels.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 *
 * @return array
 *   The form.
 */
function bpi_channel_edit_form(array $form, array &$form_state) {
  $channel_id = isset($form_state['build_info']['args'][0]) ? $form_state['build_info']['args'][0] : NULL;

  if ($channel_id) {
    // Edit channel.
    $channel = bpi_get_channel($channel_id);

    if (!bpi_can_edit_channel($channel)) {
      drupal_set_message(t("You're not allowed to edit this channel"), 'error');
      return $form;
    }
  }

  $form['channel']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => isset($channel) ? $channel->getName() : NULL,
    '#required' => TRUE,
  );

  $form['channel']['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#default_value' => isset($channel) ? $channel->getDescription() : NULL,
    '#required' => TRUE,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => $channel_id ? t('Save') : t('Create channel'),
  );

  $form['cancel'] = array(
    '#type' => 'markup',
    '#markup' => l(t('Cancel'), 'admin/bpi/channel/' . (isset($channel) ? $channel->getId() : '')),
  );

  $form['#submit'][] = 'bpi_channel_edit_form_submit';

  $form['#attributes']['class'][] = 'bpi';
  $form['#attached']['css'][] = drupal_get_path('module', 'bpi') . '/css/bpi-admin.styles.css';
  $form['#attached']['js'][] = drupal_get_path('module', 'bpi') . '/js/bpi-admin.js';

  return $form;
}

/**
 * Submit handler for bpi_channel_edit_form.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 */
function bpi_channel_edit_form_submit(array $form, array &$form_state) {
  $channel_id = isset($form_state['build_info']['args'][0]) ? $form_state['build_info']['args'][0] : NULL;

  $values = $form_state['values'];

  $channel_data = array(
    'name' => $values['name'],
    'description' => $values['description'],
  );

  if (!$channel_id) {
    $channel_data['adminId'] = bpi_get_current_bpi_user_id();
    try {
      $bpi = bpi_client_instance();
      $channel = $bpi->createChannel($channel_data);
      drupal_set_message(t('Channel created.'));
      $channel_id = $channel->getId();
    }
    catch (\Exception $e) {
      watchdog_exception('bpi', $e);
      drupal_set_message(t('Channel creation failed.'), 'error');
    }
  }
  else {
    try {
      $bpi = bpi_client_instance();
      $bpi->updateChannel($channel_id, $channel_data);
      drupal_set_message(t('Channel updated.'));
    }
    catch (\Exception $e) {
      watchdog_exception('bpi', $e);
      drupal_set_message(t('Channel update failed.'), 'error');
    }
  }

  drupal_goto('admin/bpi/channel/' . $channel_id);
}

/**
 * Delete channel form.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 *
 * @return array
 *   The form.
 */
function bpi_channel_delete_form(array $form, array &$form_state) {
  $channel_id = isset($form_state['build_info']['args'][0]) ? $form_state['build_info']['args'][0] : NULL;

  $channel = bpi_get_channel($channel_id);

  if (!bpi_can_edit_channel($channel)) {
    drupal_set_message(t("You're not allowed to edit this channel"), 'error');
    return $form;
  }

  return confirm_form($form,
    t('Are you sure you want to delete %title?', array('%title' => $channel->getName())),
    'admin/bpi/channel/' . $channel->getId(),
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Submit handler for bpi_channel_delete_form.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 */
function bpi_channel_delete_form_submit(array $form, array &$form_state) {
  $channel_id = isset($form_state['build_info']['args'][0]) ? $form_state['build_info']['args'][0] : NULL;

  try {
    $bpi = bpi_client_instance();
    $success = $bpi->deleteChannel($channel_id);
    if ($success) {
      drupal_set_message(t('Channel deleted.'));
      drupal_goto('admin/bpi/channel');
    }
    else {
      drupal_set_message(t('Deleting channel failed.'), 'error');
    }
  }
  catch (\Exception $e) {
    watchdog_exception('bpi', $e);
    drupal_set_message(t('Deleting channel failed.'), 'error');
  }
}

/**
 * Handler for managing subscription/unsubscription to channels.
 */
function bpi_channel_subscription() {
  $user = bpi_get_user();
  $command = isset($_POST['command']) ? $_POST['command'] : NULL;
  $channel_id = isset($_POST['channel_id']) ? $_POST['channel_id'] : NULL;
  $redirect = isset($_POST['redirect']) ? $_POST['redirect'] : 'admin/bpi/channel';

  $channel = bpi_get_channel($channel_id);
  if (!$channel) {
    drupal_set_message(t('No such channel: %channel', array('%channel' => $channel_id)), 'error');
    return drupal_goto($redirect);
  }

  $title = _bpi_get_channel_subscription_title($user, $channel);

  switch ($command) {
    case 'subscribe':
      try {
        $bpi = bpi_client_instance();
        $bpi->createSubscription($user->getId(), array(
          'title' => $title,
          'filter' => array(
            'channels' => array($channel->getId()),
          ),
        ));
        bpi_flush_user();
        drupal_set_message(t('Subscription on channel %channel created', array('%channel' => $channel->getName())));
      }
      catch (\Exception $e) {
        watchdog_exception('bpi', $e);
        drupal_set_message(t('Cannot subscribe to channel %channel', array('%channel' => $channel->getName())), 'error');
      }
      break;

    case 'unsubscribe':
      try {
        $bpi = bpi_client_instance();
        $bpi->deleteSubscription($user->getId(), $title);
        bpi_flush_user();
        drupal_set_message(t('Subscription on channel %channel deleted', array('%channel' => $channel->getName())));
      }
      catch (\Exception $e) {
        watchdog_exception('bpi', $e);
        drupal_set_message(t('Cannot unsubscribe from channel %channel', array('%channel' => $channel->getName())), 'error');
      }
      break;

    default:
      break;
  }

  return drupal_goto($redirect);
}

/**
 * Create a subscription to a channel for the current user.
 *
 * @param string $channel_id
 *   The channel id.
 */
function bpi_channel_subscribe($channel_id) {
  $user = bpi_get_user();
  $channel = bpi_get_channel($channel_id);
  if (!$channel) {
    drupal_set_message(t('No such channel: %channel', array('%channel' => $channel_id)), 'error');
    return drupal_goto('admin/bpi/channel');
  }

  $title = _bpi_get_channel_subscription_title($user, $channel);

  try {
    $bpi = bpi_client_instance();
    $bpi->createSubscription($user->getId(), array(
      'title' => $title,
      'filter' => array(
        'channels' => array($channel->getId()),
      ),
    ));
    bpi_flush_user();
    drupal_set_message(t('Channel subscription created'));
  }
  catch (\Exception $e) {
    watchdog_exception('bpi', $e);
    drupal_set_message(t('Cannot subscribe to channel %channel', array('%channel' => $channel_id)), 'error');
  }

  return drupal_goto('admin/bpi/channel');
}

/**
 * Remove a subscription to a channel for the current user.
 *
 * @param string $channel_id
 *   The channel id.
 */
function bpi_channel_unsubscribe($channel_id) {
  $user = bpi_get_user();
  $channel = bpi_get_channel($channel_id);
  if (!$channel) {
    drupal_set_message(t('No such channel: %channel', array('%channel' => $channel_id)), 'error');
    return drupal_goto('admin/bpi/channel');
  }

  $title = _bpi_get_channel_subscription_title($user, $channel);

  try {
    $bpi = bpi_client_instance();
    $bpi->deleteSubscription($user->getId(), $title);
    bpi_flush_user();
    drupal_set_message(t('Channel subscription deleted'));
  }
  catch (\Exception $e) {
    watchdog_exception('bpi', $e);
    drupal_set_message(t('Cannot unsubscribe from channel %channel', array('%channel' => $channel_id)), 'error');
  }

  return drupal_goto('admin/bpi/channel');
}

/**
 * Get title for a channel subscription for a user.
 *
 * Subscriptions must have unique names (per user).
 */
function _bpi_get_channel_subscription_title($user, $channel) {
  return '### ' . $user->getId() . ' - ' . $channel->getId() . ' ###';
}

/**
 * Determine if a subscription is a channel subscription.
 *
 * @param Subscription $subscription
 *   The subscription.
 */
function bpi_channel_is_channel_subscription(Subscription $subscription) {
  return preg_match('/^#+.+#+$/', $subscription->getTitle());
}

/**
 * Get channels by filters.
 *
 * @param array $filters
 *   The filters.
 *
 * @return array|null
 *   The channels.
 */
function bpi_get_channels_by($filters = array()) {
  $page = pager_find_page();
  $query = _bpi_get_query_parameter('query');
  $sort = _bpi_get_current_sorting();

  return bpi_search_channels($query, $page, $filters, $sort);
}

/**
 * Get channels for a user.
 *
 * @param string $user_id
 *   The user id.
 *
 * @return \Bpi\Sdk\ChannelList
 *   The channel list.
 */
function bpi_get_channels_by_user($user_id) {
  $bpi = bpi_client_instance();
  return $bpi->getChannelsByUser($user_id);
}

/**
 * Get channels by ids.
 *
 * @param array $ids
 *   The ids.
 *
 * @return \Bpi\Sdk\ChannelList
 *   The channel list.
 */
function bpi_get_channels_by_ids(array $ids) {
  return bpi_get_channels_by(array('id' => $ids));
}

/**
 * Get a channel by id.
 *
 * @param string $id
 *   The channel id.
 *
 * @return \Bpi\Sdk\Item\Channel|null
 *   The channel if found.
 */
function bpi_get_channel($id) {
  try {
    $bpi = bpi_client_instance();

    $channel = $bpi->getChannel($id);

    return $channel;
  }
  catch (\Exception $e) {
    watchdog_exception('bpi', $e);
    drupal_set_message(t('Failed to fetch channel. Check reports for more information.'), 'error');
  }

  return NULL;
}

/**
 * Search channels.
 *
 * @return \Bpi\Sdk\ChannelList
 *   The channels.
 */
function bpi_channel_search_get_items() {
  if ($_SERVER['REQUEST_METHOD'] != 'GET') {
    return NULL;
  }

  $page = pager_find_page();
  $phrase = _bpi_get_current_search_phrase();
  $filters = _bpi_get_current_filter();
  $sort = _bpi_get_current_sorting();

  $response = bpi_search_channels($phrase, $page, $filters, $sort);

  return $response;
}

/**
 * Search channels.
 *
 * @param string $query
 *   The search query.
 * @param int $page
 *   The page (for paging).
 * @param array $filters
 *   The search filters.
 * @param array $sorting
 *   How to sort the result.
 *
 * @return array|null
 *   The channels matching the search query and filters.
 */
function bpi_search_channels($query = '', $page = 1, $filters = array(), $sorting = array()) {
  try {
    $bpi = bpi_client_instance();
    $amount = max(intval(_bpi_get_query_parameter('amount')), BPI_DEFAULT_PAGE_SIZE);
    $offset = $page * $amount;

    $bpi_data = $bpi->searchChannels(
      array(
        'amount' => $amount,
        'offset' => $offset,
        'filter' => $filters,
        'sort' => $sorting ? $sorting : array(),
        'search' => $query,
      )
    );

    return $bpi_data;
  }
  catch (Exception $e) {
    watchdog_exception('bpi', $e);
    drupal_set_message(t('Failed to fetch channels. Check reports for more information.'), 'error');
  }

  return NULL;
}

/**
 * Implements theme_HOOK().
 *
 * @param array $variables
 *   Theme variables.
 *
 * @return string
 *   An HTML string representing the themed output.
 */
function theme_bpi_channel_list(array $variables) {
  return theme('table', $variables);
}

/**
 * Implements hook_preprocess_HOOK().
 */
function bpi_preprocess_bpi_channel_list(array &$variables) {
  $items = $variables['items'];

  $user = bpi_get_user();

  $table_head = array(
    array(
      'data' => bpi_get_sort_link(t('Name'), 'name'),
      'class' => array('bpi-title', _bpi_get_current_sorting('name') ? 'active' : ''),
    ),
    array(
      'data' => t('Description'),
      'data' => bpi_get_sort_link(t('Description'), 'description'),
      'class' => array('bpi-description', _bpi_get_current_sorting('description') ? 'active' : ''),
    ),
    array(
      'data' => bpi_get_sort_link(t('Administrator'), 'admin'),
      'class' => array('bpi-title', _bpi_get_current_sorting('title') ? 'active' : ''),
    ),
    array(
      'data' => bpi_get_sort_link(t('Agency'), 'agency'),
      'class' => array('bpi-agency', _bpi_get_current_sorting('agency') ? 'active' : ''),
    ),
    array(
      'data' => t('Number of nodes'),
      'class' => array('bpi-nodes'),
    ),
    array(
      'data' => bpi_get_sort_link(t('Node last added at'), 'nodeLastAddedAt'),
      'class' => array('bpi-node-last-added-at', _bpi_get_current_sorting('nodeLastAddedAt') ? 'active' : ''),
    ),
    array(
      'data' => t('Has new content'),
      'class' => array('bpi-has-new-content'),
    ),
    array(
      'data' => t('Subscribed to channel?'),
      'class' => array('bpi-subscribed-to-channel'),
    ),
    array(
      'data' => t('Actions'),
      'class' => 'bpi-actions',
    ),
  );

  // Set table defaults.
  $variables['header'] = $table_head;
  $variables['sticky'] = TRUE;
  $variables['rows'] = array();

  $rows = array();
  if (!empty($items)) {
    foreach ($items as $item) {
      $title = l($item->getName(), 'admin/bpi/channel/' . $item->getId());
      $description = $item->getDescription();

      $administrator = '';
      $agency = '';
      $admin = $item->getAdmin();
      if ($admin) {
        $administrator = l($admin->getName(), 'admin/bpi/user/' . $admin->getId());
        $agency = $admin->getAgency()->getName();
      }
      $is_subscribed = _bpi_channel_is_subscribed($user, $item);
      $subscribed_to_channel = $user ? array(
        'data' => $is_subscribed ? t('Yes') : t('No'),
        'class' => $is_subscribed ? 'bpi-is-subscribed' : 'bpi-is-not-subscribed',
      ) : '';

      $actions = [];
      if (bpi_can_edit_channel($item)) {
        $actions[] = l(t('Edit'), 'admin/bpi/channel/' . $item->getId() . '/edit');
        $actions[] = l(t('Delete'), 'admin/bpi/channel/' . $item->getId() . '/delete');
      }
      if ($user) {
        $actions[] = $is_subscribed
                   ? '<a href="#" onclick="BpiChannel.unsubscribe(\'' . $item->getId() . '\')">' . t('Unsubscribe from channel') . '</a>'
                   : '<a href="#" onclick="BpiChannel.subscribe(\'' . $item->getId() . '\')">' . t('Subscribe to channel') . '</a>';
      }

      $node_last_added_at = $item->getNodeLastAddedAt() ? $item->getNodeLastAddedAt()->format('Y-m-d H:i:s') : NULL;
      $has_new_content = bpi_channel_has_new_content($item) ? t('Yes') : t('No');

      $row = array(
        'title' => $title,
        'description' => $description,
        'administrator' => $administrator,
        'agency' => $agency,
        'nodes' => count($item->getNodes()),
        'node_last_added_at' => $node_last_added_at,
        'has_new_content' => $has_new_content,
        'subscribed_to_channel' => $subscribed_to_channel,
        'actions' => implode(' ', $actions),
      );

      $rows[] = $row;
    }
  }

  // Unset old data.
  unset($variables['items']);

  // Set table data.
  $variables['rows'] = $rows;
}

/**
 * Check if a user has a subscription to a channel.
 *
 * @param \Bpi\Item\User|NULL $user
 *   The user.
 * @param \Bpi\Item\Channel|NULL $channel
 *   The channel.
 *
 * @return bool
 *   The result.
 */
function _bpi_channel_is_subscribed($user, $channel) {
  if (!$user || !$channel || !$user->getSubscriptions()) {
    return FALSE;
  }

  $title = _bpi_get_channel_subscription_title($user, $channel);

  return !empty(array_filter($user->getSubscriptions(), function($subscription) use ($channel, $title) {
    $filter = $subscription->getFilter();
    return $subscription->getTitle() == $title
      && isset($filter['channels']) && is_array($filter['channels']) && in_array($channel->getId(), $filter['channels']);
  }));
}

/**
 * Implements theme_HOOK().
 *
 * @param array $variables
 *   Theme variables.
 *
 * @return string
 *   An HTML string representing the themed output.
 */
function theme_bpi_channel_node_list(array $variables) {
  return theme('table', $variables);
}

/**
 * Add additional actions to channel node list.
 *
 * @param array $actions
 *   The list of actions.
 * @param array $item
 *   The current item list.
 * @param array $variables
 *   The variables sent in the list function.
 */
function bpi_channel_node_list_action_callback(array &$actions, array $item, array &$variables) {
  if (!empty($variables['#channel'])) {
    $channel = $variables['#channel'];
    if (bpi_can_contribute_to_channel($channel)) {
      $actions[] = l(t('Remove node from channel'),
                   'admin/bpi/channel/' . $channel->getId() . '/node/remove/' . $item['bpi_id']
      );
    }
  }
}

/**
 * Implements hook_preprocess_HOOK().
 */
function bpi_preprocess_bpi_channel_node_list(array &$variables) {
  drupal_add_css(drupal_get_path('module', 'bpi') . '/css/bpi-admin.styles.css');
  $variables['actions_callback'] = 'bpi_channel_node_list_action_callback';
  bpi_preprocess_bpi_search_results($variables);
}

/**
 * Form for removing an editor from a channel.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 *
 * @return array
 *   The form.
 */
function bpi_channel_editor_remove_form(array $form, array &$form_state) {
  list($channel_id, $editor_id) = $form_state['build_info']['args'];

  $channel = bpi_get_channel($channel_id);

  if (!bpi_can_edit_channel($channel)) {
    drupal_set_message(t("You're not allowed to edit this channel"), 'error');
    return $form;
  }

  $editor = bpi_get_user($editor_id);

  if (!$editor) {
    drupal_set_message(t('Invalid editor'), 'error');
    return $form;
  }

  return confirm_form($form,
    t('Are you sure you want to remove %editor from %channel?', array('%editor' => $editor->getName() ? $editor->getName() : $editor->getEmail(), '%channel' => $channel->getName())),
    'admin/bpi/channel/' . $channel->getId(),
    t('This action cannot be undone.'),
    t('Remove'),
    t('Cancel')
  );
}

/**
 * Submit handler for bpi_channel_editor_remove_form.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 */
function bpi_channel_editor_remove_form_submit(array $form, array &$form_state) {
  list($channel_id, $editor_id) = $form_state['build_info']['args'];

  $bpi = bpi_client_instance();
  $success = $bpi->removeEditorFromChannel($channel_id, bpi_get_current_bpi_user_id(), array($editor_id));

  if ($success) {
    drupal_set_message(t('Editor removed from channel'));
  }

  drupal_goto('admin/bpi/channel/' . $channel_id);
}

/**
 * Form for adding a node to a channel.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 *
 * @return array
 *   The form.
 */
function bpi_channel_node_add_form(array $form, array &$form_state) {
  list($node_id) = $form_state['build_info']['args'];

  $items = bpi_get_channels_by_user(bpi_get_current_bpi_user_id());
  $options = array('' => '');
  if ($items && $items->count() > 0) {
    foreach ($items as $channel) {
      $options[$channel->getId()] = $channel->getName();
    }
  }

  $bpi = bpi_client_instance();
  $bpi_node = $bpi->getNode($node_id);
  $bpi_content = $bpi_node->getProperties();

  $form['node'] = array(
    '#type' => 'item',
    '#markup' => theme('bpi_preview_item', array(
      'item' => $bpi_content,
      'no_actions' => TRUE,
    )),
  );

  $form['bpi_actions_bottom'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'bpi-actions',
        drupal_html_class('container-inline'),
      ),
    ),
  );

  $form['bpi_actions_bottom']['channel'] = array(
    '#type' => 'select',
    '#title' => t('Channel'),
    '#options' => $options,
    '#required' => TRUE,
    '#default_value' => isset($_GET['channel']) ? $_GET['channel'] : '',
  );

  $form['bpi_actions_bottom']['add_to_channel'] = array(
    '#type' => 'submit',
    '#value' => t('Add node to channel'),
    '#submit' => array('bpi_channel_node_add_form_submit'),
  );

  return $form;
}

/**
 * Submit handler for bpi_channel_node_add_form.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 */
function bpi_channel_node_add_form_submit(array $form, array &$form_state) {
  list($node_id) = $form_state['build_info']['args'];
  $values = $form_state['values'];
  $channel_id = $values['channel'];

  $bpi = bpi_client_instance();
  $success = $bpi->addNodeToChannel($channel_id, bpi_get_current_bpi_user_id(), array($node_id));

  if ($success) {
    drupal_set_message(t('Node added to channel'));
  }

  drupal_goto('admin/bpi/channel/' . $channel_id);
}

/**
 * Form for removing a node from a channel.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 *
 * @return array
 *   The form.
 */
function bpi_channel_node_remove_form(array $form, array &$form_state) {
  list($channel_id, $node_id) = $form_state['build_info']['args'];

  $bpi = bpi_client_instance();
  $channel = $bpi->getChannel($channel_id);

  if (!bpi_can_edit_channel($channel)) {
    drupal_set_message(t("You're not allowed to edit this channel"), 'error');
    return $form;
  }

  $node = $bpi->getNode($node_id);

  return confirm_form($form,
    t('Are you sure you want to remove %node from %channel?', array('%node' => $node->getProperties()['title'], '%channel' => $channel->getName())),
    'admin/bpi/channel/' . $channel->getId(),
    t('This action cannot be undone.'),
    t('Remove'),
    t('Cancel')
  );
}

/**
 * Submit handler for bpi_channel_node_remove_form.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 */
function bpi_channel_node_remove_form_submit(array $form, array &$form_state) {
  list($channel_id, $node_id) = $form_state['build_info']['args'];

  $bpi = bpi_client_instance();
  $success = $bpi->removeNodeFromChannel($channel_id, bpi_get_current_bpi_user_id(), array($node_id));

  if ($success) {
    drupal_set_message(t('Node removed from channel'));
  }

  drupal_goto('admin/bpi/channel/' . $channel_id);
}

/**
 * Decide if the current user can edit a channel.
 *
 * @param Channel $channel
 *   The channel.
 *
 * @return bool
 *   True iff the current user can edit the channel.
 */
function bpi_can_edit_channel(Channel $channel) {
  return $channel && $channel->getAdmin() && $channel->getAdmin()->getId() == bpi_get_current_bpi_user_id();
}

/**
 * Decide if the current user can administer a channel.
 *
 * @param Channel $channel
 *   The channel.
 *
 * @return bool
 *   True iff the current user can administer the channel.
 */
function bpi_can_contribute_to_channel(Channel $channel) {
  if (bpi_can_edit_channel($channel)) {
    return TRUE;
  }
  $user_id = bpi_get_current_bpi_user_id();
  $editors = $channel->getEditors();
  if ($editors) {
    foreach ($editors as $editor) {
      if ($editor->getId() == $user_id) {
        return TRUE;
      }
    }
  }
  return FALSE;
}

/**
 * Build facets form fields.
 *
 * @param array $form
 *   The form.
 */
function bpi_channel_build_search_facets(array &$form) {
  $facets = bpi_channel_get_facets();

  if (!empty($facets)) {
    $filter_form = array(
      '#type' => 'fieldset',
      '#title' => t('Filters'),
      '#collapsible' => TRUE,
      '#collapsed' => !_bpi_is_filter_applied(),
      '#attributes' => array(
        'class' => array(
          'bpi-filters',
        ),
      ),
    );

    $facets_form = array(
      '#type' => 'container',
      '#tree' => TRUE,
      '#attributes' => array(
        'class' => array(
          'bpi-facets',
        ),
      ),
    );

    // Use chosen to render select controls?
    $library = libraries_detect('chosen');
    $use_chosen = !empty($library['installed']);

    if ($use_chosen) {
      foreach ($library['files']['css'] as $file => $v) {
        $form['#attached']['css'][] = $library['library path'] . '/' . $file;
      }
      foreach ($library['files']['js'] as $file => $v) {
        $form['#attached']['js'][] = $library['library path'] . '/' . $file;
      }
    }

    foreach ($facets as $name => $terms) {
      $id = $name;
      $type = $use_chosen ? 'select' : 'checkboxes';
      $multiple = TRUE;
      $options = array();
      foreach ($terms as $term => $item) {
        $options[$term] = $item['title'];
      }
      $default_value = _bpi_get_query_parameter(array('filter', $name), array());

      $facets_form[$id] = array(
        '#type' => $type,
        '#multiple' => $multiple,
        '#chosen' => $multiple && $use_chosen,
        '#size' => $multiple ? min(20, count($options)) : NULL,
        '#title' => bpi_label_mapper($name) ? bpi_label_mapper($name) : $name,
        '#options' => $options,
        '#default_value' => $default_value,
        '#attributes' => array(
          'data-placeholder' => $multiple ? t('Pick some values') : t('Pick a value'),
          'data-no-matches' => t('Nothing matches'),
        ),
        '#prefix' => '<div class="bpi-facet bpi-facet-' . drupal_html_class($name) . '">',
        '#suffix' => '</div>',
      );
    }

    if (count($facets) > 1) {
      // Add logical operator.
      $name = 'logicalOperator';
      $id = $name;
      $facets_form[$id] = array(
        '#type' => 'select',
        '#title' => bpi_label_mapper($name) ? bpi_label_mapper($name) : $name,
        '#options' => array(
          'and' => t('All must apply'),
          'or' => t('Any must apply'),
        ),
        '#default_value' => _bpi_get_query_parameter(array('filter', $name), 'and'),
        '#weight' => -10,
      );
    }

    $filter_form['bpi_facets'] = $facets_form;

    $filter_form['bpi_actions'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array(
          drupal_html_class('container-inline'),
        ),
      ),
    );

    if (_bpi_get_current_filter()) {
      $filter_form['bpi_actions']['reset_filter'] = array(
        '#type' => 'item',
        '#markup' => l(t('Reset filters'), current_path(), array(
          'query' => _bpi_get_current_search_query(),
          'attributes' => array(
            'class' => array('button'),
          ),
        )),
      );
    }

    $form['bpi_filter'] = $filter_form;
  }
}

/**
 * Get facets as an array.
 *
 * For performance reasons facets will only be loaded when no search or
 * filters are applied.
 *
 * @return array|null
 *   All facets.
 */
function bpi_channel_get_facets() {
  // Reload facets if they're not cached locally.
  $reload = !isset($_SESSION[BPI_CHANNEL_ALL_FACETS_KEY]) || !is_array($_SESSION[BPI_CHANNEL_ALL_FACETS_KEY]);
  if (!$reload) {
    // Reload if neither text nor filter is applied.
    $reload = !(_bpi_get_current_search_phrase() || _bpi_get_current_filter());
  }

  if ($reload) {
    $response = bpi_search_channels();
    if (!empty($response)) {
      $facets = $response->getFacets();
      $_SESSION[BPI_CHANNEL_ALL_FACETS_KEY] = bpi_facets_to_array($facets);
    }
    else {
      $_SESSION[BPI_CHANNEL_ALL_FACETS_KEY] = NULL;
    }
  }

  return $_SESSION[BPI_CHANNEL_ALL_FACETS_KEY];
}
