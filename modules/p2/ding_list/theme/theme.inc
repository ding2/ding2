<?php

/**
 * @file
 * Theme and preprocess files.
 */

use DingList\DingList;

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
          '#value' => t('This material has been deleted from the library'),
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

  switch ($variables['display']) {
    case 'public list':
      $list_title = ($list->isOwner()) ? $list->getTitle() : $list->getTitle() . ' - ' . $list->getOwnerName();
      $variables['title'] = l($list_title, 'list/' . $list->getId());
      $variables['content']['carousel'] = array(
        '#type' => 'ding_carousel',
        '#items' => array(),
        '#path' => 'ding-list/carousel/ajax/' . $list->getId(),
        '#offset' => 0,
        // Add a single placeholder to fetch more content later if there
        // is more content.
        '#placeholders' => count($list->getElements()) > DING_LIST_CAROUSEL_CHUNK_SIZE ? DING_LIST_CAROUSEL_CHUNK_SIZE + 1 : count($list->getElements()),
      );

      // Create Carousel actions.
      $variables['content']['carousel_actions'] = array(
        '#type' => 'container',
        '#attributes' => array(
          'class' => array(
            'ding-carousel-actions',
          ),
        ),
      );

      $variables['content']['carousel_actions']['more'] = array(
        '#theme' => 'link',
        '#text' => t('Go to list'),
        '#path' => 'list/' . $list->getId(),
        '#prefix' => '<div class="more-link">',
        '#suffix' => '</div>',
        '#options' => array(
          'attributes' => array(
            'class' => array(
              'goto-list',
            ),
          ),
          'html' => FALSE,
        ),
      );
      if (!$list->isOwner() && user_access('use personalisation')) {
        $follow_list = ding_list_get_list(DING_LIST_TYPE_LISTS);
        if ($element = $follow_list->hasElement($list->getId())) {
          // If we have more than 1 remove form on a page Drupal will use the first
          // occoring remove form everytime, unless they all got a unique ID, which
          // is why the element ID is appended.
          // See the ding_list_forms() hook in ding_list/include/form.inc.
          $variables['content']['carousel_actions']['follow_form'] = drupal_get_form('ding_list_remove_element_form__' . $element->getId(), $element, t('Unfollow list'));
        }
        else {
          $variables['content']['carousel_actions']['follow_form'] = drupal_get_form('ding_list_add_element_form', 'ding_list', $list->getId(), t('Add to lists I follow'));
        }
      }
      break;

    default:
      if ($list->isOwner()) {
        $variables['content']['elements'] = array(
          '#theme' => 'table',
          '#attributes' => array(
            'id' => drupal_html_id('ding-list-list-elements'),
            'class' => array(
              'ding-list-list__elements', 
              'ding-list-list__owner', 
              'clearfix',
            ),
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
      }
      else {
        $variables['content']['elements'] = array(
          '#theme' => 'table',
          '#attributes' => array(
            'id' => drupal_html_id('ding-list-list-elements'),
            'class' => array(
              'ding-list-list__elements', 
              'ding-list-list__guest', 
              'clearfix',
            ),
            'data-list-id' => $list->getId(),
          ),
          '#rows' => array(),
        );
      }

      $total = $list->getElementCount();
      if ($total > 0) {
        $elements_per_page = DingList::PRELOADED_ELEMENTS;
        $current_page = pager_default_initialize($total, $elements_per_page);

        $drag_delta = 0;
        foreach ($list->getElements($current_page * $elements_per_page, $elements_per_page) as $element) {
          $variables['content']['elements']['#rows'][$element->getId()] = array(
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
            'data-element-id' => $element->getId(),
          );
        }

        $variables['content']['pager'] = array(
          '#theme' => 'pager',
        );
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
      'class' => array(
        'buttons',
      ),
    ),
    '#attached' => array(
      'library' => array(array('system', 'drupal.ajax')),
    ),
  );

  if ($variables['options'] === FALSE) {
    $options = ding_list_get_add_to_list_data($variables['type'], $variables['value'], $variables['value_title']);
  }
  else {
    $options = $variables['options'];
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
  }

  if (count($variables['buttons']['#links']) === 1) {
    $variables['classes_array'][] = 'ding-list-add-button--single-action';
  }
  else {
    $variables['classes_array'][] = 'ding-list-add-button--multiple-actions';
  }
}

/**
 * Ding list label/value theme.
 */
function theme_ding_list_label_value($variables) {
  $label = '';
  if ($variables['label']) {
    $label = '<div class="ding-list-field-label">' . $variables['label'] . '</div>';
  }
  $out = '<div class="ding-list-field">' . $label . '<div class="ding-list-field-text">' . $variables['value'] . '</div></div>';

  return $out;
}

/**
 * Ding list data theme.
 */
function template_preprocess_ding_list_data(&$variables) {
  $list = $variables['list'];
  $variables['info_items'] = array();
  $variables['button_items'] = array();

  $note = $list->getNote();
  // If no note isset, get the default note for the list type.
  if (!$note) {
    $list_information = ding_list_list_operations();
    $list_type = $list->getType();
    if (isset($list_information[$list_type])) {
      $list_information = $list_information[$list_type];
      if (isset($list_information['_data']['description'])) {
        $note = $list_information['_data']['description'];
      }
    }
  }
  $variables['note'] = $note;

  // Print authorname if not owner.
  if (!$list->isOwner()) {
    $variables['info_items'][] = array(
      '#theme' => 'ding_list_label_value',
      '#label' => t('Created by'),
      '#value' => $list->getOwnerName(),
    );
  }

  // Print Number of followers.
  if ($list->allowed(DING_LIST_OPERATION_SHARE) && $list->getData('visibility', 'private') != 'private') {
    $followers_count = $list->getFollowersCount();
    $variables['info_items'][] = array(
      '#theme' => 'ding_list_label_value',
      '#label' => t('Number of followers'),
      '#value' => format_plural($followers_count, '1 user following this list', '@count users following this list'),
    );
  }

  // Users can only follow/unfollow lists they don't own.
  // If list belongs to the user, add a sharing button.
  if (!$list->isOwner() && user_access('use personalisation')) {
    $follow_list = ding_list_get_list(DING_LIST_TYPE_LISTS);
    if ($element = $follow_list->hasElement($list->getId())) {
      // If we have more than 1 remove form on a page Drupal will use the first
      // occoring remove form everytime, unless they all got a unique ID, which
      // is why the element ID is appended.
      // See the ding_list_forms() hook in ding_list/include/form.inc.
      $variables['button_items'][] = drupal_get_form('ding_list_remove_element_form__' . $element->getId(), $element, t('Unfollow list'));
    }
    else {
      $variables['button_items'][] = drupal_get_form('ding_list_add_element_form', 'ding_list', $list->getId(), t('Add to lists I follow'));
    }
  }
  elseif ($list->allowed(DING_LIST_OPERATION_SHARE)) {
    $variables['button_items'][] = array(
      '#markup' => l(t('Share list'), 'list/' . $list->getId() . '/share', array('attributes' => array('class' => array('button')))),
    );
  }
}
