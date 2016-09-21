<?php

/**
 * Implements hook_preprocess_ding_ddbasic_all_opening_hours().
 */
function ddbasic_preprocess_ding_ddbasic_all_opening_hours(&$variables) {
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

  usort($instances, '_ddbasic_opening_hours_sort');

  $order = array_flip($order);

  foreach ($instances as $instance) {
    $category_weight = _ddbasic_opening_hours_get_category_weight($instance->category_tid);
    $library = $order[$instance->nid];

    if (!isset($structured[$library])) {
      $structured[$library] = array(
        'cols' => array(),
        'extra' => array(),
        'name' => l($library, 'node/' . $instance->nid),
      );
    }

    if(!empty($instance->notice)) {
      $notice = '<span class="notice">' . $instance->notice . '</span>';
    } else {
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
      $categories[$category_weight] = _ddbasic_opening_hours_get_category_name($instance->category_tid);
    }
  }

  // Order the structure by the nodequeue order.
  $structured = array_merge(array_intersect_key(array_flip($order), $structured), $structured);

  $variables['table'] = _ddbasic_opening_hours_table(
    t('Today: @date', array('@date' => format_date(time(), 'ding_date_only'))),
    $categories,
    $structured
  );
}

/**
 * Implements hook_preprocess_opening_hours_week().
 */
function ddbasic_preprocess_opening_hours_week(&$variables) {
  $timespan = array(
    strtotime('last monday', strtotime('+1 day')),
    strtotime('next sunday', strtotime('-1 day'))
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

  usort($instances, '_ddbasic_opening_hours_sort');

  // Insert the instances into the structured array.
  foreach ($instances as $instance) {
    $category_weight = _ddbasic_opening_hours_get_category_weight($instance->category_tid);
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

    if(!empty($instance->notice)) {
      $notice = '<span class="notice">' . $instance->notice . '</span>';
    } else {
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
      $categories[$category_weight] = _ddbasic_opening_hours_get_category_name($instance->category_tid);
    }
  }

  // Sort the categories by key (weight).
  ksort($categories);

  $variables['table'] = _ddbasic_opening_hours_table(
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
    'Next',
    'ding-ddbasic/opening-hours/week/' . $variables['node']->nid
    . '/' . strtotime('next monday', $timespan[1])
    . '/' . strtotime('next sunday', $timespan[1]),
    array(
      'attributes' => array('class' => array('use-ajax', 'button-next')),
    )
  ) . l(
    'Previous',
    'ding-ddbasic/opening-hours/week/' . $variables['node']->nid
    . '/' . strtotime('last monday', $timespan[0])
    . '/' . strtotime('last sunday', $timespan[0]),
    array(
      'attributes' => array('class' => array('use-ajax', 'button-previous')),
    )
  );
}

/**
 * Turn a structrued "opening hours" array into a table theme render array.
 */
function _ddbasic_opening_hours_table($title, $categories, $structured) {
  $table = array(
    '#theme' => 'table',
    '#header' => array_merge(array($title), $categories),
    '#rows' => array(),
    '#attributes' => array('class' => array('opening-hours-table')),
    // TODO If we want to use sticky, we need to look into how to set the table
    // header sticky offset (see the tableheader.js in root/misc).
    '#sticky' => FALSE,
  );

  foreach ($structured as $label => $row) {
    if (!isset($row['name'])) {
      $cols = array($label);
    }
    else {
      $cols = array($row['name']);
    }

    foreach ($categories as $category_weight => $header) {
      if (!empty($row['cols'][$category_weight])) {
        $col = array(
          'data' => $row['cols'][$category_weight],
          'data-label' => $header
        );
      }
      else {
        $col = array('class' => array('empty'));
      }

      $cols[] = $col;
    }

    $table['#rows'][] = array('data' => $cols) + $row['extra'];
  }

  return $table;
}

/**
 * Get name of an opening hours category tid.
 */
function _ddbasic_opening_hours_get_category_name($category_tid) {
  $name = &drupal_static(__FUNCTION__, array());

  if (!isset($name[$category_tid])) {
    if ($category_tid === NULL) {
      $name[$category_tid] = t('Opening hours');
    }
    else {
      $name[$category_tid] = taxonomy_term_load($category_tid)->name;
    }
  }

  return $name[$category_tid];
}

/**
 * Get weight of an opening hours category tid.
 */
function _ddbasic_opening_hours_get_category_weight($category_tid) {
  $weight = &drupal_static(__FUNCTION__, array());

  if (!isset($weight[$category_tid])) {
    if ($category_tid === NULL) {
      $weight[$category_tid] = -1;
    }
    else {
      $weight[$category_tid] = taxonomy_term_load($category_tid)->weight;
    }
  }
  return $weight[$category_tid];
}

/**
 * Array sort function.
 *
 * Sort opening hours instances in an array, by date and category weight.
 */
function _ddbasic_opening_hours_sort($a, $b) {
  return $a->date > $b->date ?
    1 : ($a->date < $b->date ?
    -1 : _ddbasic_opening_hours_get_category_weight($a->category_tid) > _ddbasic_opening_hours_get_category_weight($b->category_tid));
}
