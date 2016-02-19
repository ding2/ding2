<?php
/**
 * @file
 * CTools plugin definition file.
 */

/**
 * General ctools plugin settings.
 */
$plugin = array(
  'title' => t('Ding item list'),
  'category' => t('Ding!'),
  'description' => t('Add ting items as a list'),
  'single' => TRUE,
  'render callback' => 'ding_item_list_plugin_render',
  'edit form' => 'ding_item_list_plugin_edit_form',
);

/**
 * Plugin content renderer.
 */
function ding_item_list_plugin_render($subtype, $conf, $panel_args, $context) {
  // Add cron job callback to be able to warmup the cache.
  if (!empty($conf['item_query'])) {
    _ding_item_list_cronapi_task($conf['item_query'], __FUNCTION__, func_get_args());
  }

  $plugin_data = new stdClass();
  $plugin_data->content = '';
  $item_query = $conf['item_query'];
  $item_count = $conf['item_count'];
  $item_sort = empty($conf['item_sort']) ? '' : $conf['item_sort'];

  $markup = ding_item_list_get_content($item_query, $item_count, $item_sort);

  drupal_add_css(drupal_get_path('module', 'ding_item_list') . '/css/ding_item_list.css', 'file');
  $plugin_data->content = theme('ding_item_list_list', array('items' => $markup));
  $plugin_data->title = t(isset($conf['item_list_item_list_custom_title']) ? $conf['item_list_item_list_custom_title'] : 'Related materials');

  return $plugin_data;
}

/**
 * Plugin edit form.
 */
function ding_item_list_plugin_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  // Use specific title handling - hide pane title if no content is present.
  // Standard pane title handling does not provide such functionality,
  // so use custom title field and hide the standard ones.
  unset($form['override_title']);
  unset($form['override_title_text']);
  unset($form['override_title_markup']);

  $form['item_list_item_list_custom_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Pane title'),
    '#default_value' => t(isset($conf['item_list_item_list_custom_title']) ? $conf['item_list_item_list_custom_title'] : 'Related materials'),
  );

  ding_item_list_search_form($form, $conf);

  return $form;
}

/**
 * Plugin edit form submit handler.
 *
 * Saves the data from the form.
 */
function ding_item_list_plugin_edit_form_submit($form, &$form_state) {
  $form_state['conf']['item_list_item_list_custom_title'] = $form_state['values']['item_list_item_list_custom_title'];
  $form_state['conf']['item_query'] = $form_state['input']['item_query'];
  $form_state['conf']['item_count'] = $form_state['input']['item_count'];
  $form_state['conf']['item_sort'] = $form_state['input']['item_sort'];

  // Clear cache when saving settings.
  $cid = ding_item_list_generate_cache_id($form_state['conf']['item_query']);
  cache_clear_all($cid, 'cache_ding_item');
}
