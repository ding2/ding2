<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function ding_tabroll_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_imagecache_default_presets().
 */
function ding_tabroll_imagecache_default_presets() {
  $items = array(
    '460_240_crop' => array(
      'presetname' => '460_240_crop',
      'actions' => array(
        '0' => array(
          'weight' => '-10',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '460',
            'height' => '',
            'upscale' => 1,
          ),
        ),
        '1' => array(
          'weight' => '-9',
          'module' => 'imagecache',
          'action' => 'imagecache_crop',
          'data' => array(
            'width' => '460',
            'height' => '240',
            'xoffset' => '',
            'yoffset' => '',
          ),
        ),
        '2' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_desaturate',
          'data' => array(),
        ),
      ),
    ),
  );
  return $items;
}

/**
 * Implementation of hook_node_info().
 */
function ding_tabroll_node_info() {
  $items = array(
    'rolltab' => array(
      'name' => t('Rullefane'),
      'module' => 'features',
      'description' => t('Rullefaner vises i en Fanerulle (Tabroll), hvor en fane afløser den næste i karrusel'),
      'has_title' => '1',
      'title_label' => t('Titel'),
      'has_body' => '0',
      'body_label' => '',
      'min_word_count' => '0',
      'help' => t('En Fanerulle indeholder 5 rullefaner. Det er de 5 nyeste aktive faner, der vises. NB: Slideshowet med fanerne kan kun køre når der er mindst 5 faner oprettet.'),
    ),
  );
  return $items;
}

/**
 * Implementation of hook_nodequeue_export_features_default_settings().
 */
function ding_tabroll_nodequeue_export_features_default_settings() {
 $nodequeue_export = array();

 $nodequeue_export['ding_tabroll_frontpage_queue'] = array(
   'name' => 'ding_tabroll_frontpage_queue',
   'title' => 'Frontpage tabroll',
   'subqueue_title' => '',
   'size' => '5',
   'reverse' => '0',
   'link' => '',
   'link_remove' => '',
   'owner' => '',
   'roles' => array(),
   'types' => array(
     '0' => 'rolltab',
   ),
   'reference' => '0',
   'i18n' => '0',
   'show_in_links' => '0',
   'show_in_tab' => '1',
   'show_in_ui' => '1',
   'new' => TRUE,
   'add_subqueue' => array(
     '0' => 'Frontpage tabroll',
   ),
 );
 return $nodequeue_export;
}

/**
 * Implementation of hook_rules_defaults().
 */
function ding_tabroll_rules_defaults() {
  return array(
    'rules' => array(
      'rules_rolltab_saved' => array(
        '#type' => 'rule',
        '#set' => 'event_node_insert',
        '#label' => 'rolltab_saved',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'ding_tabroll',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Created content is rolltab',
              'label callback' => FALSE,
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#name' => 'rules_condition_content_is_type',
            '#settings' => array(
              'type' => array(
                'rolltab' => 'rolltab',
              ),
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#type' => 'condition',
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#type' => 'action',
            '#settings' => array(
              'view' => 'tabroll',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'view' => array(
                    '0' => ':global',
                  ),
                ),
              ),
            ),
            '#name' => 'cache_actions_action_clear_views_cache',
            '#info' => array(
              'label' => 'Clear the tabroll view cache',
              'label callback' => FALSE,
              'arguments' => array(
                'view' => array(
                  'type' => 'string',
                  'label' => 'View',
                  'description' => 'Specify the view you want to clear.',
                ),
              ),
              'module' => 'Cache Actions',
            ),
            '#weight' => 0,
          ),
        ),
        '#version' => 6003,
      ),
      'rules_rolltab_saved_cloned' => array(
        '#type' => 'rule',
        '#set' => 'event_node_delete',
        '#label' => 'rolltab_saved',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'ding_tabroll',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#weight' => 0,
            '#type' => 'condition',
            '#settings' => array(
              'type' => array(
                'rolltab' => 'rolltab',
              ),
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_condition_content_is_type',
            '#info' => array(
              'label' => 'Deleted content is rolltab',
              'label callback' => FALSE,
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Clear the tabroll view cache',
              'label callback' => FALSE,
              'arguments' => array(
                'view' => array(
                  'type' => 'string',
                  'label' => 'View',
                  'description' => 'Specify the view you want to clear.',
                ),
              ),
              'module' => 'Cache Actions',
            ),
            '#name' => 'cache_actions_action_clear_views_cache',
            '#settings' => array(
              'view' => 'tabroll',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'view' => array(
                    '0' => ':global',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'rules_rolltab_updated' => array(
        '#type' => 'rule',
        '#set' => 'event_node_update',
        '#label' => 'rolltab_updated',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'ding_tabroll',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#weight' => 0,
            '#type' => 'condition',
            '#settings' => array(
              'type' => array(
                'rolltab' => 'rolltab',
              ),
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_condition_content_is_type',
            '#info' => array(
              'label' => 'Updated content is rolltab',
              'label callback' => FALSE,
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Clear the tabroll view cache',
              'label callback' => FALSE,
              'arguments' => array(
                'view' => array(
                  'type' => 'string',
                  'label' => 'View',
                  'description' => 'Specify the view you want to clear.',
                ),
              ),
              'module' => 'Cache Actions',
            ),
            '#name' => 'cache_actions_action_clear_views_cache',
            '#settings' => array(
              'view' => 'tabroll',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'view' => array(
                    '0' => ':global',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'rules_tabroll_node_added' => array(
        '#type' => 'rule',
        '#set' => 'event_nodequeue_added_ding_tabroll_frontpage_queue',
        '#label' => 'tabroll_node_added',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'ding_tabroll',
        ),
        '#status' => 'default',
        '#conditions' => array(),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#type' => 'action',
            '#settings' => array(
              'view' => 'tabroll',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'view' => array(
                    '0' => ':global',
                  ),
                ),
              ),
            ),
            '#name' => 'cache_actions_action_clear_views_cache',
            '#info' => array(
              'label' => 'Clear the tabroll view cache',
              'label callback' => FALSE,
              'arguments' => array(
                'view' => array(
                  'type' => 'string',
                  'label' => 'Vis',
                  'description' => 'Specify the view you want to clear.',
                ),
              ),
              'module' => 'Cache Actions',
            ),
          ),
        ),
        '#version' => 6003,
      ),
      'rules_tabroll_node_removed' => array(
        '#type' => 'rule',
        '#set' => 'event_nodequeue_removed_ding_tabroll_frontpage_queue',
        '#label' => 'tabroll_node_removed',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'ding_tabroll',
        ),
        '#status' => 'default',
        '#conditions' => array(),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Clear the tabroll view cache',
              'label callback' => FALSE,
              'arguments' => array(
                'view' => array(
                  'type' => 'string',
                  'label' => 'Vis',
                  'description' => 'Specify the view you want to clear.',
                ),
              ),
              'module' => 'Cache Actions',
            ),
            '#name' => 'cache_actions_action_clear_views_cache',
            '#settings' => array(
              'view' => 'tabroll',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'view' => array(
                    '0' => ':global',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
    ),
  );
}

/**
 * Implementation of hook_views_api().
 */
function ding_tabroll_views_api() {
  return array(
    'api' => '2',
  );
}
