<?php

/**
 * @file
 * Provides search results as a Panels content type.
 */

$plugin = array(
  'title' => t('Ting search carousel'),
  'single' => TRUE,
  'description' => t('A carousel displaying search results against the data well'),
  'category' => t('Ting'),
  'hook theme' => 'ting_search_carousel_carousel_content_type_theme',
);

/**
 * Return the pane contents.
 */
function ting_search_carousel_carousel_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  if (!isset($conf['searches'])) {
    return $block;
  }
  $searches = $conf['searches'];

  if (!empty($searches)) {
    $carousels = array();
    foreach ($searches as $search) {
      $search += array(
        'title' => '',
        'query' => '',
        'sort' => '',
        'available' => '',
      );
      $query = new TingSearchCarouselQuery($search['query'], $search['sort'], $search['available']);

      $carousels[] = array(
        '#type' => 'ding_carousel',
        '#title' => $search['title'],
        '#path' => ting_search_carousel_ajax_path($query),
        // Start without any covers, but load them all via AJAX. This eliminates
        // rendering covers and hitting the availability service, which slows
        // down page rendering.
        '#items' => [],
        '#offset' => 0,
        // Add placeholders instead.
        '#placeholders' => TING_SEARCH_CAROUSEL_CHUNK_SIZE,
      );
    }

    $block->content = array(
      '#type' => 'ding_tabbed_carousel',
      '#tabs' => $carousels,
      '#transition' => $conf['settings']['transition'],
    );
  }

  return $block;
}

/**
 * Return the pane titles.
 */
function ting_search_carousel_carousel_content_type_admin_title($subtype, $conf, $context) {
  return t('Ting search carousel');
}

/**
 * Panel pane configuration form.
 */
