<?php
/**
 * @file
 * Admin related functionality.
 */

/**
 * The admin settings form.
 */
function ting_openlist_settings_form($form, &$form_state) {
  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Openlist settings'),
  );

  $form['settings']['ting_openlist_wsdl'] = array(
    '#type' => 'textfield',
    '#title' => t('URI of the WSDL file'),
    '#description' => t("The client doesn't support non-WSDL mode, so this is required."),
    '#default_value' => variable_get('ting_openlist_wsdl', ''),
    '#required' => TRUE,
  );

  $form['settings']['ting_library_code'] = array(
    '#type' => 'textfield',
    '#title' => t('Library code'),
    '#description' => '',
    '#default_value' => variable_get('ting_library_code', ''),
    '#required' => TRUE,
  );

  $form['settings']['ting_openlist_prefix'] = array(
    '#type' => 'textfield',
    '#title' => t('Openlist prefix'),
    '#description' => t('The prefix used for creating a unique hashed user id.'),
    '#default_value' => variable_get('ting_openlist_prefix', uniqid()),
    '#disabled' => TRUE,
  );

  // Caching settings.
  $form['caching'] = array(
    '#type' => 'fieldset',
    '#title' => t('Openlist WSDL caching'),
    '#description' => t('These settings only affect the SoapClients created for openlist, and will not interfere with other SoapClients on your site.'),
  );

  $form['caching']['ting_openlist_wsdl_cache'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable WSDL caching'),
    '#description' => '',
    '#default_value' => variable_get('ting_openlist_wsdl_cache', TRUE),
  );

  // Debugging settings.
  $form['debugging'] = array(
    '#type' => 'fieldset',
    '#title' => t('Debugging settings'),
    '#description' => t('Do not enable these settings in a production environment.<br />Even without any debugging on, openlist will log actual errors'),
  );

  $form['debugging']['ting_openlist_log'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable logging'),
    '#description' => t('Log requests send to the openlist service.'),
    '#default_value' => variable_get('ting_openlist_log', FALSE),
  );

  // The detailed log will log the full argument list send to openlist.
  $form['debugging']['ting_openlist_log_details'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable detailed logging'),
    '#description' => t('If logging, this will log more details, but the log messages can get big and confusing.'),
    '#default_value' => variable_get('ting_openlist_log_details', FALSE),
  );

  $form['debugging']['ting_openlist_developer'] = array(
    '#type' => 'checkbox',
    '#title' => t('Developer'),
    '#description' => t('Send the developer cookie to the service.'),
    '#default_value' => variable_get('ting_openlist_developer', FALSE),
  );
  
  $form['debugging']['ting_openlist_no_wsdl_cache'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable WSDL caching'),
    '#description' => t('Only disable WSDL caching when testing experimental OpenList API'),
    '#default_value' => variable_get('ting_openlist_no_wsdl_cache', FALSE),
  );

  // Statistics.
  $form['stats'] = array(
    '#type' => 'fieldset',
    '#title' => t('Statistics'),
  );

  $form['stats']['show_stats'] = array(
    '#type' => 'button',
    '#value' => t('Fetch statistics'),
    '#ajax' => array(
      'wrapper' => 'show-stats-container',
      'callback' => 'ting_openlist_show_stats_form_callback',
    ),
    '#suffix' => '<div id="show-stats-container"></div>',
  );

  return system_settings_form($form);
}

/**
 * Callback for satistics.
 */
function ting_openlist_show_stats_form_callback($form, &$form_state) {
  $out = array();

  $query = db_select('users', 'u');
  $query->join('users_roles', 'ur', 'ur.uid = u.uid');
  $query->join('role', 'r', "r.rid = ur.rid AND r.name = 'provider'");

  $out[] = array(
    '#markup' => '<strong>' . t('Local patrons') . '</strong> ' . $query->countQuery()->execute()->fetchField(),
    '#prefix' => '<div>',
    '#suffix' => '</div>',
  );

  $query->condition('u.login', strtotime('-1 month'), '>');
  $out[] = array(
    '#markup' => '<strong>' . t('Active patrons last 30 days') . '</strong> ' . $query->countQuery()->execute()->fetchField(),
    '#prefix' => '<div>',
    '#suffix' => '</div>',
  );

  // Machine names to readable text.
  $m2r = array(
    'books_read' => t("Books I've read"),
    'follow' => t('Subjects I follow'),
    'follow_author' => t('Authors I follow'),
    'follow_user' => t('Users I follow'),
    'interests' => t('Interests'),
    'lists_list' => t('Lists I follow'),
    'ratings' => t('Ratings'),
    'remember' => t('Read later'),
    'user_list' => t('User lists'),
    'user_loan_history' => t('Loan history'),
    'user_searches' => t('Searches I follow'),
  );

  $table = array(
    '#caption' => t('Lists'),
    '#header' => array(
      t('List type'),
      t('Machine name'),
      t('List count'),
      t('Element count'),
    ),
    '#rows' => array(),
  );

  $stats = ding_provider_invoke('openlist', 'call_module', 'ListStats', 'lists');
  foreach ($stats as $list_type => $counts) {
    if (isset($m2r[$list_type])) {
      $table['#rows'][] = array(
        $m2r[$list_type],
        $list_type,
        $counts['lists'],
        $counts['elements'],
      );
    }
    else {
      $table['#rows'][] = array(
        'style' => 'opacity: 0.5',
        'data' => array(
          t('@list_type (unsupported)', array('@list_type' => $list_type)),
          $counts['lists'], $counts['elements'],
        ),
      );
    }
  }

  $out[] = array('#theme' => 'table') + $table;

  return '<div id="show-stats-container">' . render($out) . '</div>';
}
