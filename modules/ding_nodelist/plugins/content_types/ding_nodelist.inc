<?php

/**
 * @file
 * Ctools plugin definition file.
 */

define('DING_NODELIST_LIST_TYPE_DYNAMIC', 'custom-dynamic');
define('DING_NODELIST_LIST_TYPE_ALL', 'all');
define('DING_NODELIST_SORT_BY_CREATION_DATE', 'created');
define('DING_NODELIST_SORT_BY_TITLE', 'title');
define('DING_NODELIST_SORT_BY_STICKY', 'sticky');
define('DING_NODELIST_SORT_ASCENDING', 'asc');
define('DING_NODELIST_SORT_DESCENDING', 'desc');
/**
 * General ctools plugin settings.
 */
$plugin = array(
  'title' => t('Nodelist'),
  'category' => t('Ding!'),
  'description' => t('Allows to create highly customizable list of contents'),
  'single' => TRUE,
  'content_types' => 'ding_nodelist_content_type',
  'render callback' => 'ding_nodelist_content_type_render',
  'admin title' => 'ding_nodelist_content_type_admin_title',
  'admin info' => 'ding_nodelist_content_type_admin_info',
  'edit form' => 'ding_nodelist_content_type_edit_form',
);

/**
 * Run-time rendering of the body of the list.
 */
function ding_nodelist_content_type_render($subtype, $conf, $args, $context) {
  $block = new stdClass();

  // Prepare classes for widget container.
  $columns = $conf['columns'];
  $classes = array();
  $classes[] = 'ding_nodelist';
  $classes[] = 'ding_nodelist-' . $conf['widget_type'];
  $classes[] = 'ding_nodelist-col-' . $columns;
  $classes[] = $conf['unique_id'];

  // Build title.
  $title = NULL;
  if (!empty($conf['override_title_text'])) {
    $title = t('!title', array('!title' => check_plain($conf['override_title_text'])));
  }

  // Create proper layout for variable-width lists.
  $map = _ding_nodelist_get_column_map();
  $columns_layout = &drupal_static('ding_nodelist_cols', 0);
  if (!$columns_layout) {
    $classes[] = 'ding_nodelist-col-first';
    $columns_layout += $map[$columns];
  }
  else {
    // Maximum of 4 sub-columns is reached.
    $expected_width = $columns_layout + $map[$columns];
    if ($expected_width == 1) {
      $classes[] = 'ding_nodelist-col-last';
      $columns_layout = 0;
    }
    else {
      $columns_layout += $map[$columns];
    }
  }

  // Load default CSS.
  $uri = 'public://nodelist_colored_css/ding_nodelist.css';
  drupal_add_css($uri, 'file');

  // Fetch content IDs.
  $nids = _ding_nodelist_get_custom_list_nodes($conf);

  // Check if dynamic nodes must be loaded.
  $custom_content = !empty($conf['selected_nodes']);
  $dynamic_content = !empty($conf['taxonomy_filters']);
  $only_custom_content = (($custom_content == TRUE) && ($dynamic_content == FALSE));
  if (!$only_custom_content) {
    $nids = array_merge($nids, _ding_nodelist_get_dynamic_list_nodes($conf));
  }
  // Limit items on widgets.
  if ($conf['limit']) {
    $nids = array_slice($nids, 0, $conf['limit']);
  }

  // Load items by their IDs.
  $nodes = node_load_multiple($nids);

  if (count($nodes) > 0) {
    // Apply sorting.
    $nodes = _ding_nodelist_sort_nodes($nodes, $conf);
    $nodes = _ding_nodelist_striptags($nodes);

    $trimmed_widgets = _ding_nodelist_widgets_content_trim();
    if (in_array($conf['widget_type'], $trimmed_widgets)) {
      $nodes = _ding_nodelist_trim_fields($nodes, $conf);
    }
  }

  foreach ($nodes as $node) {
    if (is_array($node)) {
      $node = array_shift($node);
    }
    $node->item_template = 'ding_nodelist.' . $node->type . '.' . $conf['widget_type'];
    $field = "field_{$node->type}_list_image";
    if (!empty($node->{$field})) {
      $media_field = field_view_field('node', $node, $field);
      if ($media_field['#items'][0]['type'] == 'video') {
        $node->video = file_create_url($media_field['#items'][0]['uri']);
      }
    }
  }

  // Init JS for widgets.
  _ding_nodelist_add_js($conf['widget_type'], $conf['autoscroll_delay'], $conf['unique_id']);

  // Ensure that slick library is loaded properly.
  if ($conf['widget_type'] == 'carousel' && libraries_detect('slick')) {
    libraries_load('slick');
  }
  $theme_func = 'ding_nodelist_widget_' . $conf['widget_type'];

  $block->content = theme($theme_func, array(
    'items' => $nodes,
    'links' => $conf['more_links'],
    'conf' => array(
      'title' => $title,
      'classes' => implode(' ', $classes),
      'image_style' => _ding_nodelist_init_image_style($conf['widget_type']),
      'sorting' => $conf['sort_field'],
      'image_field' => !empty($conf['image_field']) ? $conf['image_field'] : '',
      'unique_id' => $conf['unique_id'],
    ),
  ));

  return $block;
}

/**
 * Ctools admin view pane's title.
 */
