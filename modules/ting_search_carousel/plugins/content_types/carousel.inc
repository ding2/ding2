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
);

/**
 * Return the pane contents.
 */
function ting_search_carousel_carousel_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();
  $searches = $conf['ting_searches'];
  $hash = md5(drupal_json_encode($searches));

  if (!empty($searches)) {
    $carousels = array();
    foreach ($searches as $index => $search) {
      $chunk = _ting_search_carousel_get_frontpage_entities($index, 0, TING_SEARCH_CAROUSEL_CHUNK_SIZE, $hash, FALSE);

      $items = array();
      foreach ($chunk['entities'] as $entity) {
        $items[] = ting_object_view($entity, 'teaser');
      }

      $carousels[] = array(
        '#type' => 'ding_carousel',
        '#title' => $search['title'],
        '#path' => 'ting_search_carousel/results/ajax/' . $hash . '/' . $index,
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
      '#transition' => variable_get('ting_search_carousel_transition', 'fade'),
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
  module_load_include('module', 'ting_search_carousel', 'ting_search_carousel');

  $searches_num = !empty($form_state['values']['num_searches']) ? $form_state['values']['num_searches'] : 0;
  $clicked_btn = '';
  $hidden = array();

  if (isset($form_state['clicked_button'])) {
    $clicked_btn = $form_state['clicked_button']['#name'];

    // Get a clicked 'remove' button.
    foreach ($form_state['buttons'] as $k => $v) {
      if ($v['#name'] == $clicked_btn) {
        if (preg_match('/edit-remove/', $v['#id'])) {
          $clicked_btn = explode('_', $clicked_btn);
          $hidden[] = $clicked_btn[1];
          break;
        }
      }
    }
  }

  $form['ting_search_carousel'] = array(
    '#type' => 'fieldset',
    '#title' => 'Searches',
    '#prefix' => '<div id="ting-search-carousel-queries">',
    '#suffix' => '</div>',
    '#theme' => array('ting_search_carousel_admin_form'),
  );

  // Get current saved queries.
  $searches = $form_state['pane']->configuration['ting_searches'];
  $conf = $form_state['pane']->configuration['settings'];

  $index = 0;
  $count = 1;

  // Display saved queries.
  if (isset($searches[0]['title'])) {
    $count = count($searches);
    for (; $index < $count; $index++) {
      $form['ting_search_carousel']['ting_searches']['search_' . $index] = ting_search_carousel_query_form($searches[$index], $index);
    }
  }

  // Whether add a new query field.
  if ($clicked_btn == 'add_query') {
    $searches_num++;
  }

  for (; $index < $searches_num + $count; $index++) {
    $unsubmitted = array();
    // Maybe prev field had some data in it...
    if (isset($form_state['input']['title'][$index])) {
      $unsubmitted = array(
        'title' => $form_state['input']['title'][$index],
        'subtitle' => $form_state['input']['subtitle'][$index],
        'query' => $form_state['input']['query'][$index],
      );
    }

    $form['ting_search_carousel']['ting_searches']['search_' . $index] = ting_search_carousel_query_form($unsubmitted, $index);
  }

  // Hide removed fields.
  for ($index = 0; $index <= $searches_num + $count; $index++) {
    if (in_array($index, $hidden)) {
      // Hide title, used to sort needed queries when saving.
      $form['ting_search_carousel']['ting_searches']['search_' . $index]['title[]']['#value'] = '';
      $form['ting_search_carousel']['ting_searches']['search_' . $index]['#prefix'] = '<div style="display: none;">';
      $form['ting_search_carousel']['ting_searches']['search_' . $index]['#suffix'] = '</div>';
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
      'effect' => 'fade',
    ),
  );

  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Frontend settings'),
  );

  $form['settings']['ting_search_carousel_description_toggle'] = array(
    '#title' => t('Show descriptions for navigational tabs'),
    '#type' => 'checkbox',
    '#default_value' => isset($conf['ting_search_carousel_description_toggle']) ? $conf['ting_search_carousel_description_toggle'] : 0,
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
    '#default_value' => isset($conf['ting_search_carousel_transition']) ? $conf['ting_search_carousel_transition'] : 'fade',
    '#description' => t('The JS transition used when switching tabs. This applies to the front page carousel.'),
  );

  return $form;
}

/**
 * Panel pane configuration form submit handler.
 */
function ting_search_carousel_carousel_content_type_edit_form_submit(&$form, &$form_state) {
  $count = count($form_state['input']['title']);
  $searches = array();

  for ($i = 0; $i < $count; $i++) {
    // Make an array for saving, ignoring queries w/o title.
    if (!empty($form_state['input']['title'][$i])) {
      $searches[] = array(
        'title' => $form_state['input']['title'][$i],
        'subtitle' => $form_state['input']['subtitle'][$i],
        'query' => $form_state['input']['query'][$i],
      );
    }
  }

  $settings = array(
    'ting_search_carousel_description_toggle' => $form_state['input']['ting_search_carousel_description_toggle'],
    'ting_search_carousel_transition' => $form_state['input']['ting_search_carousel_transition'],
  );

  $form_state['conf'] = array(
    'ting_searches' => $searches,
    'settings' => $settings,
  );

  // Pre-request first set of results so the caching will be done while form
  // submit and the client will not have to wait until those requests are
  // happening when page is opened.
  foreach ($searches as $index => $search) {
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
function ting_search_carousel_query_form($item = array(), $index = 0) {
  $form = array();

  $form['sort[]'] = array(
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
        'remove',
      ),
    ),
    '#suffix' => '</div><div class="clearfix"></div>',
    '#ajax' => array(
      'callback' => 'ting_search_carousel_admin_form_ajaxify',
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
function ting_search_carousel_admin_form_ajaxify(array $form, array &$form_state) {
  return $form['ting_search_carousel'];
}
