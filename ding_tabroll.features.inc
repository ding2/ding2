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
      'rules_ding_tabroll_frontpage_queue_updated' => array(
        '#type' => 'rule',
        '#set' => 'event_nodequeue_saved',
        '#label' => 'Ding! tabroll frontpage nodequeue updated',
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
              'label' => 'Queue is frontpage tabroll',
              'label callback' => FALSE,
              'module' => 'Nodequeue',
              'arguments' => array(
                'nodequeue' => array(
                  'type' => 'nodequeue',
                  'label' => 'Nodekø',
                ),
              ),
            ),
            '#name' => 'nodequeue_rules_condition_belongs_to_nodequeue',
            '#settings' => array(
              'queues' => array(
                '1' => '1',
              ),
              '#argument map' => array(
                'nodequeue' => 'nodequeue',
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
              'label' => 'Clear the cache of a specific view.',
              'arguments' => array(
                'view' => array(
                  'type' => 'string',
                  'label' => 'Vis',
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
