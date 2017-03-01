<?php
/**
 * @file
 * Theme and preprocess files
 */

/**
 * Ding list message theme.
 */
function theme_ding_list_message($variables) {
  return '<div class="ding-list-message">' . $variables['message'] . '</div>';
}

/**
 * Ding list permission description theme.
 */
function theme_ding_list_permission_description($variables) {
  return '<div id="status-description">' . $variables['message'] . '</div>';
}

/**
 * Default preprocess.
 */
function template_preprocess_ding_list_list(&$variables) {
  if ($variables['sortable'] !== FALSE) {
    $variables['classes_array'][] = 'sort-enabled';
  }
}

/**
 * Add button.
 */
function template_preprocess_ding_list_add_button(&$variables) {
  if (empty($variables['title'])) {
    $variables['title'] = t('More...');
  }

  $path = drupal_get_path('module', 'ding_list');
  $variables['buttons'] = array(
    '#theme' => 'links',
    '#links' => array(),
    '#attributes' => array(
      'class' => array('buttons'),
    ),
    '#attached' => array(
      'library' => array(array('system', 'drupal.ajax')),
      'css' => array($path . '/css/ding-list-add-button.css'),
      'js' => array($path . '/js/ding-list-add-button.js'),
    ),
  );

  $variables['single_link'] = FALSE;

  if ($variables['options'] === FALSE) {
    $options = ding_list_get_add_to_list_data($variables['type'], $variables['value'], $variables['value_title']);
  }
  else {
    $options = $variables['options'];
  }

  if ($variables['type'] == 'ting_object') {
    $options[] = array(
      'custom' => array(
        'title' => t('Add to new list'),
        'href' => 'list/create',
        'attributes' => array(
          'class' => array(),
        ),
        'query' => array('at' => $variables['type'], 'av' => $variables['value']),
        'html' => TRUE,
      ),
    );
  }
  foreach ($options as $option) {
    if (!isset($option['custom'])) {
      $l = array(
        'title' => $option['title'],
        'href' => 'dinglist/attach/' . $option['type'] . '/' . $option['list_id'] . '/' . $option['value'],
        'attributes' => array(
          'class' => array('use-ajax', drupal_html_class($option['type'])),
        ),
        'html' => TRUE,
      );

      if (!empty($option['value_title'])) {
        $l['query'] = array('title' => $option['value_title']);
      }
    }
    else {
      $l = $option['custom'];
    }

    $variables['buttons']['#links'][] = $l;
    if (isset($option['#single_link'])) {
      $variables['single_link'] = TRUE;
    }
  }
}

/**
 * Ding list followers preprocessor.
 */
function template_preprocess_ding_list_followers(&$variables) {
  $list = $variables['list'];
  $variables['count'] = ding_list_get_list_followers_count($list);

  $variables['note'] = ding_base_get_value('ding_type', $list, 'field_notes');
  if ($variables['note'] === FALSE) {
    $list_information = ding_list_list_operations();
    $list_type = ding_base_get_value('ding_type', $list, 'field_list_type');
    if (isset($list_information[$list_type])) {
      $list_information = $list_information[$list_type];
      if (isset($list_information['_data']['description'])) {
        $variables['note'] = $list_information['_data']['description'];
      }
    }
  }

  $variables['no_objects'] = empty($list->field_list_objects);
}

/**
 * Ding list followers theme.
 */
function theme_ding_list_followers($variables) {
  $out = format_plural($variables['count'], '1 user following this list', '@count users following this list');

  return $out;
}

/**
 * Ding list info theme
 */
function theme_ding_list_info($variables) {
  $out = '';

  if ($variables['note'] !== FALSE) {
    $out .= '<div class="ding-list-note">' . $variables['note'] . '</div>';
  }

  if ($variables['no_objects']) {
    $out .= '<div class="ding-list-no-elements">' . t('No elements in this list.') . '</div>';
  }

  return $out;
}

/**
 * Ding list lists theme.
 */
function theme_ding_list_lists($variables) {
  $out = '';

  foreach ($variables['groups'] as $group_name => $group) {
    $out .= "<a name='" . $group_name . "'></a>";
    $rows = array();

    foreach ($group['lists'] as $lists) {
      foreach ($lists as $list) {
        // Remove the #list reference, so the item_list theme doesn't confuse
        // it with an attribute.
        unset($list['#list']);
        $rows[] = $list;
      }
    }

    $out .= theme('item_list', array(
      'items' => $rows,
      'title' => $group['title'],
      'type' => 'ul',
      'attributes' => array(),
    ));
  }

  // Footer links.
  $out .= theme('item_list', array(
    'items' => array(
      l(t("Mark all notifications as read"), "ding_message/purge_user_messages", array('attributes' => array('class' => array('button')))),
      l(t("Create new list"), "list/create", array('attributes' => array('class' => array('button')))),
    ),
    'title' => "",
    'type' => 'ul',
    'attributes' => array('class' => array('bottom-links')),
  ));

  return '<div class="ding-user-lists">' . $out . '</div>';
}
