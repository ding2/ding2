<?php
/**
 * @file
 * Template opening hours.
 */

/**
 * Implements hook_preprocess_opening_hours_week().
 */
function ddbasic_preprocess_opening_hours_week(&$variables) {
  $timespan = array(
    strtotime('last monday', strtotime('+1 day')),
    strtotime('next sunday', strtotime('-1 day')),
  );
  $today = strtotime('today');
  $structured = array();
  $categories = array();

  if (isset($GLOBALS['ddbasic_opening_hours_week_timespan'])) {
    $timespan = $GLOBALS['ddbasic_opening_hours_week_timespan'];
  }

  // Get and sort all the instances in the given timespan.
  $instances = opening_hours_instance_load_multiple(
    array($variables['node']->nid),
    date('Y-m-d', $timespan[0]),
    date('Y-m-d', $timespan[1])
  );

  // Add closed days.
  for ($day = $timespan[0]; $day <= $timespan[1]; $day += 86400) {
    $date = date('Y-m-d', $day);
    $closed = TRUE;
    foreach ($instances as $instance) {
      if ($instance->date == $date) {
        $closed = FALSE;
      }
    }

    if ($closed === TRUE) {
      $instances[] = (object) array(
        'instance_id' => -1,
        'nid' => $variables['node']->nid,
        'start_time' => '0',
        'end_time' => '0',
        'category_tid' => NULL,
        'date' => $date,
        'closed' => TRUE,
        'notice' => t('Closed'),
      );
    }
  }

  usort($instances, 'ding_ddbasic_opening_hours_sort');

  // Insert the instances into the structured array.
  foreach ($instances as $instance) {
    $category_weight = ding_ddbasic_opening_hours_get_category_weight($instance->category_tid);
    $time = strtotime($instance->date);
    $day = format_date($time, 'custom', 'l');

    if (!isset($structured[$day])) {
      $structured[$day] = array(
        'cols' => array(),
        'extra' => array(),
      );

      if ($time == $today) {
        $structured[$day]['extra']['class'] = array('today');
      }
    }

    if (!empty($instance->notice)) {
      $notice = '<span class="notice">' . $instance->notice . '</span>';
    }
    else {
      $notice = '';
    }

    if (empty($instance->closed)) {
      $structured[$day]['cols'][$category_weight] = t('@from - @to', array(
        '@from' => $instance->start_time,
        '@to' => $instance->end_time,
      )) . $notice;
    }
    else {
      $structured[$day]['cols'][$category_weight] = $notice;
    }

    if (!isset($categories[$category_weight])) {
      $categories[$category_weight] = ding_ddbasic_opening_hours_get_category_name($instance->category_tid);
    }
  }

  // Sort the categories by key (weight).
  ksort($categories);

  $variables['table'] = ding_ddbasic_opening_hours_table(
    // TODO Use preset date types from admin/config/regional/date-time instead
    // of the custom format, so it can be customized in the interface.
    t('Week @week, @from - @to', array(
      '@week' => format_date($timespan[0], 'custom', 'W'),
      '@from' => format_date($timespan[0], 'custom', 'd.m'),
      '@to' => format_date($timespan[1], 'custom', 'd.m'),
    )),
    $categories,
    $structured
  );

  drupal_add_library('system', 'drupal.ajax');
  $variables['table']['#suffix'] = l(
    t('Next'),
    'ding-ddbasic/opening-hours/week/' . $variables['node']->nid
    . '/' . strtotime('next monday', $timespan[1])
    . '/' . strtotime('next sunday', $timespan[1]),
    array(
      'attributes' => array('class' => array('use-ajax', 'button-next')),
    )
  ) . l(
    t('Previous'),
    'ding-ddbasic/opening-hours/week/' . $variables['node']->nid
    . '/' . strtotime('last monday', $timespan[0])
    . '/' . strtotime('last sunday', $timespan[0]),
    array(
      'attributes' => array('class' => array('use-ajax', 'button-previous')),
    )
  );

  $variables['classes_array'][] = 'opening-hours-week-' . $variables['node']->nid;
}