function ding_nodelist_content_type_admin_title($subtype, $conf, $context = NULL) {
  if (!empty($conf['override_title_text'])) {
    $output = t('Nodelist: @override_title_text', array('@override_title_text' => filter_xss_admin($conf['override_title_text'])));
  }
  else {
    $output = t('Nodelist (untitled)');
  }
  return $output;
}

/**
 * Callback to provide admin info (the preview in panels when building a panel).
 */
function ding_nodelist_content_type_admin_info($subtype, $conf, $context = NULL) {
  $block = new stdClass();

  // Get widget type for current pane.
  $widget_type = $conf['widget_type'];

  // Get active content types for current pane.
  $nodelist_content_types = $conf['content_types'];
  $nodelist_cts_names = node_type_get_names();
  $available_name = array_intersect_key($nodelist_content_types, $nodelist_cts_names);

  $items = array();
  foreach ($available_name as $item) {
    $items[] = $nodelist_cts_names[$item];
  }

  // Return rendered list of active content types.
  $returned_cts = theme('item_list', array('items' => $items));

  // Forming content of the block.
  $info = t('Displaying <strong>@widget_type</strong> widget for: !returned_cts content type(s).',
    array(
      '@widget_type' => $widget_type,
      '!returned_cts' => $returned_cts,
    )
  );

  $block->title = t('Nodelist @widget_type widget', array('@widget_type' => $widget_type));
  $block->content = $info;
  return $block;
}

/**
 * Ctools plugin callback for settings form.
 */
function ding_nodelist_content_type_edit_form($form, &$form_state) {
  form_load_include($form_state, 'inc', 'ding_nodelist', 'plugins/content_types/ding_nodelist');

  drupal_add_css(drupal_get_path('module', 'ding_nodelist') . '/css/ding_nodelist-admin.css', 'file');

  // Cache the form for correct workflow.
  $form_state['cache'] = TRUE;

  // Save original form to restore it later.
  // @todo: remove this workaround code and find ctools/drupal-way approach.
  if (!isset($form_state['restore'])) {
    $form_state['original_form'] = $form;
  }

  $trigger = !empty($form_state['triggering_element']) ? $form_state['triggering_element'] : NULL;

  // CT/widget select change handlers.
  // Process them first since they affect the rest of the form.
  if ($trigger) {
    if ($trigger['#name'] == 'content_type') {
      // Refresh CT setting.
      $node_type = $form_state['triggering_element']['#value'];

      // Reset other form values.
      $form_state['values']['content_type'] = $node_type;
      $form_state['values']['selected_nodes'] = array();
      $form_state['values']['widget_type'] = '';
      $form_state['values']['taxonomy_filters'] = array();
      unset($form_state['input']);
      _ding_nodelist_content_type_form_save($form_state, TRUE);
    }
    elseif ($trigger['#name'] == 'widget_type') {
      $node_type = $form_state['values']['content_type'];
      // Reset default scrolling delay.
      unset($form_state['input']['autoscroll_delay']);
      $form_state['values']['autoscroll_delay'] = '';

      _ding_nodelist_content_type_form_save($form_state, TRUE);
    }
  }

  $conf = $form_state['conf'];

  // Show only allowed content types.
  $node_types = variable_get('ding_nodelist_node_types', array());
  $all_node_types = node_type_get_names();
  $node_types_opts = array();
  foreach ($node_types as $nt => $active) {
    if ($active) {
      $node_types_opts[$nt] = $all_node_types[$nt];
    }
  }

  if (empty($node_types_opts)) {
    drupal_set_message(t('No eligible content types were found, please configure a few first.'), 'error', FALSE);
  }

  $node_type = array();
  if (isset($conf['content_types']) && !isset($form_state['values']['content_types'])) {
    $node_type = $conf['content_types'];
  }
  elseif (isset($form_state['values']['content_types'])) {
    $node_type = $form_state['values']['content_types'];
  }
  else {
    $node_type = array_keys($node_types_opts);
  }

  $default_conf = array(
    'content_type' => $node_type,
    'widget_type' => DING_NODELIST_WIDGET_CAROUSEL,
    'columns' => DING_NODELIST_COL_FULL,
    'sort_field' => DING_NODELIST_SORT_BY_CREATION_DATE,
    'limit' => 5,
    'more_text' => t('More'),
    'more_link' => '',
    'teaser_length' => 100,
    'autoscroll_delay' => 3000,
  );

  $form['#prefix'] = '<div id="ding_nodelist-form-wrapper">';
  $form['#suffix'] = '</div>';

  // Initial settings.
  $form['ding_nodelist_wrapper'] = array(
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#tree' => FALSE,
    '#title' => t('Configure nodelist'),
  );

  _ding_nodelist_plugin_content_types($form, $node_type, $node_types_opts);

  _ding_nodelist_plugin_widget_section($form, $node_type, $conf, $default_conf);

  _ding_nodelist_plugin_content_section($form, $form_state, $node_type, $conf, $node_types_opts);

  _ding_nodelist_plugin_various_section($form, $node_type, $conf, $default_conf);

  _ding_nodelist_plugin_bottom_links_section($form, $form_state, $conf);

  _ding_nodelist_plugin_cache_section($form, $form_state);

  // Restore other form elements if this is not the first form display.
  if (isset($form_state['restore'])) {
    $form = array_merge($form_state['original_form'], $form);
  }

  // Forcing form know which validation handler to use.
  $form['#validate'][] = 'ding_nodelist_content_type_edit_form_validate';

  return $form;
}

