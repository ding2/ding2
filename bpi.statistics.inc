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
  $form['bpi_stats_start_date'] = array(
    '#title' => t('From:'),
    '#type' => 'date_popup',
  );

  $form['bpi_stats_end_date'] = array(
    '#title' => t('To:'),
    '#type' => 'date_popup',
  );

  $bpi_stats_timespan = isset($form_state['bpi']['stats']) ? $form_state['bpi']['stats'] : array('from' => '', 'to' => '');
  $bpi_stats_data = bpi_statistics_data($bpi_stats_timespan);
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
    )
  );

  $form['#attached']['css'][] = drupal_get_path('module', 'bpi') . '/css/statistics.styles.css';
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
 * @param type $from
 * @param type $to
 * @return type
 */
function bpi_statistics_data($from = '', $to = '') {
  return array(
    'pushed' => mt_rand(1, 99),
    'syndicated' => mt_rand(1, 99),
  );
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
