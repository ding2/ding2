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

    $commands[] = ajax_command_alert('Stub guys!');

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
function bpi_statistics_form($form, $form_state) {
  $form['bpi_stats_start_date'] = array(
    '#title' => t('From:'),
    '#type' => 'date_popup',
  );

  $form['bpi_stats_end_date'] = array(
    '#title' => t('To:'),
    '#type' => 'date_popup',
  );

  $form['bpi_stats_results'] = array(
    '#type' => 'item',
    '#markup' => '<h2>DUMMY RESULTS</h2>',
  );

  $form['bpi_stats_filter_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Filter'),
  );

  $form['#attached']['css'][] = drupal_get_path('module', 'bpi') . '/css/statistics.styles.css';
  $form['#prefix'] = '<div class="bpi-stats-form">';
  $form['#suffix'] = '</div>';

  return $form;
}

/**
 * Submit handler for bpi_statistics_form.
 *
 * @see bpi_statistics_form()
 *
 * @param array $form
 *   Form structure.
 * @param array $form_state
 *   Form state values.
 *
 * @ingroup forms
 */
function bpi_statistics_form_submit(&$form, &$form_state) {

}