/**
 * Edit form validation function.
 */
function ding_nodelist_content_type_edit_form_validate($form, &$form_state) {
  $form_state['restore'] = TRUE;
  // Do not validate if filter was changed or deleted.
  $te = empty($form_state['triggering_element']) ? NULL : $form_state['triggering_element'];
  if (strpos($te['#name'], 'widget_type') === 0 || $te['#name'] == 'filter_field') {
    return;
  }

  $list_type = $form_state['values']['list_type'];
  if ($list_type === DING_NODELIST_LIST_TYPE_DYNAMIC) {
    $node_switch = isset($form_state['values']['nodes_switch']) ? $form_state['values']['nodes_switch'] : 0;
    $dynamic_switch = isset($form_state['values']['dynamic_switch']) ? $form_state['values']['dynamic_switch'] : 0;

    if (!$node_switch && !$dynamic_switch) {
      form_set_error('', t('Select at least one content pick rule (custom and/or dynamic).'));
    }
    else {
      // Check for empty nodes.
      if (!empty($form_state['values']['selected_nodes']) && $form_state['values']['nodes_switch']) {
        $node_cnt = count($form_state['values']['selected_nodes']);
        foreach ($form_state['values']['selected_nodes'] as $key => $node) {
          if ($te['#name'] == 'add_node' || $te['#value'] === 'Finish' || $node_cnt > 1) {
            if (empty($node['node'])) {
              form_set_error("selected_nodes][$key", t('No custom list content specified.'));
            }
          }
        }
      }

      // Check for empty filters.
      if (!empty($form_state['values']['taxonomy_filters']) && $form_state['values']['dynamic_switch']) {
        $filter_cnt = count($form_state['values']['taxonomy_filters']);
        foreach ($form_state['values']['taxonomy_filters'] as $key => $filter) {
          if ($te['#name'] == 'add_filter' || $te['#value'] === 'Finish' || $filter_cnt > 1) {
            if (empty($filter['filter_terms'])) {
              form_set_error("taxonomy_filters][$key][filter_terms", t('No terms specified for dynamic list filter.'));
            }
          }
        }
      }
    }
  }

  // Check if the link is valid.
  foreach ($form_state['values']['more_links'] as $key => &$bottom) {
    if (!empty($bottom['text']) || !empty($bottom['links'])) {
      if (!_ding_nodelist_is_valid_link($bottom['links'])) {
        $msg = t('Invalid local or external link. External links must begin with "http" or "https", local links should point to existing pages.');
        form_set_error("more_links][$key][links", $msg);
      }
    }
  }
}

/**
 * Edit form submit function.
 */
function ding_nodelist_content_type_edit_form_submit($form, $form_state) {
  foreach ($form_state['values']['content_types'] as $ct_name => $selected) {
    if (!$selected) {
      unset($form_state['values']['content_types'][$ct_name]);
    }
  }

  // Removing empty nodes.
  if (!empty($form_state['values']['selected_nodes'])) {
    foreach ($form_state['values']['selected_nodes'] as $key => $node) {
      if (empty($node['node'])) {
        unset($form_state['values']['selected_nodes'][$key]);
      }
      else {
        _ding_nodelist_get_node_nid($key, $node, $form_state);
      }
    }
  }

  // Removing empty filters.
  if (!empty($form_state['values']['taxonomy_filters'])) {
    foreach ($form_state['values']['taxonomy_filters'] as $key => $filter) {
      if (empty($filter['filter_terms'])) {
        unset($form_state['values']['taxonomy_filters'][$key]);
      }
    }
  }

  // Check if there are any empty links.
  if (!empty($form_state['values']['more_links'])) {
    foreach ($form_state['values']['more_links'] as $key => &$bottom) {
      if (empty($bottom['text']) || empty($bottom['links'])) {
        unset($form_state['values']['more_links'][$key]);
      }
      // Trim slashes.
      $bottom['links'] = ltrim($bottom['links'], '/');
    }
  }

  // Anything in $form_state['conf'] will be saved automatically.
  _ding_nodelist_content_type_form_save($form_state);
}

/**
 * Save CT plugin form values.
 */
