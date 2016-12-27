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
  $plugin_data = new stdClass();
  $plugin_data->content = '';
  $item_sort = empty($conf['item_sort']) ? '' : $conf['item_sort'];

  $params = implode('', array(
    'query' => $conf['item_query'],
    'count' => $conf['item_count'],
    'sort' => $item_sort,
  ));
  $hash = md5($params);

  $path = drupal_get_path('module', 'ding_item_list');
  $plugin_data->content['#markup'] = theme('ding_item_list_list', array('hash' => $hash));
  $plugin_data->content['#attached'] = array(
    'js' => array(
      array('data' => $path . '/js/ding_item_list.js'),
      array(
        'data' => array(
          $hash => array(
            'query' => $conf['item_query'],
            'count' => $conf['item_count'],
            'sort' => $item_sort,
          ),
        ),
        'type' => 'setting'
      ),
    ),
  );

  $plugin_data->title = isset($conf['item_list_item_list_custom_title']) ? $conf['item_list_item_list_custom_title'] : t('Related materials');

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
    '#default_value' => isset($conf['item_list_item_list_custom_title']) ? $conf['item_list_item_list_custom_title'] : t('Related materials'),
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
