<?php

/**
 * @file
 * Configuration of module.
 */

/**
 * Implements hook_form_FORM_ID_alter().
 */
function ting_subsearch_suggestions_form_opensearch_admin_settings_alter(&$form, &$form_state) {
  // KPI.
  $form['subsearch_settings']['#type'] = 'fieldset';
  $form['subsearch_settings']['#title'] = t('Ting Subsearch');
  $form['subsearch_settings']['#description'] = t('Feature modules allow additional searches to be made based on predefined conditions.');
  $form['subsearch_settings']['#tree'] = FALSE;

  $form['subsearch_settings']['kpi_settings'] = [
    '#type' => 'fieldset',
    '#title' => t('KPI settings'),
    '#weight' => 1,
  ];

  $form['subsearch_settings']['kpi_settings']['trigger'] = [
    '#type' => 'fieldset',
    '#title' => t('Trigger'),
  ];

  $form['subsearch_settings']['kpi_settings']['trigger']['ting_subsearch_kpi_distance'] = [
    '#type' => 'textfield',
    '#title' => t('Levenshtein distance'),
    '#default_value' => variable_get('ting_subsearch_kpi_distance', 3),
    '#description' => t('Enter the maximum Levenshtein Distance here, ie. the maximum number of characters to replace, insert or delete to transform the input string into a string from the KPI data. A higher numbere allows for less similar words to be suggested.'),
    '#element_validate' => ['ting_subsearch_common_sensitive_fields_validate'],
  ];

  $form['subsearch_settings']['kpi_settings']['trigger']['ting_subsearch_kpi_trigger_limit'] = [
    '#type' => 'textfield',
    '#title' => t('Number of hits to trigger KPI subsearch'),
    '#default_value' => variable_get('ting_subsearch_kpi_trigger_limit', 5),
    '#description' => t('In order to trigger a subsearch which will provide a suggestion to the user, the user-provided search string must trigger at most this number of hits. NOTE: User-provided searches that trigger 0 hits always trigger a subsearch.'),
    '#element_validate' => ['ting_subsearch_common_sensitive_fields_validate'],
  ];

  $form['subsearch_settings']['kpi_settings']['trigger']['ting_subsearch_suggestions_ps_factor'] = [
    '#type' => 'textfield',
    '#title' => t('Ratio between primary and secondary searches for suggestions'),
    '#default_value' => variable_get('ting_subsearch_suggestions_ps_factor', 10),
    '#description' => t('Factor between amount of results from primary and secondary search for displaying suggestions.'),
    '#element_validate' => ['ting_subsearch_common_sensitive_fields_validate'],
  ];

  $form['subsearch_settings']['kpi_settings']['ting_subsearch_kpi_webservice_endpoint'] = [
    '#type' => 'textfield',
    '#title' => t('KPI Webtrekk On-Site Searches Web Service URL'),
    '#default_value' => variable_get('ting_subsearch_kpi_webservice_endpoint', ''),
    '#description' => t('The URL can be found in the DDB CMS manual.'),
  ];

  $week_numbers = range(1, 52);
  $form['subsearch_settings']['kpi_settings']['ting_subsearch_kpi_week_nrs'] = [
    '#type' => 'select',
    '#title' => t('Weeks count'),
    '#description' => t('Indicates how many weeks from local storage to use in suggestion process.'),
    '#options' => $week_numbers,
    '#default_value' => variable_get('ting_subsearch_kpi_week_nrs', 0),
  ];

  // Opensuggestions.
  $form['subsearch_settings']['#type'] = 'fieldset';
  $form['subsearch_settings']['#title'] = t('Ting subsearch settings');
  $form['subsearch_settings']['#tree'] = FALSE;

  $form['subsearch_settings']['os_settings'] = [
    '#type' => 'fieldset',
    '#title' => t('Open Suggestion settings'),
    '#states' => [
      'visible' => [
        'input[name=ting_subsearch_suggestions_service]' => ['value' => 'os'],
      ],
    ],
    '#access' => FALSE,
    '#weight' => 2,
  ];

  $form['subsearch_settings']['os_settings']['ting_subsearch_os_trigger_limit'] = [
    '#type' => 'textfield',
    '#title' => t('Number of hits to trigger Open Suggestion subsearch'),
    '#default_value' => variable_get('ting_subsearch_os_trigger_limit', 5),
    '#description' => t('In order to trigger a subsearch which will provide a suggestion to the user, the user-provided search string must trigger at most this number of hits. NOTE: User-provided searches that trigger 0 hits always trigger a subsearch.'),
  ];

  $form['subsearch_settings']['os_settings']['ting_subsearch_os_message_limit'] = [
    '#type' => 'textfield',
    '#title' => t('Number of subsearch hits to display message'),
    '#default_value' => variable_get('ting_subsearch_os_message_limit', 10),
    '#description' => t('Minimum number of hits on secondary search to display suggested search message. Given that the trigger above is hit.'),
  ];
  $form['subsearch_settings']['os_settings']['ting_subsearch_os_additional_url_params_0_hit'] = [
    '#type' => 'textfield',
    '#title' => t('Additional URL parameters for redirect link'),
    '#default_value' => variable_get('ting_subsearch_os_additional_url_params_0_hit', ''),
    '#description' => t('Parameters goes like this param1=value1&amp;param2=value2. Do not assume that the first parameter is the first actual. The system will figure it out.'),
  ];

  $form['subsearch_settings']['os_settings']['ting_subsearch_os_additional_url_params_inlimit'] = [
    '#type' => 'textfield',
    '#title' => t('Additional URL parameters for link in message'),
    '#default_value' => variable_get('ting_subsearch_os_additional_url_params_inlimit', ''),
    '#description' => t('Parameters goes like this param1=value1&amp;param2=value2. Do not assume that the first parameter is the first actual. The system will figure it out.'),
  ];

  // Reordering fieldsets.
  $form['subsearch_settings']['secondary_settings']['#weight'] = 3;
  $form['subsearch_settings']['subsearch_translate']['#weight'] = 4;
}