function _ding_nodelist_content_type_form_save(&$form_state, $rebuild = FALSE) {
  $form_state['conf']['list_type'] = $form_state['values']['list_type'];
  $form_state['conf']['title_length'] = !empty($form_state['values']['title_length']) ? $form_state['values']['title_length'] : DING_NODELIST_TITLE_SIZE;
  $form_state['conf']['body_length'] = !empty($form_state['values']['body_length']) ? $form_state['values']['body_length'] : DING_NODELIST_BODY_SIZE;
  $form_state['conf']['dynamic_switch'] = ($form_state['conf']['list_type'] === DING_NODELIST_LIST_TYPE_DYNAMIC) ? $form_state['values']['dynamic_switch'] : 0;
  $form_state['conf']['nodes_switch'] = ($form_state['conf']['list_type'] === DING_NODELIST_LIST_TYPE_DYNAMIC) ? $form_state['values']['nodes_switch'] : 0;

  $form_state['conf']['autoscroll_delay'] = $form_state['values']['autoscroll_delay'];
  $form_state['conf']['columns'] = $form_state['values']['columns'];
  $form_state['conf']['content_filter_promoted'] = $form_state['values']['content_filter_promoted'];
  $form_state['conf']['content_filter_date'] = $form_state['values']['content_filter_date'];
  $form_state['conf']['content_types'] = $form_state['values']['content_types'];

  $form_state['conf']['limit'] = $form_state['values']['limit'];
  $form_state['conf']['more_links'] = !empty($form_state['values']['more_links']) ? $form_state['values']['more_links'] : array();
  $form_state['conf']['override_title_text'] = $form_state['values']['override_title_text'];
  $form_state['conf']['selected_nodes'] = !empty($form_state['values']['selected_nodes']) && $form_state['conf']['nodes_switch'] ? $form_state['values']['selected_nodes'] : array();
  $form_state['conf']['sort_field'] = $form_state['values']['sort_field'];
  $form_state['conf']['sort_order'] = $form_state['values']['sort_order'];
  $form_state['conf']['taxonomy_filters'] = !empty($form_state['values']['taxonomy_filters']) && $form_state['conf']['dynamic_switch'] ? $form_state['values']['taxonomy_filters'] : array();
  $form_state['conf']['unique_id'] = 'pane-' . (microtime(TRUE) * 10000);
  $form_state['conf']['widget_type'] = $form_state['values']['widget_type'];

  if ($form_state['values']['widget_type'] == DING_NODELIST_WIDGET_PROMOTED_NODES) {
    $form_state['conf']['limit'] = 4;
  }

  // @todo
  // As for now the template config is still there, so here we fetch the very
  // first assigned template.
  $item_templates = _ding_nodelist_get_templates(FALSE, $form_state['values']['content_types'], $form_state['conf']['widget_type']);
  $template = is_array($item_templates) ? reset($item_templates) : NULL;
  $form_state['conf']['item_template'] = isset($template['filename']) ? $template['filename'] : '';

  // Not a final save yet.
  if ($rebuild) {
    $form_state['rebuild'] = TRUE;
  }
  // Finally, save cache settings to display cache.
  else {
    _ding_nodelist_simple_cache_save($form_state);
  }
}

/**
 * Saves simple cache settings.
 */
function _ding_nodelist_simple_cache_save(&$form_state) {
  // Save cache settings.
  $pane_cache = &$form_state['pane']->cache;
  $pane_cache['method'] = 'simple';
  $pane_cache['settings'] = array(
    // Defaults the setting for users w/o cache access to 30 minutes.
    'lifetime' => user_access('nodelist cache settings') && isset($form_state['values']['lifetime']) ? $form_state['values']['lifetime'] : variable_get('ding_nodelist_cache_default_time', DING_NODELIST_CACHE_LIFETIME),
    'granularity' => 'context',
  );

  // Invalidate old cache.
  // @todo: check if any changes were introduced.
  ctools_include('plugins');
  $simple_cache_plugin = ctools_plugin_get_info('panels', 'cache');
  ctools_plugin_load_includes($simple_cache_plugin);
  $cid = panels_simple_cache_get_id($pane_cache['settings'], $form_state['display'], array() /* args not used */, $form_state['contexts'], $form_state['pane']);
  cache_clear_all($cid, 'cache');
}

/**
 * Handler for "Content types" form section.
 */
