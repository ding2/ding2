<?php
/**
 * @file
 * BPI statistics related logic here.
 */

/**
 * Entry point for the statistics page.
 *
 * @param string $type
 *   Request type, whether it's ajax or not.
 * @return array
 *   Set of ajax commands if request is ajax, renderable form array otherwise.
 */
function bpi_statistics($type) {
  $ajax = ($type == 'ajax') ? TRUE : FALSE;

  if ($ajax) {
    $commands = array();

    $commands[] = ajax_command_ding_popup(
      'bpi-stats',
      t('BPI statistics'),
      drupal_render(drupal_get_form('bpi_statistics_form'))
    );

    return array('#type' => 'ajax', '#commands' => $commands);
  }
  else {
    return drupal_get_form('bpi_statistics_form');
  }
}

/**
 * Statistics form with timespan filtering.
 *
 * @param array $form
 *   Form structure.
 * @param array $form_state
 *   Form state values.
 * @return array
 *   Form structure.
 *
 * @ingroup forms
 */
function bpi_statistics_form($form, &$form_state) {
  $now = time();
  $from = isset($form_state['input']['bpi_stats_start_date']['date'])
    ? $form_state['input']['bpi_stats_start_date']['date']
    : date(BPI_DATE_PICKER_FORMAT, $now - BPI_ONE_MONTH);
  $to = isset($form_state['input']['bpi_stats_end_date']['date'])
    ? $form_state['input']['bpi_stats_end_date']['date']
    : date(BPI_DATE_PICKER_FORMAT, $now);

  $form_formatted = $from;
  $to_formatted = $to;

  $form['bpi_stats_start_date'] = array(
    '#title' => t('From:'),
    '#type' => 'date_popup',
    '#date_format' => BPI_DATE_PICKER_FORMAT,
    '#default_value' => $from,
  );

  $form['bpi_stats_end_date'] = array(
    '#title' => t('To:'),
    '#type' => 'date_popup',
    '#date_format' => BPI_DATE_PICKER_FORMAT,
    '#default_value' => $to,
  );

  $bpi_stats_data = bpi_statistics_data($form_formatted, $to_formatted);
  $bpi_stats_markup = bpi_statistics_markup($bpi_stats_data);

  $form['bpi_stats_results'] = array(
    '#type' => 'item',
    '#markup' => $bpi_stats_markup,
    '#prefix' => '<div id="bpi-statistics-results">',
    '#suffix' => '</div>',
  );

  $form['bpi_stats_filter_submit'] = array(
    '#type' => 'button',
    '#value' => t('Filter'),
    '#ajax' => array(
      'callback' => '_bpi_statistics_ajax_callback',
      'wrapper' => 'bpi-statistics-results',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  $form['#attached']['css'][] = drupal_get_path('module', 'bpi') . '/css/bpi-statistics.styles.css';
  $form['#prefix'] = '<div class="bpi-stats-form">';
  $form['#suffix'] = '</div>';

  return $form;
}

/**
 * Custom AJAX callback for the statistic results.
 *
 * Just update the statistics element.
 *
 * @see bpi_statistics_form()
 * @ingroup forms
 */
function _bpi_statistics_ajax_callback(&$form, &$form_state) {
  return $form['bpi_stats_results'];
}

/**
 * @todo
 * Dummy stuff
 * @param string $from
 *   Start date, in Y-m-d format.
 * @param string $to
 *   End date, in Y-m-d format.
 * @return array
 *   Array of keys and values with various information.
 *   Keys denote the type of stat, and value - stat value.
 */
function bpi_statistics_data($from = '', $to = '') {
  $stats = array();
  $endpoint = variable_get('bpi_service_url', '');
  $agency_id = variable_get('bpi_agency_id', '');
  $api_key = variable_get('bpi_api_key', '');
  $secret_key = variable_get('bpi_secret_key', '');

  try {
    $bpi = new Bpi($endpoint, $agency_id, $api_key, $secret_key);
    $stats = $bpi->getStatistics($from, $to)->getProperties();
  }
  catch (Exception $e) {
    // TODO Please use watchdog_exception here.
    watchdog(
      'bpi',
      t('Failed to fetch statistics, with message %message.'),
      array(
        '%message' => $e->getMessage()
      ),
      WATCHDOG_ERROR
    );
    // TODO How about notifying the user?
  }

  return $stats;
}

/**
 * Build statistics markup.
 *
 * @param array $items
 *   Statistic properties, in structure:
 *   - prop name: prop value
 * @return string
 *   HTML markup.
 */
function bpi_statistics_markup($items) {
  $rows = array();

  if (is_array($items)) {
    foreach ($items as $prop => $value) {
      $rows[] = '<p class="bpi-stats-stat">' . t('Total @prop: %value', array('@prop' => $prop, '%value' => $value)) . '</p>';
    }
  }

  return implode('', $rows);
}
