<?php
/**
 * @file
 * Ding DDBasic opening hours themes.
 */

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
