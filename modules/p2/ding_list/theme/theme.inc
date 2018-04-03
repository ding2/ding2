<?php

/**
 * @file
 * Theme and preprocess files.
 */

/**
 * Ding list message theme.
 */
function theme_ding_list_message($variables) {
  return '<div class="ding-list-message">' . $variables['message'] . '</div>';
}

/**
 * Preprocesses variables for ding_list_element.
 */
function template_preprocess_ding_list_element(&$variables) {
  $element = $variables['element'];
  $variables['classes_array'][] = 'ding-list-element--type-' . drupal_html_class($element['type']);
  $variables['classes_array'][] = 'ding-list-element--display-' . drupal_html_class($variables['display']);
  $variables['classes_array'][] = 'clearfix';
  $variables['attributes_array']['data-element-id'] = $element['element_id'];

  switch ($element['type']) {
    case 'ting_object':
      $view_mode_matrix = array(
        // @TODO Constants
        'view list' => 'ting_reference_preview',
      );
      $ting_object = ting_object_load(ding_list_convert_cql($element['value']));
      if ($ting_object) {
        $variables['content']['value']['ting_object'] = ting_object_view(
          $ting_object,
          isset($view_mode_matrix[$variables['display']]) ? $view_mode_matrix[$variables['display']] : 'default'
        );
      }
      else {
        $variables['content']['value'] = array(
          '#theme' => 'html_tag',
          '#tag' => 'div',
          '#value' => t('Missing object'),
          '#attributes' => array(
            'class' => array('ding-list-element__title'),
          ),
        );
      }
      break;

    case 'ding_list':
      $list = ding_list_get_list($element['value']);
      $variables['content']['value'] = array(
        '#theme' => 'link',
        '#text' => check_plain($list['title']),
        '#path' => 'list/' . $element['value'],
        '#options' => array(
          'attributes' => array('class' => array('ding-list-element__title')),
          'html' => TRUE,
        ),
      );
      break;

    case 'search_query':
    case 'follow_author':
      $parsed = drupal_parse_url($element['value']);
      $variables['content']['value'] = array(
        '#theme' => 'link',
        '#text' => check_plain(empty($element['extra']['title']) ? $element['value'] : $element['extra']['title']),
        '#path' => 'search/ting/' . $parsed['path'],
        '#options' => array(
          'query' => $parsed['query'],
          'attributes' => array('class' => array('ding-list-element__title')),
          'html' => TRUE,
        ),
      );
      break;
  }

  $variables['content']['remove'] = drupal_get_form('ding_list_remove_element_form__' . $element['element_id'], $element);
}

/**
 * Info displayed, when a list is created.
 */
function theme_ding_list_create_info($variables) {
  $list = $variables['list'];

  $out = '<div class="ding-list-test-button"></div>';

  $items = array();
  $items[] = t("You've create the list !list.", array(
    '!list' => l($list->title, 'list/' . $list->id),
  ));
  $items[] = t('Use the "More" button on materials, to add them to the list.');
  $items[] = t('You can search after materials !search, that you can add to the list.', array(
    '!search' => l(t('Here'), 'search'),
  ));
  $items[] = t('Read more about how you use the lists !help', array(
    '!help' => l(t('Here'), 'help/lists'),
  ));

  $list = array(
    '#theme' => 'item_list',
    '#items' => $items,
  );
  $out .= drupal_render($list);;

  return '<div class="ding-list-create-info">' . $out . '</div>';
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
  $list = $variables['list'];

  $variables['classes_array'][] = 'ding-list-list--' . drupal_html_class($list['type']);
  $variables['content'] = array();

  $variables['title_attributes_array']['class'][] = 'ding-list-list__title';
  $variables['title'] = check_plain($list['title']);
  if (!ding_list_is_owner($list)) {
    $variables['title'] = t('@list_title, By @list_author', array(
      '@list_title' => $variables['title'],
      '@list_author' => ding_list_list_username($list),
    ));
  }

  switch ($variables['display']) {
    case 'public list':
      $variables['title'] = l($variables['title'], 'list/' . $list['list_id']);
      $variables['content']['carousel'] = array(
        '#type' => 'ding_carousel',
        '#items' => array(),
        '#path' => 'ding-list/carousel/ajax/' . $list['list_id'],
        '#offset' => 0,
        // Add a single placeholder to fetch more content later if there
        // is more content.
        '#placeholders' => count($list['elements']) > DING_LIST_CAROUSEL_CHUNK_SIZE ? DING_LIST_CAROUSEL_CHUNK_SIZE + 1 : count($list['elements']),
      );
      break;

    default:
      if (!empty($list['elements'])) {
        $variables['content']['elements'] = array(
          '#prefix' => '<div class="ding-list-list__elements">',
          '#suffix' => '</div>',
        );

        foreach ($list['elements'] as $element_key => $element) {
          $variables['content']['elements'][$element_key] = array(
            '#theme' => 'ding_list_element',
            '#display' => $variables['display'],
            '#element' => $element,
          );
        }
      }
      break;
  }
}

/**
 * Add button.
 */
function template_preprocess_ding_list_add_button(&$variables) {
  if (empty($variables['title'])) {
    $variables['title'] = t('Add to list');
  }

  $variables['buttons'] = array(
    '#theme' => 'links',
    '#links' => array(),
    '#attributes' => array(
      'class' => array('buttons'),
    ),
    '#attached' => array(
      'library' => array(array('system', 'drupal.ajax')),
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
    $new_list = array(
      'custom' => array(
        'title' => '<div class="list-title">' . t('New list') . '</div><div class="add-to-list-button button">' . t('Add to new list') . '</div>',
        'href' => 'list/create',
        'attributes' => array(
          'class' => array(),
        ),
        'query' => array('at' => $variables['type'], 'av' => $variables['value']),
        'html' => TRUE,
      ),
    );

    if (!user_is_logged_in()) {
      $new_list['custom']['attributes']['class'][] = 'use-ajax';
      $new_list['custom']['href'] = 'ding-list/login-create';
    }

    $options[] = $new_list;
  }

  foreach ($options as $option) {
    if (!isset($option['custom'])) {
      if ($option['type'] == 'search_query') {
        $option['title'] = t('Add to searches I follow');
      }

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
 * Ding list info theme.
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
