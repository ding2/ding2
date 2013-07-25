<?php
/**
 * @file
 * Create sub-menu based on taxonomy.
 */

$plugin = array(
  'title' => t('Ding taxonomy menu'),
  'description' => t('Generates links based on a taxonomy.'),
  'single' => TRUE,
  'edit form' => 'ding_frontend_taxonomy_menu_content_type_edit_form',
  'render callback' => 'ding_frontend_taxonomy_menu_content_type_render',
  'category' => t('Ding!'),
  'required context' => array(
    new ctools_context_required(t('Taxonomy term id'), array('term', 'taxonomy_term')),
    new ctools_context_optional(t('Library'), 'node'),
  ),
  'defaults' => array(
    'slug' => '',
    'default_link_text' => '',
  ),
);

/**
 * Implements hook_ID_content_type_render().
 */
function ding_frontend_taxonomy_menu_content_type_render($subtype, $conf, $panel_args, $context = NULL) {
  $block = new stdClass();
  $selected_term = FALSE;
  $items = array();

  // Set base path based on node context.
  $base = '';
  if (isset($context[1]->data)) {
    $node = $context[1]->data;
    $uri = entity_uri('node', $node);
    $base = drupal_lookup_path('alias', $uri['path']) . '/';
  }

  // If default link text is set.
  if (!empty($conf['default_link_text'])) {
    // If first context don't exists (tid not given) the the "All link" should be
    // used.
    $options = array('attributes' => array('class' => array('active')));
    if (isset($context[0]->data)) {
      $selected_term = $context[0]->data;
      $options = array();
    }
    $items[] = l(t($conf['default_link_text']), $base . $conf['slug'], $options);
  }

  // Find the vocabulary id based on context and load the terms.
  $vid = '';
  if (isset($context[0]->data)) {
    $vid = $context[0]->data->vid;
  }
  else {
    $vids = array_filter($context[0]->placeholder['conf']['vids']);
    $vid = reset($vids);
  }
  $terms = taxonomy_get_tree($vid);

  foreach ($terms as $term) {
    $alias = drupal_lookup_path('alias', 'taxonomy/term/' . $term->tid);

    $options = array('attributes' => array('class' => array('menu-item')));
    if ($selected_term && $selected_term->tid == $term->tid) {
      // Add active menu class.
      $options['attributes']['class'][] = 'active';
    }

    // Try to find the correct uri based on the context/configuration.
    $uri = $base . $conf['slug'] . '/' . $term->tid;
    if (!$base) {
      $uri = $conf['slug'] . '/' . $term->tid;
      if (isset($alias)) {
        $uri = $alias;
      }
    }
    $items[] = l($term->name, $uri, $options);
  }

  // Return render array with item list as theme function.
  $block->content = array(
    '#theme' => 'item_list',
    '#items' => $items,
    '#attributes' => array(
      'class' => array('sub-menu')
    ),
  );

  return $block;
}

/**
 * The settings form for default values.
 */
function ding_frontend_taxonomy_menu_content_type_edit_form($form, &$form_state) {
  $form['slug'] = array(
    '#type' => 'textfield',
    '#title' => t('Slug'),
    '#description' => t('The slug could be "arrangementer" or "nyheder" and will be inserted based on the context.'),
    '#required' => TRUE,
    '#default_value' => $form_state['conf']['slug'],
  );

  $form['default_link_text'] = array(
    '#type' => 'textfield',
    '#title' => t('Default link text'),
    '#description' => t('Text string to used as link text. If not given default link will be omited.'),
    '#required' => TRUE,
    '#default_value' => $form_state['conf']['default_link_text'],
  );

  return $form;
}

/**
 * Submit handler for the settings form.
 */
function ding_frontend_taxonomy_menu_content_type_edit_form_submit($form, &$form_state) {
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}

/**
 * Returns the administrative title for a type.
 */
function ding_frontend_taxonomy_menu_content_type_admin_title($subtype, $conf, $context) {
  return t('"@context" menu', array('@context' => $context[0]->identifier));
}