<?php

/**
 * @file
 * Admin related backend.
 */

/**
 * Admin page menu callback.
 *
 * @return array
 *   Admin form.
 */
function ting_search_carousel_admin_page() {
  drupal_add_js(drupal_get_path('module', 'ting_search_carousel') . '/js/ting_search_carousel.admin.js');
  variable_set('ting_carousel_search_queries_hidden', array());

  return drupal_get_form('ting_search_carousel_admin_form');
}

/**
 * Admin settings form for frontend display of carousel.
 */
function ting_search_carousel_settings_admin_form($form, &$form_state) {
  $form = array();

  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Frontend settings'),
  );

  $form['settings']['ting_search_carousel_description_toggle'] = array(
    '#title' => t('Show descriptions for navigational tabs'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('ting_search_carousel_description_toggle', 0),
    '#required' => FALSE,
    '#description' => t('Toggle whether descriptions of the various searches are displayed or not.'),
  );

  $transitions = array();
  foreach (ding_carousel_transitions() as $name => $transition) {
    $transitions[$name] = $transition['name'];
  }

  $form['settings']['ting_search_carousel_transition'] = array(
    '#title' => t('Tab switching transition'),
    '#type' => 'select',
    '#options' => $transitions,
    '#default_value' => variable_get('ting_search_carousel_transition', 'fade'),
    '#description' => t('The JS transition used when switching tabs. This applies to the front page carousel.'),
  );

  return system_settings_form($form);
}

/**
 * Search queries admin form.
 *
 * @param array $form
 *   Form.
 * @param array $form_state
 *   Form state.
 *
 * @return array
 *   Form structure.
 */