/**
 * Form builder for search feed status/import page.
 */
function ting_subsearch_suggestions_import_form($form, &$form_state) {
  // Show a status area with basic statistics from feed index.
  $form['status'] = [
    '#type' => 'fieldset',
    '#title' => t('Index status'),
  ];

  // Try to get everything we need in one go.
  $query = db_select('ting_subsearch_kpi_index_popular_keys', 'tsk')
    ->fields('tsk', ['year']);
  $query->addExpression('count(id)', 'count');
  $query->addExpression('max(weekno)', 'max_weekno');
  $query->addExpression('min(weekno)', 'min_weekno');
  $query->groupBy('tsk.year');
  $query->orderBy('tsk.year', 'ASC');
  $results = $query->execute();

  $rows_total_database = 0;
  $items = [];
  $oldest_week = '';
  $newest_week = '';
  foreach ($results as $record) {
    $count = $record->count;
    $year = $record->year;

    $count_formatted = number_format($count, 0, ',', '.');
    $items[] = '<strong>' . $year . '</strong>: ' . $count_formatted;

    $rows_total_database += $count;

    // If first iteration; set oldest week.
    if (empty($oldest_week)) {
      $oldest_week = $year . ', ' . $record->min_weekno;
    }
    // Set the newest week. The last set will be newest.
    $newest_week = $year . ', ' . $record->max_weekno;
  }

  if (!empty($items)) {
    $form['status']['rows_total_database'] = [
      '#type' => 'item',
      '#title' => t('Total number of rows:'),
      '#markup' => number_format($rows_total_database, 0, ',', '.'),
    ];

    $form['status']['year_count'] = [
      '#type' => 'item',
      '#title' => t('Year count'),
      '#markup' => theme('item_list', ['items' => $items, 'type' => 'ul']),
    ];

    $form['status']['oldest_week'] = [
      '#markup' => t('<strong>Oldest week:</strong> !week', [
        '!week' => $oldest_week,
      ]),
      '#suffix' => '<br>',
    ];
    $form['status']['newest_week'] = [
      '#markup' => t('<strong>Newest week:</strong> !week', [
        '!week' => $newest_week,
      ]),
    ];
  }
  else {
    $form['status']['total_rows'] = [
      '#type' => 'item',
      '#title' => t('No feed data in database'),
    ];
  }

  // CSV-file status and download.
  $form['csv'] = [
    '#type' => 'fieldset',
    '#title' => t('CSV'),
  ];

  $path = drupal_realpath("public://subsearch_kpi/temp_file.csv");

  if (file_exists($path)) {
    $file = new SplFileObject($path);
    // Ensure we get to the end of file.
    $file->seek(PHP_INT_MAX);
    // We do not have to subtract one to account for header since $file->key()
    // starts at 0.
    $rows_total_csv = $file->key();

    $form['csv']['download_time'] = [
      '#type' => 'item',
      '#title' => t('Download time'),
      '#markup' => format_date($file->getCTime(), 'short'),
    ];

    $file_size = $file->getSize() / 1024 / 1024;

    $form['csv']['size'] = [
      '#type' => 'item',
      '#title' => t('File size'),
      '#markup' => number_format($file_size, 0, ',', '.') . ' MB',
    ];

    $form['csv']['rows_total_csv'] = [
      '#type' => 'item',
      '#title' => t('Number of rows (excluding header)'),
      '#markup' => number_format($rows_total_csv, 0, ',', '.'),
    ];

    $form['csv']['update'] = [
      '#type' => 'submit',
      '#value' => t('Update search feed CSV'),
      '#submit' => ['ting_subsearch_suggestions_download_csv_submit'],
      '#suffix' => t('This may take a while. Be Patient! :)'),
    ];
  }
  else {
    $form['csv']['status'] = [
      '#type' => 'item',
      '#title' => t('No CSV file found'),
    ];
    $form['csv']['download'] = [
      '#type' => 'submit',
      '#value' => t('Download search feed CSV'),
      '#submit' => ['ting_subsearch_suggestions_download_csv_submit'],
      '#suffix' => t('This may take a while. Be Patient! :)'),
    ];
  }

  // CSV-file import.
  $form['import'] = [
    '#type' => 'submit',
    '#value' => t('Import CSV'),
    '#submit' => ['ting_subsearch_suggestions_import_csv_submit'],
  ];

  // CSV-file import.
  $form['reset'] = [
    '#type' => 'submit',
    '#value' => t('Reset index'),
    '#submit' => ['ting_subsearch_suggestions_reset_index_submit'],
  ];

  return $form;
}

