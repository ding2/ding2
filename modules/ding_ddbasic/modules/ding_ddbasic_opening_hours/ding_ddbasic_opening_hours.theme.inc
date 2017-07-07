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
  for ($day = $timespan[0]; $day <= $timespan[1]; $day += DING_DDBASIC_OPENING_HOURS_ONE_DAY) {
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

  // Add NULL to the categories, if the the NO_CATEGORY category is selected.
  // So an empty category_tid of the instance matches the selected categories.
  if (in_array(DING_DDBASIC_OPENING_HOURS_NO_CATEGORY, $variables['categories'])) {
    $variables['categories'][''] = NULL;
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
      $notice = '<span class="opening-hours-table-notice">' . $instance->notice . '</span>';
    }
    else {
      $notice = '';
    }

    if (empty($structured[$day]['cols'][$category_weight])) {
      $structured[$day]['cols'][$category_weight] = '';
    }

    if (empty($instance->closed)) {
      $structured[$day]['cols'][$category_weight] .= '<div>' . t('@from - @to', array(
        '@from' => $instance->start_time,
        '@to' => $instance->end_time,
      )) . $notice . '</div>';
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

  $title = t('Week @week, @from - @to', array(
    '@week' => format_date($timespan[0], 'custom', 'W'),
    '@from' => format_date($timespan[0], 'custom', 'd.m'),
    '@to' => format_date($timespan[1], 'custom', 'd.m'),
  ));

  $variables['table'] = ding_ddbasic_opening_hours_table(
    $title,
    $categories,
    $structured
  );

  drupal_add_library('system', 'drupal.ajax');
  $extra_categories = '';
  if (!empty($variables['categories'])) {
    $extra_categories = '/' . implode('|', $variables['categories']);
  }
  $variables['table']['#suffix'] = '<div class="opening-hours-title">' . $title . '</div>'
  . l(
    t('next ›'),
    'ding-ddbasic/opening-hours/week/' . $variables['node']->nid
    . '/' . strtotime('next monday', $timespan[1])
    . '/' . strtotime('next sunday', $timespan[1])
    . $extra_categories,
    array(
      'attributes' => array('class' => array('use-ajax', 'button-next')),
    )
  ) . l(
    t('‹ previous'),
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

  if (variable_get('ding_ddbasic_opening_hours_expand_on_library', FALSE)) {
    drupal_add_js(array('ding_ddbasic_opening_hours' => array('expand_on_library' => TRUE)), 'setting');
  }
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

  $order = array();
  $queue = nodequeue_load_queue_by_name('ding_library_listing');
  foreach (nodequeue_load_nodes($queue->qid, FALSE, 0, 0) as $node) {
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

    if (empty($structured[$library]['cols'][$category_weight])) {
      $structured[$library]['cols'][$category_weight] = '';
    }

    if (empty($instance->closed)) {
      $structured[$library]['cols'][$category_weight] .= '<div>' . t('@from - @to', array(
        '@from' => $instance->start_time,
        '@to' => $instance->end_time,
      )) . $notice . '</div>';
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
