<?php
/**
 * @file
 * Handling of BPI users.
 */

use Bpi\Sdk\Item\User;

// This is needed to store User objects in session (see bpi_get_user())
require_once __DIR__ . '/lib/bpi-client/Bpi/Sdk/Item/User.php';
require_once __DIR__ . '/lib/bpi-client/Bpi/Sdk/Item/Agency.php';
require_once __DIR__ . '/lib/bpi-client/Bpi/Sdk/Item/Subscription.php';

// We want to reuse some helper functions.
require_once __DIR__ . '/bpi.syndicate.inc';
require_once __DIR__ . '/bpi.channel.inc';

/**
 * Key for storing user facets in session.
 */
define('BPI_USER_ALL_FACETS_KEY', 'BPI_USER_ALL_FACETS');

/**
 * Render a list of users.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 *
 * @return array
 *   The form.
 */
function bpi_user_list_form(array $form, array &$form_state) {
  if (bpi_service_is_configured()) {
    bpi_check_bpi_user();

    drupal_add_library('system', 'drupal.ajax');

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
      '#description' => t('Search in name and email'),
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

    $items = bpi_user_search_get_items();
    bpi_user_build_search_facets($query_form);

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

    $result_form['bpi_search_results'] = array_merge(bpi_build_user_table($items), array(
      '#empty' => t('No users found'),
    ));
    $result_form['bpi_search_results']['#prefix'] = '<div class="bpi-search-result bpi-user-list">';
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
          'bpi-actions',
        ),
      ),
    );

    $form['bpi_query'] = $query_form;
    $form['bpi_result'] = $result_form;

    $form['bpi_actions_bottom'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array(
          'bpi-actions',
          drupal_html_class('container-inline'),
        ),
      ),
    );

    $bpi = bpi_client_instance();
    $options = array('' => '');
    try {
      $channels = $bpi->getChannelsByUser(bpi_get_current_bpi_user_id());
      if ($channels) {
        foreach ($channels as $channel) {
          if (bpi_can_edit_channel($channel)) {
            $options[$channel->getId()] = $channel->getName();
          }
        }
      }
    }
    catch (\Exception $e) {
    }
    if (count($options) > 1) {
      $form['bpi_actions_bottom']['channel'] = array(
        '#type' => 'select',
        '#title' => t('Channel'),
        '#options' => $options,
        '#default_value' => isset($_GET['add-to-channel']) ? $_GET['add-to-channel'] : '',
      );

      $form['bpi_actions_bottom']['add_editors_to_channel_submit'] = array(
        '#type' => 'submit',
        '#value' => t('Add selected editors to channel'),
        '#submit' => array('bpi_user_list_form_add_editors_to_channel_submit'),
        '#validate' => array('bpi_user_list_form_add_editors_to_channel_validate'),
      );
    }

    $form['#attributes']['class'][] = 'bpi';
    $form['#attached']['css'][] = drupal_get_path('module', 'bpi') . '/css/bpi-admin.styles.css';
    $form['#attached']['js'][] = drupal_get_path('module', 'bpi') . '/js/bpi-admin.js';
    $form['#submit'][] = 'bpi_user_list_form_submit';
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
function bpi_user_list_form_submit(array $form, array &$form_state) {
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
  drupal_goto('admin/bpi/user', array('query' => _bpi_build_query($bpi_query, TRUE)));
}

/**
 * Build facets form fields.
 *
 * @param array $form
 *   The form.
 */