/**
 * Submit handler for download CSV.
 */
function ting_subsearch_suggestions_download_csv_submit($form, &$form_state) {
  $url = variable_get('ting_subsearch_kpi_webservice_endpoint', '');

  if (empty($url)) {
    drupal_set_message(t('KPI webservice endpoint not configured'));
    return;
  }

  $temp_files_folder = 'public://subsearch_kpi/';
  if (!is_dir($temp_files_folder)) {
    file_prepare_directory($temp_files_folder, FILE_CREATE_DIRECTORY);
  }

  $path_to_file = drupal_realpath("public://subsearch_kpi/temp_file.csv");
  if (copyfile_chunked($url, $path_to_file)) {
    drupal_set_message(t('CSV file downloaded successfully from KPI webservice'));
  }
  else {
    drupal_set_message(t('There was a problem downloading CSV file from KPI webservice'));
  }
}

/**
 * Submit handler for import CSV.
 */
function ting_subsearch_suggestions_import_csv_submit($form, &$form_state) {
  $path = drupal_realpath("public://subsearch_kpi/temp_file.csv");

  if (!file_exists($path)) {
    drupal_set_message('CSV file missing. Click "Download search feed CSV" to proceed');
    return;
  }

  // Analyze the file with SplFileObject to get total number of rows. This
  // should be really fast:
  // https://stackoverflow.com/a/13060695.
  $file = new SplFileObject($path);
  // Ensure we get to the end of file.
  $file->seek(PHP_INT_MAX);
  // We do not have to subtract one to account for header since $file->key()
  // starts at 0.
  $rows_total = $file->key();

  if (!$rows_total) {
    drupal_set_message('CSV file has no data. Try to Download the search feed CSV again');
    return;
  }

  $batch = [
    'operations' => [
      ['ting_subsearch_suggestions_import_csv_batch', [$rows_total]],
    ],
    'finished' => 'ting_subsearch_suggestions_import_csv_batch_finished',
    'title' => t('Search feed CSV import'),
    'init_message' => t('Starting CSV import...'),
    'progress_message' => t('Importing search feed CSV...'),
    'error_message' => t('CSV import failed. Check error message and logs.'),
  ];

  batch_set($batch);
}

