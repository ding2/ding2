<?php
/**
 * @file
 * Create sub-menu based on taxonomy.
 *
 * With example content added, this would etc create sub menus for the link
 * /arrangementer. These links would be build from event_category.
 * Every sub-menu is setup in Panels.
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
    new ctools_context_optional(t('Group'), 'node'),
  ),
  'defaults' => array(
    'slug' => '',
    'default_link_text' => t('All terms'),
    'dropdown' => FALSE,
    'vocabulary' => array(),
    'base' => '',
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
    // Set base path based on configuration.
    if (isset($conf['base'])) {
      $base = $conf['base'] . '/' . $node->nid . '/';
    }
    else {
      $uri = entity_uri('node', $node);
      $base = drupal_lookup_path('alias', $uri['path']) . '/';
    }
  }

  if (isset($context[0]->data)) {
    $selected_term = $context[0]->data;
  }

  // If default link text is set.
  if (!empty($conf['default_link_text'])) {
    $uri = drupal_get_path_alias($base . $conf['slug']);
    if ($conf['dropdown']) {
      $items[$uri] = t($conf['default_link_text']);
      $default_value = $uri;
    }
    else {
      // If first context don't exists (tid not given) the the "All link" should
      // have the active class. The context many no exists if no links in the
      // sub-menu have been clicked yet.
      $options = array('attributes' => array('class' => array('active')));
      if ($selected_term) {
        $options = array();
      }
      $items[] = l(t($conf['default_link_text']), $uri, $options);
    }
  }

  // Set block title.
  $vocab = taxonomy_vocabulary_machine_name_load($conf['vocabulary']);
  $terms = taxonomy_get_tree($vocab->vid);

  foreach ($terms as $term) {
    // Try to find the correct uri based on the context/configuration.
    $alias = drupal_lookup_path('alias', 'taxonomy/term/' . $term->tid);
    $uri = drupal_get_path_alias($base . $conf['slug'] . '/' . $term->tid);
    if (!$base) {
      $uri = $conf['slug'] . '/' . $term->tid;
      if (isset($alias)) {
        $uri = $alias;
      }
    }

    if ($conf['dropdown']) {
      // Build drop-down items.
      $items[$uri] = $term->name;
      if ($selected_term && $selected_term->tid == $term->tid) {
        $default_value = drupal_get_path_alias($uri);
      }
    }
    else {
      // Build links to use in item list.
      $options = array('attributes' => array('class' => array('menu-item')));
      if ($selected_term && $selected_term->tid == $term->tid) {
        // Add active menu class.
        $options['attributes']['class'][] = 'active';
      }
      $items[] = l($term->name, $uri, $options);
    }
  }

  // Use the items generated to format the block content.
  if ($conf['dropdown']) {
    $block->content = drupal_get_form('ding_frontend_taxonomy_menu_select_dropdown', $items, $default_value, t($vocab->name));
  }
  else {
    // Return render array with item list as theme function.
    $block->title = t($vocab->name);
    $block->content = array(
      '#theme' => 'item_list',
      '#items' => $items,
      '#attributes' => array(
        'class' => array(
          'sub-menu',
        ),
      ),
    );
  }

  return $block;
}

/**
 * Form which creates a select box with available taxonomy terms.
 */
function ding_frontend_taxonomy_menu_select_dropdown($form, &$form_state, $items, $default_value, $title) {
  $form = array(
    '#attributes' => array(
      'class' => array(
        'taxonomy-dropdown',
      ),
    ),
  );

  $form['select_term'] = array(
    '#type' => 'select',
    '#title' => check_plain($title),
    '#options' => $items,
    '#attributes' => array('onchange' => "form.submit('select_term');"),
    '#default_value' => $default_value,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#attributes' => array(
      'class' => array('button'),
      'style' => array('display: none;'),
    ),
    '#value' => t('Show'),
  );

  return $form;
}

/**
 * Submit handler for the taxonomy drop-down menu form.
 */
function ding_frontend_taxonomy_menu_select_dropdown_submit($form, &$form_state) {
  drupal_goto($form_state['values']['select_term']);
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

  $form['base'] = array(
    '#type' => 'textfield',
    '#title' => t('Base URL'),
    '#description' => t('Base URL used to create context in OG e.g. bibliotek, temaer.'),
    '#required' => FALSE,
    '#default_value' => $form_state['conf']['base'],
  );

  $form['default_link_text'] = array(
    '#type' => 'textfield',
    '#title' => t('Default link text'),
    '#description' => t('Text string to used as link text. If not given default link will be omited.'),
    '#required' => TRUE,
    '#default_value' => $form_state['conf']['default_link_text'],
  );

  $form['dropdown'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display as dropdown menu'),
    '#description' => t('Change the taxonomy into a dropdown select box.'),
    '#default_value' => $form_state['conf']['dropdown'],
  );

  $options = array();
  $vocabularies = taxonomy_vocabulary_get_names();
  foreach ($vocabularies as $vocabulary) {
    $options[$vocabulary->machine_name] = $vocabulary->name;
  }

  $form['vocabulary'] = array(
    '#type' => 'select',
    '#title' => t('Vocabulary'),
    '#description' => t('Select the vocabulary to use.'),
    '#options' => $options,
    '#default_value' => $form_state['conf']['vocabulary'],
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