function ting_search_carousel_admin_form(array $form, array &$form_state) {
  $form['#tree'] = TRUE;

  $form['ting_search_carousel'] = array(
    '#type' => 'fieldset',
    '#title' => t('Searches'),
  );

  if (empty($form_state['num_searches'])) {
    $form_state['existing_searches'] = variable_get('ting_search_carousel_searches', array());
  }

  $form['ting_search_carousel']['ting_searches'] = array(
    '#type' => 'container',
    '#prefix' => '<div id="ting-search-carousel-wrapper">',
    '#suffix' => '</div>',
    '#theme' => 'ting_search_carousel_admin_form',
  );

  if (!isset($form_state['num_searches'])) {
    $ids = array_keys($form_state['existing_searches']);
    if (!empty($ids)) {
      $form_state['num_searches'] = array_combine($ids, $ids);
    }
    else {
      $form_state['num_searches'] = array(0 => 0);
    }
  }

  foreach ($form_state['num_searches'] as $i) {
    $form['ting_search_carousel']['ting_searches'][$i] = ting_search_carousel_query_form($form_state['existing_searches'][$i], $i);
  }

  $form['ting_search_carousel']['add_search'] = array(
    '#type' => 'submit',
    '#value' => t('Add one more'),
    '#name' => 'ting_search_carousel_add',
    '#submit' => array('ting_search_carousel_add_more_add_one'),
    '#ajax' => array(
      'callback' => 'ting_search_carousel_ajax_callback',
      'wrapper' => 'ting-search-carousel-wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  $form['#submit'] = array('ting_search_carousel_admin_form_submit');

  return system_settings_form($form);
}

/**
 * Callback function for ajax add more searches.
 *
 * @param array $form
 *   Form.
 * @param array $form_state
 *   Form state.
 *
 * @see ting_search_carousel_admin_form
 */
function ting_search_carousel_add_more_add_one(array $form, array &$form_state) {
  $max = max(array_values($form_state['num_searches']));
  $form_state['num_searches'][$max + 1] = $max + 1;
  $form_state['rebuild'] = TRUE;
}

/**
 * Callback function for ajax remove search.
 *
 * @param array $form
 *   Form.
 * @param array $form_state
 *   Form state.
 *
 * @see ting_search_carousel_admin_form
 */
function ting_search_carousel_remove_submit(array $form, array &$form_state) {
  $elem = $form_state['triggering_element'];
  unset($form_state['num_searches'][$elem['#search_id']]);
  unset($form_state['existing_searches'][$elem['#search_id']]);
  $form_state['rebuild'] = TRUE;
}

/**
 * Callback for searches form.
 *
 * @param array $form
 *   Form.
 * @param array $form_state
 *   Form state.
 *
 * @see ting_search_carousel_admin_form
 *
 * @return array
 *   Form.
 */
function ting_search_carousel_ajax_callback(array $form, array &$form_state) {
  return $form['ting_search_carousel']['ting_searches'];
}

/**
 * Theme the queries form, mainly adding a table drag-n-drop feature.
 *
 * @param array $variables
 *   Theme related variables.
 *
 * @return string
 *   Themed form output.
 */
function theme_ting_search_carousel_admin_form(array $variables) {
  $form = $variables['form'];


  $header = array('Searches', '');
  $rows = array();
  foreach (element_children($form) as $key) {
    // Add class to group weight fields for drag and drop.
    $form[$key]['sort']['#attributes']['class'][] = 'sort';

    // Build rows.
    $classes = array('draggable');

    $rows[] = array(
      'data' => array(
        drupal_render($form[$key]['data']),
        drupal_render($form[$key]['sort']),
      ),
      'class' => $classes,
    );
  }

  $table_vars = array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array('id' => 'ting-search-carousel-admin-sort'),
    'caption' => '',
    'colgroups' => array(),
    'sticky' => FALSE,
    'empty' => t('At this moments not one searhes doesnt exists.'),
  );
  $output = theme('table', $table_vars);

  // Render remaining elements.
  $output .= drupal_render_children($form);
  drupal_add_tabledrag('ting-search-carousel-admin-sort', 'order', 'sibling', 'sort');

  return $output;
}

/**
 * Form part, describing query fields.
 *
 * @param array $item
 *   Values for existing query.
 * @param int $index
 *   Current item index.
 *
 * @return array
 *   Fields structure.
 */
function ting_search_carousel_query_form($item = array(), $index = 0) {
  $form = array();

  $form['sort'] = array(
    '#type' => 'weight',
    '#title' => t('Weight'),
    '#delta' => 5,
    '#default_value' => (isset($item['sort'])) ? $item['sort'] : 0,
    '#value' => 0,
    '#title_display' => 'invisible',
  );

  $form['data']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#description' => t('The title of the search is used for the tab in the carousel. Keep it short.'),
    '#default_value' => isset($item['title']) ? $item['title'] : '',
    '#prefix' => '<div class="search-carousel-query">',
  );

  $form['data']['subtitle'] = array(
    '#type' => 'textfield',
    '#title' => t('Description'),
    '#description' => t('The subtitle displayed next to the search results.'),
    '#default_value' => isset($item['subtitle']) ? $item['subtitle'] : '',
  );

  $form['data']['query'] = array(
    '#type' => 'textfield',
    '#title' => t('Query'),
    '#maxlength' => 2048,
    '#description' => t('The query to display search results for.'),
    '#default_value' => isset($item['query']) ? $item['query'] : '',
  );

  if ($index != 0) {
    $form['data']['remove'] = array(
      '#type' => 'submit',
      '#value' => t('Remove'),
      '#name' => 'ting_search_carousel_remove_' . $index,
      '#search_id' => $index,
      '#attributes' => array(
        'class' => array(
          'remove',
        ),
      ),
      '#submit' => array('ting_search_carousel_remove_submit'),
      '#ajax' => array(
        'callback' => 'ting_search_carousel_ajax_callback',
        'wrapper' => 'ting-search-carousel-wrapper',
        'method' => 'replace',
        'effect' => 'fade',
      ),
    );
  }

  return $form;
}

/**
 * Submit handler for admin backend queries form.
 *
 * @param array $form
 *   Form.
 * @param array $form_state
 *   Form state.
 */
function ting_search_carousel_admin_form_submit(array $form, array &$form_state) {
  $queries = $form_state['input']['ting_search_carousel']['ting_searches'];

  $searches = array();

  foreach ($queries as $key => $query) {
    // Make an array for saving, ignoring queries w/o title.
    if (!empty($queries[$key]['data']['title'])) {
      $searches[] = array(
        'title' => $queries[$key]['data']['title'],
        'subtitle' => $queries[$key]['data']['subtitle'],
        'query' => $queries[$key]['data']['query'],
      );
    }
  }

  // Save the queries as a persistent variable.
  variable_set('ting_search_carousel_searches', array_values($searches));

  // Clear carousel search cache.
  cache_clear_all('ting_search_carousel_search_', 'cache', TRUE);
}
