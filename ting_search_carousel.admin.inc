<?php

/**
 * Rules editing page callback.
 *
 * Simple wrapper for the form, only required to add the JavaScript.
 */
function ting_search_carousel_admin_page() {
  drupal_add_js(drupal_get_path('module', 'ting_search_carousel'). '/js/ting_search_carousel.admin.js');
  drupal_add_css(drupal_get_path('module', 'ting_search_carousel'). '/css/ting_search_carousel.css');

  return drupal_get_form('ting_search_carousel_admin_form');
}


/**
 * Ting search carousel admin form.
 */
function ting_search_carousel_admin_form($form, &$form_state) {
  $searches = !empty($form_state['values']['num_searches']) ? $form_state['values']['num_searches'] : 0;

  $form['ting_search_carousel'] = array(
    '#type' => 'fieldset',
    '#title' => 'Searches',
    '#theme' => array('ting_search_carousel_admin_form'),
    '#prefix' => '<div id="ting-search-carousel-queries">',
    '#suffix' => '</div>'
  );

  $i = 0;
  $c = 1;
  for($i = 0; $i < 1; $i++) {
    $form['ting_search_carousel']['ting_searches']['search_' . $i] = ting_search_carousel_query_form();
  }

  for(; $i < $searches + $c; $i++) {
    $form['ting_search_carousel']['ting_searches']['search_' . $i] = ting_search_carousel_query_form();
  }

  $form['ting_search_carousel']['num_searches'] = array(
    '#type' => 'hidden',
    '#value' => $searches += 1,
  );

  $form['ting_search_carousel']['new_search_carousel_button'] = array(
    '#type' => 'button',
    '#value' => 'Add another',
    '#ajax' => array(
      'callback' => 'ting_search_carousel_add_query',
      'wrapper' => 'edit-new-search-carousel-button',
      'method' => 'before',
      'effect' => 'slide'
    ),
  );

  $form['ting_search_carousel']['ting_search_carousel_cache_duration'] = array(
    '#type' => 'select',
    '#title' => t('Cache duration'),
    '#description' => t('Determines how long search results in the carousel will be cached for.'),
    '#options' => array(
      3600 => t('1 hour'),
      10800 => t('3 hours'),
      43200 => t('12 hours'),
      86400 => t('1 day'),
      259200 => t('3 days'),
      604800 => t('7 days'),
      1209600 => t('2 weeks'),
      2592000 => t('1 month'),
    ),
    '#default_value' => variable_get('ting_search_carousel_cache_duration', 604800),
  );

  // Override submit, need to sort data before save
  $form['#submit'] = array('ting_search_carousel_search_submit');
  
  return system_settings_form($form);
}

function ting_search_carousel_add_query($form) {
  $c = count(element_children($form['ting_search_carousel']['ting_searches']));
  
  return $form['ting_search_carousel']['ting_searches']['search_' . ($c - 1)];
}

function theme_ting_search_carousel_admin_form($variables) {
  $form = $variables['form'];
  drupal_add_tabledrag('ting-search-carousel-admin-sort', 'order', 'sibling', 'sort');

  $header = array('Searches', '');
  $rows = array();
  foreach (element_children($form['ting_searches']) as $key) {
    // Add class to group weight fields for drag and drop.
    $form['ting_searches'][$key]['sort']['#attributes']['class'][] = 'sort';

    // Get sort element
    $sort = $form['ting_searches'][$key]['sort'];
    unset($form['ting_searches'][$key]['sort']);

    // Build rows
    $rows[] = array(
      'data' => array(
        drupal_render($form['ting_searches'][$key]),
        drupal_render($sort)
      ),
      'class' => array('draggable')
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

  $output .= drupal_render_children($form);

  return $output;
}


function ting_search_carousel_query_form($item = array()) {
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
    '#title' => t('subtitle'),
    '#description' => t('The subtitle displayed next to the search results'),
    '#default_value' => isset($item['subtitle']) ? $item['subtitle'] : '',
  );

  $form['query[]'] = array(
    '#type' => 'textfield',
    '#title' => t('Query'),
    '#maxlength' => 2048,
    '#description' => t('The query to display search results for'),
    '#default_value' => isset($item['query']) ? $item['query'] : '',
  );
  
  $form['remove[]'] = array(
    '#type' => 'button',
    '#submit' => FALSE,
    '#value' => t('Remove'),
    '#attributes' => array(
      'class' => array(
        'remove'
      )
    ),
    '#suffix' => '</div><div class="clear"></div>',
  );

  return $form;
}

/*
  This function is largely based on the poll module, its been simplified for reuse.
  $fields is the specific form elements you want to attach via ahah,
  $name is the form fields array key... e.g. the name for $form['title'] is "title"
*/
/*
function ting_search_carousel_form_ahah($form_state) {
  $form_state = array('submitted' => FALSE);
  $form_build_id = $_POST['form_build_id'];
  // Add the new element to the stored form. Without adding the element to the
  // form, Drupal is not aware of this new elements existence and will not
  // process it. We retreive the cached form, add the element, and resave.
  $form = form_get_cache($form_build_id, $form_state);

  // Delta is assigned to the count of current elements, so it'll be the
  // next in the zero-based list.
  $key = count(element_children($form['ting_search_carousel_searches']));
  $key++;

  $form['ting_search_carousel_searches'][$key] = array(
    '#type' => 'ting_search_carousel_search',
    '#sort' => 10,
  );
  form_set_cache($form_build_id, $form, $form_state);

  $form += array(
    '#post' => $_POST,
    '#programmed' => FALSE,
  );

  // Rebuild the form.
  $form = form_builder($_POST['form_id'], $form, $form_state);

  // Render and return the new field.
  drupal_json(array(
    'data' => drupal_render($form['ting_search_carousel_searches'][$key]),
    'status' => TRUE));
  exit();
}*/

function ting_search_carousel_search_submit($form, &$form_state) {
  var_dump($form_state['input']);die();
  /*foreach ($form_state['values']['ting_search_carousel_searches'] as $key => $val) {
    if (!$val['title']) {
      unset($form_state['values']['ting_search_carousel_searches'][$key]);
    }
  }
  // Sort searches, before saveing (preformance).
  usort($form_state['values']['ting_search_carousel_searches'], "ting_search_carousel_usort_cmp");

  // Return control to system settings form submit.
  system_settings_form_submit($form, &$form_state);*/
}

/**
 * Theme function for the admin form, enables drag and drop of form elements.
 *
 * @param array $form
 * @return string
 */


/**
 * Custom sort function, to sort form by weight (sort col.)
 *
 * @param array $a
 * @param array $b
 * @return <type>
 */
function ting_search_carousel_usort_cmp($a, $b) {
    if ($a['sort'] == $b['sort']) {
        return 0;
    }
    return ($a['sort'] < $b['sort']) ? -1 : 1;
}

function dump_it($v) {
  $f = drupal_get_path('module', 'ting_search_carousel') . '/dump.txt';
  $h = fopen($f, 'wt');
  ftruncate($h, 0);
  fwrite($h, print_r($v, TRUE));
  fclose($h);
}

