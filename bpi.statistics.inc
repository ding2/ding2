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
 *
 * @return array
 *   Set of ajax commands if request is ajax, renderable form array otherwise.
 */
function bpi_statistics($type) {
  $ajax = ($type == 'ajax') ? TRUE : FALSE;

  if ($ajax) {
    $commands = array();
    $form = drupal_get_form('bpi_statistics_form');

    $commands[] = ajax_command_ding_popup(
      'bpi-stats',
      t('BPI statistics'),
      drupal_render($form)
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
 *
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

  try {
    $bpi = bpi_client_instance();
    $bpi_stats_data = $bpi->getStatistics($form_formatted, $to_formatted)->getProperties();
    $bpi_stats_markup = bpi_statistics_markup($bpi_stats_data);

  }
  catch (Exception $e) {
    drupal_set_message(t('Failed to fetch statistics. Check reports for more information.'), 'error');
  }

  $form['bpi_stats_results'] = array(
    '#type' => 'item',
    '#markup' => isset($bpi_stats_markup) ? $bpi_stats_markup : '',
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

  $form['#attached']['css'][] = drupal_get_path('module', 'bpi') . '/css/bpi-admin.styles.css';
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
 * Build statistics markup.
 *
 * @param array $items
 *   Statistic properties, in structure:
 *   - prop name: prop value
 *
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