/**
 * Import search feed CSV batch operation callback.
 */
function ting_subsearch_suggestions_import_csv_batch($rows_total, &$context) {
  // Initialize if first run.
  if (empty($context['sandbox'])) {
    $max_year = db_query("SELECT MAX(year) FROM {ting_subsearch_kpi_index_popular_keys}")->fetchField();
    $max_week = FALSE;
    if ($max_year) {
      $max_week = db_query("SELECT MAX(weekno) FROM {ting_subsearch_kpi_index_popular_keys} WHERE year = {$max_year}")->fetchField();
    }

    // If there's existing data we need to avoid making duplicates.
    $existing_data = $max_year && $max_week;

    $context['sandbox']['max_year'] = $max_year;
    $context['sandbox']['max_week'] = $max_week;
    $context['sandbox']['existing_data'] = $existing_data;
    $context['results']['rows_inspected'] = 0;
    $context['results']['rows_inserted'] = 0;
  }

  $path = drupal_realpath("public://subsearch_kpi/temp_file.csv");
  $file = new SplFileObject($path);
  $file->setFlags(SplFileObject::SKIP_EMPTY | SplFileObject::DROP_NEW_LINE);

  $max_year = $context['sandbox']['max_year'];
  $max_week = $context['sandbox']['max_week'];
  $existing_data = $context['sandbox']['existing_data'];
  $rows_inspected = $context['results']['rows_inspected'];
  $rows_inserted = $context['results']['rows_inserted'];

  // This will also skip header on first run.
  $file->seek($rows_inspected + 1);

  // Rows inspected for the current batch.
  $rows_inspected_bacth = 0;

  // Use a multi insert which will greatly improve performance in MYSQL.
  // The number of records we can insert in one multi db_insert call depends on
  // the value of max_allowed_packet. With the default value of 16m we should be
  // able to make insert queries that insert up 10.000 rows without any issues.
  $value_count = 0;
  $fields = [ 'popular_keys', 'numtotalsearches', 'weekno', 'year' ];
  $query = db_insert('ting_subsearch_kpi_index_popular_keys')->fields($fields);

  while ($rows_inspected_bacth < TING_SUBSEARCH_SUGGESTIONS_IMPORT_BATCH_SIZE && !$file->eof()) {
    $data = $file->fgetcsv();

    if (isset($data[0]) && isset($data[1]) && isset($data[2]) && isset($data[4])) {
      $popular_keys = mb_convert_encoding($data[2], 'UTF-8', 'ISO-8859-15');
      $year = $data[0];
      $weekno = $data[1];
      $numtotalsearches = (int) $data[3];

      // If there's no existing data we add everything. Otherwise we make the
      // reasonable assumption that only new data will be added to the CSV-file
      // and use that to avoid duplicate data, neglecting all data that is older
      // than the current $max_year, $max_week in DB.
      if (!$existing_data || (($year == $max_year && $weekno > $max_week) || $year > $max_year)) {
        $query->values([
          'popular_keys' => $popular_keys,
          'numtotalsearches' => $numtotalsearches,
          'weekno' => $weekno,
          'year' => $year,
        ]);

        ++$value_count;
      }
    }

    // Limit reached. Execute multi insert and reset.
    if ($value_count == TING_SUBSEARCH_SUGGESTIONS_MULTI_INSERT_LIMIT) {
      $query->execute();
      $rows_inserted += $value_count;
      $value_count = 0;
      $query = db_insert('ting_subsearch_kpi_index_popular_keys')->fields($fields);
    }

    ++$rows_inspected_bacth;
  }
  // Execute remaining inserts if any.
  if ($value_count > 0) {
    $query->execute();
    $rows_inserted += $value_count;
  }

  $rows_inspected += $rows_inspected_bacth;

  $context['message'] = t('!rows_inspected/!rows_total rows inspected, !rows_inserted rows inserted', [
    '!rows_inspected' => number_format($rows_inspected, 0, ',', '.'),
    '!rows_total' => number_format($rows_total, 0, ',', '.'),
    '!rows_inserted' => number_format($rows_inserted, 0, ',', '.'),
  ]);

  // Carry progress to next batch.
  $context['results']['rows_inspected'] = $rows_inspected;
  $context['results']['rows_inserted'] = $rows_inserted;

  // In case of empty rows we could hit EOF before rows_total. So check both.
  if ($rows_inspected < $rows_total && !$file->eof()) {
    $context['finished'] = $rows_inspected / $rows_total;
  }
  else {
    // We're finished. Update results with number of skipped rows.
    $rows_skipped = $rows_total - $rows_inspected;
    $context['results']['rows_skipped'] = $rows_skipped;
  }
}

