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
  $variables['classes_array'][] = 'ding-list-element--type-' . drupal_html_class($element->getType());
  $variables['classes_array'][] = 'ding-list-element--display-' . drupal_html_class($variables['display']);
  $variables['classes_array'][] = 'clearfix';
  $variables['attributes_array']['data-element-id'] = $element->getId();

  switch ($element->getType()) {
    case 'ting_object':
      $view_mode_matrix = array(
        'view list' => 'ting_reference_preview',
      );
      $ting_object = ting_object_load(ding_list_convert_cql($element->getValue()));
      if ($ting_object) {
        $variables['content']['ting_object'] = ting_object_view(
          $ting_object,
          isset($view_mode_matrix[$variables['display']]) ? $view_mode_matrix[$variables['display']] : 'default'
        );
      }
      else {
        $variables['content']['value'] = array(
          '#theme' => 'html_tag',
          '#tag' => 'div',
          '#value' => t('Missing item'),
          '#attributes' => array(
            'class' => array('ding-list-element__title'),
          ),
        );
        drupal_set_message(t('Unable to retrieve some of the items on this list. The list may appear incomplete.'), 'warning', FALSE);
        watchdog(
          'ding_list',
          'Unable to load ting_object %object in list %list',
          array('%object' => $element->getValue(), '%list' => $element->getListId()),
          WATCHDOG_ERROR
        );
      }
      break;

    case 'ding_list':
      $list = ding_list_get_list($element->getValue());
      if ($list) {
        $variables['content']['link'] = array(
          '#theme' => 'link',
          '#text' => check_plain($list->getTitle()),
          '#path' => 'list/' . $element->getValue(),
          '#options' => array(
            'attributes' => array('class' => array('ding-list-element__title')),
            'html' => TRUE,
          ),
        );
      }
      else {
        $variables['content']['value'] = array(
          '#theme' => 'html_tag',
          '#tag' => 'div',
          '#value' => t('List no longer avaiable'),
          '#attributes' => array(
            'class' => array('ding-list-element__title'),
          ),
        );
        drupal_set_message(t("A list you're following are no longer available."));
      }
      break;

    case 'search_query':
    case 'follow_author':
      $parsed = drupal_parse_url($element->getValue());
      $variables['content']['link'] = array(
        '#theme' => 'link',
        '#text' => check_plain($element->getData('title', $element->getValue())),
        '#path' => 'search/ting/' . $parsed['path'],
        '#options' => array(
          'query' => $parsed['query'],
          'attributes' => array('class' => array('ding-list-element__title')),
          'html' => TRUE,
        ),
      );
      break;
  }

  $variables['remove'] = drupal_get_form('ding_list_remove_element_form__' . $element->getId(), $element);
}

/**
 * Info displayed, when a list is created.
 */
function theme_ding_list_create_info($variables) {
  $list = $variables['list'];

  $out = '<div class="ding-list-test-button"></div>';

  $items = array();
  $items[] = t("You've create the list !list.", array(
    '!list' => l($list->getTitle(), 'list/' . $list->getId()),
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

  $variables['classes_array'][] = 'ding-list-list--' . drupal_html_class($list->getType());
  $variables['content'] = array();

  $variables['title_attributes_array']['class'][] = 'ding-list-list__title';
  $variables['title'] = check_plain($list->getTitle());
  if (!$list->isOwner()) {
    $variables['title'] = t('@list_title, By @list_author', array(
      '@list_title' => $variables['title'],
      '@list_author' => $list->getOwnerName(),
    ));
  }

  switch ($variables['display']) {
    case 'public list':
      $variables['title'] = l($variables['title'], 'list/' . $list->getId());
      $variables['content']['carousel'] = array(
        '#type' => 'ding_carousel',
        '#items' => array(),
        '#path' => 'ding-list/carousel/ajax/' . $list->getId(),
        '#offset' => 0,
        // Add a single placeholder to fetch more content later if there
        // is more content.
        '#placeholders' => count($list->getElements()) > DING_LIST_CAROUSEL_CHUNK_SIZE ? DING_LIST_CAROUSEL_CHUNK_SIZE + 1 : count($list->getElements()),
      );
      break;

    default:
      if ($list->hasData('visibility') && $list->getData('visibility') === 'public') {
        $followers_count = $list->getFollowersCount();

        if ($followers_count > 0) {
          $variables['content']['followers'] = array(
            '#prefix' => '<div class="ding-list-list__followers">',
            '#suffix' => '</div>',
            '#markup' => format_plural($followers_count, '1 user following this list', '@count users following this list'),
          );
        }
      }

      if (!empty($list->getNote())) {
        $variables['content']['note'] = array(
          '#prefix' => '<div class="ding-list-list__note">',
          '#suffix' => '</div>',
          '#markup' => $list->getNote(),
        );
      }

      $variables['content']['elements'] = array(
        '#theme' => 'table',
        '#attributes' => array(
          'id' => drupal_html_id('ding-list-list-elements'),
          'class' => array('ding-list-list__elements'),
          'data-list-id' => $list->getId(),
        ),
        '#rows' => array(),
        '#attached' => array(
          'js' => array(
            drupal_get_path('module', 'ding_list') . '/js/ding_list_tabledrag.js',
          ),
          'css' => array(
            drupal_get_path('module', 'ding_list') . '/css/ding-list-tabledrag.css',
          ),
        ),
      );
      drupal_add_tabledrag(
        $variables['content']['elements']['#attributes']['id'],
        'order',
        'sibling',
        'ding-list-list__element-delta'
      );

      if (!empty($list->getElements())) {
        $drag_delta = 0;
        foreach ($list->getElements() as $element_id => $element) {
          $variables['content']['elements']['#rows'][$element_id] = array(
            'data' => array(
              array(
                'data' => array(
                  '#theme' => 'ding_list_element',
                  '#display' => $variables['display'],
                  '#element' => $element,
                ),
              ),
              array(
                'data' => $drag_delta++,
                'class' => array('ding-list-list__element-delta'),
              ),
            ),
            'class' => array('draggable'),
            'data-element-id' => $element_id,
          );
        }
      }
      else {
        $variables['content']['elements']['#markup'] = t('No elements in this list.');
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
