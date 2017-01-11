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
  $clicked_btn = '';
  $remove_btn = null;
  $num_searches = (!empty($form_state['values']['num_searches']))
    ? $form_state['values']['num_searches']
    : 0;

  $form['#tree'] = TRUE;

  if (isset($form_state['clicked_button'])) {
    $clicked_btn = $form_state['clicked_button']['#name'];

    // Get a clicked 'remove' button.
    foreach ($form_state['buttons'] as $k => $v) {
      if ($v['#name'] == $clicked_btn) {
        if (preg_match('/remove--[0-9]+$/', $v['#id'])) {
          $remove_btn = $k;
          break;
        }
      }
    }
  }

  $form['ting_search_carousel'] = array(
    '#type' => 'fieldset',
    '#title' => 'Searches',
  );

  // Get current saved queries.
  $searches = variable_get('ting_search_carousel_searches', array());

  $index = 0;
  $count = 1;

  // Display saved queries.
  if (isset($searches[0]['title'])) {
    $count = count($searches);
    for (; $index < $count; $index++) {
      $form['ting_search_carousel']['ting_searches'][$index] = ting_search_carousel_query_form($searches[$index], $index);
    }
  }

  for (; $index < $num_searches + $count; $index++) {
    $unsubmitted = array();
    // Maybe prev field had some data in it...
    if (isset($form_state['input']['title'][$index])) {
      $unsubmitted = array(
        'title' => $form_state['input']['title'][$index],
        'subtitle' => $form_state['input']['subtitle'][$index],
        'query' => $form_state['input']['query'][$index],
      );
    }

    $form['ting_search_carousel']['ting_searches'][$index] = ting_search_carousel_query_form($unsubmitted, $index);
  }

  if (!empty($clicked_btn) && !is_null($remove_btn)) {
    unset($form['ting_search_carousel']['ting_searches'][$remove_btn]);
  }

  // Keep track of query fields count.
  $form['ting_search_carousel']['num_searches'] = array(
    '#type' => 'hidden',
    '#value' => $num_searches,
  );

  $form['ting_search_carousel']['add_search'] = array(
    '#type' => 'submit',
    '#value' => t('Add one more'),
    '#submit' => array('ting_search_carousel_add_more_add_one'),
    '#ajax' => array(
      'callback' => 'ting_search_carousel_ajax_callback',
      'wrapper' => 'ting-search-carousel-wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  // Wrap the form, due to draggable items renewal.
  $form['#prefix'] = '<div id="ting-search-carousel-wrapper">';
  $form['#suffix'] = '</div>';

  // Custom themer, mainly used for dragable table creation.
  $form['#theme'] = array('ting_search_carousel_admin_form');

  $form['#submit'] = array('ting_search_carousel_admin_form_submit');

  return system_settings_form($form);
}

/**
 * Callback function for ajax add more searches.
 *
 * @see ting_search_carousel_admin_form
 *
 * @param $form
 * @param $form_state
 */
function ting_search_carousel_add_more_add_one($form, &$form_state) {
  $form_state['values']['num_searches']++;
  $form_state['rebuild'] = TRUE;
}

/**
 * Callback for searches form.
 *
 * @see ting_search_carousel_admin_form
 *
 * @param $form
 * @param $form_state
 *
 * @return mixed
 */
function ting_search_carousel_ajax_callback($form, $form_state) {
  return $form;
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
  drupal_add_tabledrag('ting-search-carousel-admin-sort', 'order', 'sibling', 'sort');

  $header = array('Searches', '');
  $rows = array();
  foreach (element_children($form['ting_search_carousel']['ting_searches']) as $key) {
    // Add class to group weight fields for drag and drop.
    $form['ting_search_carousel']['ting_searches'][$key]['sort']['#attributes']['class'][] = 'sort';

    // Get sort element.
    $sort = $form['ting_search_carousel']['ting_searches'][$key]['sort'];
    unset($form['ting_search_carousel']['ting_searches'][$key]['sort']);

    // Build rows.
    $classes = array('draggable');
    if (isset($form['ting_search_carousel']['ting_searches'][$key]['#prefix'])) {
      $classes[] = 'search-query-hidden';
    }

    $rows[] = array(
      'data' => array(
        drupal_render($form['ting_search_carousel']['ting_searches'][$key]),
        drupal_render($sort),
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
    'empty' => 'EMPTY',
  );
  $output = theme('table', $table_vars);

  // Render remaining elements.
  $output .= drupal_render_children($form);

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
    '#delta' => 5,
    '#default_value' => 0,
    '#value' => 0,
    '#attributes' => array(
      'class' => array(
        'sort-hidden',
      ),
    ),
  );

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#description' => t('The title of the search is used for the tab in the carousel. Keep it short.'),
    '#default_value' => isset($item['title']) ? $item['title'] : '',
    '#prefix' => '<div class="search-carousel-query">',
  );

  $form['subtitle'] = array(
    '#type' => 'textfield',
    '#title' => t('Description'),
    '#description' => t('The subtitle displayed next to the search results.'),
    '#default_value' => isset($item['subtitle']) ? $item['subtitle'] : '',
  );

  $form['query'] = array(
    '#type' => 'textfield',
    '#title' => t('Query'),
    '#maxlength' => 2048,
    '#description' => t('The query to display search results for.'),
    '#default_value' => isset($item['query']) ? $item['query'] : '',
  );

  $form['remove'] = array(
    '#type' => 'button',
    '#value' => t('Remove'),
    '#name' => 'remove_' . $index,
    '#attributes' => array(
      'class' => array(
        'remove',
      ),
    ),
    '#suffix' => '</div><div class="clearfix"></div>',
    '#ajax' => array(
      'callback' => 'ting_search_carousel_ajax_callback',
      'wrapper' => 'ting-search-carousel-wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

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
    if (!empty($queries[$key]['title'])) {
      $searches[] = array(
        'title' => $queries[$key]['title'],
        'subtitle' => $queries[$key]['subtitle'],
        'query' => $queries[$key]['query']
      );
    }
  }

  // Save the queries as a persistent variable.
  variable_set('ting_search_carousel_searches', array_values($searches));

  // Clear carousel search cache.
  cache_clear_all('ting_search_carousel_search_', 'cache', TRUE);
}
