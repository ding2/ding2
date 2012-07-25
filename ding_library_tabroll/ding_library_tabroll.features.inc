<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function ding_library_tabroll_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_nodequeue_export_features_default_settings().
 */
function ding_library_tabroll_nodequeue_export_features_default_settings() {
 $nodequeue_export = array();

 $nodequeue_export['ding_tabroll_library_frontpage_queue'] = array(
   'name' => 'ding_tabroll_library_frontpage_queue',
   'title' => 'Library tabroll',
   'subqueue_title' => '%subqueue',
   'size' => '5',
   'reverse' => '0',
   'link' => '',
   'link_remove' => '',
   'owner' => 'smartqueue_nodetypes',
   'roles' => array(),
   'types' => array(
     '0' => 'rolltab',
   ),
   'reference' => 'library',
   'i18n' => '0',
   'show_in_links' => '0',
   'show_in_tab' => '1',
   'show_in_ui' => '1',
   'new' => TRUE,
 );
 return $nodequeue_export;
}

/**
 * Implementation of hook_rules_defaults().
 */
function ding_library_tabroll_rules_defaults() {
  return array(
    'rules' => array(
      'rules_ding_library_tabroll_nodequeue_updated' => array(
        '#type' => 'rule',
        '#set' => 'event_nodequeue_saved',
        '#label' => 'Ding! tabroll Library nodequeue updated',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'ding_library_tabroll',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
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
                '3' => '3',
              ),
              '#argument map' => array(
                'nodequeue' => 'nodequeue',
              ),
            ),
            '#type' => 'condition',
            '#weight' => 0,
          ),
        ),
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
          ),
        ),
        '#version' => 6003,
      ),
    ),
  );
}
