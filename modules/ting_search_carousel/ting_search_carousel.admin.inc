<?php
/**
 * @file
 * Admin related backend.
 */

/**
 * Admin page menu callback.
 *
 * @return
 *   Admin form.
 */
function ting_search_carousel_admin_page() {
  drupal_add_js(drupal_get_path('module', 'ting_search_carousel') . '/js/ting_search_carousel.admin.js');
  drupal_add_css(drupal_get_path('module', 'ting_search_carousel') . '/css/ting_search_carousel.css');
  variable_set('ting_carousel_search_queries_hidden', array());

  return drupal_get_form('ting_search_carousel_admin_form');
}

/**
 * Admin settings form for frontend display of carousel.
 */
function ting_search_carousel_settings_admin_form($form, &$form_state) {
  $form = array();

  $form['ting_search_carousel_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Frontend settings'),
  );

  $form['ting_search_carousel_settings']['ting_search_carousel_tabs_position'] = array(
    '#title' => t('Position of navigational tabs'),
    '#type' => 'select',
    '#options' => array(
      'bottom' => t("Bottom"),
    ),
    '#default_value' => variable_get('ting_search_carousel_tabs_position', 'bottom'),
    '#required' => TRUE,
    '#description' => t('Select where you want the tabs for displaying the various searches to be placed in frontend.'),
  );

  $form['ting_search_carousel_settings']['ting_search_carousel_item_limit'] = array(
    '#type' => 'select',
    '#title' => t('Item limit'),
    '#options' => array_combine(range(6, 24, 6), range(6, 24, 6)),
    '#description' => t('The number of items to be returned in search result.'),
    '#default_value' => variable_get('ting_search_carousel_item_limit', 12),
  );

  $form['ting_search_carousel_settings']['ting_search_carousel_description_toggle'] = array(
    '#title' => t('Show descriptions for navigational tabs'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('ting_search_carousel_description_toggle', 0),
    '#required' => FALSE,
    '#description' => t('Toggle whether descriptions of the various searches are displayed or not.'),
  );

  $form['ting_search_carousel_settings']['ting_search_carousel_item_sorting'] = array(
    '#type' => 'select',
    '#title' => t('Sorting'),
    '#options' => array(
      '' => t('- None -'),
      'title_ascending' => t('Title (Ascending)'),
      'title_descending' => t('Title (Descending)'),
      'creator_ascending' => t('Creator (Ascending)'),
      'creator_descending' => t('Creator (Descending)'),
      'date_ascending' => t('Date (Ascending)'),
      'date_descending' => t('Date (Descending)'),
      'acquisitionDate_ascending' => t('Acquisition date (Ascending)'),
      'acquisitionDate_descending' => t('Acquisition date (Descending)'),
    ),
    '#default_value' => variable_get('ting_search_carousel_item_sorting', ''),
    '#description' => t('If not set, defaults to Ranking'),
  );

  return system_settings_form($form);
}

/**
 * Search queries admin form.
 *
 * @param $form
 *   Form.
 * @param $form_state
 *   Form state.
 *
 * @return
 *   Form structure.
 */
