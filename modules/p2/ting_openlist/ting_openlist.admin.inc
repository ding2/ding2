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

  $form['settings']['ting_openlist_domain'] = array(
    '#type' => 'textfield',
    '#title' => t('Openlist domain'),
    '#description' => t("The openlist URL."),
    '#default_value' => variable_get('ting_openlist_domain', TING_OPENLIST_DEFAULT_DOMAIN),
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
  );

  $form['settings']['ting_openlist_authkey'] = array(
    '#type' => 'textfield',
    '#title' => t('Openlist authkey'),
    '#description' => t('The key that authenticates this library code towards OpenList.'),
    '#default_value' => variable_get('ting_openlist_authkey', ''),
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

  $form['debugging']['ting_openlist_developer'] = array(
    '#type' => 'checkbox',
    '#title' => t('Developer'),
    '#description' => t('Send the developer cookie to the service.'),
    '#default_value' => variable_get('ting_openlist_developer', FALSE),
  );

  // Statistics.
  $form['stats'] = array(
    '#type' => 'fieldset',
    '#title' => t('Statistics and authentication test'),
    '#description' => t('You can check that your authkey, library code and IP is correct by fetching the OpenList statistics here.'),
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

  $form['analysis'] = array(
    '#type' => 'fieldset',
    '#title' => t('Analysis'),
    '#description' => t('Show or submit local statistics to OpenList for analysis.'),
  );

  $form['analysis']['show_local_analysis'] = array(
    '#type' => 'button',
    '#value' => t('Show local analysis'),
    '#ajax' => array(
      'wrapper' => 'show-local-analysis-container',
      'callback' => 'ting_openlist_show_local_analysis_form_callback',
    ),
    '#suffix' => '<div id="show-local-analysis-container"></div>',
  );

  $form['analysis']['submit_local_analysis'] = array(
    '#type' => 'button',
    '#value' => t('Submit local analysis'),
    '#ajax' => array(
      'wrapper' => 'submit-local-analysis-container',
      'callback' => 'ting_openlist_submit_local_analysis_form_callback',
    ),
    '#suffix' => '<div id="submit-local-analysis-container"></div>',
  );

  return system_settings_form($form);
}

/**
 * Callback for local statistics.
 */
function ting_openlist_show_local_analysis_form_callback($form, &$form_state) {
  module_load_include('inc', 'ting_openlist', 'include/ting_openlist_analysis');
  $data = ting_openlist_get_local_analysis_data();

  $out = array(
    '#type' => 'html_tag',
    '#tag' => 'div',
    '#attributes' => array('id' => 'show-local-analysis-container'),
    '#value' => '<pre>' . htmlentities(var_export($data, TRUE)) . '</pre>',
  );

  return render($out);
}

/**
 * Callback for submission of local statistics.
 */
function ting_openlist_submit_local_analysis_form_callback($form, &$form_state) {
  module_load_include('inc', 'ting_openlist', 'include/ting_openlist_analysis');

  $result = ding_provider_invoke('openlist', 'call_module', 'LocalAnalysis', 'sendData', array(ting_openlist_get_local_analysis_data()));

  $out = array(
    '#type' => 'html_tag',
    '#tag' => 'div',
    '#attributes' => array('id' => 'show-local-analysis-container'),
    '#value' => $result ? t('Stats are sent') : t('Unknown error try again later'),
  );

  return render($out);
}

/**
 * Callback for statistics.
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