function ting_search_carousel_carousel_content_type_edit_form($form, &$form_state) {
  ctools_form_include($form_state, 'carousel', 'ting_search_carousel', 'plugins/content_types');

  // Add defoults.
  $form_state['conf'] += array(
    'searches' => array(),
    'settings' => array(
      'transition' => 'fade',
    ),
  );
  ctools_form_include($form_state, 'carousel', 'ting_search_carousel', 'plugins/content_types');
  module_load_include('module', 'ting_search_carousel');

  $form['searches'] = array(
    '#type' => 'fieldset',
    '#title' => 'Searches',
    '#prefix' => '<div id="ting-search-carousel-queries">',
    '#suffix' => '</div>',
    '#theme' => array('ting_search_carousel_admin_form'),
    '#tree' => TRUE,
  );
  $i = 0;
  foreach ($form_state['conf']['searches'] as $search) {
    // Removed searches are replaced with null values, in order to retain the
    // indexing between form rebuilds.
    if ($search) {
      $form['searches'][$i] = ting_search_carousel_query_form($search, $i);
    }
    $i++;
  }

  $form['add_more'] = array(
    '#type' => 'submit',
    '#value' => t('Add one more'),
    '#submit' => array('ting_search_carousel_admin_form_add_one'),
    '#ajax' => array(
      'callback' => 'ting_search_carousel_admin_form_callback',
      'wrapper' => 'ting-search-carousel-queries',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Frontend settings'),
    '#tree' => TRUE,
  );

  $transitions = array();
  foreach (ding_carousel_transitions() as $name => $transition) {
    $transitions[$name] = $transition['name'];
  }

  $form['settings']['transition'] = array(
    '#title' => t('Tab switching transition'),
    '#type' => 'select',
    '#options' => $transitions,
    '#default_value' => isset($form_state['conf']['transition']) ? $form_state['conf']['transition'] : 'fade',
    '#description' => t('The JS transition used when switching tabs.'),
  );

  return $form;
}

/**
 * Panel pane configuration form validate handler.
 */
function ting_search_carousel_carousel_content_type_edit_form_validate(&$form, &$form_state) {
  foreach ($form_state['values']['searches'] as $index => $search) {
    $query = new TingSearchCarouselQuery($search['query'], $search['sort']);
    $path = ting_search_carousel_ajax_path($query);
    if (strlen($path) > 2048) {
      form_error($form['searches'][$index]['query'], t('Search string too long. Please limit the lenght.'));
    }
  }
}

/**
 * Panel pane configuration form submit handler.
 */
function ting_search_carousel_carousel_content_type_edit_form_submit(&$form, &$form_state) {
  $sorted = $form_state['values']['searches'];
  uasort($sorted, 'drupal_sort_weight');

  $searches = array();
  foreach ($sorted as $search) {
    if (!empty($search['title'])) {
      unset($search['weight'], $search['remove']);
      $searches[] = $search;
    }
  }
  $form_state['conf']['searches'] = $searches;
  $form_state['conf']['settings'] = $form_state['values']['settings'];
}

/**
 * Form part, describing query fields.
 *
 * @param array $item
 *   Values for existing query.
 *
 * @return array
 *   Fields structure.
 */
function ting_search_carousel_query_form(array $item = array(), $index = 0) {
  $form = array();

  $sort_options = array();

  foreach (ting_search_sort_options() as $name => $sort) {
    $sort_options[$name] = $sort['label'];
  }

  $form['weight'] = array(
    '#type' => 'weight',
    '#delta' => 10,
    '#default_value' => $index,
  );

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#description' => t('The title of the search is used for the tab in the carousel. Keep it short.'),
    '#default_value' => isset($item['title']) ? $item['title'] : '',
  );

  $form['query'] = array(
    '#type' => 'textfield',
    '#title' => t('Query'),
    '#maxlength' => 2048,
    '#description' => t('The query to display search results for.'),
    '#default_value' => isset($item['query']) ? $item['query'] : '',
  );

  $form['sort'] = array(
    '#type' => 'select',
    '#title' => t('Sort'),
    '#options' => $sort_options,
    '#description' => t('The sort order to use.'),
    '#default_value' => isset($item['sort']) ? $item['sort'] : '',
  );

  $form['available'] = array(
    '#type' => 'checkbox',
    '#title' => t('Only show available materials'),
    '#description' => t('Filter out unavailable materials when rendering carousel.'),
    '#default_value' => isset($item['available']) ? $item['available'] : '',
  );

  $form['remove'] = array(
    '#type' => 'submit',
    '#value' => t('Remove'),
    '#remove_index' => $index,
    '#name' => 'remove_' . $index,
    '#attributes' => array(
      'class' => array(
        'remove',
      ),
    ),
    '#submit' => array('ting_search_carousel_admin_form_remove'),
    '#ajax' => array(
      'callback' => 'ting_search_carousel_admin_form_callback',
      'wrapper' => 'ting-search-carousel-queries',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  return $form;
}

/**
 * AJAX responder for field addition/removal fields.
 *
 * @param array $form
 *   Form.
 *
 * @return array
 *   Changed field to be updated.
 */
function ting_search_carousel_admin_form_callback(array $form, array &$form_state) {
  return $form['searches'];
}

/**
 * AJAX callback for adding searches.
 */
function ting_search_carousel_admin_form_add_one($form, &$form_state) {
  $form_state['conf']['searches'][] = array(
    'title' => '',
    'query' => '',
    'sort' => '',
    'available' => 0,
  );
  $form_state['rebuild'] = TRUE;
}

/**
 * AJAX callback for removing searches.
 */
function ting_search_carousel_admin_form_remove($form, &$form_state) {
  if (isset($form_state['triggering_element']['#remove_index'])) {
    $index = $form_state['triggering_element']['#remove_index'];
    $form_state['conf']['searches'][$index] = NULL;
  }
  $form_state['rebuild'] = TRUE;
}

/**
 * Hook theme for this content type.
 */
function ting_search_carousel_carousel_content_type_theme(&$theme, $plugin) {
  $theme['ting_search_carousel_admin_form'] = array(
    'render element' => 'form',
  );
}

/**
 * Theme the queries form in a table.
 *
 * @param array $variables
 *   Theme related variables.
 *
 * @return string
 *   Themed form output.
 */
function theme_ting_search_carousel_admin_form(array $variables) {
  $form = $variables['form'];

  $header = array(t('Weight'), t('Search'), t('Operations'));
  $rows = array();
  foreach (element_children($form) as $key) {
    $form[$key]['weight']['#attributes']['class'] = array('ting-search-carousel-element-weight');
    // Pre-render elements we want to remove from the main part.
    $weight = drupal_render($form[$key]['weight']);
    $actions = drupal_render($form[$key]['remove']);
    $rows[] = array(
      'data' => array(
        drupal_render($form[$key]),
        $weight,
        $actions,
      ),
      'class' => array('draggable'),
    );
  }

  $table = array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array('id' => 'ting-search-carousel-admin-sort'),
    'sticky' => TRUE,
  );
  $output = theme('table', $table);

  // Render remaining elements.
  $output .= drupal_render_children($form);

  drupal_add_tabledrag('ting-search-carousel-admin-sort', 'order', 'sibling', 'ting-search-carousel-element-weight');

  return $output;
}
