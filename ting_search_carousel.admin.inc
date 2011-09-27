<?php

/**
 * Rules editing page callback.
 *
 * Simple wrapper for the form, only required to add the JavaScript.
 */
function ting_search_carousel_admin_page() {
  // Use the admin module's theme if available.
  /*if (function_exists('_admin_init_theme')) {
    _admin_init_theme();
  }*/

  drupal_add_js(drupal_get_path('module', 'ting_search_carousel'). '/js/ting_search_carousel.admin.js');
  drupal_add_css(drupal_get_path('module', 'ting_search_carousel'). '/css/ting_search_carousel.css');

  return drupal_get_form('ting_search_carousel_admin_form');
}


/**
 * Ting search carousel admin form.
 */
function ting_search_carousel_admin_form($form, &$form_state) {
  $form['ting_search_carousel'] = array(
    '#type' => 'fieldset',
    '#title' => 'Searches',
    '#attributes' => array('id' => 'ting-search-carousels'),
    '#theme' => array('ting_search_carousel_admin_form'),
  );

  $searches = variable_get('searches', array());

  if ($searches) {
    foreach ($searches as $key => $search) {
      // Filter out searches with empty title. Previous versions created
      // those, left here for compatibility.
    	if ($search['title']) {
	      $form['ting_search_carousel']['searches'][$key] = ting_search_carousel_query_form();
    	}
    }
  }
  else {
    $form['ting_search_carousel']['searches'][0] = ting_search_carousel_query_form();
  }

  $form['ting_search_carousel']['new_search_carousel_button'] = array(
    '#type' => 'button',
    '#value' => 'Add another',
    '#ahah' => array(
      'path' => 'admin/settings/ting_search_carousel/form/ahah',
      'wrapper' => 'add-another-fields',
      'method' => 'append',
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
  //$form['#submit'] = array('ting_search_carousel_search_submit');
  
  return system_settings_form($form);
}


function theme_ting_search_carousel_admin_form($variables) {
  $form = $variables['form'];
  drupal_add_tabledrag('ting-search-carousel-admin-sort', 'order', 'sibling', 'sort');

  $header = array('', 'Searches');
  $rows = array();
  foreach (element_children($form['searches']) as $key) {
    // Add class to group weight fields for drag and drop.
    $form['searches'][$key]['sort']['#attributes']['class'][] = 'sort';

    // Get sort element
    $sort = $form['searches'][$key]['sort'];
    unset($form['searches'][$key]['sort']);

    // Build rows
    $rows[] = array(
      'data' => array(
        drupal_render($form['searches'][$key]),
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
    'empty' => 'FUCK U!'
  );
  $output = theme_table($table_vars);

  // Add placeholder for ahah objects
  $output .= '<div id="add-another-fields" class="clear-block">' . drupal_render($form['new_search_carousel_button']) . '</div>';

  $output .= drupal_render_children($form);

  return $output;
}


function ting_search_carousel_query_form() {
  $form = array();

  $form['sort'] = array(
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

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#description' => t('The title of the search is used for the tab in the carousel. Keep it short.'),
    '#default_value' => '',
  );

  $form['subtitle'] = array(
    '#type' => 'textfield',
    '#title' => t('subtitle'),
    '#description' => t('The subtitle displayed next to the search results'),
    '#default_value' => '',
  );

  $form['query'] = array(
    '#type' => 'textfield',
    '#title' => t('Query'),
    '#maxlength' => 2048,
    '#description' => t('The query to display search results for'),
    '#default_value' => '',
  );
  
  $form['remove'] = array(
    '#type' => 'button',
    '#submit' => FALSE,
    '#value' => t('Remove'),
    '#attributes' => array(
      'class' => array(
        'remove'
      )
    )
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

/*
function ting_search_carousel_search_submit($form, &$form_state) {
  foreach ($form_state['values']['ting_search_carousel_searches'] as $key => $val) {
    if (!$val['title']) {
      unset($form_state['values']['ting_search_carousel_searches'][$key]);
    }
  }
  // Sort searches, before saveing (preformance).
  usort($form_state['values']['ting_search_carousel_searches'], "ting_search_carousel_usort_cmp");

  // Return control to system settings form submit.
  system_settings_form_submit($form, &$form_state);
}
*/
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

