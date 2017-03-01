<?php

/**
 * Inform the content exporting system about plugins.
 *
 * @return
 *   An array whose keys are plugin names and whose values identify
 *   plugin info that the exporting system needs to know about:
 *   - title: The human-readable name of the plugin.
 *   - description: Long description of plugin.
 *   - exec_callback: Execution callback.
 *   - config_form_callback: A configuration form for a plugin.
 *   - config_form_validate: Validate handler for the configuration form.
 *   - config_form_submit: Submit handler for the configuration form.
 *
 * @see hook_mobilesearch_plugin_config()
 */
function hook_ding_mobilesearch_plugin_info() {
  return array(
    'mobilesearch_example_plugin' => array(
      'title' => t('Example plugin'),
      'description' => t('Plugin description.'),
      'exec_callback' => 'mobilesearch_example_plugin_exec',
      'config_form_callback' => 'mobilesearch_example_plugin_config_form',
      'config_form_validate' => 'mobilesearch_example_plugin_config_form_validate',
      'config_form_submit' => 'mobilesearch_example_plugin_config_form_submit',
    ),
  );
}

/**
 * Prepares and mapping the data for content methods of a service.
 *
 * @param $node
 *   The node that is being proceed.
 */
function hook_ding_mobilesearch_node_export_mapping($node) {
  $mapping = array(
    'special' => array(// 'faust' => '...',
    ),
    'fields' => array(
      'title' => array(
        'name' => t('Title'),
        'value' => $node->title,
        'attr' => array(
          //'plain text',
          // ...
        ),
      ),
      // ...
    ),
    'taxonomy' => array(
      'term_reference_field' => array(
        'name' => 'vocabulary',
        'terms' => array(
          'term0',
          'term1',
        ),
      ),
      // ...
    ),
  );
  return $mapping;
}