function bpi_user_build_search_facets(array &$form) {
  $facets = bpi_user_get_facets();

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
function bpi_user_get_facets() {
  // Reload facets if they're not cached locally.
  $reload = !isset($_SESSION[BPI_USER_ALL_FACETS_KEY]) || !is_array($_SESSION[BPI_USER_ALL_FACETS_KEY]);
  if (!$reload) {
    // Reload if neither text nor filter is applied.
    $reload = !(_bpi_get_current_search_phrase() || _bpi_get_current_filter());
  }

  if ($reload) {
    $response = bpi_search_users();
    if (!empty($response)) {
      $facets = $response->getFacets();
      $_SESSION[BPI_USER_ALL_FACETS_KEY] = bpi_facets_to_array($facets);
    }
    else {
      $_SESSION[BPI_USER_ALL_FACETS_KEY] = NULL;
    }
  }

  return $_SESSION[BPI_USER_ALL_FACETS_KEY];
}

/**
 * Render user details.
 *
 * @param string $user_id
 *   The user id.
 *
 * @return string
 *   The rendered view.
 */
function bpi_user_view($user_id) {
  $user = bpi_get_user($user_id);

  if (!$user) {
    return '';
  }

  $items = bpi_get_channels_by_user($user->getId());

  // Channel (un)subscribe form.
  $form = drupal_get_form('bpi_channel_subscription_form');
  $content = render($form);
  // Actual view content.
  $content .= theme('bpi_user_view', array(
    'user' => $user,
    'channels' => $items,
  ));

  return $content;
}

/**
 * Validation handler for bpi_user_list_form_add_editors_to_channel_validate.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 */
function bpi_user_list_form_add_editors_to_channel_validate(array $form, array &$form_state) {
  $values = $form_state['values'];
  $channel_id = $values['channel'];
  $editor_ids = array_filter($values['bpi_search_results']);

  if (!$channel_id) {
    form_set_error('channel', t('Please select a channel'));
  }
  if (!$editor_ids) {
    form_set_error('bpi_search_results', t('Please select one or more users'));
  }
}

/**
 * Submit handler for bpi_user_list_form_add_editors_to_channel.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 */
function bpi_user_list_form_add_editors_to_channel_submit(array $form, array &$form_state) {
  $values = $form_state['values'];
  $channel_id = $values['channel'];
  $editor_ids = array_filter($values['bpi_search_results']);

  $bpi = bpi_client_instance();
  $success = $bpi->addEditorToChannel($channel_id, bpi_get_current_bpi_user_id(), $editor_ids);

  if ($success) {
    drupal_set_message(t('Editors added to channel'));
  }

  drupal_goto('admin/bpi/channel/' . $channel_id);
}

/**
 * Search users in BPI web service.
 *
 * @return array
 *   A list of users.
 */
function bpi_user_search_get_items() {
  $page = pager_find_page();
  $phrase = _bpi_get_current_search_phrase();
  $filters = _bpi_get_current_filter();
  $sort = _bpi_get_current_sorting();

  $response = bpi_search_users($phrase, $page, $filters, $sort);

  return $response;
}

/**
 * Search bpi users.
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
 *   The users matching the search query and filters.
 */
function bpi_search_users($query = '', $page = 1, $filters = array(), $sorting = array()) {
  try {
    $bpi = bpi_client_instance();
    $amount = max(intval(_bpi_get_query_parameter('amount')), BPI_DEFAULT_PAGE_SIZE);
    $offset = $page * $amount;

    $bpi_data = $bpi->searchUsers(
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
    drupal_set_message(t('Failed to fetch users. Check reports for more information.'), 'error');
  }

  return NULL;
}

/**
 * Build a tableselect element for selecting user.
 *
 * @param array $users
 *   The users.
 *
 * @return array
 *   The form element.
 */
function bpi_build_user_table($users) {
  $header = array(
    'name' => array(
      'data' => t('Name'),
      'class' => array('bpi-name'),
    ),
    'email' => array(
      'data' => t('E-mail'),
      'class' => array('bpi-email'),
    ),
    'agency' => array(
      'data' => t('Agency'),
      'class' => array('bpi-agency'),
    ),
  );

  $options = array();
  if ($users) {
    foreach ($users as $user) {
      $name = l($user->getName(), 'admin/bpi/user/' . $user->getId());
      $email = l($user->getEmail(), 'admin/bpi/user/' . $user->getId());
      $agency = $user->getAgency()->getName();

      $options[$user->getId()] = array(
        'name' => $name,
        'email' => $email,
        'agency' => $agency,
      );
    }
  }

  return array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#process' => array('form_process_tableselect', 'bpi_user_form_process_tableselect'),
  );
}

/**
 * Process user tableselect.
 */
function bpi_user_form_process_tableselect($element) {
  // Disable selection of current bpi user.
  $user_id = bpi_get_current_bpi_user_id();
  if (isset($element[$user_id])) {
    $element[$user_id]['#disabled'] = TRUE;
  }

  return $element;
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
function theme_bpi_user_list(array $variables) {
  return theme('table', $variables);
}

/**
 * Implements hook_preprocess_HOOK().
 */
function bpi_preprocess_bpi_user_list(array &$variables) {
  $items = $variables['items'];
  $channel = isset($variables['#channel']) ? $variables['#channel'] : NULL;

  $has_actions = FALSE;
  $rows = array();
  if (!empty($items)) {
    foreach ($items as $item) {
      $name = l($item->getName(), 'admin/bpi/user/' . $item->getId());
      $email = l($item->getEmail(), 'admin/bpi/user/' . $item->getId());
      $agency = $item->getAgency()->getName();
      $actions = array();
      if ($channel && bpi_can_edit_channel($channel)) {
        $actions[] = l(t('Remove editor from channel'), 'admin/bpi/channel/' . $channel->getID() . '/editor/remove/' . $item->getId());
        $has_actions = TRUE;
      }

      $row = array(
        'name' => $name,
        'email' => $email,
        'agency' => $agency,
      );
      if ($actions) {
        $row['actions'] = implode(' ', $actions);
      }
      $rows[] = $row;
    }
  }

  $table_head = array(
    'name' => array(
      'data' => bpi_get_sort_link(t('Name'), 'name'),
      'class' => array('bpi-name', _bpi_get_current_sorting('name') ? 'active' : ''),
    ),
    'email' => array(
      'data' => bpi_get_sort_link(t('E-mail'), 'email'),
      'class' => array('bpi-email', _bpi_get_current_sorting('email') ? 'active' : ''),
    ),
    'agency' => array(
      'data' => bpi_get_sort_link(t('Agency'), 'agency'),
      'class' => array('bpi-agency', _bpi_get_current_sorting('agency') ? 'active' : ''),
    ),
  );
  if ($has_actions) {
    $table_head['actions'] = t('Actions');
  }

  $variables['header'] = $table_head;
  $variables['sticky'] = TRUE;
  $variables['rows'] = $rows;

  // Unset old data.
  unset($variables['items']);
}

/**
 * Get a user by id.
 *
 * For performance reasons (i.e. not hitting the web service too much) we cache
 * the user in the session.
 *
 * @param string $id
 *   The user id.
 *
 * @return \Bpi\Sdk\Item\User|null
 *   The user if found.
 */
function bpi_get_user($id = NULL) {
  $is_current_user = FALSE;
  if ($id === NULL) {
    $id = bpi_get_current_bpi_user_id();
    $is_current_user = TRUE;
  }
  try {
    if ($is_current_user && isset($_SESSION['BPI_CURRENT_USER'])) {
      $user = $_SESSION['BPI_CURRENT_USER'];
      if ($user instanceof User) {
        return $user;
      }
    }

    $bpi = bpi_client_instance();
    $user = $bpi->getUser($id);

    if ($is_current_user) {
      $_SESSION['BPI_CURRENT_USER'] = $user;
    }

    return $user;
  }
  catch (\Exception $e) {
    watchdog_exception('bpi', $e);
  }

  return NULL;
}

/**
 * Remove current user from cache.
 */
function bpi_flush_user() {
  unset($_SESSION['BPI_CURRENT_USER']);
}

/**
 * Get current Drupal user's BPI user id.
 *
 * @return string|null
 *   The bpi user id if any.
 */
function bpi_get_current_bpi_user_id() {
  global $user;

  return isset($user->data['bpi_user_id']) ? $user->data['bpi_user_id'] : NULL;
}

/**
 * Check if current Drupal user has a valid BPI user.
 *
 * A warning is displayed if no valid BPI user is found.
 */
function bpi_check_bpi_user() {
  global $user;

  if (empty(bpi_get_current_bpi_user_id()) || empty(bpi_get_user())) {
    drupal_set_message(t('Current user (!email) does not have a valid BPI user id', array('!email' => $user->mail)), 'warning');
  }
}