function ting_search_carousel_admin_form($form, &$form_state) {
  $searches_num = !empty($form_state['values']['num_searches']) ? $form_state['values']['num_searches'] : 0;
  $clicked_btn = '';
  $remove_btn = '';
  $hidden = variable_get('ting_carousel_search_queries_hidden', array());

  if (isset($form_state['clicked_button'])) {
    $clicked_btn = $form_state['clicked_button']['#name'];

    // Get a clicked 'remove' button
    foreach ($form_state['buttons'] as $k => $v) {
      if ($v['#name'] == $clicked_btn) {
        if (preg_match('/edit-remove/', $v['#id'])) {
          $remove_btn = $k;
          $hidden[] = $remove_btn;
          variable_set('ting_carousel_search_queries_hidden', $hidden);
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
  $searches = variable_get('ting_carousel_search_queries', array());

  $i = 0;
  $c = 1;

  // Display saved queries.
  if (isset($searches[0]['title'])) {
    $c = count($searches);
    for (; $i < $c; $i++) {
      $form['ting_search_carousel']['ting_searches']['search_' . $i] = ting_search_carousel_query_form($searches[$i], $i);
    }
  }

  // Whether add a new query field.
  if ($clicked_btn == 'add_query') {
    $searches_num++;
  }

  for (; $i < $searches_num + $c; $i++) {
    $unsubmitted = array();
    // Maybe prev field had some data in it...
    if (isset($form_state['input']['title'][$i])) {
      $unsubmitted = array(
        'title' => $form_state['input']['title'][$i],
        'subtitle' => $form_state['input']['subtitle'][$i],
        'query' => $form_state['input']['query'][$i],
      );
    }

    $form['ting_search_carousel']['ting_searches']['search_' . $i] = ting_search_carousel_query_form($unsubmitted, $i);
  }

  // Hide removed fields.
  for ($i = 0; $i < $searches_num + $c; $i++) {
    if (in_array($i, $hidden)) {
      // Hide title, used to sort needed queries when saving
      $form['ting_search_carousel']['ting_searches']['search_' . $i]['title[]']['#value'] = '';
      $form['ting_search_carousel']['ting_searches']['search_' . $i]['#prefix'] = '<div class="search-query-hidden">';
      $form['ting_search_carousel']['ting_searches']['search_' . $i]['#suffix'] = '</div>';
    }
  }

  // Keep track of query fields count.
  $form['ting_search_carousel']['num_searches'] = array(
    '#type' => 'hidden',
    '#value' => $searches_num,
  );

  // Ajaxified button for new fields.
  $form['ting_search_carousel']['new_search_carousel_button'] = array(
    '#type' => 'button',
    '#value' => 'Add another',
    '#name' => 'add_query',
    '#ajax' => array(
      'callback' => 'ting_search_carousel_admin_form_ajaxify',
      'wrapper' => 'ting-search-carousel-queries',
      'method' => 'replace',
      'effect' => 'fade'
    ),
  );

  // Wrap the form, due to draggable items renewal.
  $form['#prefix'] = '<div id="ting-search-carousel-queries">';
  $form['#suffix'] = '</div>';
  // Custom themer, mainly used for dragable table creation.
  $form['#theme'] = array('ting_search_carousel_admin_form');
  // Custom form submit handler.
  $form['#submit'] = array('ting_search_carousel_search_submit');

  return system_settings_form($form);
}

/**
 * AJAX responder for field addition/removal fields.
 *
 * @param $form
 *   Form.
 *
 * @return
 *   Changed field to be updated.
 */
function ting_search_carousel_admin_form_ajaxify($form, &$form_state) {
  return $form;
}

/**
 * Theme the queries form, mainly adding a table drag-n-drop feature.
 *
 * @param $variables
 *   Theme related variables.
 *
 * @return
 *   Themed form output.
 */
function theme_ting_search_carousel_admin_form($variables) {
  $form = $variables['form'];
  drupal_add_tabledrag('ting-search-carousel-admin-sort', 'order', 'sibling', 'sort');

  $header = array('Searches', '');
  $rows = array();
  foreach (element_children($form['ting_search_carousel']['ting_searches']) as $key) {
    // Add class to group weight fields for drag and drop.
    $form['ting_search_carousel']['ting_searches'][$key]['sort[]']['#attributes']['class'][] = 'sort';

    // Get sort element.
    $sort = $form['ting_search_carousel']['ting_searches'][$key]['sort[]'];
    unset($form['ting_search_carousel']['ting_searches'][$key]['sort[]']);

    // Build rows.
    $classes = array('draggable');
    if (isset($form['ting_search_carousel']['ting_searches'][$key]['#prefix'])) {
      $classes[] = 'search-query-hidden';
    }

    $rows[] = array(
      'data' => array(
        drupal_render($form['ting_search_carousel']['ting_searches'][$key]),
        drupal_render($sort)
      ),
      'class' => $classes
    );
  }

  $table_vars = array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array('id' => 'ting-search-carousel-admin-sort'),
    'caption' => '',
    'colgroups' => array(),
    'sticky' => FALSE,
    'empty' => 'EMPTY'
  );
  $output = theme_table($table_vars);

  // Render remaining elements.
  $output .= drupal_render_children($form);

  return $output;
}

/**
 * Form part, describing query fields.
 *
 * @param $item
 *   Values for existing query.
 *
 * @return
 *   Fields structure.
 */
function ting_search_carousel_query_form($item = array(), $index = 0) {
  $form = array();

  $form['sort[]'] = array(
    '#type' => 'weight',
    '#delta' => 5,
    '#default_value' => 0,
    '#value' => 0,
    '#attributes' => array(
      'class' => array(
        'sort-hidden'
      )
    ),
  );

  $form['title[]'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#description' => t('The title of the search is used for the tab in the carousel. Keep it short.'),
    '#default_value' => isset($item['title']) ? $item['title'] : '',
    '#prefix' => '<div class="search-carousel-query">',
  );

  $form['subtitle[]'] = array(
    '#type' => 'textfield',
    '#title' => t('Description'),
    '#description' => t('The subtitle displayed next to the search results.'),
    '#default_value' => isset($item['subtitle']) ? $item['subtitle'] : '',
  );

  $form['query[]'] = array(
    '#type' => 'textfield',
    '#title' => t('Query'),
    '#maxlength' => 2048,
    '#description' => t('The query to display search results for.'),
    '#default_value' => isset($item['query']) ? $item['query'] : '',
  );

  $form['remove[]'] = array(
    '#type' => 'button',
    '#value' => t('Remove'),
    '#name' => 'remove_' . $index,
    '#attributes' => array(
      'class' => array(
        'remove'
      )
    ),
    '#suffix' => '</div><div class="clearfix"></div>',
    '#ajax' => array(
      'callback' => 'ting_search_carousel_admin_form_ajaxify',
      'wrapper' => 'ting-search-carousel-queries',
      'method' => 'replace',
      'effect' => 'fade'
    ),
  );

  return $form;
}

/**
 * Submit handler for admin backend queries form.
 *
 * @param $form
 *   Form.
 * @param $form_state
 *   Form state.
 */
function ting_search_carousel_search_submit($form, &$form_state) {
  $c = count($form_state['input']['title']);
  $searches = array();
  $search_items = array();

  for ($i = 0; $i < $c; $i++) {
    // Make an array for saving, ignoring queries w/o title.
    if (!empty($form_state['input']['title'][$i])) {
      $searches[] = array(
        'title' => $form_state['input']['title'][$i],
        'subtitle' => $form_state['input']['subtitle'][$i],
        'query' => $form_state['input']['query'][$i]
      );
    }
  }

  /**
   * @TODO: Add clear cache button and detect changes in the query input fields
   * so only partial cache can be rebuild. This will slow down the submit but
   * may speed up the presentation for the users by kick starting the cache.
   */

  // Save the queries as a persistent variable.
  variable_set('ting_carousel_search_queries', $searches);

  // Clear carousel search cache
  cache_clear_all('ting_search_carousel_result', 'cache');
}
