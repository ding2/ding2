<?php
/**
 * @file
 * Define items list pane.
 */

/**
 * General ctools plugin settings.
 */
$plugin = array(
  'title' => t('Ding MKWS item list.'),
  'category' => t('Ding!'),
  'description' => t('Add MKWS items as a list.'),
  'single' => TRUE,
  'render callback' => 'ding_mkws_item_list_render',
);

/**
 * Plugin render.
 */
function ding_mkws_item_list_render($subtype, $conf, $panel_args, $context) {
  $pane = new stdClass();
  $global_options = variable_get('ding_mkws_global', array());
  $global_settings = (!empty($global_options['opac'])) ? $global_options['opac'][$subtype] : array();

  $params = array(
    'type' => $subtype,
    'amount' => (!empty($global_settings)) ? $global_settings['amount'] : ' 0',
  );
  $hash = md5(implode('', $params));

  if (in_array($subtype, array('ting_object', 'ting_collection'))) {
    $entities = ding_entity_load_multiple($panel_args);
    foreach ($entities as $entity) {
      $record = $entity->reply->record;
      $title = $record['dc:title'][''][0];
      $params['limit'] = null;
      if (count($record['dc:creator']) > 0) {
        $result = reset($record['dc:creator']);
        if (isset($result[0])) {
          $author = $result[0];
          $params['limit'] = array('author' => drupal_strtolower($author));
        }
      }
      $params['term'] = str_replace(array('.', '!', '?', '#', ','), ' ', $title);
    }
  }
  else {
    $params['term'] = reset($panel_args);
  }

  $params['resources'] = (!empty($global_settings)) ? $global_settings['resources'] : NULL;
  $pane->content['#markup'] = "<div data-hash='{$hash}' 
            data-process='ProcessDataForPaneWidget' 
            data-template='dingMkwsPaneWidget' 
            class='ding-mkws-widget ding-mkws-pane-widget'>
        </div>";
  $pane->content['#attached'] = array(
    'css' => array(
      drupal_get_path('module', 'ding_mkws') . '/css/ding_mkws.css',
    ),
    'js' => array(
      drupal_get_path('module', 'ding_mkws') . '/js/ding_mkws.js',
      array(
        'type' => 'setting',
        'data' => array(
          $hash => $params,
        ),
      ),
    ),
  );

  return $pane;
}