/**
 * Import search feed CSV batch finished callback.
 */
function ting_subsearch_suggestions_import_csv_batch_finished($success, $results, $operations) {
  if ($success) {
    $message = '<p>' . t('Search feed CSV import completed successfully') . '</p>';
    $args = [
      '!rows_inspected' => number_format($results['rows_inspected'] , 0, ',', '.'),
      '!rows_inserted' => number_format($results['rows_inserted'] , 0, ',', '.'),
      '!rows_skipped' => number_format($results['rows_skipped'] , 0, ',', '.'),
    ];
    $message .= '<p>' . t('Inspected: !rows_inspected, Inserted: !rows_inserted, Skipped: !rows_skipped', $args) . '</p>';
    drupal_set_message($message);
  }
  else {
    drupal_set_message(t('An error occured while imported search feed CSV. Check logs.'));
  }
}

/**
 * Submit handler for reset index.
 */
function ting_subsearch_suggestions_reset_index_submit($form, &$form_state) {
  $form_state['redirect'] = 'admin/config/ting/subsearch-suggestions/import/confirm-reset';
}

/**
 * Reset index confirm form.
 */
function ting_subsearch_suggestions_reset_index_confirm_form($form, &$form_state) {
  return confirm_form($form,
    t('Are you sure you want to reset the search feed index?'),
    'admin/config/ting/subsearch-suggestions/import',
    t('This will remove all imported search feed data from the database, and it will have to be reimported again for the module to work correctly.'),
    t('Confirm'),
    t('Cancel')
  );
}

/**
 * Reset index confirm form submit.
 */
function ting_subsearch_suggestions_reset_index_confirm_form_submit($form, &$form_state) {
  if ($form_state['values']['confirm'])  {
    db_truncate('ting_subsearch_kpi_index_popular_keys')->execute();
    drupal_set_message(t('Search feed index reset'));
  }
  $form_state['redirect'] = 'admin/config/ting/subsearch-suggestions/import';
}
