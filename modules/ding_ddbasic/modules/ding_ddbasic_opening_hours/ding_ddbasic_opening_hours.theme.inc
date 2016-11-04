<?php
/**
 * @file
 * Ding DDBasic opening hours themes.
 */

/**
 * A single library.
 */
function theme_ding_ddbasic_opening_hours_week($variables) {
  $classes = implode(' ', $variables['classes_array']);
  return '<div class="' . $classes . '">' . render($variables['table']) . '</div>';
}

/**
 * Preprocessor for ding_ddbasic_opening_hours_week.
 */
function template_preprocess_ding_ddbasic_opening_hours_week(&$variables) {
  $timespan = array(
    strtotime('last monday', strtotime('+1 day')),
    strtotime('next sunday', strtotime('-1 day')),
  );
  $today = strtotime('today');
  $structured = array();
  $categories = array();

  if (!empty($variables['timespan'])) {
    $timespan = $variables['timespan'];
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

  // Add true NULL to the categories.
  if (in_array('_null', $variables['categories'])) {
    $variables['categories'][NULL] = NULL;
  }

  // Insert the instances into the structured array.
  foreach ($instances as $instance) {
    if (!empty($variables['categories']) && !in_array($instance->category_tid, $variables['categories'])) {
      continue;
    }

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

  unset($variables['categories'][NULL]);

  // Sort the categories by key (weight).
  ksort($categories);

  $variables['table'] = ding_ddbasic_opening_hours_table(
    t('Week @week, @from - @to', array(
      '@week' => format_date($timespan[0], 'custom', 'W'),
      '@from' => format_date($timespan[0], 'custom', 'd.m'),
      '@to' => format_date($timespan[1], 'custom', 'd.m'),
    )),
    $categories,
    $structured
  );

  drupal_add_library('system', 'drupal.ajax');
  $extra_categories = '';
  if (!empty($variables['categories'])) {
    $extra_categories = '/' . implode('|', $variables['categories']);
  }
  $variables['table']['#suffix'] = l(
    t('Next'),
    'ding-ddbasic/opening-hours/week/' . $variables['node']->nid
    . '/' . strtotime('next monday', $timespan[1])
    . '/' . strtotime('next sunday', $timespan[1])
    . $extra_categories,
    array(
      'attributes' => array('class' => array('use-ajax', 'button-next')),
    )
  ) . l(
    t('Previous'),
    'ding-ddbasic/opening-hours/week/' . $variables['node']->nid
    . '/' . strtotime('last monday', $timespan[0])
    . '/' . strtotime('last sunday', $timespan[0])
    . $extra_categories,
    array(
      'attributes' => array('class' => array('use-ajax', 'button-previous')),
    )
  );

  $variables['classes_array'][] = 'opening-hours-week-' . $variables['node']->nid;
  $variables['classes_array'][] = 'opening-hours-week';
}

/**
 * All libraries.
 */
function theme_ding_ddbasic_opening_hours_all($variables) {
  return render($variables['table']);
}

/**
 * Preprocessor for ding_ddbasic_opening_hours_all.
 */
function template_preprocess_ding_ddbasic_opening_hours_all(&$variables) {
  $today = strtotime('today');

  if (!empty($variables['today'])) {
    $today = $variables['today'];
  }

  $structured = array();
  $categories = array();

  // TODO Get rid of the magical nodequeue number.
  $order = array();
  foreach (nodequeue_load_nodes(1, FALSE, 0, FALSE) as $node) {
    $order[$node->title] = $node->nid;
  }

  // Get and sort all the instances in the given timespan.
  $instances = opening_hours_instance_load_multiple(
    array_values($order),
    date('Y-m-d', $today),
    date('Y-m-d', $today)
  );

  // Fill in closed instances.
  foreach ($order as $library_nid) {
    $closed = TRUE;
    foreach ($instances as $instance) {
      if ($instance->nid == $library_nid) {
        $closed = FALSE;
      }
    }

    if ($closed === TRUE) {
      $instances[] = (object) array(
        'instance_id' => -1,
        'nid' => $library_nid,
        'start_time' => '0',
        'end_time' => '0',
        'category_tid' => NULL,
        'date' => date('Y-m-d', $today),
        'closed' => TRUE,
        'notice' => t('Closed'),
      );
    }
  }

  usort($instances, 'ding_ddbasic_opening_hours_sort');

  $order = array_flip($order);

  foreach ($instances as $instance) {
    $category_weight = ding_ddbasic_opening_hours_get_category_weight($instance->category_tid);
    $library = $order[$instance->nid];

    if (!isset($structured[$library])) {
      $structured[$library] = array(
        'cols' => array(),
        'extra' => array(),
        'name' => l($library, 'node/' . $instance->nid),
      );
    }

    if (!empty($instance->notice)) {
      $notice = '<span class="notice">' . $instance->notice . '</span>';
    }
    else {
      $notice = '';
    }

    if (empty($instance->closed)) {
      $structured[$library]['cols'][$category_weight] = t('@from - @to', array(
        '@from' => $instance->start_time,
        '@to' => $instance->end_time,
      )) . $notice;
    }
    else {
      $structured[$library]['cols'][$category_weight] = $notice;
    }

    if (!isset($categories[$category_weight])) {
      $categories[$category_weight] = ding_ddbasic_opening_hours_get_category_name($instance->category_tid);
    }
  }

  // Order the structure by the nodequeue order.
  $structured = array_merge(array_intersect_key(array_flip($order), $structured), $structured);

  $variables['table'] = ding_ddbasic_opening_hours_table(
    t('Today: @date', array('@date' => format_date(time(), 'ding_date_only'))),
    $categories,
    $structured
  );
}
