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
    foreach ($searches as $index => $search) {
      $chunk = ting_search_carousel_get_entities($search['query'], 0, TING_SEARCH_CAROUSEL_CHUNK_SIZE);

      $items = array();
      foreach ($chunk['entities'] as $entity) {
        $items[] = ting_object_view($entity, 'teaser');
      }

      $carousels[] = array(
        '#type' => 'ding_carousel',
        '#title' => $search['title'],
        '#path' => 'ting_search_carousel/results/ajax/' . urlencode($search['query']) . '/' . $index,
        '#items' => $items,
        '#offset' => $chunk['next_offset'],
        // Add a single placeholder to fetch more content later if there is more
        // content.
        '#placeholders' => $chunk['next_offset'] > -1 ? TING_SEARCH_CAROUSEL_CHUNK_SIZE + 1 : 0,
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

  // Hide the title override settings.
  $form['override_title']['#access'] = FALSE;
  $form['override_title_text']['#access'] = FALSE;
  $form['override_title_heading']['#access'] = FALSE;
  $form['override_title_markup']['#access'] = FALSE;

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
  // Pre-request first set of results so the caching will be done while form
  // submit and the client will not have to wait until those requests are
  // happening when page is opened.
  foreach ($searches as $search) {
    ting_search_carousel_get_entities($search['query'], 0, 8, FALSE);
  }
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
    'subtitle' => '',
    'query' => '',
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
 * No tabledrag, as it doesn't seem to like CTools popup window.
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
    // Pre-render elements we want to remove from the main part.
    $weight = drupal_render($form[$key]['weight']);
    $actions = drupal_render($form[$key]['remove']);
    $rows[] = array(
      'data' => array(
        $weight,
        drupal_render($form[$key]),
        $actions,
      ),
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

  return $output;
}