function _ding_nodelist_plugin_content_types(&$form, $node_type, $node_types_opts) {
  $form['ding_nodelist_wrapper']['content_types'] = array(
    '#type' => 'checkboxes',
    '#id' => 'nodelist_cts',
    '#title' => t('Content type'),
    '#required' => TRUE,
    '#default_value' => $node_type,
    '#options' => $node_types_opts,
    '#description' => t("Select the content type of the list's items."),
    '#prefix' => '<div id="nodelist-ct-selector">',
    '#suffix' => '</div>',
    '#ajax' => array(
      'wrapper' => 'ding_nodelist-selected-nodes',
      'callback' => 'ding_nodelist_js',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
}

/**
 * Handler for "Widget type" section and its settings.
 */
function _ding_nodelist_plugin_widget_section(&$form, $node_type, $conf, $default_conf) {
  $entity = entity_get_info('node');
  $node_formats = array();
  foreach ($entity['view modes'] as $view_mode => $settings) {
    $node_formats[$view_mode] = $settings['label'];
  }

  $widget_types = _ding_nodelist_get_widget_types($node_type);
  $widget_type = isset($conf['widget_type']) ? $conf['widget_type'] : $default_conf['widget_type'];
  $form['ding_nodelist_wrapper']['widget_type'] = array(
    '#type' => 'select',
    '#title' => t('List type'),
    '#required' => TRUE,
    '#default_value' => $widget_type,
    '#options' => $widget_types,
    '#empty_option' => t('- Select -'),
    '#description' => t('If single item selected, only the first item will be rendered'),
    '#ajax' => array(
      'wrapper' => 'ding_nodelist-item-template',
      'callback' => 'ding_nodelist_js_template',
      'method' => 'replace',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class=ding_nodelist-widget-config>',
  );

  $form['ding_nodelist_wrapper']['widget_dependent'] = array(
    '#type' => 'container',
    '#prefix' => '<div id="ding_nodelist-item-template">',
    '#suffix' => '</div></div>',
  );

  $autoscrolling_widgets = array(DING_NODELIST_WIDGET_CAROUSEL);
  if (in_array($widget_type, $autoscrolling_widgets)) {
    $generic_autoscroll_delay = variable_get('ding_nodelist_' . $widget_type . '_delay', $default_conf['autoscroll_delay']);
    $form['ding_nodelist_wrapper']['widget_dependent']['autoscroll_delay'] = array(
      '#type' => 'textfield',
      '#title' => t('Delay (miliseconds)'),
      '#default_value' => !empty($conf['autoscroll_delay']) ? $conf['autoscroll_delay'] : $generic_autoscroll_delay,
      '#description' => t('Time in milliseconds an item will be shown before switching to the next one'),
      '#size' => 4,
    );
  }

  // Make title appear only on some widgets.
  $widgets_with_title = array(
    DING_NODELIST_WIDGET_CAROUSEL,
    DING_NODELIST_WIDGET_ROLLTAB,
    DING_NODELIST_WIDGET_PROMOTED_NODES,
    DING_NODELIST_WIDGET_NODE_BLOCKS,
  );
  if (in_array($widget_type, $widgets_with_title)) {
    $form['ding_nodelist_wrapper']['widget_dependent']['override_title_text'] = array(
      '#type' => 'textfield',
      '#title' => t('List title'),
      '#description' => t('Enter a title to be shown above the list items. Leave empty to omit the title.') . ' ' .
      t('You may use %keywords from contexts, as well as %title to contain the original title.'),
      '#required' => FALSE,
      '#default_value' => isset($conf['override_title_text']) ? $conf['override_title_text'] : '',
    );
  }
}

/**
 * Handler for "Content" section of the form.
 */
function _ding_nodelist_plugin_content_section(&$form, &$form_state, $node_type, $conf, $node_types_opts) {
  $form['ding_nodelist_wrapper']['nodelist_content'] = array(
    '#type' => 'fieldset',
    '#title' => t('Content'),
    '#states' => array(
      'invisible' => array(
        'select[name=widget_type]' => array('value' => DING_NODELIST_WIDGET_SINGLE),
      ),
    ),
  );

  $form['ding_nodelist_wrapper']['nodelist_content']['list_type'] = array(
    '#type' => 'radios',
    '#options' => array(
      DING_NODELIST_LIST_TYPE_DYNAMIC => t('Custom / Dynamic'),
      DING_NODELIST_LIST_TYPE_ALL => t('All content'),
    ),
    '#default_value' => isset($conf['list_type']) ? $conf['list_type'] : DING_NODELIST_LIST_TYPE_ALL,
  );

  $form['ding_nodelist_wrapper']['nodelist_content']['nodelist_content_wrapper'] = array(
    '#type' => 'container',
    '#states' => array(
      'visible' => array(
        ':input[name=list_type]' => array('value' => DING_NODELIST_LIST_TYPE_DYNAMIC),
      ),
    ),
  );

  $form['ding_nodelist_wrapper']['nodelist_content']['nodelist_content_wrapper']['nodes_switch'] = array(
    '#type' => 'checkbox',
    '#title' => t('Custom content?'),
    '#prefix' => '<hr />',
    '#default_value' => isset($conf['nodes_switch']) ? $conf['nodes_switch'] : 0,
  );

  $form['ding_nodelist_wrapper']['nodelist_content']['nodelist_content_wrapper']['ding_nodelist_nodes'] = array(
    '#type' => 'container',
    '#collapsible' => FALSE,
    '#tree' => FALSE,
    '#title' => t('Custom item list'),
    '#prefix' => '<div class="clear-block" id="ding_nodelist-wrapper">',
    '#suffix' => '</div>',
    '#states' => array(
      'invisible' => array(
        ':input[name=nodes_switch]' => array('checked' => FALSE),
      ),
    ),
  );

  // Render selected nodes.
  $form['ding_nodelist_wrapper']['nodelist_content']['nodelist_content_wrapper']['ding_nodelist_nodes']['selected_nodes'] = array(
    '#prefix' => '<div id="ding_nodelist-selected-nodes">',
    '#suffix' => '</div>',
    '#theme' => 'ding_nodelist_items_table',
    '#tree' => TRUE,
  );

  $delta = 0;
  $weight = 0;
  $max_weight = $weight;
  $node_count = NULL;
  $filter_count = NULL;

  if (isset($form_state['values']['selected_nodes_count'])) {
    $node_count = $form_state['values']['selected_nodes_count'];
  }
  else {
    $node_count = empty($form_state['values']['selected_nodes']) ? 1 : count($form_state['values']['selected_nodes']);
  }

  if (!empty($conf['selected_nodes'])) {
    $delta = count($conf['selected_nodes']);
    foreach ($conf['selected_nodes'] as $key => $node) {
      $weight = $node['weight'];
      $max_weight = ($max_weight < $weight) ? $weight : $max_weight;
      $form['ding_nodelist_wrapper']['nodelist_content']['nodelist_content_wrapper']['ding_nodelist_nodes']['selected_nodes'][$key] = _ding_nodelist_selected_node($key, $node_type, $node, $weight);
    }
  }

  // Add new node field.
  $weight = ++$max_weight;
  for (; $delta < $node_count; $delta++) {
    $key = $delta;
    $form['ding_nodelist_wrapper']['nodelist_content']['nodelist_content_wrapper']['ding_nodelist_nodes']['selected_nodes'][$key] = _ding_nodelist_selected_node($key, $node_type, NULL, $weight);
  }

  $form['ding_nodelist_wrapper']['nodelist_content']['nodelist_content_wrapper']['ding_nodelist_nodes']['add_node'] = array(
    // Used to identify the button in validate/submit handler(s).
    '#name' => 'add_node',
    '#parents' => array('ding_nodelist_nodes', 'add_node'),
    '#type' => 'submit',
    '#value' => t('Add content'),
    '#weight' => 1,
    '#submit' => array('ding_nodelist_add_node_submit'),
    '#limit_validation_errors' => array(array('selected_nodes')),
    '#ajax' => array(
      'wrapper' => 'ding_nodelist-selected-nodes',
      'callback' => 'ding_nodelist_js_add_node',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  $form['ding_nodelist_wrapper']['nodelist_content']['nodelist_content_wrapper']['dynamic_switch'] = array(
    '#type' => 'checkbox',
    '#title' => t('Dynamic content?'),
    '#prefix' => '<div id="node_list-dynamic-content-switch">',
    '#suffix' => '</div>',
    '#default_value' => isset($conf['dynamic_switch']) ? $conf['dynamic_switch'] : 0,
    '#disabled' => (count(array_filter($node_type)) > 1),
  );

  // Dynamic list settings.
  $form['ding_nodelist_wrapper']['nodelist_content']['nodelist_content_wrapper']['ding_nodelist_dynamic'] = array(
    '#type' => 'container',
    '#states' => array(
      'invisible' => array(
        ':input[name=dynamic_switch]' => array('checked' => FALSE),
      ),
    ),
  );

  // Render selected filters.
  $form['ding_nodelist_wrapper']['nodelist_content']['nodelist_content_wrapper']['ding_nodelist_dynamic']['taxonomy_filters'] = array(
    '#type' => 'container',
    '#prefix' => '<div id="ding_nodelist-taxonomy-filters">',
    '#suffix' => '</div>',
    '#theme' => 'ding_nodelist_filters_table',
    '#tree' => TRUE,
  );

  if (isset($form_state['values']['taxonomy_filters_count'])) {
    $filter_count = $form_state['values']['taxonomy_filters_count'];
  }
  else {
    $filter_count = empty($form_state['values']['taxonomy_filters']) ? 1 : count($form_state['values']['taxonomy_filters']);
  }

  // Retrieve vocabularies current CT references.
  $allowed_fields = array();
  $field_settings = array();
  $selected_fields = array();
  foreach ($node_type as $type) {
    $selected_fields[$type] = field_info_instances('node', $type);
  }

  foreach ($selected_fields as $ct_name => $fields) {
    foreach ($fields as $field_machine_name => $field) {
      $field_config = field_info_field($field['field_name']);

      // Check if the field is a term reference or entity reference field.
      $allowed_types = array('taxonomy_term_reference', 'entityreference');

      if (in_array($field_config['type'], $allowed_types)) {
        foreach ($node_types_opts as $k => $v) {

          if ($field['bundle'] == $k) {
            $allowed_fields[$field_machine_name]['title'] = $v . ': ' . $field['label'];
            $allowed_fields[$field_machine_name]['type'] = $k;
          }
        }

        $field_settings[$field_machine_name] = array(
          'filter_field' => $field_machine_name,
          'term_reference' => $field_config['type'],
        );
        if ($field_config['type'] == 'entityreference') {
          $field_settings[$field_machine_name]['bundle'] = $node_type;
          $field_settings[$field_machine_name]['type'] = $field_config['settings']['target_type'];
        }
        else {
          $field_settings[$field_machine_name]['vocabulary'] = $field_config['settings']['allowed_values'][0]['vocabulary'];
        }
      }
    }
  }

  // Check if filter vocabulary was changed.
  $changed_filter_id = NULL;
  if (!empty($form_state['triggering_element']) && isset($form_state['triggering_element']['#parents'][2])
    && $form_state['triggering_element']['#parents'][2] == 'filter_field') {
    $changed_filter_id = $form_state['triggering_element']['#parents'][1];
    $changed_filter = $form_state['values']['taxonomy_filters'][$changed_filter_id];

    // Update auto-complete, preserve other fields.
    $filter = $field_settings[$changed_filter['filter_field']];

    // Important: delete old input!
    unset($form_state['input']['taxonomy_filters'][$changed_filter_id]);

    $form['ding_nodelist_wrapper']['nodelist_content']['nodelist_content_wrapper']['ding_nodelist_dynamic']['taxonomy_filters'][$changed_filter_id]
      = _ding_nodelist_taxonomy_filter($allowed_fields, $filter, $changed_filter_id);
  }

  $delta = 0;
  if (!empty($conf['taxonomy_filters'])) {
    $delta = count($conf['taxonomy_filters']);
    foreach ($conf['taxonomy_filters'] as $key => $filter) {
      // Skip just changed filter.
      if ($changed_filter_id === $key) {
        continue;
      }

      $tags = array();
      if ($filter['term_reference'] == 'entityreference') {
        foreach ($filter['filter_terms'] as $nid) {
          $title = db_select('node', 'n', array('target' => 'slave'))
            ->fields('n', array('title'))
            ->condition('n.nid', $nid)
            ->execute()
            ->fetchField();
          $tags[$nid] = $title . ' (' . $nid . ')';
        }
        $values = implode(', ', $tags);
      }
      else {
        foreach ($filter['filter_terms'] as $tid) {
          $tags[$tid] = taxonomy_term_load($tid);
        }
        $values = taxonomy_implode_tags($tags);
      }
      $filter = $field_settings[$filter['filter_field']];
      $filter['filter_terms'] = $values;

      $form['ding_nodelist_wrapper']['nodelist_content']['nodelist_content_wrapper']['ding_nodelist_dynamic']['taxonomy_filters'][$key]
        = _ding_nodelist_taxonomy_filter($allowed_fields, $filter, $key);
    }

    ksort($form['ding_nodelist_wrapper']['nodelist_content']['nodelist_content_wrapper']['ding_nodelist_dynamic']['taxonomy_filters']);
  }

  // Add new filter field.
  for (; $delta < $filter_count; $delta++) {
    $key = $delta;
    if ($changed_filter_id === $key) {
      continue;
    }

    // Set default field value.
    $first_field = array_shift(array_keys($allowed_fields));
    $filter = $field_settings[$first_field];

    $form['ding_nodelist_wrapper']['nodelist_content']['nodelist_content_wrapper']['ding_nodelist_dynamic']['taxonomy_filters'][$key]
      = _ding_nodelist_taxonomy_filter($allowed_fields, $filter, $key);
  }

  $form['ding_nodelist_wrapper']['nodelist_content']['nodelist_content_wrapper']['ding_nodelist_dynamic']['help_text'] = array(
    '#prefix' => '<div class="ding-nodelist-help-text">',
    '#suffix' => '</div>',
    '#markup' => t('For each filter (row) the AND syntax will be used and for each term within a filter (separate by comma) the OR syntax will be used.'),
    '#weight' => 9,
  );

  $form['ding_nodelist_wrapper']['nodelist_content']['nodelist_content_wrapper']['ding_nodelist_dynamic']['add_filter'] = array(
    '#name' => 'add_filter',
    '#type' => 'submit',
    '#value' => t('Add filter'),
    '#weight' => 10,
    '#submit' => array('ding_nodelist_add_filter_submit'),
    '#limit_validation_errors' => array(array('taxonomy_filters')),
    '#ajax' => array(
      'wrapper' => 'ding_nodelist-taxonomy-filters',
      'callback' => 'ding_nodelist_js_add_filter',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  // Content filter.
  $form['ding_nodelist_wrapper']['nodelist_content']['nodelist_content_wrapper']['ding_nodelist_dynamic']['content_filter_promoted'] = array(
    '#type' => 'checkbox',
    '#weight' => 11,
    '#title' => t('Show "Promoted to front page" content only'),
    '#default_value' => isset($conf['content_filter_promoted']) ? $conf['content_filter_promoted'] : FALSE,
  );

  // Date field filtering.
  $is_event = in_array('ding_event', array_filter($node_type));
  $form['ding_nodelist_wrapper']['nodelist_content']['content_filter_date'] = array(
    '#type' => $is_event ? 'checkbox' : 'hidden',
    '#title' => t('Show upcoming events only'),
    '#description' => t('If checked only future events will be shown'),
    '#prefix' => '<div id="ding_nodelist-content-filter-date">',
    '#suffix' => '</div>',
  );

  $default_value = $is_event && !empty($conf['content_filter_date']);
  $_content_filter_date = &$form['ding_nodelist_wrapper']['nodelist_content']['content_filter_date'];
  $element_key = $_content_filter_date['#type'] == 'hidden' ? '#value' : '#default_value';
  $_content_filter_date[$element_key] = $default_value;
  // Remove the reference for safety purposes.
  unset($_content_filter_date);
}

/**
 * Handler for "Various" settings section of the form.
 */
function _ding_nodelist_plugin_various_section(&$form = array(), $node_type = array(), $conf = array(), $default_conf = array()) {
  $form['ding_nodelist_wrapper']['nodelist_various_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Various'),
    '#states' => array(
      'invisible' => array(
        'select[name=widget_type]' => array('value' => DING_NODELIST_WIDGET_SINGLE),
      ),
    ),
  );

  // Initialize drop-down array's values.
  $options = array(0 => 'none') +
    array_combine(range(1, 25), range(1, 25)) +
    array_combine(range(30, 50, 5), range(30, 50, 5)) +
    array_combine(range(50, 100, 10), range(50, 100, 10));

  $form['ding_nodelist_wrapper']['nodelist_various_settings']['limit'] = array(
    '#type' => 'select',
    '#title' => t('Item limit'),
    '#default_value' => isset($conf['limit']) ? $conf['limit'] : $default_conf['limit'],
    '#options' => $options,
    '#description' => t('Limit amount of items displayed. This value is used only for Dynamic and All content displays.'),
    '#states' => array(
      'invisible' => array(
        array(
          ':input[name=nodes_switch]' => array('checked' => TRUE),
          ':input[name=dynamic_switch]' => array('checked' => FALSE),
        ),
        array(
          'select[name=widget_type]' => array('value' => 'promoted_nodes'),
        ),
      ),
      'visible' => array(
        ':input[name=list_type]' => array(
          array('value' => DING_NODELIST_LIST_TYPE_DYNAMIC),
          array('value' => DING_NODELIST_LIST_TYPE_ALL),
        ),
      ),
    ),
  );

  $form['ding_nodelist_wrapper']['nodelist_various_settings']['ding_nodelist_sorting'] = array(
    '#type' => 'container',
  );

  $sort_options = array(
    DING_NODELIST_SORT_BY_CREATION_DATE => t('Creation date'),
    DING_NODELIST_SORT_BY_TITLE => t('Title'),
    DING_NODELIST_SORT_BY_STICKY => t('Sticky first'),
  );

  if (array_shift($node_type) == 'ding_event') {
    $sort_options['event_date'] = t('Event date');
  }

  $form['ding_nodelist_wrapper']['nodelist_various_settings']['ding_nodelist_sorting']['sort_field'] = array(
    '#type' => 'select',
    '#title' => t('Sort by'),
    '#options' => $sort_options,
    '#empty_option' => t('No sorting'),
    '#default_value' => isset($conf['sort_field']) ? $conf['sort_field'] : '',
    '#prefix' => '<div id="ding_nodelist-sort-field">',
    '#suffix' => '</div>',
  );

  $sort_order = isset($conf['sort_order']) ? $conf['sort_order'] : '';
  $form['ding_nodelist_wrapper']['nodelist_various_settings']['ding_nodelist_sorting']['sort_order'] = array(
    '#type' => 'select',
    '#title' => t('Sorting order'),
    '#options' => array(
      DING_NODELIST_SORT_ASCENDING => t('Ascending'),
      DING_NODELIST_SORT_DESCENDING => t('Descending'),
    ),
    '#default_value' => $sort_order,
    '#states' => array(
      // Hide the settings when the sorting order is not applicable.
      'invisible' => array(
        ':input[name="sort_field"]' => array(array('value' => ''), array('value' => DING_NODELIST_SORT_BY_STICKY)),
      ),
    ),
  );

  $form['ding_nodelist_wrapper']['nodelist_various_settings']['columns'] = array(
    '#type' => 'select',
    '#title' => t('Width (columns)'),
    '#options' => array(
      DING_NODELIST_COL_FULL => t('Full width'),
      DING_NODELIST_COL_HALF => '1/2',
      DING_NODELIST_COL_THIRD => '1/3',
      DING_NODELIST_COL_QRT => '1/4',
    ),
    '#default_value' => isset($conf['columns']) ? $conf['columns'] : $default_conf['columns'],
  );
}

/**
 * Handler for "Bottom links" section of the form.
 */
function _ding_nodelist_plugin_bottom_links_section(&$form, &$form_state, $conf) {
  $form['ding_nodelist_wrapper']['ding_nodelist_bottom_links'] = array(
    '#type' => 'fieldset',
    '#title' => t('Additional links'),
    '#collapsible' => FALSE,
    '#description' => t('List of "read more" links.'),
  );

  // Container for bottom links.
  $form['ding_nodelist_wrapper']['ding_nodelist_bottom_links']['more_links'] = array(
    '#prefix' => '<div id="ding_nodelist-more-link">',
    '#suffix' => '</div>',
    '#theme' => 'ding_nodelist_links_table',
    '#tree' => TRUE,
  );

  // Get all bottom links.
  $delta = 0;

  if (isset($form_state['values']['bottom_links_count'])) {
    $links_count = $form_state['values']['bottom_links_count'];
  }
  else {
    $links_count = empty($form_state['values']['more_links']) ? 1 : count($form_state['values']['more_links']);
  }

  if (isset($conf['more_links'])) {
    $delta = count($conf['more_links']);
    foreach ($conf['more_links'] as $key => $link) {
      $form['ding_nodelist_wrapper']['ding_nodelist_bottom_links']['more_links'][$key] = _ding_nodelist_links_form($key, $link);
    }
  }

  // Add new bottom link field.
  for ($delta; $delta < $links_count; $delta++) {
    $key = $delta;
    $form['ding_nodelist_wrapper']['ding_nodelist_bottom_links']['more_links'][$key] = _ding_nodelist_links_form($key, NULL);
  }

  $form['ding_nodelist_wrapper']['ding_nodelist_bottom_links']['ding_bottom_links_more'] = array(
    '#type' => 'submit',
    '#value' => t('Add more link'),
    '#submit' => array('ding_nodelist_add_bottom_link_submit'),
    '#ajax' => array(
      'wrapper' => 'ding_nodelist-more-link',
      'callback' => 'ding_nodelist_js_add_links',
      'effect' => 'fade',
      'method' => 'replace',
    ),
  );
}

/**
 * Handler for "Cache settings" section of the form.
 */
function _ding_nodelist_plugin_cache_section(&$form, &$form_state) {
  $form['ding_nodelist_wrapper']['cache_settings'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#tree' => FALSE,
    '#title' => t('Cache settings'),
  );

  // Load cache settings and prepare form.
  if (user_access('nodelist cache settings')) {
    ctools_include('plugins');
    $simple_cache_plugin = ctools_plugin_get_info('panels', 'cache');
    ctools_plugin_load_includes($simple_cache_plugin);
    $pane = $form_state['pane'];
    $settings = !empty($pane->cache['settings'])
      ? $pane->cache['settings']
      : array(
        'lifetime' => variable_get('ding_nodelist_cache_default_time', DING_NODELIST_CACHE_LIFETIME),
        'granularity' => 'context',
      );
    $cache_form = panels_simple_cache_settings_form($settings, $form_state['display'], $pane->pid);
    // @todo: Granularity is forced to 'context' now.
    unset($cache_form['granularity']);
    $form['ding_nodelist_wrapper']['cache_settings'] = array_merge($form['ding_nodelist_wrapper']['cache_settings'], $cache_form);
  }
}
